# Underground Node (STM32L476) – End-to-End TCN Demodulation

本目录对应 **井下终端（Underground Node）** 工程，运行在 **STM32L476** 上，负责：

- 监听井上指令并执行 AI 解调
- 解析下行命令（单次回传模式）
- 采集温度/压力数据并回传
- 通过 AD9833 进行 BFSK 调制发送

本文档说明 **工作流程、时序关系、关键参数**，并给出典型示例。

---

## 1. 系统总体流程

系统运行状态机如下：

1. **STATE_LISTENING（监听）**
   - RX 继电器闭合、TX 断开、功放关闭
   - TIM2 触发 ADC 采样，DMA 收集一帧（1200 点）
   - 采样完成后进入推理状态

2. **STATE_INFERENCING（推理/解调）**
   - 预处理与量化
   - 调用 TCN 模型推理
   - 从 `boundary` 输出中选 Top‑3 候选
   - 同步头严格匹配（0 误差）
   - 若命令指向本机，执行并进入回传流程

3. **STATE_TRANSMITTING（回传发送）**
   - TIM3 定时器驱动 AD9833 输出 BFSK
   - 发送完成后回到监听态

当前版本：**仅支持单次回传**（连续回传逻辑暂不启用）。

---

## 2. 时序与外设关系

### 2.1 ADC 采样时序

- **TIM2** 作为 ADC 外部触发源（`ADC_EXTERNALTRIG_T2_TRGO`）
- TIM2 周期：
  - `Prescaler = 79`
  - `Period = 832`
- 采样点数：`FRAME_SAMPLES = 1200`
- DMA 方式：`DMA_NORMAL`

采样完成后，`HAL_ADC_ConvCpltCallback()` 置位 `adcReadyFlag`，进入推理。

### 2.2 BFSK 发送时序

- **TIM3** 用于 bit 级调制节拍
  - `Prescaler = 7999`
  - `Period = 199`
- 每个定时器中断发送 1 bit
- 发送顺序为：
  - 8 bit 同步头
  - 4 bit 目的地址
  - 4 bit 源地址
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

量化参数（来自 `network.c` 的 intq 表）：

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

## 5. 命令与回传逻辑

- 下行命令帧由井上端发送
- 井下端解调后，如果 `destAddr == LOCAL_ADDRESS` 则执行命令
- 当前版本仅支持 **单次回传**，命令触发回传流程

示例命令：

- `0x55`：进入连续回传（当前版本不启用，仅预留）
- `0xAA`：扫频功能（预留）

---

## 6. 回传载荷格式

回传 payload 为 24bit，格式如下：

```
payload = (t_int << 16) | (t_frac << 12) | (p_int << 4) | p_frac
```

示例（串口侧解析）：

```
[RX] Node:0xF -> Ground | Temp: 24.3 C | Pres: 8.6 MPa
```

---

## 7. 关键源码位置

- 状态机与 AI 解调：`Core/Src/main.c`
- 采样参数：`Core/Inc/main.h`
- AD9833 BFSK 调制：`Core/Src/ad9833.c`
- 定时器配置：`Core/Src/tim.c`

---

## 8. 工作流程示例

**场景：井上发送命令触发井下回传**

1. 井上端发送指令帧
2. 井下端 ADC 采样 1200 点
3. TCN 推理输出 `boundary + frame`
4. Top‑3 边界候选逐一解调并校验同步头
5. 命令匹配后执行回传
6. 井下端调制发送温压数据

