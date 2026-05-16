/**
  ******************************************************************************
  * @file    network.c
  * @author  AST Embedded Analytics Research Platform
  * @date    2026-03-13T12:51:48+0800
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  ******************************************************************************
  */


#include "network.h"
#include "network_data.h"

#include "ai_platform.h"
#include "ai_platform_interface.h"
#include "ai_math_helpers.h"

#include "core_common.h"
#include "core_convert.h"

#include "layers.h"



#undef AI_NET_OBJ_INSTANCE
#define AI_NET_OBJ_INSTANCE g_network
 
#undef AI_NETWORK_MODEL_SIGNATURE
#define AI_NETWORK_MODEL_SIGNATURE     "0x59a162f8ed9e66f87cd969191326bf47"

#ifndef AI_TOOLS_REVISION_ID
#define AI_TOOLS_REVISION_ID     ""
#endif

#undef AI_TOOLS_DATE_TIME
#define AI_TOOLS_DATE_TIME   "2026-03-13T12:51:48+0800"

#undef AI_TOOLS_COMPILE_TIME
#define AI_TOOLS_COMPILE_TIME    __DATE__ " " __TIME__

#undef AI_NETWORK_N_BATCHES
#define AI_NETWORK_N_BATCHES         (1)

static ai_ptr g_network_activations_map[1] = AI_C_ARRAY_INIT;
static ai_ptr g_network_weights_map[1] = AI_C_ARRAY_INIT;



/**  Array declarations section  **********************************************/
/* Array#0 */
AI_ARRAY_OBJ_DECLARE(
  input_output_array, AI_ARRAY_FORMAT_S8|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 1200, AI_STATIC)

/* Array#1 */
AI_ARRAY_OBJ_DECLARE(
  _frontend_frontend_2_Clip_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 1600, AI_STATIC)

/* Array#2 */
AI_ARRAY_OBJ_DECLARE(
  _expand_expand_2_Clip_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 6400, AI_STATIC)

/* Array#3 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_0_net_net_0_Conv_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 6400, AI_STATIC)

/* Array#4 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_0_net_net_3_Clip_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 6400, AI_STATIC)

/* Array#5 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_0_net_net_5_avg_pool_GlobalAveragePool_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 16, AI_STATIC)

/* Array#6 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 8, AI_STATIC)

/* Array#7 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_0_net_net_5_fc_fc_2_MatMul_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 16, AI_STATIC)

/* Array#8 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_0_net_net_5_fc_fc_3_HardSigmoid_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 16, AI_STATIC)

/* Array#9 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_0_net_net_5_Mul_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 6400, AI_STATIC)

/* Array#10 */
AI_ARRAY_OBJ_DECLARE(
  _Add_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 6400, AI_STATIC)

/* Array#11 */
AI_ARRAY_OBJ_DECLARE(
  _Add_output_0_0_0__tcn_layers_1_net_net_0_Conv_output_0_conversion_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#12 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_1_net_net_0_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#13 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_1_net_net_0_Conv_output_0_0_0__tcn_layers_1_net_net_3_Clip_output_0_conversion_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 6400, AI_STATIC)

/* Array#14 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_1_net_net_3_Clip_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 6400, AI_STATIC)

/* Array#15 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_1_net_net_5_avg_pool_GlobalAveragePool_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 16, AI_STATIC)

/* Array#16 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_1_net_net_5_fc_fc_1_Clip_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 8, AI_STATIC)

/* Array#17 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_1_net_net_5_fc_fc_2_MatMul_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 16, AI_STATIC)

/* Array#18 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_1_net_net_5_fc_fc_3_HardSigmoid_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 16, AI_STATIC)

/* Array#19 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_1_net_net_5_Mul_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 6400, AI_STATIC)

/* Array#20 */
AI_ARRAY_OBJ_DECLARE(
  _Add_1_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 6400, AI_STATIC)

/* Array#21 */
AI_ARRAY_OBJ_DECLARE(
  _Add_1_output_0_0_0__tcn_layers_2_net_net_0_Conv_output_0_conversion_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#22 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_2_net_net_0_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#23 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_2_net_net_0_Conv_output_0_0_0__tcn_layers_2_net_net_3_Clip_output_0_conversion_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 6400, AI_STATIC)

/* Array#24 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_2_net_net_3_Clip_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 6400, AI_STATIC)

/* Array#25 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_2_net_net_5_avg_pool_GlobalAveragePool_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 16, AI_STATIC)

/* Array#26 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_2_net_net_5_fc_fc_1_Clip_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 8, AI_STATIC)

/* Array#27 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_2_net_net_5_fc_fc_2_MatMul_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 16, AI_STATIC)

/* Array#28 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_2_net_net_5_fc_fc_3_HardSigmoid_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 16, AI_STATIC)

/* Array#29 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_2_net_net_5_Mul_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 6400, AI_STATIC)

/* Array#30 */
AI_ARRAY_OBJ_DECLARE(
  _Add_2_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 6400, AI_STATIC)

/* Array#31 */
AI_ARRAY_OBJ_DECLARE(
  _Add_2_output_0_0_0__tcn_layers_3_net_net_0_Conv_output_0_conversion_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#32 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_3_net_net_0_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#33 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_3_net_net_0_Conv_output_0_0_0__tcn_layers_3_net_net_3_Clip_output_0_conversion_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 6400, AI_STATIC)

/* Array#34 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_3_net_net_3_Clip_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 6400, AI_STATIC)

/* Array#35 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_3_net_net_5_avg_pool_GlobalAveragePool_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 16, AI_STATIC)

/* Array#36 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_3_net_net_5_fc_fc_1_Clip_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 8, AI_STATIC)

/* Array#37 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_3_net_net_5_fc_fc_2_MatMul_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 16, AI_STATIC)

/* Array#38 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_3_net_net_5_fc_fc_3_HardSigmoid_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 16, AI_STATIC)

/* Array#39 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_3_net_net_5_Mul_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 6400, AI_STATIC)

/* Array#40 */
AI_ARRAY_OBJ_DECLARE(
  _Add_3_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 6400, AI_STATIC)

/* Array#41 */
AI_ARRAY_OBJ_DECLARE(
  _boundary_head_Conv_output_0_output_array, AI_ARRAY_FORMAT_S8|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 400, AI_STATIC)

/* Array#42 */
AI_ARRAY_OBJ_DECLARE(
  _frame_head_Conv_output_0_output_array, AI_ARRAY_FORMAT_S8|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 400, AI_STATIC)

/* Array#43 */
AI_ARRAY_OBJ_DECLARE(
  _frontend_frontend_2_Clip_output_0_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 96, AI_STATIC)

/* Array#44 */
AI_ARRAY_OBJ_DECLARE(
  _frontend_frontend_2_Clip_output_0_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 4, AI_STATIC)

/* Array#45 */
AI_ARRAY_OBJ_DECLARE(
  _expand_expand_2_Clip_output_0_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 64, AI_STATIC)

/* Array#46 */
AI_ARRAY_OBJ_DECLARE(
  _expand_expand_2_Clip_output_0_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 16, AI_STATIC)

/* Array#47 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_0_net_net_0_Conv_output_0_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 112, AI_STATIC)

/* Array#48 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_0_net_net_0_Conv_output_0_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 16, AI_STATIC)

/* Array#49 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_0_net_net_3_Clip_output_0_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 256, AI_STATIC)

/* Array#50 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_0_net_net_3_Clip_output_0_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 16, AI_STATIC)

/* Array#51 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 128, AI_STATIC)

/* Array#52 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 8, AI_STATIC)

/* Array#53 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_0_net_net_5_fc_fc_2_MatMul_output_0_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 128, AI_STATIC)

/* Array#54 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_1_net_net_0_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 112, AI_STATIC)

/* Array#55 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_1_net_net_0_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 16, AI_STATIC)

/* Array#56 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_1_net_net_3_Clip_output_0_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 256, AI_STATIC)

/* Array#57 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_1_net_net_3_Clip_output_0_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 16, AI_STATIC)

/* Array#58 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_1_net_net_5_fc_fc_1_Clip_output_0_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 128, AI_STATIC)

/* Array#59 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_1_net_net_5_fc_fc_2_MatMul_output_0_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 128, AI_STATIC)

/* Array#60 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_2_net_net_0_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 112, AI_STATIC)

/* Array#61 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_2_net_net_3_Clip_output_0_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 256, AI_STATIC)

/* Array#62 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_2_net_net_3_Clip_output_0_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 16, AI_STATIC)

/* Array#63 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_2_net_net_5_fc_fc_1_Clip_output_0_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 128, AI_STATIC)

/* Array#64 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_2_net_net_5_fc_fc_2_MatMul_output_0_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 128, AI_STATIC)

/* Array#65 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_3_net_net_0_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 112, AI_STATIC)

/* Array#66 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_3_net_net_3_Clip_output_0_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 256, AI_STATIC)

/* Array#67 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_3_net_net_3_Clip_output_0_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 16, AI_STATIC)

/* Array#68 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_3_net_net_5_fc_fc_1_Clip_output_0_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 128, AI_STATIC)

/* Array#69 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_3_net_net_5_fc_fc_2_MatMul_output_0_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 128, AI_STATIC)

/* Array#70 */
AI_ARRAY_OBJ_DECLARE(
  _boundary_head_Conv_output_0_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 16, AI_STATIC)

/* Array#71 */
AI_ARRAY_OBJ_DECLARE(
  _boundary_head_Conv_output_0_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 1, AI_STATIC)

/* Array#72 */
AI_ARRAY_OBJ_DECLARE(
  _frame_head_Conv_output_0_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 16, AI_STATIC)

/* Array#73 */
AI_ARRAY_OBJ_DECLARE(
  _frame_head_Conv_output_0_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 1, AI_STATIC)

/* Array#74 */
AI_ARRAY_OBJ_DECLARE(
  _frontend_frontend_2_Clip_output_0_scratch0_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 344, AI_STATIC)

/* Array#75 */
AI_ARRAY_OBJ_DECLARE(
  _frontend_frontend_2_Clip_output_0_scratch1_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 4796, AI_STATIC)

/* Array#76 */
AI_ARRAY_OBJ_DECLARE(
  _expand_expand_2_Clip_output_0_scratch0_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 176, AI_STATIC)

/* Array#77 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_0_net_net_0_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 497, AI_STATIC)

/* Array#78 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_0_net_net_3_Clip_output_0_scratch0_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 224, AI_STATIC)

/* Array#79 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_scratch0_array, AI_ARRAY_FORMAT_S16,
  NULL, NULL, 56, AI_STATIC)

/* Array#80 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_0_net_net_5_fc_fc_2_MatMul_output_0_scratch0_array, AI_ARRAY_FORMAT_S16,
  NULL, NULL, 88, AI_STATIC)

/* Array#81 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_1_net_net_3_Clip_output_0_scratch0_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 224, AI_STATIC)

/* Array#82 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_1_net_net_5_fc_fc_1_Clip_output_0_scratch0_array, AI_ARRAY_FORMAT_S16,
  NULL, NULL, 56, AI_STATIC)

/* Array#83 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_1_net_net_5_fc_fc_2_MatMul_output_0_scratch0_array, AI_ARRAY_FORMAT_S16,
  NULL, NULL, 88, AI_STATIC)

/* Array#84 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_2_net_net_3_Clip_output_0_scratch0_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 224, AI_STATIC)

/* Array#85 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_2_net_net_5_fc_fc_1_Clip_output_0_scratch0_array, AI_ARRAY_FORMAT_S16,
  NULL, NULL, 56, AI_STATIC)

/* Array#86 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_2_net_net_5_fc_fc_2_MatMul_output_0_scratch0_array, AI_ARRAY_FORMAT_S16,
  NULL, NULL, 88, AI_STATIC)

/* Array#87 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_3_net_net_3_Clip_output_0_scratch0_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 224, AI_STATIC)

/* Array#88 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_3_net_net_5_fc_fc_1_Clip_output_0_scratch0_array, AI_ARRAY_FORMAT_S16,
  NULL, NULL, 56, AI_STATIC)

/* Array#89 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_3_net_net_5_fc_fc_2_MatMul_output_0_scratch0_array, AI_ARRAY_FORMAT_S16,
  NULL, NULL, 88, AI_STATIC)

/* Array#90 */
AI_ARRAY_OBJ_DECLARE(
  _boundary_head_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 64, AI_STATIC)

/* Array#91 */
AI_ARRAY_OBJ_DECLARE(
  _frame_head_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 64, AI_STATIC)

/**  Array metadata declarations section  *************************************/
/* Int quant #0 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_Add_1_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.05302070826292038f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #1 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_Add_2_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.07099438458681107f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #2 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_Add_3_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.08770780265331268f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #3 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_Add_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.035688064992427826f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #4 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_boundary_head_Conv_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.2990305721759796f),
    AI_PACK_INTQ_ZP(81)))

/* Int quant #5 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_boundary_head_Conv_output_0_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.008963393978774548f),
    AI_PACK_INTQ_ZP(0)))

/* Int quant #6 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_expand_expand_2_Clip_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0235294122248888f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #7 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_expand_expand_2_Clip_output_0_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 16,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0211018119007349f, 0.027059826999902725f, 0.020389411598443985f, 0.012810052372515202f, 0.021210486069321632f, 0.014602799899876118f, 0.014381476677954197f, 0.027071010321378708f, 0.008943090215325356f, 0.025242099538445473f, 0.009548317641019821f, 0.05088923126459122f, 0.02458481676876545f, 0.021629802882671356f, 0.013608668930828571f, 0.016352195292711258f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #8 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_frame_head_Conv_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.07829631865024567f),
    AI_PACK_INTQ_ZP(13)))

/* Int quant #9 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_frame_head_Conv_output_0_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.005581629928201437f),
    AI_PACK_INTQ_ZP(0)))

/* Int quant #10 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_frontend_frontend_2_Clip_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.020191220566630363f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #11 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_frontend_frontend_2_Clip_output_0_scratch1_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.020191220566630363f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #12 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_frontend_frontend_2_Clip_output_0_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 4,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0011386797996237874f, 0.0010836648289114237f, 0.001593423425219953f, 0.0017809912096709013f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0)))

/* Int quant #13 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_0_net_net_0_Conv_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.028016412630677223f),
    AI_PACK_INTQ_ZP(24)))

/* Int quant #14 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_0_net_net_0_Conv_output_0_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 16,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.003944080322980881f, 0.003893510904163122f, 0.003963097929954529f, 0.0039986493065953255f, 0.003132025245577097f, 0.0059794471599161625f, 0.004691713023930788f, 0.004434620030224323f, 0.0040533095598220825f, 0.004000046290457249f, 0.0041926270350813866f, 0.0035921423695981503f, 0.0031858282163739204f, 0.004526501055806875f, 0.004893537610769272f, 0.0032379645854234695f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #15 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_0_net_net_3_Clip_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0235294122248888f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #16 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_0_net_net_3_Clip_output_0_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 16,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0252547450363636f, 0.026693450286984444f, 0.029540300369262695f, 0.018888039514422417f, 0.010944174602627754f, 0.025008803233504295f, 0.02508329413831234f, 0.02815987542271614f, 0.031194113194942474f, 0.016826307401061058f, 0.019697682932019234f, 0.07562526315450668f, 0.017849484458565712f, 0.021369781345129013f, 0.028160059824585915f, 0.016779346391558647f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #17 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_0_net_net_5_Mul_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0235294122248888f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #18 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_0_net_net_5_avg_pool_GlobalAveragePool_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.005885048303753138f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #19 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.015555220656096935f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #20 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 8,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0025428656954318285f, 0.002056330209597945f, 0.0019406179198995233f, 0.007384167984127998f, 0.0018630471313372254f, 0.005421694368124008f, 0.0019255458610132337f, 0.0063841878436505795f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #21 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_0_net_net_5_fc_fc_2_MatMul_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.035818926990032196f),
    AI_PACK_INTQ_ZP(-68)))

/* Int quant #22 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_0_net_net_5_fc_fc_2_MatMul_output_0_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 16,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0031464516650885344f, 0.007975665852427483f, 0.006082253530621529f, 0.003345375880599022f, 0.0038611111231148243f, 0.0059588016010820866f, 0.00394121278077364f, 0.005754758603870869f, 0.006256204564124346f, 0.0050399717874825f, 0.004761766642332077f, 0.005348954815417528f, 0.006949721835553646f, 0.007262177765369415f, 0.008018177933990955f, 0.007276475895196199f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #23 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_0_net_net_5_fc_fc_3_HardSigmoid_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.003921568859368563f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #24 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_1_net_net_0_Conv_output_0_0_0__tcn_layers_1_net_net_3_Clip_output_0_conversion_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.05209880322217941f),
    AI_PACK_INTQ_ZP(24)))

/* Int quant #25 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_1_net_net_3_Clip_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0235294122248888f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #26 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_1_net_net_3_Clip_output_0_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 16,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.014734909869730473f, 0.011967810802161694f, 0.005578104872256517f, 0.009641172364354134f, 0.012169604189693928f, 0.00817657820880413f, 0.0102523909881711f, 0.007542375475168228f, 0.015708668157458305f, 0.006219628266990185f, 0.004988027270883322f, 0.01469169557094574f, 0.004545074887573719f, 0.014617586508393288f, 0.009846938773989677f, 0.018079152330756187f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #27 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_1_net_net_5_Mul_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0235294122248888f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #28 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_1_net_net_5_avg_pool_GlobalAveragePool_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.007666793651878834f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #29 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_1_net_net_5_fc_fc_1_Clip_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0235294122248888f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #30 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_1_net_net_5_fc_fc_1_Clip_output_0_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 8,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.00510044302791357f, 0.0019700147677212954f, 0.0015957928262650967f, 0.004593497607856989f, 0.0020752246491611004f, 0.001966816373169422f, 0.002125316997990012f, 0.006531988270580769f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #31 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_1_net_net_5_fc_fc_2_MatMul_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.049279045313596725f),
    AI_PACK_INTQ_ZP(-28)))

/* Int quant #32 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_1_net_net_5_fc_fc_2_MatMul_output_0_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 16,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.003195837838575244f, 0.00547718396410346f, 0.006091626361012459f, 0.005840463098138571f, 0.0036443150602281094f, 0.0056910947896540165f, 0.005133023019880056f, 0.004443724639713764f, 0.003747958457097411f, 0.0045592524111270905f, 0.0030329767614603043f, 0.003678141161799431f, 0.006139117293059826f, 0.005461954511702061f, 0.006809822283685207f, 0.0031719461549073458f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #33 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_1_net_net_5_fc_fc_3_HardSigmoid_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.003921568859368563f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #34 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_2_net_net_0_Conv_output_0_0_0__tcn_layers_2_net_net_3_Clip_output_0_conversion_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.08265189081430435f),
    AI_PACK_INTQ_ZP(-25)))

/* Int quant #35 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_2_net_net_3_Clip_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0235294122248888f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #36 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_2_net_net_3_Clip_output_0_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 16,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0036336721386760473f, 0.00637028319761157f, 0.00756419263780117f, 0.00912754237651825f, 0.009631798602640629f, 0.00606917031109333f, 0.015319588594138622f, 0.007884521968662739f, 0.008996658958494663f, 0.00881719309836626f, 0.005656063556671143f, 0.006364994216710329f, 0.005150092300027609f, 0.006807519122958183f, 0.007259315811097622f, 0.0097011998295784f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #37 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_2_net_net_5_Mul_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0235294122248888f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #38 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_2_net_net_5_avg_pool_GlobalAveragePool_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.00945251528173685f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #39 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_2_net_net_5_fc_fc_1_Clip_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.021392155438661575f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #40 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_2_net_net_5_fc_fc_1_Clip_output_0_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 8,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.001851201057434082f, 0.0017881097737699747f, 0.0017296777805313468f, 0.004721894860267639f, 0.003184600966051221f, 0.0023363179061561823f, 0.0037196173798292875f, 0.004288064315915108f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #41 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_2_net_net_5_fc_fc_2_MatMul_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.05367770418524742f),
    AI_PACK_INTQ_ZP(-19)))

/* Int quant #42 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_2_net_net_5_fc_fc_2_MatMul_output_0_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 16,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.004832141101360321f, 0.005082712508738041f, 0.0034320231061428785f, 0.004397052805870771f, 0.004260830581188202f, 0.004877747502177954f, 0.004267010372132063f, 0.005359525792300701f, 0.003726884024217725f, 0.004368486814200878f, 0.0035068411380052567f, 0.0031378488056361675f, 0.0033265864476561546f, 0.003561342367902398f, 0.004575990606099367f, 0.0037428971845656633f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #43 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_2_net_net_5_fc_fc_3_HardSigmoid_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.003921568859368563f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #44 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_3_net_net_0_Conv_output_0_0_0__tcn_layers_3_net_net_3_Clip_output_0_conversion_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.08570254594087601f),
    AI_PACK_INTQ_ZP(1)))

/* Int quant #45 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_3_net_net_3_Clip_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0235294122248888f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #46 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_3_net_net_3_Clip_output_0_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 16,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.005626107566058636f, 0.008724389597773552f, 0.010177329182624817f, 0.006081770174205303f, 0.010906200855970383f, 0.004459033720195293f, 0.010644892230629921f, 0.0068571437150239944f, 0.011787724681198597f, 0.004043739289045334f, 0.018188124522566795f, 0.006133025512099266f, 0.005205945577472448f, 0.005615864414721727f, 0.007710917387157679f, 0.003095668973401189f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #47 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_3_net_net_5_Mul_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0235294122248888f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #48 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_3_net_net_5_avg_pool_GlobalAveragePool_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.013968074694275856f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #49 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_3_net_net_5_fc_fc_1_Clip_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0235294122248888f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #50 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_3_net_net_5_fc_fc_1_Clip_output_0_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 8,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0016677869716659188f, 0.004486927296966314f, 0.0041449666023254395f, 0.004250882193446159f, 0.001887578866444528f, 0.0017704300116747618f, 0.0018468661000952125f, 0.004206923767924309f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #51 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_3_net_net_5_fc_fc_2_MatMul_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.07309304177761078f),
    AI_PACK_INTQ_ZP(-17)))

/* Int quant #52 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_3_net_net_5_fc_fc_2_MatMul_output_0_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 16,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.008001448586583138f, 0.0040278653614223f, 0.0028879446908831596f, 0.003576071700081229f, 0.004245624411851168f, 0.0035773292183876038f, 0.003847104962915182f, 0.0027623306959867477f, 0.00356710865162313f, 0.0037135344464331865f, 0.004720912780612707f, 0.0033962151501327753f, 0.005334392189979553f, 0.0051689185202121735f, 0.004180502612143755f, 0.0040033310651779175f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #53 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_3_net_net_5_fc_fc_3_HardSigmoid_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.003921568859368563f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #54 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(input_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.04032759368419647f),
    AI_PACK_INTQ_ZP(-5)))

/**  Tensor declarations section  *********************************************/
/* Tensor #0 */
AI_TENSOR_OBJ_DECLARE(
  _Add_1_output_0_0_0__tcn_layers_2_net_net_0_Conv_output_0_conversion_output, AI_STATIC,
  0, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 400, 1), AI_STRIDE_INIT(4, 4, 4, 64, 25600),
  1, &_Add_1_output_0_0_0__tcn_layers_2_net_net_0_Conv_output_0_conversion_output_array, NULL)

/* Tensor #1 */
AI_TENSOR_OBJ_DECLARE(
  _Add_1_output_0_output, AI_STATIC,
  1, 0x1,
  AI_SHAPE_INIT(4, 1, 16, 400, 1), AI_STRIDE_INIT(4, 1, 1, 16, 6400),
  1, &_Add_1_output_0_output_array, &_Add_1_output_0_output_array_intq)

/* Tensor #2 */
AI_TENSOR_OBJ_DECLARE(
  _Add_2_output_0_0_0__tcn_layers_3_net_net_0_Conv_output_0_conversion_output, AI_STATIC,
  2, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 400, 1), AI_STRIDE_INIT(4, 4, 4, 64, 25600),
  1, &_Add_2_output_0_0_0__tcn_layers_3_net_net_0_Conv_output_0_conversion_output_array, NULL)

/* Tensor #3 */
AI_TENSOR_OBJ_DECLARE(
  _Add_2_output_0_output, AI_STATIC,
  3, 0x1,
  AI_SHAPE_INIT(4, 1, 16, 400, 1), AI_STRIDE_INIT(4, 1, 1, 16, 6400),
  1, &_Add_2_output_0_output_array, &_Add_2_output_0_output_array_intq)

/* Tensor #4 */
AI_TENSOR_OBJ_DECLARE(
  _Add_3_output_0_output, AI_STATIC,
  4, 0x1,
  AI_SHAPE_INIT(4, 1, 16, 400, 1), AI_STRIDE_INIT(4, 1, 1, 16, 6400),
  1, &_Add_3_output_0_output_array, &_Add_3_output_0_output_array_intq)

/* Tensor #5 */
AI_TENSOR_OBJ_DECLARE(
  _Add_output_0_0_0__tcn_layers_1_net_net_0_Conv_output_0_conversion_output, AI_STATIC,
  5, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 400, 1), AI_STRIDE_INIT(4, 4, 4, 64, 25600),
  1, &_Add_output_0_0_0__tcn_layers_1_net_net_0_Conv_output_0_conversion_output_array, NULL)

