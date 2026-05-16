# Relay Node (STM32L476) – End-to-End TCN Demodulation

本目录对应 **井下通信中继站（Relay Node / Bridge）** 工程，运行在 **STM32L476** 上，负责：

- 监听井上/井下回传的模拟信号并 **TCN INT8 解调**
- 严格同步头校验（0 误差），定位帧起点并恢复 40 bit 数据
- 根据源地址决定转发方向，仅修改 **目的地址**，载荷透明转发
- 控制继电器与功放，实现收发切换（含 15ms 缓冲）

本文档重点说明 **系统流程、时序关系、关键参数与路由逻辑**。

---

## 1. 系统总体流程

系统运行三态状态机如下：

1. **STATE_LISTENING（监听）**
   - RX 继电器闭合、TX 断开、功放关闭
   - TIM2 触发 ADC 采样，DMA 收集一帧（960 点）
   - 采样完成后进入推理状态

2. **STATE_INFERENCING（推理）**
   - 预处理与量化（使用 CMSIS‑DSP 计算均值/标准差）
   - 调用 TCN 模型推理
   - 从 `boundary` 输出中取 Top‑3 边界候选
   - 当 `best_val - second_val <= 阈值` 时启用 Top‑3，否则只用 Top‑1
   - 对候选起点进行 40 bit 解调（5 点平均判决）
   - **同步头必须完全匹配 0xE5，才接收该帧**
   - 解析地址与 payload，进行路由判定并准备转发

3. **STATE_TRANSMITTING（发送）**
   - 根据路由方向改写目的地址，仅转发载荷
   - 关闭接收链路，打开 TX 继电器与功放
   - TIM3 定时驱动 AD9833 输出 BFSK
   - 发送完成后切回监听态

---

## 2. 时序与外设关系

### 2.1 ADC 采样时序

- **TIM2** 作为 ADC 外部触发源（`ADC_EXTERNALTRIG_T2_TRGO`）
- TIM2 周期：
  - `Prescaler = 79`
  - `Period = 832`
- 采样点数：`FRAME_SAMPLES = 960`
- DMA 方式：`DMA_NORMAL`（采满一帧触发回调）

采样完成后，`HAL_ADC_ConvCpltCallback()` 置位 `adcReadyFlag`，状态机进入推理流程。

### 2.2 BFSK 发送时序（转发）

- **TIM3** 用于 bit 级调制节拍
  - `Prescaler = 7999`
  - `Period = 199`
- 每个定时器中断发送 1 bit
- 发送顺序为：
  - 8 bit 同步头
  - 4 bit 目的地址（中继改写）
  - 4 bit 源地址（中继自身地址）
  - 24 bit 载荷
  - 4 bit 尾零

AD9833 输出频率：
- 逻辑 0 → FREQ0（例如 100 Hz）
- 逻辑 1 → FREQ1（例如 200 Hz）

---

## 3. AI 模型输入/输出

模型信息来自 `X-CUBE-AI/App/network.h`：

- 输入：`1 x 1200`，INT8
- 输出：
  - `boundary`：长度 400（帧起点置信度）
  - `frame`：长度 400（用于 bit 解调）

### 3.1 预处理与量化（与训练一致）

```text
full_wave = (full_wave - mean) / (std + 1e-5)
q = round(full_wave / scale) + zp
```

量化参数（来自工程宏）：

- `AI_INPUT_SCALE = 0.04032759368419647`
- `AI_INPUT_ZP = -5`

关键配置参数表：

| 参数 | 含义 | 当前值 |
| --- | --- | --- |
| `AI_INPUT_SCALE` | 输入量化 scale | `0.04032759368419647` |
| `AI_INPUT_ZP` | 输入量化 zero point | `-5` |
| `AI_FRAME_ZP` | frame 输出 zero point | `13` |
| `AI_STRIDE` | 前端步进 | `3` |
| `AI_LATENT_SAMPLES` | 解调窗口长度 | `320` |
| `AI_LATENT_SPB` | 每 bit 的 latent 点数 | `8` |
| `AI_BOUNDARY_TOP_K` | 边界候选数量 | `3` |
| `AI_BOUNDARY_AMBIGUOUS_THRESHOLD` | 边界启用阈值 | `4` |

说明：均值与标准差由 CMSIS‑DSP 的 `arm_mean_f32` 与 `arm_std_f32` 计算，工程需要启用 `USE_CMSIS_DSP=1`。

### 3.2 解调逻辑

1. **边界候选**：从 `boundary` 中选 Top‑3 峰值索引
2. **候选启用条件**：当 `best_val - second_val <= AI_BOUNDARY_AMBIGUOUS_THRESHOLD` 时启用 Top‑3，否则只用 Top‑1
3. **每个候选解调 40 bit**：按 5 点平均（2..6）判决
4. **同步头 0xE5 必须完全匹配**（严格 0 误差）
5. 若任一候选匹配成功，视为有效帧

---

## 4. 数据帧结构

```
| 8b Sync(0xE5) | 4b Dest | 4b Src | 24b Payload | 4b Tail |
```

说明：`Tail` 为发送端在 **40 bit 数据结束后固定追加的 4 个 0**，不是 AI 模型解调输出的一部分。

尾零用途：
1. 提供帧结束的保护区，避免最后一个有效 bit 被截断
2. 形成帧间空档，降低相邻帧粘连与误判
3. 为功放/继电器切换留出稳定过渡时间

---

## 5. 路由与转发逻辑

- 仅当 `destAddr == LOCAL_ADDRESS` 时继续转发，否则丢弃并恢复监听
- 中继根据 `srcAddr` 判断方向：
  - `srcAddr < LOCAL_ADDRESS` → 向下行转发（目标 `ADDR_UNDERGROUND`）
  - `srcAddr > LOCAL_ADDRESS` → 向上行转发（目标 `ADDR_GROUND`）
- 转发时 **改写目的地址**，源地址改为本机地址，payload 透明透传
- 继电器切换前加入 **15ms 缓冲** 以减少硬件冲击

---

## 6. 关键源码位置

- 状态机、AI 解调与转发：`Core/Src/main.c`
- 协议与地址定义：`Core/Inc/main.h`
- AD9833 BFSK 调制：`Core/Src/ad9833.c`
- 定时器配置：`Core/Src/tim.c`
- 继电器控制：`Core/Src/relay_control.c`

---

## 7. 工作流程示例

**场景 A：井下 → 井上数据回传（经中继转发）**

1. 井下设备调制发送一帧数据
2. 中继 ADC 采样 960 点
3. TCN 推理输出 `boundary + frame`
4. 中继尝试 Top‑3 边界解调并严格匹配同步头
5. 解析地址与 payload，判定向上行
6. 改写目的地址为 `ADDR_GROUND` 并转发

**场景 B：井上 → 井下指令下发（经中继转发）**

1. 上位机/井上发送一帧数据
2. 中继解调后判定向下行
3. 改写目的地址为 `ADDR_UNDERGROUND`
4. 关闭接收链路、打开 TX 继电器与功放
5. TIM3 按 bit 时序驱动 AD9833 输出 BFSK
6. 发送完成后切回监听态

---

## 8. 备注与建议

- 若出现偶发丢包：
  - 可增大 `AI_BOUNDARY_AMBIGUOUS_THRESHOLD` 以启用 Top‑3
- 若想降低误接收风险：
  - 保持同步头 0 误差（当前策略）
- 若需要更强校验：
  - 可在 payload 层加入 CRC（当前为透明转发）

---