/* Tensor #6 */
AI_TENSOR_OBJ_DECLARE(
  _Add_output_0_output, AI_STATIC,
  6, 0x1,
  AI_SHAPE_INIT(4, 1, 16, 400, 1), AI_STRIDE_INIT(4, 1, 1, 16, 6400),
  1, &_Add_output_0_output_array, &_Add_output_0_output_array_intq)

/* Tensor #7 */
AI_TENSOR_OBJ_DECLARE(
  _boundary_head_Conv_output_0_bias, AI_STATIC,
  7, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &_boundary_head_Conv_output_0_bias_array, NULL)

/* Tensor #8 */
AI_TENSOR_OBJ_DECLARE(
  _boundary_head_Conv_output_0_output, AI_STATIC,
  8, 0x1,
  AI_SHAPE_INIT(4, 1, 1, 400, 1), AI_STRIDE_INIT(4, 1, 1, 1, 400),
  1, &_boundary_head_Conv_output_0_output_array, &_boundary_head_Conv_output_0_output_array_intq)

/* Tensor #9 */
AI_TENSOR_OBJ_DECLARE(
  _boundary_head_Conv_output_0_scratch0, AI_STATIC,
  9, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 1, 1, 64, 64),
  1, &_boundary_head_Conv_output_0_scratch0_array, NULL)

/* Tensor #10 */
AI_TENSOR_OBJ_DECLARE(
  _boundary_head_Conv_output_0_weights, AI_STATIC,
  10, 0x1,
  AI_SHAPE_INIT(4, 16, 1, 1, 1), AI_STRIDE_INIT(4, 1, 16, 16, 16),
  1, &_boundary_head_Conv_output_0_weights_array, &_boundary_head_Conv_output_0_weights_array_intq)

/* Tensor #11 */
AI_TENSOR_OBJ_DECLARE(
  _expand_expand_2_Clip_output_0_bias, AI_STATIC,
  11, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 1, 1), AI_STRIDE_INIT(4, 4, 4, 64, 64),
  1, &_expand_expand_2_Clip_output_0_bias_array, NULL)

/* Tensor #12 */
AI_TENSOR_OBJ_DECLARE(
  _expand_expand_2_Clip_output_0_output, AI_STATIC,
  12, 0x1,
  AI_SHAPE_INIT(4, 1, 16, 400, 1), AI_STRIDE_INIT(4, 1, 1, 16, 6400),
  1, &_expand_expand_2_Clip_output_0_output_array, &_expand_expand_2_Clip_output_0_output_array_intq)

/* Tensor #13 */
AI_TENSOR_OBJ_DECLARE(
  _expand_expand_2_Clip_output_0_scratch0, AI_STATIC,
  13, 0x0,
  AI_SHAPE_INIT(4, 1, 176, 1, 1), AI_STRIDE_INIT(4, 1, 1, 176, 176),
  1, &_expand_expand_2_Clip_output_0_scratch0_array, NULL)

/* Tensor #14 */
AI_TENSOR_OBJ_DECLARE(
  _expand_expand_2_Clip_output_0_weights, AI_STATIC,
  14, 0x1,
  AI_SHAPE_INIT(4, 4, 1, 1, 16), AI_STRIDE_INIT(4, 1, 4, 64, 64),
  1, &_expand_expand_2_Clip_output_0_weights_array, &_expand_expand_2_Clip_output_0_weights_array_intq)

/* Tensor #15 */
AI_TENSOR_OBJ_DECLARE(
  _frame_head_Conv_output_0_bias, AI_STATIC,
  15, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &_frame_head_Conv_output_0_bias_array, NULL)

/* Tensor #16 */
AI_TENSOR_OBJ_DECLARE(
  _frame_head_Conv_output_0_output, AI_STATIC,
  16, 0x1,
  AI_SHAPE_INIT(4, 1, 1, 400, 1), AI_STRIDE_INIT(4, 1, 1, 1, 400),
  1, &_frame_head_Conv_output_0_output_array, &_frame_head_Conv_output_0_output_array_intq)

/* Tensor #17 */
AI_TENSOR_OBJ_DECLARE(
  _frame_head_Conv_output_0_scratch0, AI_STATIC,
  17, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 1, 1, 64, 64),
  1, &_frame_head_Conv_output_0_scratch0_array, NULL)

/* Tensor #18 */
AI_TENSOR_OBJ_DECLARE(
  _frame_head_Conv_output_0_weights, AI_STATIC,
  18, 0x1,
  AI_SHAPE_INIT(4, 16, 1, 1, 1), AI_STRIDE_INIT(4, 1, 16, 16, 16),
  1, &_frame_head_Conv_output_0_weights_array, &_frame_head_Conv_output_0_weights_array_intq)

/* Tensor #19 */
AI_TENSOR_OBJ_DECLARE(
  _frontend_frontend_2_Clip_output_0_bias, AI_STATIC,
  19, 0x0,
  AI_SHAPE_INIT(4, 1, 4, 1, 1), AI_STRIDE_INIT(4, 4, 4, 16, 16),
  1, &_frontend_frontend_2_Clip_output_0_bias_array, NULL)

/* Tensor #20 */
AI_TENSOR_OBJ_DECLARE(
  _frontend_frontend_2_Clip_output_0_output, AI_STATIC,
  20, 0x1,
  AI_SHAPE_INIT(4, 1, 4, 400, 1), AI_STRIDE_INIT(4, 1, 1, 4, 1600),
  1, &_frontend_frontend_2_Clip_output_0_output_array, &_frontend_frontend_2_Clip_output_0_output_array_intq)

/* Tensor #21 */
AI_TENSOR_OBJ_DECLARE(
  _frontend_frontend_2_Clip_output_0_scratch0, AI_STATIC,
  21, 0x0,
  AI_SHAPE_INIT(4, 1, 344, 1, 1), AI_STRIDE_INIT(4, 1, 1, 344, 344),
  1, &_frontend_frontend_2_Clip_output_0_scratch0_array, NULL)

/* Tensor #22 */
AI_TENSOR_OBJ_DECLARE(
  _frontend_frontend_2_Clip_output_0_scratch1, AI_STATIC,
  22, 0x1,
  AI_SHAPE_INIT(4, 1, 4, 1199, 1), AI_STRIDE_INIT(4, 1, 1, 4, 4796),
  1, &_frontend_frontend_2_Clip_output_0_scratch1_array, &_frontend_frontend_2_Clip_output_0_scratch1_array_intq)

/* Tensor #23 */
AI_TENSOR_OBJ_DECLARE(
  _frontend_frontend_2_Clip_output_0_weights, AI_STATIC,
  23, 0x1,
  AI_SHAPE_INIT(4, 1, 24, 1, 4), AI_STRIDE_INIT(4, 1, 1, 4, 96),
  1, &_frontend_frontend_2_Clip_output_0_weights_array, &_frontend_frontend_2_Clip_output_0_weights_array_intq)

/* Tensor #24 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_0_net_net_0_Conv_output_0_bias, AI_STATIC,
  24, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 1, 1), AI_STRIDE_INIT(4, 4, 4, 64, 64),
  1, &_tcn_layers_0_net_net_0_Conv_output_0_bias_array, NULL)

/* Tensor #25 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_0_net_net_0_Conv_output_0_output, AI_STATIC,
  25, 0x1,
  AI_SHAPE_INIT(4, 1, 16, 400, 1), AI_STRIDE_INIT(4, 1, 1, 16, 6400),
  1, &_tcn_layers_0_net_net_0_Conv_output_0_output_array, &_tcn_layers_0_net_net_0_Conv_output_0_output_array_intq)

/* Tensor #26 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_0_net_net_0_Conv_output_0_scratch0, AI_STATIC,
  26, 0x0,
  AI_SHAPE_INIT(4, 1, 497, 1, 1), AI_STRIDE_INIT(4, 1, 1, 497, 497),
  1, &_tcn_layers_0_net_net_0_Conv_output_0_scratch0_array, NULL)

/* Tensor #27 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_0_net_net_0_Conv_output_0_weights, AI_STATIC,
  27, 0x1,
  AI_SHAPE_INIT(4, 16, 7, 1, 1), AI_STRIDE_INIT(4, 1, 16, 16, 112),
  1, &_tcn_layers_0_net_net_0_Conv_output_0_weights_array, &_tcn_layers_0_net_net_0_Conv_output_0_weights_array_intq)

/* Tensor #28 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_0_net_net_3_Clip_output_0_bias, AI_STATIC,
  28, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 1, 1), AI_STRIDE_INIT(4, 4, 4, 64, 64),
  1, &_tcn_layers_0_net_net_3_Clip_output_0_bias_array, NULL)

/* Tensor #29 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_0_net_net_3_Clip_output_0_output, AI_STATIC,
  29, 0x1,
  AI_SHAPE_INIT(4, 1, 16, 400, 1), AI_STRIDE_INIT(4, 1, 1, 16, 6400),
  1, &_tcn_layers_0_net_net_3_Clip_output_0_output_array, &_tcn_layers_0_net_net_3_Clip_output_0_output_array_intq)

/* Tensor #30 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_0_net_net_3_Clip_output_0_scratch0, AI_STATIC,
  30, 0x0,
  AI_SHAPE_INIT(4, 1, 224, 1, 1), AI_STRIDE_INIT(4, 1, 1, 224, 224),
  1, &_tcn_layers_0_net_net_3_Clip_output_0_scratch0_array, NULL)

/* Tensor #31 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_0_net_net_3_Clip_output_0_weights, AI_STATIC,
  31, 0x1,
  AI_SHAPE_INIT(4, 16, 1, 1, 16), AI_STRIDE_INIT(4, 1, 16, 256, 256),
  1, &_tcn_layers_0_net_net_3_Clip_output_0_weights_array, &_tcn_layers_0_net_net_3_Clip_output_0_weights_array_intq)

/* Tensor #32 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_0_net_net_5_Mul_output_0_output, AI_STATIC,
  32, 0x1,
  AI_SHAPE_INIT(4, 1, 16, 400, 1), AI_STRIDE_INIT(4, 1, 1, 16, 6400),
  1, &_tcn_layers_0_net_net_5_Mul_output_0_output_array, &_tcn_layers_0_net_net_5_Mul_output_0_output_array_intq)

/* Tensor #33 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_0_net_net_5_avg_pool_GlobalAveragePool_output_0_output, AI_STATIC,
  33, 0x1,
  AI_SHAPE_INIT(4, 1, 16, 1, 1), AI_STRIDE_INIT(4, 1, 1, 16, 16),
  1, &_tcn_layers_0_net_net_5_avg_pool_GlobalAveragePool_output_0_output_array, &_tcn_layers_0_net_net_5_avg_pool_GlobalAveragePool_output_0_output_array_intq)

/* Tensor #34 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_bias, AI_STATIC,
  34, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 1), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_bias_array, NULL)

/* Tensor #35 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_output, AI_STATIC,
  35, 0x1,
  AI_SHAPE_INIT(4, 1, 8, 1, 1), AI_STRIDE_INIT(4, 1, 1, 8, 8),
  1, &_tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_output_array, &_tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_output_array_intq)

/* Tensor #36 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_scratch0, AI_STATIC,
  36, 0x0,
  AI_SHAPE_INIT(4, 1, 56, 1, 1), AI_STRIDE_INIT(4, 2, 2, 112, 112),
  1, &_tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_scratch0_array, NULL)

/* Tensor #37 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_weights, AI_STATIC,
  37, 0x1,
  AI_SHAPE_INIT(4, 16, 8, 1, 1), AI_STRIDE_INIT(4, 1, 16, 128, 128),
  1, &_tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_weights_array, &_tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_weights_array_intq)

/* Tensor #38 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_0_net_net_5_fc_fc_2_MatMul_output_0_output, AI_STATIC,
  38, 0x1,
  AI_SHAPE_INIT(4, 1, 16, 1, 1), AI_STRIDE_INIT(4, 1, 1, 16, 16),
  1, &_tcn_layers_0_net_net_5_fc_fc_2_MatMul_output_0_output_array, &_tcn_layers_0_net_net_5_fc_fc_2_MatMul_output_0_output_array_intq)

/* Tensor #39 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_0_net_net_5_fc_fc_2_MatMul_output_0_scratch0, AI_STATIC,
  39, 0x0,
  AI_SHAPE_INIT(4, 1, 88, 1, 1), AI_STRIDE_INIT(4, 2, 2, 176, 176),
  1, &_tcn_layers_0_net_net_5_fc_fc_2_MatMul_output_0_scratch0_array, NULL)

/* Tensor #40 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_0_net_net_5_fc_fc_2_MatMul_output_0_weights, AI_STATIC,
  40, 0x1,
  AI_SHAPE_INIT(4, 8, 16, 1, 1), AI_STRIDE_INIT(4, 1, 8, 128, 128),
  1, &_tcn_layers_0_net_net_5_fc_fc_2_MatMul_output_0_weights_array, &_tcn_layers_0_net_net_5_fc_fc_2_MatMul_output_0_weights_array_intq)

/* Tensor #41 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_0_net_net_5_fc_fc_3_HardSigmoid_output_0_output, AI_STATIC,
  41, 0x1,
  AI_SHAPE_INIT(4, 1, 16, 1, 1), AI_STRIDE_INIT(4, 1, 1, 16, 16),
  1, &_tcn_layers_0_net_net_5_fc_fc_3_HardSigmoid_output_0_output_array, &_tcn_layers_0_net_net_5_fc_fc_3_HardSigmoid_output_0_output_array_intq)

/* Tensor #42 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_1_net_net_0_Conv_output_0_0_0__tcn_layers_1_net_net_3_Clip_output_0_conversion_output, AI_STATIC,
  42, 0x1,
  AI_SHAPE_INIT(4, 1, 16, 400, 1), AI_STRIDE_INIT(4, 1, 1, 16, 6400),
  1, &_tcn_layers_1_net_net_0_Conv_output_0_0_0__tcn_layers_1_net_net_3_Clip_output_0_conversion_output_array, &_tcn_layers_1_net_net_0_Conv_output_0_0_0__tcn_layers_1_net_net_3_Clip_output_0_conversion_output_array_intq)

/* Tensor #43 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_1_net_net_0_Conv_output_0_bias, AI_STATIC,
  43, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 1, 1), AI_STRIDE_INIT(4, 4, 4, 64, 64),
  1, &_tcn_layers_1_net_net_0_Conv_output_0_bias_array, NULL)

/* Tensor #44 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_1_net_net_0_Conv_output_0_output, AI_STATIC,
  44, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 400, 1), AI_STRIDE_INIT(4, 4, 4, 64, 25600),
  1, &_tcn_layers_1_net_net_0_Conv_output_0_output_array, NULL)

/* Tensor #45 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_1_net_net_0_Conv_output_0_weights, AI_STATIC,
  45, 0x0,
  AI_SHAPE_INIT(4, 1, 7, 1, 16), AI_STRIDE_INIT(4, 1, 16, 16, 16),
  1, &_tcn_layers_1_net_net_0_Conv_output_0_weights_array, NULL)

/* Tensor #46 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_1_net_net_3_Clip_output_0_bias, AI_STATIC,
  46, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 1, 1), AI_STRIDE_INIT(4, 4, 4, 64, 64),
  1, &_tcn_layers_1_net_net_3_Clip_output_0_bias_array, NULL)

/* Tensor #47 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_1_net_net_3_Clip_output_0_output, AI_STATIC,
  47, 0x1,
  AI_SHAPE_INIT(4, 1, 16, 400, 1), AI_STRIDE_INIT(4, 1, 1, 16, 6400),
  1, &_tcn_layers_1_net_net_3_Clip_output_0_output_array, &_tcn_layers_1_net_net_3_Clip_output_0_output_array_intq)

/* Tensor #48 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_1_net_net_3_Clip_output_0_scratch0, AI_STATIC,
  48, 0x0,
  AI_SHAPE_INIT(4, 1, 224, 1, 1), AI_STRIDE_INIT(4, 1, 1, 224, 224),
  1, &_tcn_layers_1_net_net_3_Clip_output_0_scratch0_array, NULL)

/* Tensor #49 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_1_net_net_3_Clip_output_0_weights, AI_STATIC,
  49, 0x1,
  AI_SHAPE_INIT(4, 16, 1, 1, 16), AI_STRIDE_INIT(4, 1, 16, 256, 256),
  1, &_tcn_layers_1_net_net_3_Clip_output_0_weights_array, &_tcn_layers_1_net_net_3_Clip_output_0_weights_array_intq)

/* Tensor #50 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_1_net_net_5_Mul_output_0_output, AI_STATIC,
  50, 0x1,
  AI_SHAPE_INIT(4, 1, 16, 400, 1), AI_STRIDE_INIT(4, 1, 1, 16, 6400),
  1, &_tcn_layers_1_net_net_5_Mul_output_0_output_array, &_tcn_layers_1_net_net_5_Mul_output_0_output_array_intq)

/* Tensor #51 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_1_net_net_5_avg_pool_GlobalAveragePool_output_0_output, AI_STATIC,
  51, 0x1,
  AI_SHAPE_INIT(4, 1, 16, 1, 1), AI_STRIDE_INIT(4, 1, 1, 16, 16),
  1, &_tcn_layers_1_net_net_5_avg_pool_GlobalAveragePool_output_0_output_array, &_tcn_layers_1_net_net_5_avg_pool_GlobalAveragePool_output_0_output_array_intq)

/* Tensor #52 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_1_net_net_5_fc_fc_1_Clip_output_0_output, AI_STATIC,
  52, 0x1,
  AI_SHAPE_INIT(4, 1, 8, 1, 1), AI_STRIDE_INIT(4, 1, 1, 8, 8),
  1, &_tcn_layers_1_net_net_5_fc_fc_1_Clip_output_0_output_array, &_tcn_layers_1_net_net_5_fc_fc_1_Clip_output_0_output_array_intq)

/* Tensor #53 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_1_net_net_5_fc_fc_1_Clip_output_0_scratch0, AI_STATIC,
  53, 0x0,
  AI_SHAPE_INIT(4, 1, 56, 1, 1), AI_STRIDE_INIT(4, 2, 2, 112, 112),
  1, &_tcn_layers_1_net_net_5_fc_fc_1_Clip_output_0_scratch0_array, NULL)

/* Tensor #54 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_1_net_net_5_fc_fc_1_Clip_output_0_weights, AI_STATIC,
  54, 0x1,
  AI_SHAPE_INIT(4, 16, 8, 1, 1), AI_STRIDE_INIT(4, 1, 16, 128, 128),
  1, &_tcn_layers_1_net_net_5_fc_fc_1_Clip_output_0_weights_array, &_tcn_layers_1_net_net_5_fc_fc_1_Clip_output_0_weights_array_intq)

/* Tensor #55 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_1_net_net_5_fc_fc_2_MatMul_output_0_output, AI_STATIC,
  55, 0x1,
  AI_SHAPE_INIT(4, 1, 16, 1, 1), AI_STRIDE_INIT(4, 1, 1, 16, 16),
  1, &_tcn_layers_1_net_net_5_fc_fc_2_MatMul_output_0_output_array, &_tcn_layers_1_net_net_5_fc_fc_2_MatMul_output_0_output_array_intq)

/* Tensor #56 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_1_net_net_5_fc_fc_2_MatMul_output_0_scratch0, AI_STATIC,
  56, 0x0,
  AI_SHAPE_INIT(4, 1, 88, 1, 1), AI_STRIDE_INIT(4, 2, 2, 176, 176),
  1, &_tcn_layers_1_net_net_5_fc_fc_2_MatMul_output_0_scratch0_array, NULL)

/* Tensor #57 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_1_net_net_5_fc_fc_2_MatMul_output_0_weights, AI_STATIC,
  57, 0x1,
  AI_SHAPE_INIT(4, 8, 16, 1, 1), AI_STRIDE_INIT(4, 1, 8, 128, 128),
  1, &_tcn_layers_1_net_net_5_fc_fc_2_MatMul_output_0_weights_array, &_tcn_layers_1_net_net_5_fc_fc_2_MatMul_output_0_weights_array_intq)

/* Tensor #58 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_1_net_net_5_fc_fc_3_HardSigmoid_output_0_output, AI_STATIC,
  58, 0x1,
  AI_SHAPE_INIT(4, 1, 16, 1, 1), AI_STRIDE_INIT(4, 1, 1, 16, 16),
  1, &_tcn_layers_1_net_net_5_fc_fc_3_HardSigmoid_output_0_output_array, &_tcn_layers_1_net_net_5_fc_fc_3_HardSigmoid_output_0_output_array_intq)

/* Tensor #59 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_2_net_net_0_Conv_output_0_0_0__tcn_layers_2_net_net_3_Clip_output_0_conversion_output, AI_STATIC,
  59, 0x1,
  AI_SHAPE_INIT(4, 1, 16, 400, 1), AI_STRIDE_INIT(4, 1, 1, 16, 6400),
  1, &_tcn_layers_2_net_net_0_Conv_output_0_0_0__tcn_layers_2_net_net_3_Clip_output_0_conversion_output_array, &_tcn_layers_2_net_net_0_Conv_output_0_0_0__tcn_layers_2_net_net_3_Clip_output_0_conversion_output_array_intq)

/* Tensor #60 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_2_net_net_0_Conv_output_0_output, AI_STATIC,
  60, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 400, 1), AI_STRIDE_INIT(4, 4, 4, 64, 25600),
  1, &_tcn_layers_2_net_net_0_Conv_output_0_output_array, NULL)

/* Tensor #61 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_2_net_net_0_Conv_output_0_weights, AI_STATIC,
  61, 0x0,
  AI_SHAPE_INIT(4, 1, 7, 1, 16), AI_STRIDE_INIT(4, 1, 16, 16, 16),
  1, &_tcn_layers_2_net_net_0_Conv_output_0_weights_array, NULL)

/* Tensor #62 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_2_net_net_3_Clip_output_0_bias, AI_STATIC,
  62, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 1, 1), AI_STRIDE_INIT(4, 4, 4, 64, 64),
  1, &_tcn_layers_2_net_net_3_Clip_output_0_bias_array, NULL)

/* Tensor #63 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_2_net_net_3_Clip_output_0_output, AI_STATIC,
  63, 0x1,
  AI_SHAPE_INIT(4, 1, 16, 400, 1), AI_STRIDE_INIT(4, 1, 1, 16, 6400),
  1, &_tcn_layers_2_net_net_3_Clip_output_0_output_array, &_tcn_layers_2_net_net_3_Clip_output_0_output_array_intq)

/* Tensor #64 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_2_net_net_3_Clip_output_0_scratch0, AI_STATIC,
  64, 0x0,
  AI_SHAPE_INIT(4, 1, 224, 1, 1), AI_STRIDE_INIT(4, 1, 1, 224, 224),
  1, &_tcn_layers_2_net_net_3_Clip_output_0_scratch0_array, NULL)

/* Tensor #65 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_2_net_net_3_Clip_output_0_weights, AI_STATIC,
  65, 0x1,
  AI_SHAPE_INIT(4, 16, 1, 1, 16), AI_STRIDE_INIT(4, 1, 16, 256, 256),
  1, &_tcn_layers_2_net_net_3_Clip_output_0_weights_array, &_tcn_layers_2_net_net_3_Clip_output_0_weights_array_intq)

/* Tensor #66 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_2_net_net_5_Mul_output_0_output, AI_STATIC,
  66, 0x1,
  AI_SHAPE_INIT(4, 1, 16, 400, 1), AI_STRIDE_INIT(4, 1, 1, 16, 6400),
  1, &_tcn_layers_2_net_net_5_Mul_output_0_output_array, &_tcn_layers_2_net_net_5_Mul_output_0_output_array_intq)

/* Tensor #67 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_2_net_net_5_avg_pool_GlobalAveragePool_output_0_output, AI_STATIC,
  67, 0x1,
  AI_SHAPE_INIT(4, 1, 16, 1, 1), AI_STRIDE_INIT(4, 1, 1, 16, 16),
  1, &_tcn_layers_2_net_net_5_avg_pool_GlobalAveragePool_output_0_output_array, &_tcn_layers_2_net_net_5_avg_pool_GlobalAveragePool_output_0_output_array_intq)

/* Tensor #68 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_2_net_net_5_fc_fc_1_Clip_output_0_output, AI_STATIC,
  68, 0x1,
  AI_SHAPE_INIT(4, 1, 8, 1, 1), AI_STRIDE_INIT(4, 1, 1, 8, 8),
  1, &_tcn_layers_2_net_net_5_fc_fc_1_Clip_output_0_output_array, &_tcn_layers_2_net_net_5_fc_fc_1_Clip_output_0_output_array_intq)

/* Tensor #69 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_2_net_net_5_fc_fc_1_Clip_output_0_scratch0, AI_STATIC,
  69, 0x0,
  AI_SHAPE_INIT(4, 1, 56, 1, 1), AI_STRIDE_INIT(4, 2, 2, 112, 112),
  1, &_tcn_layers_2_net_net_5_fc_fc_1_Clip_output_0_scratch0_array, NULL)

/* Tensor #70 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_2_net_net_5_fc_fc_1_Clip_output_0_weights, AI_STATIC,
  70, 0x1,
  AI_SHAPE_INIT(4, 16, 8, 1, 1), AI_STRIDE_INIT(4, 1, 16, 128, 128),
  1, &_tcn_layers_2_net_net_5_fc_fc_1_Clip_output_0_weights_array, &_tcn_layers_2_net_net_5_fc_fc_1_Clip_output_0_weights_array_intq)

/* Tensor #71 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_2_net_net_5_fc_fc_2_MatMul_output_0_output, AI_STATIC,
  71, 0x1,
  AI_SHAPE_INIT(4, 1, 16, 1, 1), AI_STRIDE_INIT(4, 1, 1, 16, 16),
  1, &_tcn_layers_2_net_net_5_fc_fc_2_MatMul_output_0_output_array, &_tcn_layers_2_net_net_5_fc_fc_2_MatMul_output_0_output_array_intq)

/* Tensor #72 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_2_net_net_5_fc_fc_2_MatMul_output_0_scratch0, AI_STATIC,
  72, 0x0,
  AI_SHAPE_INIT(4, 1, 88, 1, 1), AI_STRIDE_INIT(4, 2, 2, 176, 176),
  1, &_tcn_layers_2_net_net_5_fc_fc_2_MatMul_output_0_scratch0_array, NULL)

/* Tensor #73 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_2_net_net_5_fc_fc_2_MatMul_output_0_weights, AI_STATIC,
  73, 0x1,
  AI_SHAPE_INIT(4, 8, 16, 1, 1), AI_STRIDE_INIT(4, 1, 8, 128, 128),
  1, &_tcn_layers_2_net_net_5_fc_fc_2_MatMul_output_0_weights_array, &_tcn_layers_2_net_net_5_fc_fc_2_MatMul_output_0_weights_array_intq)

/* Tensor #74 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_2_net_net_5_fc_fc_3_HardSigmoid_output_0_output, AI_STATIC,
  74, 0x1,
  AI_SHAPE_INIT(4, 1, 16, 1, 1), AI_STRIDE_INIT(4, 1, 1, 16, 16),
  1, &_tcn_layers_2_net_net_5_fc_fc_3_HardSigmoid_output_0_output_array, &_tcn_layers_2_net_net_5_fc_fc_3_HardSigmoid_output_0_output_array_intq)

/* Tensor #75 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_3_net_net_0_Conv_output_0_0_0__tcn_layers_3_net_net_3_Clip_output_0_conversion_output, AI_STATIC,
  75, 0x1,
  AI_SHAPE_INIT(4, 1, 16, 400, 1), AI_STRIDE_INIT(4, 1, 1, 16, 6400),
  1, &_tcn_layers_3_net_net_0_Conv_output_0_0_0__tcn_layers_3_net_net_3_Clip_output_0_conversion_output_array, &_tcn_layers_3_net_net_0_Conv_output_0_0_0__tcn_layers_3_net_net_3_Clip_output_0_conversion_output_array_intq)

/* Tensor #76 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_3_net_net_0_Conv_output_0_output, AI_STATIC,
  76, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 400, 1), AI_STRIDE_INIT(4, 4, 4, 64, 25600),
  1, &_tcn_layers_3_net_net_0_Conv_output_0_output_array, NULL)

/* Tensor #77 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_3_net_net_0_Conv_output_0_weights, AI_STATIC,
  77, 0x0,
  AI_SHAPE_INIT(4, 1, 7, 1, 16), AI_STRIDE_INIT(4, 1, 16, 16, 16),
  1, &_tcn_layers_3_net_net_0_Conv_output_0_weights_array, NULL)

/* Tensor #78 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_3_net_net_3_Clip_output_0_bias, AI_STATIC,
  78, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 1, 1), AI_STRIDE_INIT(4, 4, 4, 64, 64),
  1, &_tcn_layers_3_net_net_3_Clip_output_0_bias_array, NULL)

/* Tensor #79 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_3_net_net_3_Clip_output_0_output, AI_STATIC,
  79, 0x1,
  AI_SHAPE_INIT(4, 1, 16, 400, 1), AI_STRIDE_INIT(4, 1, 1, 16, 6400),
  1, &_tcn_layers_3_net_net_3_Clip_output_0_output_array, &_tcn_layers_3_net_net_3_Clip_output_0_output_array_intq)

/* Tensor #80 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_3_net_net_3_Clip_output_0_scratch0, AI_STATIC,
  80, 0x0,
  AI_SHAPE_INIT(4, 1, 224, 1, 1), AI_STRIDE_INIT(4, 1, 1, 224, 224),
  1, &_tcn_layers_3_net_net_3_Clip_output_0_scratch0_array, NULL)

/* Tensor #81 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_3_net_net_3_Clip_output_0_weights, AI_STATIC,
  81, 0x1,
  AI_SHAPE_INIT(4, 16, 1, 1, 16), AI_STRIDE_INIT(4, 1, 16, 256, 256),
  1, &_tcn_layers_3_net_net_3_Clip_output_0_weights_array, &_tcn_layers_3_net_net_3_Clip_output_0_weights_array_intq)

/* Tensor #82 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_3_net_net_5_Mul_output_0_output, AI_STATIC,
  82, 0x1,
  AI_SHAPE_INIT(4, 1, 16, 400, 1), AI_STRIDE_INIT(4, 1, 1, 16, 6400),
  1, &_tcn_layers_3_net_net_5_Mul_output_0_output_array, &_tcn_layers_3_net_net_5_Mul_output_0_output_array_intq)

/* Tensor #83 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_3_net_net_5_avg_pool_GlobalAveragePool_output_0_output, AI_STATIC,
  83, 0x1,
  AI_SHAPE_INIT(4, 1, 16, 1, 1), AI_STRIDE_INIT(4, 1, 1, 16, 16),
  1, &_tcn_layers_3_net_net_5_avg_pool_GlobalAveragePool_output_0_output_array, &_tcn_layers_3_net_net_5_avg_pool_GlobalAveragePool_output_0_output_array_intq)

/* Tensor #84 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_3_net_net_5_fc_fc_1_Clip_output_0_output, AI_STATIC,
  84, 0x1,
  AI_SHAPE_INIT(4, 1, 8, 1, 1), AI_STRIDE_INIT(4, 1, 1, 8, 8),
  1, &_tcn_layers_3_net_net_5_fc_fc_1_Clip_output_0_output_array, &_tcn_layers_3_net_net_5_fc_fc_1_Clip_output_0_output_array_intq)

/* Tensor #85 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_3_net_net_5_fc_fc_1_Clip_output_0_scratch0, AI_STATIC,
  85, 0x0,
  AI_SHAPE_INIT(4, 1, 56, 1, 1), AI_STRIDE_INIT(4, 2, 2, 112, 112),
  1, &_tcn_layers_3_net_net_5_fc_fc_1_Clip_output_0_scratch0_array, NULL)

/* Tensor #86 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_3_net_net_5_fc_fc_1_Clip_output_0_weights, AI_STATIC,
  86, 0x1,
  AI_SHAPE_INIT(4, 16, 8, 1, 1), AI_STRIDE_INIT(4, 1, 16, 128, 128),
  1, &_tcn_layers_3_net_net_5_fc_fc_1_Clip_output_0_weights_array, &_tcn_layers_3_net_net_5_fc_fc_1_Clip_output_0_weights_array_intq)

/* Tensor #87 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_3_net_net_5_fc_fc_2_MatMul_output_0_output, AI_STATIC,
  87, 0x1,
  AI_SHAPE_INIT(4, 1, 16, 1, 1), AI_STRIDE_INIT(4, 1, 1, 16, 16),
  1, &_tcn_layers_3_net_net_5_fc_fc_2_MatMul_output_0_output_array, &_tcn_layers_3_net_net_5_fc_fc_2_MatMul_output_0_output_array_intq)

/* Tensor #88 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_3_net_net_5_fc_fc_2_MatMul_output_0_scratch0, AI_STATIC,
  88, 0x0,
  AI_SHAPE_INIT(4, 1, 88, 1, 1), AI_STRIDE_INIT(4, 2, 2, 176, 176),
  1, &_tcn_layers_3_net_net_5_fc_fc_2_MatMul_output_0_scratch0_array, NULL)

/* Tensor #89 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_3_net_net_5_fc_fc_2_MatMul_output_0_weights, AI_STATIC,
  89, 0x1,
  AI_SHAPE_INIT(4, 8, 16, 1, 1), AI_STRIDE_INIT(4, 1, 8, 128, 128),
  1, &_tcn_layers_3_net_net_5_fc_fc_2_MatMul_output_0_weights_array, &_tcn_layers_3_net_net_5_fc_fc_2_MatMul_output_0_weights_array_intq)

/* Tensor #90 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_3_net_net_5_fc_fc_3_HardSigmoid_output_0_output, AI_STATIC,
  90, 0x1,
  AI_SHAPE_INIT(4, 1, 16, 1, 1), AI_STRIDE_INIT(4, 1, 1, 16, 16),
  1, &_tcn_layers_3_net_net_5_fc_fc_3_HardSigmoid_output_0_output_array, &_tcn_layers_3_net_net_5_fc_fc_3_HardSigmoid_output_0_output_array_intq)

/* Tensor #91 */
AI_TENSOR_OBJ_DECLARE(
  input_output, AI_STATIC,
  91, 0x1,
  AI_SHAPE_INIT(4, 1, 1, 1200, 1), AI_STRIDE_INIT(4, 1, 1, 1, 1200),
  1, &input_output_array, &input_output_array_intq)



/**  Layer declarations section  **********************************************/


AI_TENSOR_CHAIN_OBJ_DECLARE(
  _frame_head_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_Add_3_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_frame_head_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_frame_head_Conv_output_0_weights, &_frame_head_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_frame_head_Conv_output_0_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  _frame_head_Conv_output_0_layer, 160,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_integer_SSSA,
  &_frame_head_Conv_output_0_chain,
  NULL, &_frame_head_Conv_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _boundary_head_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_Add_3_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_boundary_head_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_boundary_head_Conv_output_0_weights, &_boundary_head_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_boundary_head_Conv_output_0_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  _boundary_head_Conv_output_0_layer, 161,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_integer_SSSA,
  &_boundary_head_Conv_output_0_chain,
  NULL, &_frame_head_Conv_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _Add_3_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_Add_2_output_0_output, &_tcn_layers_3_net_net_5_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_Add_3_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _Add_3_output_0_layer, 157,
  ELTWISE_INTEGER_TYPE, 0x0, NULL,
  eltwise_integer, forward_eltwise_integer_INT8,
  &_Add_3_output_0_chain,
  NULL, &_boundary_head_Conv_output_0_layer, AI_STATIC, 
  .operation = ai_sum_f32, 
  .buffer_operation = ai_sum_buffer_INT8, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _tcn_layers_3_net_net_5_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_tcn_layers_3_net_net_3_Clip_output_0_output, &_tcn_layers_3_net_net_5_fc_fc_3_HardSigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_3_net_net_5_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _tcn_layers_3_net_net_5_Mul_output_0_layer, 154,
  ELTWISE_INTEGER_TYPE, 0x0, NULL,
  eltwise_integer, forward_eltwise_integer_INT8,
  &_tcn_layers_3_net_net_5_Mul_output_0_chain,
  NULL, &_Add_3_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_INT8, 
)


AI_STATIC_CONST ai_i8 _tcn_layers_3_net_net_5_fc_fc_3_HardSigmoid_output_0_nl_params_data[] = { -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -125, -122, -119, -115, -112, -109, -106, -103, -100, -97, -94, -91, -87, -84, -81, -78, -75, -72, -69, -66, -63, -60, -56, -53, -50, -47, -44, -41, -38, -35, -32, -28, -25, -22, -19, -16, -13, -10, -7, -4, -1, 3, 6, 9, 12, 15, 18, 21, 24, 27, 31, 34, 37, 40, 43, 46, 49, 52, 55, 59, 62, 65, 68, 71, 74, 77, 80, 83, 86, 90, 93, 96, 99, 102, 105, 108, 111, 114, 118, 121, 124, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127 };
AI_ARRAY_OBJ_DECLARE(
    _tcn_layers_3_net_net_5_fc_fc_3_HardSigmoid_output_0_nl_params, AI_ARRAY_FORMAT_S8,
    _tcn_layers_3_net_net_5_fc_fc_3_HardSigmoid_output_0_nl_params_data, _tcn_layers_3_net_net_5_fc_fc_3_HardSigmoid_output_0_nl_params_data, 256, AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(
  _tcn_layers_3_net_net_5_fc_fc_3_HardSigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_3_net_net_5_fc_fc_2_MatMul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_3_net_net_5_fc_fc_3_HardSigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _tcn_layers_3_net_net_5_fc_fc_3_HardSigmoid_output_0_layer, 148,
  NL_TYPE, 0x0, NULL,
  nl, forward_nl_integer,
  &_tcn_layers_3_net_net_5_fc_fc_3_HardSigmoid_output_0_chain,
  NULL, &_tcn_layers_3_net_net_5_Mul_output_0_layer, AI_STATIC, 
  .nl_params = &_tcn_layers_3_net_net_5_fc_fc_3_HardSigmoid_output_0_nl_params, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _tcn_layers_3_net_net_5_fc_fc_2_MatMul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_3_net_net_5_fc_fc_1_Clip_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_3_net_net_5_fc_fc_2_MatMul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_tcn_layers_3_net_net_5_fc_fc_2_MatMul_output_0_weights, &_tcn_layers_0_net_net_0_Conv_output_0_bias),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_3_net_net_5_fc_fc_2_MatMul_output_0_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  _tcn_layers_3_net_net_5_fc_fc_2_MatMul_output_0_layer, 145,
  DENSE_TYPE, 0x0, NULL,
  dense, forward_dense_integer_SSSA_ch,
  &_tcn_layers_3_net_net_5_fc_fc_2_MatMul_output_0_chain,
  NULL, &_tcn_layers_3_net_net_5_fc_fc_3_HardSigmoid_output_0_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _tcn_layers_3_net_net_5_fc_fc_1_Clip_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_3_net_net_5_avg_pool_GlobalAveragePool_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_3_net_net_5_fc_fc_1_Clip_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_tcn_layers_3_net_net_5_fc_fc_1_Clip_output_0_weights, &_tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_bias),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_3_net_net_5_fc_fc_1_Clip_output_0_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  _tcn_layers_3_net_net_5_fc_fc_1_Clip_output_0_layer, 142,
  DENSE_TYPE, 0x0, NULL,
  dense, forward_dense_integer_SSSA_ch,
  &_tcn_layers_3_net_net_5_fc_fc_1_Clip_output_0_chain,
  NULL, &_tcn_layers_3_net_net_5_fc_fc_2_MatMul_output_0_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _tcn_layers_3_net_net_5_avg_pool_GlobalAveragePool_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_3_net_net_3_Clip_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_3_net_net_5_avg_pool_GlobalAveragePool_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _tcn_layers_3_net_net_5_avg_pool_GlobalAveragePool_output_0_layer, 136,
  POOL_TYPE, 0x0, NULL,
  pool, forward_ap_integer_INT8,
  &_tcn_layers_3_net_net_5_avg_pool_GlobalAveragePool_output_0_chain,
  NULL, &_tcn_layers_3_net_net_5_fc_fc_1_Clip_output_0_layer, AI_STATIC, 
  .pool_size = AI_SHAPE_2D_INIT(400, 1), 
  .pool_stride = AI_SHAPE_2D_INIT(400, 1), 
  .pool_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _tcn_layers_3_net_net_3_Clip_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_3_net_net_0_Conv_output_0_0_0__tcn_layers_3_net_net_3_Clip_output_0_conversion_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_3_net_net_3_Clip_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_tcn_layers_3_net_net_3_Clip_output_0_weights, &_tcn_layers_3_net_net_3_Clip_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_3_net_net_3_Clip_output_0_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  _tcn_layers_3_net_net_3_Clip_output_0_layer, 133,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_pw_sssa8_ch,
  &_tcn_layers_3_net_net_3_Clip_output_0_chain,
  NULL, &_tcn_layers_3_net_net_5_avg_pool_GlobalAveragePool_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _tcn_layers_3_net_net_0_Conv_output_0_0_0__tcn_layers_3_net_net_3_Clip_output_0_conversion_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_3_net_net_0_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_3_net_net_0_Conv_output_0_0_0__tcn_layers_3_net_net_3_Clip_output_0_conversion_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _tcn_layers_3_net_net_0_Conv_output_0_0_0__tcn_layers_3_net_net_3_Clip_output_0_conversion_layer, 130,
  NL_TYPE, 0x0, NULL,
  nl, node_convert,
  &_tcn_layers_3_net_net_0_Conv_output_0_0_0__tcn_layers_3_net_net_3_Clip_output_0_conversion_chain,
  NULL, &_tcn_layers_3_net_net_3_Clip_output_0_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _tcn_layers_3_net_net_0_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_Add_2_output_0_0_0__tcn_layers_3_net_net_0_Conv_output_0_conversion_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_3_net_net_0_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_tcn_layers_3_net_net_0_Conv_output_0_weights, &_tcn_layers_1_net_net_0_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _tcn_layers_3_net_net_0_Conv_output_0_layer, 130,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32_group,
  &_tcn_layers_3_net_net_0_Conv_output_0_chain,
  NULL, &_tcn_layers_3_net_net_0_Conv_output_0_0_0__tcn_layers_3_net_net_3_Clip_output_0_conversion_layer, AI_STATIC, 
  .groups = 16, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(8, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 24, 0, 24), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _Add_2_output_0_0_0__tcn_layers_3_net_net_0_Conv_output_0_conversion_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_Add_2_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_Add_2_output_0_0_0__tcn_layers_3_net_net_0_Conv_output_0_conversion_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _Add_2_output_0_0_0__tcn_layers_3_net_net_0_Conv_output_0_conversion_layer, 127,
  NL_TYPE, 0x0, NULL,
  nl, node_convert,
  &_Add_2_output_0_0_0__tcn_layers_3_net_net_0_Conv_output_0_conversion_chain,
  NULL, &_tcn_layers_3_net_net_0_Conv_output_0_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _Add_2_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_Add_1_output_0_output, &_tcn_layers_2_net_net_5_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_Add_2_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _Add_2_output_0_layer, 127,
  ELTWISE_INTEGER_TYPE, 0x0, NULL,
  eltwise_integer, forward_eltwise_integer_INT8,
  &_Add_2_output_0_chain,
  NULL, &_Add_2_output_0_0_0__tcn_layers_3_net_net_0_Conv_output_0_conversion_layer, AI_STATIC, 
  .operation = ai_sum_f32, 
  .buffer_operation = ai_sum_buffer_INT8, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _tcn_layers_2_net_net_5_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_tcn_layers_2_net_net_3_Clip_output_0_output, &_tcn_layers_2_net_net_5_fc_fc_3_HardSigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_2_net_net_5_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _tcn_layers_2_net_net_5_Mul_output_0_layer, 124,
  ELTWISE_INTEGER_TYPE, 0x0, NULL,
  eltwise_integer, forward_eltwise_integer_INT8,
  &_tcn_layers_2_net_net_5_Mul_output_0_chain,
  NULL, &_Add_2_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_INT8, 
)


AI_STATIC_CONST ai_i8 _tcn_layers_2_net_net_5_fc_fc_3_HardSigmoid_output_0_nl_params_data[] = { -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -126, -124, -121, -119, -117, -115, -112, -110, -108, -105, -103, -101, -99, -96, -94, -92, -89, -87, -85, -83, -80, -78, -76, -74, -71, -69, -67, -64, -62, -60, -58, -55, -53, -51, -48, -46, -44, -42, -39, -37, -35, -32, -30, -28, -26, -23, -21, -19, -16, -14, -12, -10, -7, -5, -3, -1, 2, 4, 6, 9, 11, 13, 15, 18, 20, 22, 25, 27, 29, 31, 34, 36, 38, 41, 43, 45, 47, 50, 52, 54, 57, 59, 61, 63, 66, 68, 70, 73, 75, 77, 79, 82, 84, 86, 88, 91, 93, 95, 98, 100, 102, 104, 107, 109, 111, 114, 116, 118, 120, 123, 125, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127 };
AI_ARRAY_OBJ_DECLARE(
    _tcn_layers_2_net_net_5_fc_fc_3_HardSigmoid_output_0_nl_params, AI_ARRAY_FORMAT_S8,
    _tcn_layers_2_net_net_5_fc_fc_3_HardSigmoid_output_0_nl_params_data, _tcn_layers_2_net_net_5_fc_fc_3_HardSigmoid_output_0_nl_params_data, 256, AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(
  _tcn_layers_2_net_net_5_fc_fc_3_HardSigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_2_net_net_5_fc_fc_2_MatMul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_2_net_net_5_fc_fc_3_HardSigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _tcn_layers_2_net_net_5_fc_fc_3_HardSigmoid_output_0_layer, 118,
  NL_TYPE, 0x0, NULL,
  nl, forward_nl_integer,
  &_tcn_layers_2_net_net_5_fc_fc_3_HardSigmoid_output_0_chain,
  NULL, &_tcn_layers_2_net_net_5_Mul_output_0_layer, AI_STATIC, 
  .nl_params = &_tcn_layers_2_net_net_5_fc_fc_3_HardSigmoid_output_0_nl_params, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _tcn_layers_2_net_net_5_fc_fc_2_MatMul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_2_net_net_5_fc_fc_1_Clip_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_2_net_net_5_fc_fc_2_MatMul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_tcn_layers_2_net_net_5_fc_fc_2_MatMul_output_0_weights, &_tcn_layers_0_net_net_0_Conv_output_0_bias),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_2_net_net_5_fc_fc_2_MatMul_output_0_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  _tcn_layers_2_net_net_5_fc_fc_2_MatMul_output_0_layer, 115,
  DENSE_TYPE, 0x0, NULL,
  dense, forward_dense_integer_SSSA_ch,
  &_tcn_layers_2_net_net_5_fc_fc_2_MatMul_output_0_chain,
  NULL, &_tcn_layers_2_net_net_5_fc_fc_3_HardSigmoid_output_0_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _tcn_layers_2_net_net_5_fc_fc_1_Clip_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_2_net_net_5_avg_pool_GlobalAveragePool_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_2_net_net_5_fc_fc_1_Clip_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_tcn_layers_2_net_net_5_fc_fc_1_Clip_output_0_weights, &_tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_bias),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_2_net_net_5_fc_fc_1_Clip_output_0_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  _tcn_layers_2_net_net_5_fc_fc_1_Clip_output_0_layer, 112,
  DENSE_TYPE, 0x0, NULL,
  dense, forward_dense_integer_SSSA_ch,
  &_tcn_layers_2_net_net_5_fc_fc_1_Clip_output_0_chain,
  NULL, &_tcn_layers_2_net_net_5_fc_fc_2_MatMul_output_0_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _tcn_layers_2_net_net_5_avg_pool_GlobalAveragePool_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_2_net_net_3_Clip_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_2_net_net_5_avg_pool_GlobalAveragePool_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _tcn_layers_2_net_net_5_avg_pool_GlobalAveragePool_output_0_layer, 106,
  POOL_TYPE, 0x0, NULL,
  pool, forward_ap_integer_INT8,
  &_tcn_layers_2_net_net_5_avg_pool_GlobalAveragePool_output_0_chain,
  NULL, &_tcn_layers_2_net_net_5_fc_fc_1_Clip_output_0_layer, AI_STATIC, 
  .pool_size = AI_SHAPE_2D_INIT(400, 1), 
  .pool_stride = AI_SHAPE_2D_INIT(400, 1), 
  .pool_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _tcn_layers_2_net_net_3_Clip_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_2_net_net_0_Conv_output_0_0_0__tcn_layers_2_net_net_3_Clip_output_0_conversion_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_2_net_net_3_Clip_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_tcn_layers_2_net_net_3_Clip_output_0_weights, &_tcn_layers_2_net_net_3_Clip_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_2_net_net_3_Clip_output_0_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  _tcn_layers_2_net_net_3_Clip_output_0_layer, 103,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_pw_sssa8_ch,
  &_tcn_layers_2_net_net_3_Clip_output_0_chain,
  NULL, &_tcn_layers_2_net_net_5_avg_pool_GlobalAveragePool_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _tcn_layers_2_net_net_0_Conv_output_0_0_0__tcn_layers_2_net_net_3_Clip_output_0_conversion_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_2_net_net_0_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_2_net_net_0_Conv_output_0_0_0__tcn_layers_2_net_net_3_Clip_output_0_conversion_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _tcn_layers_2_net_net_0_Conv_output_0_0_0__tcn_layers_2_net_net_3_Clip_output_0_conversion_layer, 100,
  NL_TYPE, 0x0, NULL,
  nl, node_convert,
  &_tcn_layers_2_net_net_0_Conv_output_0_0_0__tcn_layers_2_net_net_3_Clip_output_0_conversion_chain,
  NULL, &_tcn_layers_2_net_net_3_Clip_output_0_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _tcn_layers_2_net_net_0_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_Add_1_output_0_0_0__tcn_layers_2_net_net_0_Conv_output_0_conversion_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_2_net_net_0_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_tcn_layers_2_net_net_0_Conv_output_0_weights, &_tcn_layers_1_net_net_0_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _tcn_layers_2_net_net_0_Conv_output_0_layer, 100,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32_group,
  &_tcn_layers_2_net_net_0_Conv_output_0_chain,
  NULL, &_tcn_layers_2_net_net_0_Conv_output_0_0_0__tcn_layers_2_net_net_3_Clip_output_0_conversion_layer, AI_STATIC, 
  .groups = 16, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(4, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 12, 0, 12), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _Add_1_output_0_0_0__tcn_layers_2_net_net_0_Conv_output_0_conversion_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_Add_1_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_Add_1_output_0_0_0__tcn_layers_2_net_net_0_Conv_output_0_conversion_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _Add_1_output_0_0_0__tcn_layers_2_net_net_0_Conv_output_0_conversion_layer, 97,
  NL_TYPE, 0x0, NULL,
  nl, node_convert,
  &_Add_1_output_0_0_0__tcn_layers_2_net_net_0_Conv_output_0_conversion_chain,
  NULL, &_tcn_layers_2_net_net_0_Conv_output_0_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _Add_1_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_Add_output_0_output, &_tcn_layers_1_net_net_5_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_Add_1_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _Add_1_output_0_layer, 97,
  ELTWISE_INTEGER_TYPE, 0x0, NULL,
  eltwise_integer, forward_eltwise_integer_INT8,
  &_Add_1_output_0_chain,
  NULL, &_Add_1_output_0_0_0__tcn_layers_2_net_net_0_Conv_output_0_conversion_layer, AI_STATIC, 
  .operation = ai_sum_f32, 
  .buffer_operation = ai_sum_buffer_INT8, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _tcn_layers_1_net_net_5_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_tcn_layers_1_net_net_3_Clip_output_0_output, &_tcn_layers_1_net_net_5_fc_fc_3_HardSigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_1_net_net_5_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _tcn_layers_1_net_net_5_Mul_output_0_layer, 94,
  ELTWISE_INTEGER_TYPE, 0x0, NULL,
  eltwise_integer, forward_eltwise_integer_INT8,
  &_tcn_layers_1_net_net_5_Mul_output_0_chain,
  NULL, &_Add_1_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_INT8, 
)


AI_STATIC_CONST ai_i8 _tcn_layers_1_net_net_5_fc_fc_3_HardSigmoid_output_0_nl_params_data[] = { -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -126, -124, -122, -120, -118, -116, -114, -112, -109, -107, -105, -103, -101, -99, -97, -95, -93, -91, -88, -86, -84, -82, -80, -78, -76, -74, -72, -70, -68, -65, -63, -61, -59, -57, -55, -53, -51, -49, -47, -44, -42, -40, -38, -36, -34, -32, -30, -28, -26, -24, -21, -19, -17, -15, -13, -11, -9, -7, -5, -3, -1, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43, 46, 48, 50, 52, 54, 56, 58, 60, 62, 64, 67, 69, 71, 73, 75, 77, 79, 81, 83, 85, 87, 90, 92, 94, 96, 98, 100, 102, 104, 106, 108, 111, 113, 115, 117, 119, 121, 123, 125, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127 };
AI_ARRAY_OBJ_DECLARE(
    _tcn_layers_1_net_net_5_fc_fc_3_HardSigmoid_output_0_nl_params, AI_ARRAY_FORMAT_S8,
    _tcn_layers_1_net_net_5_fc_fc_3_HardSigmoid_output_0_nl_params_data, _tcn_layers_1_net_net_5_fc_fc_3_HardSigmoid_output_0_nl_params_data, 256, AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(
  _tcn_layers_1_net_net_5_fc_fc_3_HardSigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_1_net_net_5_fc_fc_2_MatMul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_1_net_net_5_fc_fc_3_HardSigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _tcn_layers_1_net_net_5_fc_fc_3_HardSigmoid_output_0_layer, 88,
  NL_TYPE, 0x0, NULL,
  nl, forward_nl_integer,
  &_tcn_layers_1_net_net_5_fc_fc_3_HardSigmoid_output_0_chain,
  NULL, &_tcn_layers_1_net_net_5_Mul_output_0_layer, AI_STATIC, 
  .nl_params = &_tcn_layers_1_net_net_5_fc_fc_3_HardSigmoid_output_0_nl_params, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _tcn_layers_1_net_net_5_fc_fc_2_MatMul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_1_net_net_5_fc_fc_1_Clip_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_1_net_net_5_fc_fc_2_MatMul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_tcn_layers_1_net_net_5_fc_fc_2_MatMul_output_0_weights, &_tcn_layers_0_net_net_0_Conv_output_0_bias),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_1_net_net_5_fc_fc_2_MatMul_output_0_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  _tcn_layers_1_net_net_5_fc_fc_2_MatMul_output_0_layer, 85,
  DENSE_TYPE, 0x0, NULL,
  dense, forward_dense_integer_SSSA_ch,
  &_tcn_layers_1_net_net_5_fc_fc_2_MatMul_output_0_chain,
  NULL, &_tcn_layers_1_net_net_5_fc_fc_3_HardSigmoid_output_0_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _tcn_layers_1_net_net_5_fc_fc_1_Clip_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_1_net_net_5_avg_pool_GlobalAveragePool_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_1_net_net_5_fc_fc_1_Clip_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_tcn_layers_1_net_net_5_fc_fc_1_Clip_output_0_weights, &_tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_bias),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_1_net_net_5_fc_fc_1_Clip_output_0_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  _tcn_layers_1_net_net_5_fc_fc_1_Clip_output_0_layer, 82,
  DENSE_TYPE, 0x0, NULL,
  dense, forward_dense_integer_SSSA_ch,
  &_tcn_layers_1_net_net_5_fc_fc_1_Clip_output_0_chain,
  NULL, &_tcn_layers_1_net_net_5_fc_fc_2_MatMul_output_0_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _tcn_layers_1_net_net_5_avg_pool_GlobalAveragePool_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_1_net_net_3_Clip_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_1_net_net_5_avg_pool_GlobalAveragePool_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _tcn_layers_1_net_net_5_avg_pool_GlobalAveragePool_output_0_layer, 76,
  POOL_TYPE, 0x0, NULL,
  pool, forward_ap_integer_INT8,
  &_tcn_layers_1_net_net_5_avg_pool_GlobalAveragePool_output_0_chain,
  NULL, &_tcn_layers_1_net_net_5_fc_fc_1_Clip_output_0_layer, AI_STATIC, 
  .pool_size = AI_SHAPE_2D_INIT(400, 1), 
  .pool_stride = AI_SHAPE_2D_INIT(400, 1), 
  .pool_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _tcn_layers_1_net_net_3_Clip_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_1_net_net_0_Conv_output_0_0_0__tcn_layers_1_net_net_3_Clip_output_0_conversion_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_1_net_net_3_Clip_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_tcn_layers_1_net_net_3_Clip_output_0_weights, &_tcn_layers_1_net_net_3_Clip_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_1_net_net_3_Clip_output_0_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  _tcn_layers_1_net_net_3_Clip_output_0_layer, 73,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_pw_sssa8_ch,
  &_tcn_layers_1_net_net_3_Clip_output_0_chain,
  NULL, &_tcn_layers_1_net_net_5_avg_pool_GlobalAveragePool_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _tcn_layers_1_net_net_0_Conv_output_0_0_0__tcn_layers_1_net_net_3_Clip_output_0_conversion_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_1_net_net_0_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_1_net_net_0_Conv_output_0_0_0__tcn_layers_1_net_net_3_Clip_output_0_conversion_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _tcn_layers_1_net_net_0_Conv_output_0_0_0__tcn_layers_1_net_net_3_Clip_output_0_conversion_layer, 70,
  NL_TYPE, 0x0, NULL,
  nl, node_convert,
  &_tcn_layers_1_net_net_0_Conv_output_0_0_0__tcn_layers_1_net_net_3_Clip_output_0_conversion_chain,
  NULL, &_tcn_layers_1_net_net_3_Clip_output_0_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _tcn_layers_1_net_net_0_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_Add_output_0_0_0__tcn_layers_1_net_net_0_Conv_output_0_conversion_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_1_net_net_0_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_tcn_layers_1_net_net_0_Conv_output_0_weights, &_tcn_layers_1_net_net_0_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _tcn_layers_1_net_net_0_Conv_output_0_layer, 70,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32_group,
  &_tcn_layers_1_net_net_0_Conv_output_0_chain,
  NULL, &_tcn_layers_1_net_net_0_Conv_output_0_0_0__tcn_layers_1_net_net_3_Clip_output_0_conversion_layer, AI_STATIC, 
  .groups = 16, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(2, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 6, 0, 6), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _Add_output_0_0_0__tcn_layers_1_net_net_0_Conv_output_0_conversion_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_Add_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_Add_output_0_0_0__tcn_layers_1_net_net_0_Conv_output_0_conversion_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _Add_output_0_0_0__tcn_layers_1_net_net_0_Conv_output_0_conversion_layer, 67,
  NL_TYPE, 0x0, NULL,
  nl, node_convert,
  &_Add_output_0_0_0__tcn_layers_1_net_net_0_Conv_output_0_conversion_chain,
  NULL, &_tcn_layers_1_net_net_0_Conv_output_0_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _Add_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_expand_expand_2_Clip_output_0_output, &_tcn_layers_0_net_net_5_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_Add_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _Add_output_0_layer, 67,
  ELTWISE_INTEGER_TYPE, 0x0, NULL,
  eltwise_integer, forward_eltwise_integer_INT8,
  &_Add_output_0_chain,
  NULL, &_Add_output_0_0_0__tcn_layers_1_net_net_0_Conv_output_0_conversion_layer, AI_STATIC, 
  .operation = ai_sum_f32, 
  .buffer_operation = ai_sum_buffer_INT8, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _tcn_layers_0_net_net_5_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_tcn_layers_0_net_net_3_Clip_output_0_output, &_tcn_layers_0_net_net_5_fc_fc_3_HardSigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_0_net_net_5_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _tcn_layers_0_net_net_5_Mul_output_0_layer, 64,
  ELTWISE_INTEGER_TYPE, 0x0, NULL,
  eltwise_integer, forward_eltwise_integer_INT8,
  &_tcn_layers_0_net_net_5_Mul_output_0_chain,
  NULL, &_Add_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_INT8, 
)


AI_STATIC_CONST ai_i8 _tcn_layers_0_net_net_5_fc_fc_3_HardSigmoid_output_0_nl_params_data[] = { -92, -90, -89, -87, -86, -84, -83, -81, -80, -78, -77, -75, -74, -72, -71, -69, -67, -66, -64, -63, -61, -60, -58, -57, -55, -54, -52, -51, -49, -48, -46, -45, -43, -42, -40, -39, -37, -36, -34, -32, -31, -29, -28, -26, -25, -23, -22, -20, -19, -17, -16, -14, -13, -11, -10, -8, -7, -5, -4, -2, -1, 1, 3, 4, 6, 7, 9, 10, 12, 13, 15, 16, 18, 19, 21, 22, 24, 25, 27, 28, 30, 31, 33, 35, 36, 38, 39, 41, 42, 44, 45, 47, 48, 50, 51, 53, 54, 56, 57, 59, 60, 62, 63, 65, 66, 68, 70, 71, 73, 74, 76, 77, 79, 80, 82, 83, 85, 86, 88, 89, 91, 92, 94, 95, 97, 98, 100, 101, 103, 105, 106, 108, 109, 111, 112, 114, 115, 117, 118, 120, 121, 123, 124, 126, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127 };
AI_ARRAY_OBJ_DECLARE(
    _tcn_layers_0_net_net_5_fc_fc_3_HardSigmoid_output_0_nl_params, AI_ARRAY_FORMAT_S8,
    _tcn_layers_0_net_net_5_fc_fc_3_HardSigmoid_output_0_nl_params_data, _tcn_layers_0_net_net_5_fc_fc_3_HardSigmoid_output_0_nl_params_data, 256, AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(
  _tcn_layers_0_net_net_5_fc_fc_3_HardSigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_0_net_net_5_fc_fc_2_MatMul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_0_net_net_5_fc_fc_3_HardSigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _tcn_layers_0_net_net_5_fc_fc_3_HardSigmoid_output_0_layer, 58,
  NL_TYPE, 0x0, NULL,
  nl, forward_nl_integer,
  &_tcn_layers_0_net_net_5_fc_fc_3_HardSigmoid_output_0_chain,
  NULL, &_tcn_layers_0_net_net_5_Mul_output_0_layer, AI_STATIC, 
  .nl_params = &_tcn_layers_0_net_net_5_fc_fc_3_HardSigmoid_output_0_nl_params, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _tcn_layers_0_net_net_5_fc_fc_2_MatMul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_0_net_net_5_fc_fc_2_MatMul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_tcn_layers_0_net_net_5_fc_fc_2_MatMul_output_0_weights, &_tcn_layers_0_net_net_0_Conv_output_0_bias),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_0_net_net_5_fc_fc_2_MatMul_output_0_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  _tcn_layers_0_net_net_5_fc_fc_2_MatMul_output_0_layer, 55,
  DENSE_TYPE, 0x0, NULL,
  dense, forward_dense_integer_SSSA_ch,
  &_tcn_layers_0_net_net_5_fc_fc_2_MatMul_output_0_chain,
  NULL, &_tcn_layers_0_net_net_5_fc_fc_3_HardSigmoid_output_0_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_0_net_net_5_avg_pool_GlobalAveragePool_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_weights, &_tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_bias),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  _tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_layer, 52,
  DENSE_TYPE, 0x0, NULL,
  dense, forward_dense_integer_SSSA_ch,
  &_tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_chain,
  NULL, &_tcn_layers_0_net_net_5_fc_fc_2_MatMul_output_0_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _tcn_layers_0_net_net_5_avg_pool_GlobalAveragePool_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_0_net_net_3_Clip_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_0_net_net_5_avg_pool_GlobalAveragePool_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _tcn_layers_0_net_net_5_avg_pool_GlobalAveragePool_output_0_layer, 46,
  POOL_TYPE, 0x0, NULL,
  pool, forward_ap_integer_INT8,
  &_tcn_layers_0_net_net_5_avg_pool_GlobalAveragePool_output_0_chain,
  NULL, &_tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_layer, AI_STATIC, 
  .pool_size = AI_SHAPE_2D_INIT(400, 1), 
  .pool_stride = AI_SHAPE_2D_INIT(400, 1), 
  .pool_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _tcn_layers_0_net_net_3_Clip_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_0_net_net_0_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_0_net_net_3_Clip_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_tcn_layers_0_net_net_3_Clip_output_0_weights, &_tcn_layers_0_net_net_3_Clip_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_0_net_net_3_Clip_output_0_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  _tcn_layers_0_net_net_3_Clip_output_0_layer, 43,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_pw_sssa8_ch,
  &_tcn_layers_0_net_net_3_Clip_output_0_chain,
  NULL, &_tcn_layers_0_net_net_5_avg_pool_GlobalAveragePool_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _tcn_layers_0_net_net_0_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_expand_expand_2_Clip_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_0_net_net_0_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_tcn_layers_0_net_net_0_Conv_output_0_weights, &_tcn_layers_0_net_net_0_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_0_net_net_0_Conv_output_0_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  _tcn_layers_0_net_net_0_Conv_output_0_layer, 40,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_dw_sssa8_ch,
  &_tcn_layers_0_net_net_0_Conv_output_0_chain,
  NULL, &_tcn_layers_0_net_net_3_Clip_output_0_layer, AI_STATIC, 
  .groups = 16, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 3, 0, 3), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _expand_expand_2_Clip_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_frontend_frontend_2_Clip_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_expand_expand_2_Clip_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_expand_expand_2_Clip_output_0_weights, &_expand_expand_2_Clip_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_expand_expand_2_Clip_output_0_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  _expand_expand_2_Clip_output_0_layer, 37,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_pw_sssa8_ch,
  &_expand_expand_2_Clip_output_0_chain,
  NULL, &_tcn_layers_0_net_net_0_Conv_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _frontend_frontend_2_Clip_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &input_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_frontend_frontend_2_Clip_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_frontend_frontend_2_Clip_output_0_weights, &_frontend_frontend_2_Clip_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_frontend_frontend_2_Clip_output_0_scratch0, &_frontend_frontend_2_Clip_output_0_scratch1)
)

AI_LAYER_OBJ_DECLARE(
  _frontend_frontend_2_Clip_output_0_layer, 34,
  OPTIMIZED_CONV2D_TYPE, 0x0, NULL,
  conv2d_nl_pool, forward_conv2d_sssa8_ch_nl_pool,
  &_frontend_frontend_2_Clip_output_0_chain,
  NULL, &_expand_expand_2_Clip_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 11, 0, 11), 
  .pool_size = AI_SHAPE_2D_INIT(6, 1), 
  .pool_stride = AI_SHAPE_2D_INIT(3, 1), 
  .pool_pad = AI_SHAPE_INIT(4, 0, 2, 0, 2), 
  .pool_func = AI_HANDLE_PTR(pool_func_ap_array_integer_INT8), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)


#if (AI_TOOLS_API_VERSION < AI_TOOLS_API_VERSION_1_5)

AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 4200, 1, 1),
    4200, NULL, NULL),
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 57600, 1, 1),
    57600, NULL, NULL),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK_IN_NUM, &input_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK_OUT_NUM, &_boundary_head_Conv_output_0_output, &_frame_head_Conv_output_0_output),
  &_frontend_frontend_2_Clip_output_0_layer, 0x1f344ed7, NULL)

#else

AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_ARRAY_OBJ_INIT_STATIC(
  	AI_FLAG_NONE, 1,
    AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
      AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 4200, 1, 1),
      4200, NULL, NULL)
  ),
  AI_BUFFER_ARRAY_OBJ_INIT_STATIC(
  	AI_FLAG_NONE, 1,
    AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
      AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 57600, 1, 1),
      57600, NULL, NULL)
  ),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK_IN_NUM, &input_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK_OUT_NUM, &_boundary_head_Conv_output_0_output, &_frame_head_Conv_output_0_output),
  &_frontend_frontend_2_Clip_output_0_layer, 0x1f344ed7, NULL)

#endif	/*(AI_TOOLS_API_VERSION < AI_TOOLS_API_VERSION_1_5)*/



/******************************************************************************/
AI_DECLARE_STATIC
ai_bool network_configure_activations(
  ai_network* net_ctx, const ai_network_params* params)
{
  AI_ASSERT(net_ctx)

  if (ai_platform_get_activations_map(g_network_activations_map, 1, params)) {
    /* Updating activations (byte) offsets */
    
    input_output_array.data = AI_PTR(g_network_activations_map[0] + 25660);
    input_output_array.data_start = AI_PTR(g_network_activations_map[0] + 25660);
    _frontend_frontend_2_Clip_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 26860);
    _frontend_frontend_2_Clip_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 26860);
    _frontend_frontend_2_Clip_output_0_scratch1_array.data = AI_PTR(g_network_activations_map[0] + 27204);
    _frontend_frontend_2_Clip_output_0_scratch1_array.data_start = AI_PTR(g_network_activations_map[0] + 27204);
    _frontend_frontend_2_Clip_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 32000);
    _frontend_frontend_2_Clip_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 32000);
    _expand_expand_2_Clip_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 33600);
    _expand_expand_2_Clip_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 33600);
    _expand_expand_2_Clip_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 25600);
    _expand_expand_2_Clip_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 25600);
    _tcn_layers_0_net_net_0_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 25100);
    _tcn_layers_0_net_net_0_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 25100);
    _tcn_layers_0_net_net_0_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 32000);
    _tcn_layers_0_net_net_0_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 32000);
    _tcn_layers_0_net_net_3_Clip_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 38400);
    _tcn_layers_0_net_net_3_Clip_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 38400);
    _tcn_layers_0_net_net_3_Clip_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 19200);
    _tcn_layers_0_net_net_3_Clip_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 19200);
    _tcn_layers_0_net_net_5_avg_pool_GlobalAveragePool_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 38608);
    _tcn_layers_0_net_net_5_avg_pool_GlobalAveragePool_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 38608);
    _tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 32000);
    _tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 32000);
    _tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 32112);
    _tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 32112);
    _tcn_layers_0_net_net_5_fc_fc_2_MatMul_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 32120);
    _tcn_layers_0_net_net_5_fc_fc_2_MatMul_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 32120);
    _tcn_layers_0_net_net_5_fc_fc_2_MatMul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 38608);
    _tcn_layers_0_net_net_5_fc_fc_2_MatMul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 38608);
    _tcn_layers_0_net_net_5_fc_fc_3_HardSigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 19184);
    _tcn_layers_0_net_net_5_fc_fc_3_HardSigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 19184);
    _tcn_layers_0_net_net_5_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 19200);
    _tcn_layers_0_net_net_5_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 19200);
    _Add_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 25600);
    _Add_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 25600);
    _Add_output_0_0_0__tcn_layers_1_net_net_0_Conv_output_0_conversion_output_array.data = AI_PTR(g_network_activations_map[0] + 32000);
    _Add_output_0_0_0__tcn_layers_1_net_net_0_Conv_output_0_conversion_output_array.data_start = AI_PTR(g_network_activations_map[0] + 32000);
    _tcn_layers_1_net_net_0_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 0);
    _tcn_layers_1_net_net_0_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    _tcn_layers_1_net_net_0_Conv_output_0_0_0__tcn_layers_1_net_net_3_Clip_output_0_conversion_output_array.data = AI_PTR(g_network_activations_map[0] + 32000);
    _tcn_layers_1_net_net_0_Conv_output_0_0_0__tcn_layers_1_net_net_3_Clip_output_0_conversion_output_array.data_start = AI_PTR(g_network_activations_map[0] + 32000);
    _tcn_layers_1_net_net_3_Clip_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 0);
    _tcn_layers_1_net_net_3_Clip_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    _tcn_layers_1_net_net_3_Clip_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 224);
    _tcn_layers_1_net_net_3_Clip_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 224);
    _tcn_layers_1_net_net_5_avg_pool_GlobalAveragePool_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 0);
    _tcn_layers_1_net_net_5_avg_pool_GlobalAveragePool_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    _tcn_layers_1_net_net_5_fc_fc_1_Clip_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 16);
    _tcn_layers_1_net_net_5_fc_fc_1_Clip_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 16);
    _tcn_layers_1_net_net_5_fc_fc_1_Clip_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 128);
    _tcn_layers_1_net_net_5_fc_fc_1_Clip_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 128);
    _tcn_layers_1_net_net_5_fc_fc_2_MatMul_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 6624);
    _tcn_layers_1_net_net_5_fc_fc_2_MatMul_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 6624);
    _tcn_layers_1_net_net_5_fc_fc_2_MatMul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 0);
    _tcn_layers_1_net_net_5_fc_fc_2_MatMul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    _tcn_layers_1_net_net_5_fc_fc_3_HardSigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 16);
    _tcn_layers_1_net_net_5_fc_fc_3_HardSigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 16);
    _tcn_layers_1_net_net_5_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 6624);
    _tcn_layers_1_net_net_5_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 6624);
    _Add_1_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 0);
    _Add_1_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    _Add_1_output_0_0_0__tcn_layers_2_net_net_0_Conv_output_0_conversion_output_array.data = AI_PTR(g_network_activations_map[0] + 6400);
    _Add_1_output_0_0_0__tcn_layers_2_net_net_0_Conv_output_0_conversion_output_array.data_start = AI_PTR(g_network_activations_map[0] + 6400);
    _tcn_layers_2_net_net_0_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 32000);
    _tcn_layers_2_net_net_0_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 32000);
    _tcn_layers_2_net_net_0_Conv_output_0_0_0__tcn_layers_2_net_net_3_Clip_output_0_conversion_output_array.data = AI_PTR(g_network_activations_map[0] + 6400);
    _tcn_layers_2_net_net_0_Conv_output_0_0_0__tcn_layers_2_net_net_3_Clip_output_0_conversion_output_array.data_start = AI_PTR(g_network_activations_map[0] + 6400);
    _tcn_layers_2_net_net_3_Clip_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 12800);
    _tcn_layers_2_net_net_3_Clip_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 12800);
    _tcn_layers_2_net_net_3_Clip_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 13024);
    _tcn_layers_2_net_net_3_Clip_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 13024);
    _tcn_layers_2_net_net_5_avg_pool_GlobalAveragePool_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 6400);
    _tcn_layers_2_net_net_5_avg_pool_GlobalAveragePool_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 6400);
    _tcn_layers_2_net_net_5_fc_fc_1_Clip_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 6416);
    _tcn_layers_2_net_net_5_fc_fc_1_Clip_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 6416);
    _tcn_layers_2_net_net_5_fc_fc_1_Clip_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 6528);
    _tcn_layers_2_net_net_5_fc_fc_1_Clip_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 6528);
    _tcn_layers_2_net_net_5_fc_fc_2_MatMul_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 6536);
    _tcn_layers_2_net_net_5_fc_fc_2_MatMul_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 6536);
    _tcn_layers_2_net_net_5_fc_fc_2_MatMul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 6400);
    _tcn_layers_2_net_net_5_fc_fc_2_MatMul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 6400);
    _tcn_layers_2_net_net_5_fc_fc_3_HardSigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 6416);
    _tcn_layers_2_net_net_5_fc_fc_3_HardSigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 6416);
    _tcn_layers_2_net_net_5_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 6432);
    _tcn_layers_2_net_net_5_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 6432);
    _Add_2_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 51200);
    _Add_2_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 51200);
    _Add_2_output_0_0_0__tcn_layers_3_net_net_0_Conv_output_0_conversion_output_array.data = AI_PTR(g_network_activations_map[0] + 0);
    _Add_2_output_0_0_0__tcn_layers_3_net_net_0_Conv_output_0_conversion_output_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    _tcn_layers_3_net_net_0_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 25600);
    _tcn_layers_3_net_net_0_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 25600);
    _tcn_layers_3_net_net_0_Conv_output_0_0_0__tcn_layers_3_net_net_3_Clip_output_0_conversion_output_array.data = AI_PTR(g_network_activations_map[0] + 0);
    _tcn_layers_3_net_net_0_Conv_output_0_0_0__tcn_layers_3_net_net_3_Clip_output_0_conversion_output_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    _tcn_layers_3_net_net_3_Clip_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 6400);
    _tcn_layers_3_net_net_3_Clip_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 6400);
    _tcn_layers_3_net_net_3_Clip_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 6624);
    _tcn_layers_3_net_net_3_Clip_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 6624);
    _tcn_layers_3_net_net_5_avg_pool_GlobalAveragePool_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 0);
    _tcn_layers_3_net_net_5_avg_pool_GlobalAveragePool_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    _tcn_layers_3_net_net_5_fc_fc_1_Clip_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 16);
    _tcn_layers_3_net_net_5_fc_fc_1_Clip_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 16);
    _tcn_layers_3_net_net_5_fc_fc_1_Clip_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 128);
    _tcn_layers_3_net_net_5_fc_fc_1_Clip_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 128);
    _tcn_layers_3_net_net_5_fc_fc_2_MatMul_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 136);
    _tcn_layers_3_net_net_5_fc_fc_2_MatMul_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 136);
    _tcn_layers_3_net_net_5_fc_fc_2_MatMul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 0);
    _tcn_layers_3_net_net_5_fc_fc_2_MatMul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    _tcn_layers_3_net_net_5_fc_fc_3_HardSigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 16);
    _tcn_layers_3_net_net_5_fc_fc_3_HardSigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 16);
    _tcn_layers_3_net_net_5_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 32);
    _tcn_layers_3_net_net_5_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 32);
    _Add_3_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 6432);
    _Add_3_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 6432);
    _boundary_head_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 0);
    _boundary_head_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    _boundary_head_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 64);
    _boundary_head_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 64);
    _frame_head_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 0);
    _frame_head_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    _frame_head_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 464);
    _frame_head_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 464);
    return true;
  }
  AI_ERROR_TRAP(net_ctx, INIT_FAILED, NETWORK_ACTIVATIONS);
  return false;
}




/******************************************************************************/
AI_DECLARE_STATIC
ai_bool network_configure_weights(
  ai_network* net_ctx, const ai_network_params* params)
{
  AI_ASSERT(net_ctx)

  if (ai_platform_get_weights_map(g_network_weights_map, 1, params)) {
    /* Updating weights (byte) offsets */
    
    _frontend_frontend_2_Clip_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _frontend_frontend_2_Clip_output_0_weights_array.data = AI_PTR(g_network_weights_map[0] + 0);
    _frontend_frontend_2_Clip_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 0);
    _frontend_frontend_2_Clip_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _frontend_frontend_2_Clip_output_0_bias_array.data = AI_PTR(g_network_weights_map[0] + 96);
    _frontend_frontend_2_Clip_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 96);
    _expand_expand_2_Clip_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _expand_expand_2_Clip_output_0_weights_array.data = AI_PTR(g_network_weights_map[0] + 112);
    _expand_expand_2_Clip_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 112);
    _expand_expand_2_Clip_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _expand_expand_2_Clip_output_0_bias_array.data = AI_PTR(g_network_weights_map[0] + 176);
    _expand_expand_2_Clip_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 176);
    _tcn_layers_0_net_net_0_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _tcn_layers_0_net_net_0_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[0] + 240);
    _tcn_layers_0_net_net_0_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 240);
    _tcn_layers_0_net_net_0_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _tcn_layers_0_net_net_0_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[0] + 352);
    _tcn_layers_0_net_net_0_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 352);
    _tcn_layers_0_net_net_3_Clip_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _tcn_layers_0_net_net_3_Clip_output_0_weights_array.data = AI_PTR(g_network_weights_map[0] + 416);
    _tcn_layers_0_net_net_3_Clip_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 416);
    _tcn_layers_0_net_net_3_Clip_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _tcn_layers_0_net_net_3_Clip_output_0_bias_array.data = AI_PTR(g_network_weights_map[0] + 672);
    _tcn_layers_0_net_net_3_Clip_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 672);
    _tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_weights_array.data = AI_PTR(g_network_weights_map[0] + 736);
    _tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 736);
    _tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_bias_array.data = AI_PTR(g_network_weights_map[0] + 864);
    _tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 864);
    _tcn_layers_0_net_net_5_fc_fc_2_MatMul_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _tcn_layers_0_net_net_5_fc_fc_2_MatMul_output_0_weights_array.data = AI_PTR(g_network_weights_map[0] + 896);
    _tcn_layers_0_net_net_5_fc_fc_2_MatMul_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 896);
    _tcn_layers_1_net_net_0_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _tcn_layers_1_net_net_0_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[0] + 1024);
    _tcn_layers_1_net_net_0_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 1024);
    _tcn_layers_1_net_net_0_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _tcn_layers_1_net_net_0_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[0] + 1472);
    _tcn_layers_1_net_net_0_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 1472);
    _tcn_layers_1_net_net_3_Clip_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _tcn_layers_1_net_net_3_Clip_output_0_weights_array.data = AI_PTR(g_network_weights_map[0] + 1536);
    _tcn_layers_1_net_net_3_Clip_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 1536);
    _tcn_layers_1_net_net_3_Clip_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _tcn_layers_1_net_net_3_Clip_output_0_bias_array.data = AI_PTR(g_network_weights_map[0] + 1792);
    _tcn_layers_1_net_net_3_Clip_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 1792);
    _tcn_layers_1_net_net_5_fc_fc_1_Clip_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _tcn_layers_1_net_net_5_fc_fc_1_Clip_output_0_weights_array.data = AI_PTR(g_network_weights_map[0] + 1856);
    _tcn_layers_1_net_net_5_fc_fc_1_Clip_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 1856);
    _tcn_layers_1_net_net_5_fc_fc_2_MatMul_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _tcn_layers_1_net_net_5_fc_fc_2_MatMul_output_0_weights_array.data = AI_PTR(g_network_weights_map[0] + 1984);
    _tcn_layers_1_net_net_5_fc_fc_2_MatMul_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 1984);
    _tcn_layers_2_net_net_0_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _tcn_layers_2_net_net_0_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[0] + 2112);
    _tcn_layers_2_net_net_0_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 2112);
    _tcn_layers_2_net_net_3_Clip_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _tcn_layers_2_net_net_3_Clip_output_0_weights_array.data = AI_PTR(g_network_weights_map[0] + 2560);
    _tcn_layers_2_net_net_3_Clip_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 2560);
    _tcn_layers_2_net_net_3_Clip_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _tcn_layers_2_net_net_3_Clip_output_0_bias_array.data = AI_PTR(g_network_weights_map[0] + 2816);
    _tcn_layers_2_net_net_3_Clip_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 2816);
    _tcn_layers_2_net_net_5_fc_fc_1_Clip_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _tcn_layers_2_net_net_5_fc_fc_1_Clip_output_0_weights_array.data = AI_PTR(g_network_weights_map[0] + 2880);
    _tcn_layers_2_net_net_5_fc_fc_1_Clip_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 2880);
    _tcn_layers_2_net_net_5_fc_fc_2_MatMul_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _tcn_layers_2_net_net_5_fc_fc_2_MatMul_output_0_weights_array.data = AI_PTR(g_network_weights_map[0] + 3008);
    _tcn_layers_2_net_net_5_fc_fc_2_MatMul_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 3008);
    _tcn_layers_3_net_net_0_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _tcn_layers_3_net_net_0_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[0] + 3136);
    _tcn_layers_3_net_net_0_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 3136);
    _tcn_layers_3_net_net_3_Clip_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _tcn_layers_3_net_net_3_Clip_output_0_weights_array.data = AI_PTR(g_network_weights_map[0] + 3584);
    _tcn_layers_3_net_net_3_Clip_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 3584);
    _tcn_layers_3_net_net_3_Clip_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _tcn_layers_3_net_net_3_Clip_output_0_bias_array.data = AI_PTR(g_network_weights_map[0] + 3840);
    _tcn_layers_3_net_net_3_Clip_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 3840);
    _tcn_layers_3_net_net_5_fc_fc_1_Clip_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _tcn_layers_3_net_net_5_fc_fc_1_Clip_output_0_weights_array.data = AI_PTR(g_network_weights_map[0] + 3904);
    _tcn_layers_3_net_net_5_fc_fc_1_Clip_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 3904);
    _tcn_layers_3_net_net_5_fc_fc_2_MatMul_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _tcn_layers_3_net_net_5_fc_fc_2_MatMul_output_0_weights_array.data = AI_PTR(g_network_weights_map[0] + 4032);
    _tcn_layers_3_net_net_5_fc_fc_2_MatMul_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 4032);
    _boundary_head_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _boundary_head_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[0] + 4160);
    _boundary_head_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 4160);
    _boundary_head_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _boundary_head_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[0] + 4176);
    _boundary_head_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 4176);
    _frame_head_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _frame_head_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[0] + 4180);
    _frame_head_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 4180);
    _frame_head_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _frame_head_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[0] + 4196);
    _frame_head_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 4196);
    return true;
  }
  AI_ERROR_TRAP(net_ctx, INIT_FAILED, NETWORK_WEIGHTS);
  return false;
}


/**  PUBLIC APIs SECTION  *****************************************************/



AI_DEPRECATED
AI_API_ENTRY
ai_bool ai_network_get_info(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if (report && net_ctx)
  {
    ai_network_report r = {
      .model_name        = AI_NETWORK_MODEL_NAME,
      .model_signature   = AI_NETWORK_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = AI_STRUCT_INIT,

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 906838,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .params            = AI_STRUCT_INIT,
      .activations       = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0x1f344ed7,
    };

    if (!ai_platform_api_get_network_report(network, &r)) return false;

    *report = r;
    return true;
  }
  return false;
}



AI_API_ENTRY
ai_bool ai_network_get_report(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if (report && net_ctx)
  {
    ai_network_report r = {
      .model_name        = AI_NETWORK_MODEL_NAME,
      .model_signature   = AI_NETWORK_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = AI_STRUCT_INIT,

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 906838,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .map_signature     = AI_MAGIC_SIGNATURE,
      .map_weights       = AI_STRUCT_INIT,
      .map_activations   = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0x1f344ed7,
    };

    if (!ai_platform_api_get_network_report(network, &r)) return false;

    *report = r;
    return true;
  }
  return false;
}


AI_API_ENTRY
ai_error ai_network_get_error(ai_handle network)
{
  return ai_platform_network_get_error(network);
}


AI_API_ENTRY
ai_error ai_network_create(
  ai_handle* network, const ai_buffer* network_config)
{
  return ai_platform_network_create(
    network, network_config, 
    AI_CONTEXT_OBJ(&AI_NET_OBJ_INSTANCE),
    AI_TOOLS_API_VERSION_MAJOR, AI_TOOLS_API_VERSION_MINOR, AI_TOOLS_API_VERSION_MICRO);
}


AI_API_ENTRY
ai_error ai_network_create_and_init(
  ai_handle* network, const ai_handle activations[], const ai_handle weights[])
{
  ai_error err;
  ai_network_params params;

  err = ai_network_create(network, AI_NETWORK_DATA_CONFIG);
  if (err.type != AI_ERROR_NONE) {
    return err;
  }
  
  if (ai_network_data_params_get(&params) != true) {
    err = ai_network_get_error(*network);
    return err;
  }
#if defined(AI_NETWORK_DATA_ACTIVATIONS_COUNT)
  /* set the addresses of the activations buffers */
  for (ai_u16 idx=0; activations && idx<params.map_activations.size; idx++) {
    AI_BUFFER_ARRAY_ITEM_SET_ADDRESS(&params.map_activations, idx, activations[idx]);
  }
#endif
#if defined(AI_NETWORK_DATA_WEIGHTS_COUNT)
  /* set the addresses of the weight buffers */
  for (ai_u16 idx=0; weights && idx<params.map_weights.size; idx++) {
    AI_BUFFER_ARRAY_ITEM_SET_ADDRESS(&params.map_weights, idx, weights[idx]);
  }
#endif
  if (ai_network_init(*network, &params) != true) {
    err = ai_network_get_error(*network);
  }
  return err;
}


AI_API_ENTRY
ai_buffer* ai_network_inputs_get(ai_handle network, ai_u16 *n_buffer)
{
  if (network == AI_HANDLE_NULL) {
    network = (ai_handle)&AI_NET_OBJ_INSTANCE;
    AI_NETWORK_OBJ(network)->magic = AI_MAGIC_CONTEXT_TOKEN;
  }
  return ai_platform_inputs_get(network, n_buffer);
}


AI_API_ENTRY
ai_buffer* ai_network_outputs_get(ai_handle network, ai_u16 *n_buffer)
{
  if (network == AI_HANDLE_NULL) {
    network = (ai_handle)&AI_NET_OBJ_INSTANCE;
    AI_NETWORK_OBJ(network)->magic = AI_MAGIC_CONTEXT_TOKEN;
  }
  return ai_platform_outputs_get(network, n_buffer);
}


AI_API_ENTRY
ai_handle ai_network_destroy(ai_handle network)
{
  return ai_platform_network_destroy(network);
}


AI_API_ENTRY
ai_bool ai_network_init(
  ai_handle network, const ai_network_params* params)
{
  ai_network* net_ctx = AI_NETWORK_OBJ(ai_platform_network_init(network, params));
  ai_bool ok = true;

  if (!net_ctx) return false;
  ok &= network_configure_weights(net_ctx, params);
  ok &= network_configure_activations(net_ctx, params);

  ok &= ai_platform_network_post_init(network);

  return ok;
}


AI_API_ENTRY
ai_i32 ai_network_run(
  ai_handle network, const ai_buffer* input, ai_buffer* output)
{
  return ai_platform_network_process(network, input, output);
}


AI_API_ENTRY
ai_i32 ai_network_forward(ai_handle network, const ai_buffer* input)
{
  return ai_platform_network_process(network, input, NULL);
}



#undef AI_NETWORK_MODEL_SIGNATURE
#undef AI_NET_OBJ_INSTANCE
#undef AI_TOOLS_DATE_TIME
#undef AI_TOOLS_COMPILE_TIME

