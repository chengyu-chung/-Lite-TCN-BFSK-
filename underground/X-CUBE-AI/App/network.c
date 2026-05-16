/**
  ******************************************************************************
  * @file    network.c
  * @author  AST Embedded Analytics Research Platform
  * @date    2026-04-03T17:10:22+0800
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
#define AI_NETWORK_MODEL_SIGNATURE     "0xc442e5c9f4b045f4671eb4b91d32bac3"

#ifndef AI_TOOLS_REVISION_ID
#define AI_TOOLS_REVISION_ID     ""
#endif

#undef AI_TOOLS_DATE_TIME
#define AI_TOOLS_DATE_TIME   "2026-04-03T17:10:22+0800"

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
  NULL, NULL, 960, AI_STATIC)

/* Array#1 */
AI_ARRAY_OBJ_DECLARE(
  _frontend_frontend_2_Clip_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 1280, AI_STATIC)

/* Array#2 */
AI_ARRAY_OBJ_DECLARE(
  _expand_expand_2_Clip_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 7680, AI_STATIC)

/* Array#3 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_0_net_net_0_Conv_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 7680, AI_STATIC)

/* Array#4 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_0_net_net_3_Clip_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 7680, AI_STATIC)

/* Array#5 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_0_net_net_5_avg_pool_GlobalAveragePool_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 24, AI_STATIC)

/* Array#6 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 12, AI_STATIC)

/* Array#7 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_0_net_net_5_fc_fc_2_MatMul_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 24, AI_STATIC)

/* Array#8 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_0_net_net_5_fc_fc_3_HardSigmoid_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 24, AI_STATIC)

/* Array#9 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_0_net_net_5_Mul_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 7680, AI_STATIC)

/* Array#10 */
AI_ARRAY_OBJ_DECLARE(
  _Add_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 7680, AI_STATIC)

/* Array#11 */
AI_ARRAY_OBJ_DECLARE(
  _Add_output_0_0_0__tcn_layers_1_net_net_0_Conv_output_0_conversion_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 7680, AI_STATIC)

/* Array#12 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_1_net_net_0_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 7680, AI_STATIC)

/* Array#13 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_1_net_net_0_Conv_output_0_0_0__tcn_layers_1_net_net_3_Clip_output_0_conversion_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 7680, AI_STATIC)

/* Array#14 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_1_net_net_3_Clip_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 7680, AI_STATIC)

/* Array#15 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_1_net_net_5_avg_pool_GlobalAveragePool_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 24, AI_STATIC)

/* Array#16 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_1_net_net_5_fc_fc_1_Clip_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 12, AI_STATIC)

/* Array#17 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_1_net_net_5_fc_fc_2_MatMul_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 24, AI_STATIC)

/* Array#18 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_1_net_net_5_fc_fc_3_HardSigmoid_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 24, AI_STATIC)

/* Array#19 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_1_net_net_5_Mul_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 7680, AI_STATIC)

/* Array#20 */
AI_ARRAY_OBJ_DECLARE(
  _Add_1_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 7680, AI_STATIC)

/* Array#21 */
AI_ARRAY_OBJ_DECLARE(
  _Add_1_output_0_0_0__tcn_layers_2_net_net_0_Conv_output_0_conversion_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 7680, AI_STATIC)

/* Array#22 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_2_net_net_0_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 7680, AI_STATIC)

/* Array#23 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_2_net_net_0_Conv_output_0_0_0__tcn_layers_2_net_net_3_Clip_output_0_conversion_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 7680, AI_STATIC)

/* Array#24 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_2_net_net_3_Clip_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 7680, AI_STATIC)

/* Array#25 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_2_net_net_5_avg_pool_GlobalAveragePool_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 24, AI_STATIC)

/* Array#26 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_2_net_net_5_fc_fc_1_Clip_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 12, AI_STATIC)

/* Array#27 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_2_net_net_5_fc_fc_2_MatMul_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 24, AI_STATIC)

/* Array#28 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_2_net_net_5_fc_fc_3_HardSigmoid_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 24, AI_STATIC)

/* Array#29 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_2_net_net_5_Mul_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 7680, AI_STATIC)

/* Array#30 */
AI_ARRAY_OBJ_DECLARE(
  _Add_2_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 7680, AI_STATIC)

/* Array#31 */
AI_ARRAY_OBJ_DECLARE(
  _Add_2_output_0_0_0__tcn_layers_3_net_net_0_Conv_output_0_conversion_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 7680, AI_STATIC)

/* Array#32 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_3_net_net_0_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 7680, AI_STATIC)

/* Array#33 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_3_net_net_0_Conv_output_0_0_0__tcn_layers_3_net_net_3_Clip_output_0_conversion_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 7680, AI_STATIC)

/* Array#34 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_3_net_net_3_Clip_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 7680, AI_STATIC)

/* Array#35 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_3_net_net_5_avg_pool_GlobalAveragePool_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 24, AI_STATIC)

/* Array#36 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_3_net_net_5_fc_fc_1_Clip_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 12, AI_STATIC)

/* Array#37 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_3_net_net_5_fc_fc_2_MatMul_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 24, AI_STATIC)

/* Array#38 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_3_net_net_5_fc_fc_3_HardSigmoid_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 24, AI_STATIC)

/* Array#39 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_3_net_net_5_Mul_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 7680, AI_STATIC)

/* Array#40 */
AI_ARRAY_OBJ_DECLARE(
  _Add_3_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 7680, AI_STATIC)

/* Array#41 */
AI_ARRAY_OBJ_DECLARE(
  _Add_3_output_0_0_0__tcn_layers_4_net_net_0_Conv_output_0_conversion_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 7680, AI_STATIC)

/* Array#42 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_4_net_net_0_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 7680, AI_STATIC)

/* Array#43 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_4_net_net_0_Conv_output_0_0_0__tcn_layers_4_net_net_3_Clip_output_0_conversion_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 7680, AI_STATIC)

/* Array#44 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_4_net_net_3_Clip_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 7680, AI_STATIC)

/* Array#45 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_4_net_net_5_avg_pool_GlobalAveragePool_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 24, AI_STATIC)

/* Array#46 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_4_net_net_5_fc_fc_1_Clip_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 12, AI_STATIC)

/* Array#47 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_4_net_net_5_fc_fc_2_MatMul_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 24, AI_STATIC)

/* Array#48 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_4_net_net_5_fc_fc_3_HardSigmoid_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 24, AI_STATIC)

/* Array#49 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_4_net_net_5_Mul_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 7680, AI_STATIC)

/* Array#50 */
AI_ARRAY_OBJ_DECLARE(
  _Add_4_output_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 7680, AI_STATIC)

/* Array#51 */
AI_ARRAY_OBJ_DECLARE(
  _boundary_head_Conv_output_0_output_array, AI_ARRAY_FORMAT_S8|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 320, AI_STATIC)

/* Array#52 */
AI_ARRAY_OBJ_DECLARE(
  _frame_head_Conv_output_0_output_array, AI_ARRAY_FORMAT_S8|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 320, AI_STATIC)

/* Array#53 */
AI_ARRAY_OBJ_DECLARE(
  _frontend_frontend_2_Clip_output_0_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 96, AI_STATIC)

/* Array#54 */
AI_ARRAY_OBJ_DECLARE(
  _frontend_frontend_2_Clip_output_0_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 4, AI_STATIC)

/* Array#55 */
AI_ARRAY_OBJ_DECLARE(
  _expand_expand_2_Clip_output_0_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 96, AI_STATIC)

/* Array#56 */
AI_ARRAY_OBJ_DECLARE(
  _expand_expand_2_Clip_output_0_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 24, AI_STATIC)

/* Array#57 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_0_net_net_0_Conv_output_0_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 168, AI_STATIC)

/* Array#58 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_0_net_net_0_Conv_output_0_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 24, AI_STATIC)

/* Array#59 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_0_net_net_3_Clip_output_0_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 576, AI_STATIC)

/* Array#60 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_0_net_net_3_Clip_output_0_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 24, AI_STATIC)

/* Array#61 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 288, AI_STATIC)

/* Array#62 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 12, AI_STATIC)

/* Array#63 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_0_net_net_5_fc_fc_2_MatMul_output_0_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 288, AI_STATIC)

/* Array#64 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_1_net_net_0_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 168, AI_STATIC)

/* Array#65 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_1_net_net_0_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 24, AI_STATIC)

/* Array#66 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_1_net_net_3_Clip_output_0_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 576, AI_STATIC)

/* Array#67 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_1_net_net_3_Clip_output_0_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 24, AI_STATIC)

/* Array#68 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_1_net_net_5_fc_fc_1_Clip_output_0_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 288, AI_STATIC)

/* Array#69 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_1_net_net_5_fc_fc_2_MatMul_output_0_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 288, AI_STATIC)

/* Array#70 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_2_net_net_0_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 168, AI_STATIC)

/* Array#71 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_2_net_net_3_Clip_output_0_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 576, AI_STATIC)

/* Array#72 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_2_net_net_3_Clip_output_0_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 24, AI_STATIC)

/* Array#73 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_2_net_net_5_fc_fc_1_Clip_output_0_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 288, AI_STATIC)

/* Array#74 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_2_net_net_5_fc_fc_2_MatMul_output_0_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 288, AI_STATIC)

/* Array#75 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_3_net_net_0_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 168, AI_STATIC)

/* Array#76 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_3_net_net_3_Clip_output_0_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 576, AI_STATIC)

/* Array#77 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_3_net_net_3_Clip_output_0_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 24, AI_STATIC)

/* Array#78 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_3_net_net_5_fc_fc_1_Clip_output_0_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 288, AI_STATIC)

/* Array#79 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_3_net_net_5_fc_fc_2_MatMul_output_0_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 288, AI_STATIC)

/* Array#80 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_4_net_net_0_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 168, AI_STATIC)

/* Array#81 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_4_net_net_3_Clip_output_0_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 576, AI_STATIC)

/* Array#82 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_4_net_net_3_Clip_output_0_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 24, AI_STATIC)

/* Array#83 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_4_net_net_5_fc_fc_1_Clip_output_0_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 288, AI_STATIC)

/* Array#84 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_4_net_net_5_fc_fc_2_MatMul_output_0_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 288, AI_STATIC)

/* Array#85 */
AI_ARRAY_OBJ_DECLARE(
  _boundary_head_Conv_output_0_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 24, AI_STATIC)

/* Array#86 */
AI_ARRAY_OBJ_DECLARE(
  _boundary_head_Conv_output_0_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 1, AI_STATIC)

/* Array#87 */
AI_ARRAY_OBJ_DECLARE(
  _frame_head_Conv_output_0_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 24, AI_STATIC)

/* Array#88 */
AI_ARRAY_OBJ_DECLARE(
  _frame_head_Conv_output_0_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 1, AI_STATIC)

/* Array#89 */
AI_ARRAY_OBJ_DECLARE(
  _frontend_frontend_2_Clip_output_0_scratch0_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 344, AI_STATIC)

/* Array#90 */
AI_ARRAY_OBJ_DECLARE(
  _frontend_frontend_2_Clip_output_0_scratch1_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 3836, AI_STATIC)

/* Array#91 */
AI_ARRAY_OBJ_DECLARE(
  _expand_expand_2_Clip_output_0_scratch0_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 256, AI_STATIC)

/* Array#92 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_0_net_net_0_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 745, AI_STATIC)

/* Array#93 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_0_net_net_3_Clip_output_0_scratch0_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 336, AI_STATIC)

/* Array#94 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_scratch0_array, AI_ARRAY_FORMAT_S16,
  NULL, NULL, 84, AI_STATIC)

/* Array#95 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_0_net_net_5_fc_fc_2_MatMul_output_0_scratch0_array, AI_ARRAY_FORMAT_S16,
  NULL, NULL, 132, AI_STATIC)

/* Array#96 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_1_net_net_3_Clip_output_0_scratch0_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 336, AI_STATIC)

/* Array#97 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_1_net_net_5_fc_fc_1_Clip_output_0_scratch0_array, AI_ARRAY_FORMAT_S16,
  NULL, NULL, 84, AI_STATIC)

/* Array#98 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_1_net_net_5_fc_fc_2_MatMul_output_0_scratch0_array, AI_ARRAY_FORMAT_S16,
  NULL, NULL, 132, AI_STATIC)

/* Array#99 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_2_net_net_3_Clip_output_0_scratch0_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 336, AI_STATIC)

/* Array#100 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_2_net_net_5_fc_fc_1_Clip_output_0_scratch0_array, AI_ARRAY_FORMAT_S16,
  NULL, NULL, 84, AI_STATIC)

/* Array#101 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_2_net_net_5_fc_fc_2_MatMul_output_0_scratch0_array, AI_ARRAY_FORMAT_S16,
  NULL, NULL, 132, AI_STATIC)

/* Array#102 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_3_net_net_3_Clip_output_0_scratch0_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 336, AI_STATIC)

/* Array#103 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_3_net_net_5_fc_fc_1_Clip_output_0_scratch0_array, AI_ARRAY_FORMAT_S16,
  NULL, NULL, 84, AI_STATIC)

/* Array#104 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_3_net_net_5_fc_fc_2_MatMul_output_0_scratch0_array, AI_ARRAY_FORMAT_S16,
  NULL, NULL, 132, AI_STATIC)

/* Array#105 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_4_net_net_3_Clip_output_0_scratch0_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 336, AI_STATIC)

/* Array#106 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_4_net_net_5_fc_fc_1_Clip_output_0_scratch0_array, AI_ARRAY_FORMAT_S16,
  NULL, NULL, 84, AI_STATIC)

/* Array#107 */
AI_ARRAY_OBJ_DECLARE(
  _tcn_layers_4_net_net_5_fc_fc_2_MatMul_output_0_scratch0_array, AI_ARRAY_FORMAT_S16,
  NULL, NULL, 132, AI_STATIC)

/* Array#108 */
AI_ARRAY_OBJ_DECLARE(
  _boundary_head_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 96, AI_STATIC)

/* Array#109 */
AI_ARRAY_OBJ_DECLARE(
  _frame_head_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 96, AI_STATIC)

/**  Array metadata declarations section  *************************************/
/* Int quant #0 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_Add_1_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.025258393958210945f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #1 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_Add_2_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.04375133290886879f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #2 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_Add_3_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.05978473648428917f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #3 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_Add_4_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.07263879477977753f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #4 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_Add_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.024759206920862198f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #5 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_boundary_head_Conv_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.4288274645805359f),
    AI_PACK_INTQ_ZP(84)))

/* Int quant #6 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_boundary_head_Conv_output_0_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.013938688673079014f),
    AI_PACK_INTQ_ZP(0)))

/* Int quant #7 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_expand_expand_2_Clip_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0235294122248888f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #8 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_expand_expand_2_Clip_output_0_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 24,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.006494150962680578f, 0.0017891089664772153f, 0.016353555023670197f, 0.002039102138951421f, 0.009893455542623997f, 0.002560675609856844f, 0.012726269662380219f, 0.013349298387765884f, 0.0022365632466971874f, 0.011400884948670864f, 0.00879951473325491f, 0.006812003441154957f, 0.004500694572925568f, 0.004700831603258848f, 0.008281365968286991f, 0.0050066374242305756f, 0.0017967812018468976f, 0.004210056271404028f, 0.004324321635067463f, 0.0032585780136287212f, 0.010887795127928257f, 0.005356668494641781f, 0.004137858748435974f, 0.005037977825850248f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #9 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_frame_head_Conv_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.20760942995548248f),
    AI_PACK_INTQ_ZP(-14)))

/* Int quant #10 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_frame_head_Conv_output_0_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.010300196707248688f),
    AI_PACK_INTQ_ZP(0)))

/* Int quant #11 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_frontend_frontend_2_Clip_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0235294122248888f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #12 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_frontend_frontend_2_Clip_output_0_scratch1_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0235294122248888f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #13 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_frontend_frontend_2_Clip_output_0_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 4,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0014609484933316708f, 0.0012969954404979944f, 0.0018636825261637568f, 0.002239137189462781f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0)))

/* Int quant #14 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_0_net_net_0_Conv_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.01853587105870247f),
    AI_PACK_INTQ_ZP(20)))

/* Int quant #15 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_0_net_net_0_Conv_output_0_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 24,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.003009998006746173f, 0.010436197742819786f, 0.0062227509915828705f, 0.007784607820212841f, 0.011974559165537357f, 0.009048801846802235f, 0.00660338718444109f, 0.006745822262018919f, 0.00727413734421134f, 0.003090744372457266f, 0.003785229055210948f, 0.005697534419596195f, 0.006172816269099712f, 0.006667874753475189f, 0.003906918223947287f, 0.0033553107641637325f, 0.0068196519277989864f, 0.006717925425618887f, 0.004476403817534447f, 0.004884840454906225f, 0.0038285651244223118f, 0.00628319289535284f, 0.006030228920280933f, 0.007792912423610687f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #16 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_0_net_net_3_Clip_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.020146457478404045f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #17 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_0_net_net_3_Clip_output_0_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 24,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.025705745443701744f, 0.0344010666012764f, 0.03132977336645126f, 0.0268142931163311f, 0.01573355682194233f, 0.025017596781253815f, 0.023486878722906113f, 0.030839569866657257f, 0.04349302127957344f, 0.03684967756271362f, 0.026706600561738014f, 0.03831753134727478f, 0.027244171127676964f, 0.053810954093933105f, 0.024744655936956406f, 0.02838125079870224f, 0.026927566155791283f, 0.05472845956683159f, 0.020843826234340668f, 0.01633879728615284f, 0.021919695660471916f, 0.020425226539373398f, 0.01706589385867119f, 0.031230594962835312f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #18 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_0_net_net_5_Mul_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.012801705859601498f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #19 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_0_net_net_5_avg_pool_GlobalAveragePool_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0020738288294523954f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #20 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.010383361019194126f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #21 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 12,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.00152611976955086f, 0.02846352383494377f, 0.0015764719573780894f, 0.0018176055746152997f, 0.0015673615271225572f, 0.0016425841022282839f, 0.001941018272191286f, 0.014029434882104397f, 0.016588687896728516f, 0.015533084981143475f, 0.001754036289639771f, 0.017087645828723907f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #22 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_0_net_net_5_fc_fc_2_MatMul_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0438401959836483f),
    AI_PACK_INTQ_ZP(-8)))

/* Int quant #23 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_0_net_net_5_fc_fc_2_MatMul_output_0_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 24,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.011665751226246357f, 0.003917058929800987f, 0.008478270843625069f, 0.004905769135802984f, 0.028692934662103653f, 0.011523326858878136f, 0.007304022554308176f, 0.002160969888791442f, 0.010021887719631195f, 0.007168320007622242f, 0.023256370797753334f, 0.005825561471283436f, 0.005371057894080877f, 0.005253571551293135f, 0.00800199806690216f, 0.012063044123351574f, 0.006195180118083954f, 0.013740010559558868f, 0.005380572751164436f, 0.004209921229630709f, 0.010578599758446217f, 0.016146836802363396f, 0.013220316730439663f, 0.010556635446846485f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #24 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_0_net_net_5_fc_fc_3_HardSigmoid_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.003921568859368563f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #25 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_1_net_net_0_Conv_output_0_0_0__tcn_layers_1_net_net_3_Clip_output_0_conversion_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.02878357097506523f),
    AI_PACK_INTQ_ZP(-15)))

/* Int quant #26 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_1_net_net_3_Clip_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0235294122248888f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #27 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_1_net_net_3_Clip_output_0_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 24,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.015370380133390427f, 0.01380971074104309f, 0.012609642930328846f, 0.016514994204044342f, 0.028544753789901733f, 0.009661017917096615f, 0.006270095240324736f, 0.01099645346403122f, 0.009186534211039543f, 0.016376540064811707f, 0.011074661277234554f, 0.018386585637927055f, 0.020975222811102867f, 0.011328505352139473f, 0.009954219684004784f, 0.00791520532220602f, 0.01471028197556734f, 0.0069039794616401196f, 0.006560816429555416f, 0.007291061338037252f, 0.010725630447268486f, 0.006588003132492304f, 0.014509467408061028f, 0.027539614588022232f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #28 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_1_net_net_5_Mul_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0235294122248888f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #29 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_1_net_net_5_avg_pool_GlobalAveragePool_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.002574624726548791f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #30 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_1_net_net_5_fc_fc_1_Clip_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.011247791349887848f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #31 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_1_net_net_5_fc_fc_1_Clip_output_0_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 12,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0017961707198992372f, 0.0015194658190011978f, 0.001812213216908276f, 0.0016451887786388397f, 0.0018045235192403197f, 0.0015020587015897036f, 0.0014516074443235993f, 0.00182918191421777f, 0.017082611098885536f, 0.001550555694848299f, 0.020926788449287415f, 0.0022294700611382723f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #32 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_1_net_net_5_fc_fc_2_MatMul_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.029684320092201233f),
    AI_PACK_INTQ_ZP(-38)))

/* Int quant #33 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_1_net_net_5_fc_fc_2_MatMul_output_0_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 24,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.010009955614805222f, 0.008873562328517437f, 0.0068161929957568645f, 0.010708639398217201f, 0.009240718558430672f, 0.007728372234851122f, 0.0031681854743510485f, 0.009215001948177814f, 0.009692198596894741f, 0.0038022673688828945f, 0.008064649999141693f, 0.0039146170020103455f, 0.011622481979429722f, 0.0037297287490218878f, 0.0022583012469112873f, 0.009274095296859741f, 0.0042013018392026424f, 0.00857406947761774f, 0.0020164120942354202f, 0.007843751460313797f, 0.002669769339263439f, 0.00861064251512289f, 0.00282079610042274f, 0.008565905503928661f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #34 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_1_net_net_5_fc_fc_3_HardSigmoid_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.003921568859368563f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #35 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_2_net_net_0_Conv_output_0_0_0__tcn_layers_2_net_net_3_Clip_output_0_conversion_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.055968593806028366f),
    AI_PACK_INTQ_ZP(9)))

/* Int quant #36 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_2_net_net_3_Clip_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0235294122248888f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #37 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_2_net_net_3_Clip_output_0_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 24,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.013394379056990147f, 0.012362596578896046f, 0.006192940752953291f, 0.009376917965710163f, 0.010093675926327705f, 0.009452003985643387f, 0.006509716622531414f, 0.0061345212161540985f, 0.007549520581960678f, 0.0045964960008859634f, 0.015608185902237892f, 0.005875505041331053f, 0.011304698884487152f, 0.004592479206621647f, 0.010237028822302818f, 0.008441110141575336f, 0.008405854925513268f, 0.006355132907629013f, 0.00777455186471343f, 0.015492444857954979f, 0.003017453011125326f, 0.005273329559713602f, 0.0050823744386434555f, 0.01275751180946827f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #38 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_2_net_net_5_Mul_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0235294122248888f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #39 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_2_net_net_5_avg_pool_GlobalAveragePool_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.005741574801504612f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #40 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_2_net_net_5_fc_fc_1_Clip_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.01388351060450077f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #41 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_2_net_net_5_fc_fc_1_Clip_output_0_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 12,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0016023553907871246f, 0.010025995783507824f, 0.013571917079389095f, 0.017227264121174812f, 0.016833467409014702f, 0.0016916574677452445f, 0.014992235228419304f, 0.0017422090750187635f, 0.002121566329151392f, 0.001694267150014639f, 0.0017852513119578362f, 0.014789227396249771f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #42 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_2_net_net_5_fc_fc_2_MatMul_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0457114651799202f),
    AI_PACK_INTQ_ZP(-19)))

/* Int quant #43 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_2_net_net_5_fc_fc_2_MatMul_output_0_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 24,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.020294923335313797f, 0.00572776747867465f, 0.00584248173981905f, 0.0064329346641898155f, 0.005846851971000433f, 0.007395303342491388f, 0.006064164452254772f, 0.005731892306357622f, 0.00658727902919054f, 0.006909779738634825f, 0.005238959565758705f, 0.014638068154454231f, 0.006880817003548145f, 0.009004008956253529f, 0.017142556607723236f, 0.0072252750396728516f, 0.005505695473402739f, 0.011956966482102871f, 0.012263881973922253f, 0.012574744410812855f, 0.006512152496725321f, 0.006038714200258255f, 0.00608783308416605f, 0.006322802510112524f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #44 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_2_net_net_5_fc_fc_3_HardSigmoid_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.003921568859368563f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #45 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_3_net_net_0_Conv_output_0_0_0__tcn_layers_3_net_net_3_Clip_output_0_conversion_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.08416511863470078f),
    AI_PACK_INTQ_ZP(-7)))

/* Int quant #46 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_3_net_net_3_Clip_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0235294122248888f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #47 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_3_net_net_3_Clip_output_0_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 24,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0054502710700035095f, 0.008831367827951908f, 0.0032490030862390995f, 0.01170630194246769f, 0.003583171172067523f, 0.004693823866546154f, 0.01173490658402443f, 0.0026071579195559025f, 0.009042400866746902f, 0.004332950804382563f, 0.01597755402326584f, 0.003019186668097973f, 0.0037294316571205854f, 0.002828623866662383f, 0.003801716258749366f, 0.00665793102234602f, 0.005510430317372084f, 0.006137671414762735f, 0.003610600484535098f, 0.004275304265320301f, 0.005327489227056503f, 0.013795686885714531f, 0.012960073538124561f, 0.007266966160386801f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #48 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_3_net_net_5_Mul_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0235294122248888f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #49 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_3_net_net_5_avg_pool_GlobalAveragePool_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.010807592421770096f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #50 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_3_net_net_5_fc_fc_1_Clip_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.019769636914134026f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #51 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_3_net_net_5_fc_fc_1_Clip_output_0_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 12,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0017469079466536641f, 0.0035180363338440657f, 0.002767306985333562f, 0.0034506351221352816f, 0.0035906117409467697f, 0.003161318600177765f, 0.003361522452905774f, 0.002300913678482175f, 0.003109002485871315f, 0.003234138712286949f, 0.0027652934659272432f, 0.002786668948829174f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #52 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_3_net_net_5_fc_fc_2_MatMul_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.06807612627744675f),
    AI_PACK_INTQ_ZP(0)))

/* Int quant #53 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_3_net_net_5_fc_fc_2_MatMul_output_0_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 24,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.002764421282336116f, 0.0032775728031992912f, 0.003602617885917425f, 0.0034825531765818596f, 0.004032960627228022f, 0.003026599297299981f, 0.004520139656960964f, 0.0031514724250882864f, 0.003234234871342778f, 0.0029980549588799477f, 0.003135932143777609f, 0.0037387923803180456f, 0.0034603276289999485f, 0.00350181688554585f, 0.0035210601054131985f, 0.0029040207155048847f, 0.003130134893581271f, 0.0029577058739960194f, 0.0036954819224774837f, 0.003321125404909253f, 0.003189333714544773f, 0.0040184324607253075f, 0.003560388693585992f, 0.004414621740579605f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #54 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_3_net_net_5_fc_fc_3_HardSigmoid_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.003921568859368563f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #55 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_4_net_net_0_Conv_output_0_0_0__tcn_layers_4_net_net_3_Clip_output_0_conversion_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.15147747099399567f),
    AI_PACK_INTQ_ZP(-4)))

/* Int quant #56 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_4_net_net_3_Clip_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0235294122248888f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #57 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_4_net_net_3_Clip_output_0_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 24,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.005737615749239922f, 0.007786980830132961f, 0.014055485837161541f, 0.008627851493656635f, 0.004160880111157894f, 0.007211184594780207f, 0.01180796604603529f, 0.007583613973110914f, 0.004561952780932188f, 0.002876235404983163f, 0.009378275834023952f, 0.004453143570572138f, 0.007554450538009405f, 0.014536144211888313f, 0.005752052646130323f, 0.007447331212460995f, 0.011212500743567944f, 0.009251159615814686f, 0.011459211818873882f, 0.005881939083337784f, 0.0069909971207380295f, 0.006832956336438656f, 0.01042147260159254f, 0.0054303319193422794f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #58 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_4_net_net_5_Mul_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0235294122248888f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #59 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_4_net_net_5_avg_pool_GlobalAveragePool_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.011115346103906631f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #60 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_4_net_net_5_fc_fc_1_Clip_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0235294122248888f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #61 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_4_net_net_5_fc_fc_1_Clip_output_0_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 12,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.001606483943760395f, 0.0016276041278615594f, 0.0020133836660534143f, 0.0014047975419089198f, 0.0017535921651870012f, 0.010615951381623745f, 0.0016005531651899219f, 0.06572630256414413f, 0.04127013310790062f, 0.05348269268870354f, 0.08388511836528778f, 0.031371619552373886f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #62 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_4_net_net_5_fc_fc_2_MatMul_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.06067758798599243f),
    AI_PACK_INTQ_ZP(-58)))

/* Int quant #63 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_4_net_net_5_fc_fc_2_MatMul_output_0_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 24,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.007410822436213493f, 0.010610740631818771f, 0.008287688717246056f, 0.01138563547283411f, 0.010351685807108879f, 0.011749267578125f, 0.01385495439171791f, 0.01598983071744442f, 0.01181784924119711f, 0.00663115456700325f, 0.005960952956229448f, 0.011913030408322811f, 0.005793227348476648f, 0.010451674461364746f, 0.010959379374980927f, 0.02199140004813671f, 0.005374710075557232f, 0.006694458890706301f, 0.011586951091885567f, 0.011321750469505787f, 0.0098431296646595f, 0.0093877874314785f, 0.007159235887229443f, 0.006676767487078905f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #64 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(_tcn_layers_4_net_net_5_fc_fc_3_HardSigmoid_output_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.003921568859368563f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #65 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(input_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.04223548248410225f),
    AI_PACK_INTQ_ZP(3)))

/**  Tensor declarations section  *********************************************/
/* Tensor #0 */
AI_TENSOR_OBJ_DECLARE(
  _Add_1_output_0_0_0__tcn_layers_2_net_net_0_Conv_output_0_conversion_output, AI_STATIC,
  0, 0x0,
  AI_SHAPE_INIT(4, 1, 24, 320, 1), AI_STRIDE_INIT(4, 4, 4, 96, 30720),
  1, &_Add_1_output_0_0_0__tcn_layers_2_net_net_0_Conv_output_0_conversion_output_array, NULL)

/* Tensor #1 */
AI_TENSOR_OBJ_DECLARE(
  _Add_1_output_0_output, AI_STATIC,
  1, 0x1,
  AI_SHAPE_INIT(4, 1, 24, 320, 1), AI_STRIDE_INIT(4, 1, 1, 24, 7680),
  1, &_Add_1_output_0_output_array, &_Add_1_output_0_output_array_intq)

/* Tensor #2 */
AI_TENSOR_OBJ_DECLARE(
  _Add_2_output_0_0_0__tcn_layers_3_net_net_0_Conv_output_0_conversion_output, AI_STATIC,
  2, 0x0,
  AI_SHAPE_INIT(4, 1, 24, 320, 1), AI_STRIDE_INIT(4, 4, 4, 96, 30720),
  1, &_Add_2_output_0_0_0__tcn_layers_3_net_net_0_Conv_output_0_conversion_output_array, NULL)

/* Tensor #3 */
AI_TENSOR_OBJ_DECLARE(
  _Add_2_output_0_output, AI_STATIC,
  3, 0x1,
  AI_SHAPE_INIT(4, 1, 24, 320, 1), AI_STRIDE_INIT(4, 1, 1, 24, 7680),
  1, &_Add_2_output_0_output_array, &_Add_2_output_0_output_array_intq)

/* Tensor #4 */
AI_TENSOR_OBJ_DECLARE(
  _Add_3_output_0_0_0__tcn_layers_4_net_net_0_Conv_output_0_conversion_output, AI_STATIC,
  4, 0x0,
  AI_SHAPE_INIT(4, 1, 24, 320, 1), AI_STRIDE_INIT(4, 4, 4, 96, 30720),
  1, &_Add_3_output_0_0_0__tcn_layers_4_net_net_0_Conv_output_0_conversion_output_array, NULL)

/* Tensor #5 */
AI_TENSOR_OBJ_DECLARE(
  _Add_3_output_0_output, AI_STATIC,
  5, 0x1,
  AI_SHAPE_INIT(4, 1, 24, 320, 1), AI_STRIDE_INIT(4, 1, 1, 24, 7680),
  1, &_Add_3_output_0_output_array, &_Add_3_output_0_output_array_intq)

/* Tensor #6 */
AI_TENSOR_OBJ_DECLARE(
  _Add_4_output_0_output, AI_STATIC,
  6, 0x1,
  AI_SHAPE_INIT(4, 1, 24, 320, 1), AI_STRIDE_INIT(4, 1, 1, 24, 7680),
  1, &_Add_4_output_0_output_array, &_Add_4_output_0_output_array_intq)

/* Tensor #7 */
AI_TENSOR_OBJ_DECLARE(
  _Add_output_0_0_0__tcn_layers_1_net_net_0_Conv_output_0_conversion_output, AI_STATIC,
  7, 0x0,
  AI_SHAPE_INIT(4, 1, 24, 320, 1), AI_STRIDE_INIT(4, 4, 4, 96, 30720),
  1, &_Add_output_0_0_0__tcn_layers_1_net_net_0_Conv_output_0_conversion_output_array, NULL)

/* Tensor #8 */
AI_TENSOR_OBJ_DECLARE(
  _Add_output_0_output, AI_STATIC,
  8, 0x1,
  AI_SHAPE_INIT(4, 1, 24, 320, 1), AI_STRIDE_INIT(4, 1, 1, 24, 7680),
  1, &_Add_output_0_output_array, &_Add_output_0_output_array_intq)

/* Tensor #9 */
AI_TENSOR_OBJ_DECLARE(
  _boundary_head_Conv_output_0_bias, AI_STATIC,
  9, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &_boundary_head_Conv_output_0_bias_array, NULL)

/* Tensor #10 */
AI_TENSOR_OBJ_DECLARE(
  _boundary_head_Conv_output_0_output, AI_STATIC,
  10, 0x1,
  AI_SHAPE_INIT(4, 1, 1, 320, 1), AI_STRIDE_INIT(4, 1, 1, 1, 320),
  1, &_boundary_head_Conv_output_0_output_array, &_boundary_head_Conv_output_0_output_array_intq)

/* Tensor #11 */
AI_TENSOR_OBJ_DECLARE(
  _boundary_head_Conv_output_0_scratch0, AI_STATIC,
  11, 0x0,
  AI_SHAPE_INIT(4, 1, 96, 1, 1), AI_STRIDE_INIT(4, 1, 1, 96, 96),
  1, &_boundary_head_Conv_output_0_scratch0_array, NULL)

/* Tensor #12 */
AI_TENSOR_OBJ_DECLARE(
  _boundary_head_Conv_output_0_weights, AI_STATIC,
  12, 0x1,
  AI_SHAPE_INIT(4, 24, 1, 1, 1), AI_STRIDE_INIT(4, 1, 24, 24, 24),
  1, &_boundary_head_Conv_output_0_weights_array, &_boundary_head_Conv_output_0_weights_array_intq)

/* Tensor #13 */
AI_TENSOR_OBJ_DECLARE(
  _expand_expand_2_Clip_output_0_bias, AI_STATIC,
  13, 0x0,
  AI_SHAPE_INIT(4, 1, 24, 1, 1), AI_STRIDE_INIT(4, 4, 4, 96, 96),
  1, &_expand_expand_2_Clip_output_0_bias_array, NULL)

/* Tensor #14 */
AI_TENSOR_OBJ_DECLARE(
  _expand_expand_2_Clip_output_0_output, AI_STATIC,
  14, 0x1,
  AI_SHAPE_INIT(4, 1, 24, 320, 1), AI_STRIDE_INIT(4, 1, 1, 24, 7680),
  1, &_expand_expand_2_Clip_output_0_output_array, &_expand_expand_2_Clip_output_0_output_array_intq)

/* Tensor #15 */
AI_TENSOR_OBJ_DECLARE(
  _expand_expand_2_Clip_output_0_scratch0, AI_STATIC,
  15, 0x0,
  AI_SHAPE_INIT(4, 1, 256, 1, 1), AI_STRIDE_INIT(4, 1, 1, 256, 256),
  1, &_expand_expand_2_Clip_output_0_scratch0_array, NULL)

/* Tensor #16 */
AI_TENSOR_OBJ_DECLARE(
  _expand_expand_2_Clip_output_0_weights, AI_STATIC,
  16, 0x1,
  AI_SHAPE_INIT(4, 4, 1, 1, 24), AI_STRIDE_INIT(4, 1, 4, 96, 96),
  1, &_expand_expand_2_Clip_output_0_weights_array, &_expand_expand_2_Clip_output_0_weights_array_intq)

/* Tensor #17 */
AI_TENSOR_OBJ_DECLARE(
  _frame_head_Conv_output_0_bias, AI_STATIC,
  17, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &_frame_head_Conv_output_0_bias_array, NULL)

/* Tensor #18 */
AI_TENSOR_OBJ_DECLARE(
  _frame_head_Conv_output_0_output, AI_STATIC,
  18, 0x1,
  AI_SHAPE_INIT(4, 1, 1, 320, 1), AI_STRIDE_INIT(4, 1, 1, 1, 320),
  1, &_frame_head_Conv_output_0_output_array, &_frame_head_Conv_output_0_output_array_intq)

/* Tensor #19 */
AI_TENSOR_OBJ_DECLARE(
  _frame_head_Conv_output_0_scratch0, AI_STATIC,
  19, 0x0,
  AI_SHAPE_INIT(4, 1, 96, 1, 1), AI_STRIDE_INIT(4, 1, 1, 96, 96),
  1, &_frame_head_Conv_output_0_scratch0_array, NULL)

/* Tensor #20 */
AI_TENSOR_OBJ_DECLARE(
  _frame_head_Conv_output_0_weights, AI_STATIC,
  20, 0x1,
  AI_SHAPE_INIT(4, 24, 1, 1, 1), AI_STRIDE_INIT(4, 1, 24, 24, 24),
  1, &_frame_head_Conv_output_0_weights_array, &_frame_head_Conv_output_0_weights_array_intq)

/* Tensor #21 */
AI_TENSOR_OBJ_DECLARE(
  _frontend_frontend_2_Clip_output_0_bias, AI_STATIC,
  21, 0x0,
  AI_SHAPE_INIT(4, 1, 4, 1, 1), AI_STRIDE_INIT(4, 4, 4, 16, 16),
  1, &_frontend_frontend_2_Clip_output_0_bias_array, NULL)

/* Tensor #22 */
AI_TENSOR_OBJ_DECLARE(
  _frontend_frontend_2_Clip_output_0_output, AI_STATIC,
  22, 0x1,
  AI_SHAPE_INIT(4, 1, 4, 320, 1), AI_STRIDE_INIT(4, 1, 1, 4, 1280),
  1, &_frontend_frontend_2_Clip_output_0_output_array, &_frontend_frontend_2_Clip_output_0_output_array_intq)

/* Tensor #23 */
AI_TENSOR_OBJ_DECLARE(
  _frontend_frontend_2_Clip_output_0_scratch0, AI_STATIC,
  23, 0x0,
  AI_SHAPE_INIT(4, 1, 344, 1, 1), AI_STRIDE_INIT(4, 1, 1, 344, 344),
  1, &_frontend_frontend_2_Clip_output_0_scratch0_array, NULL)

/* Tensor #24 */
AI_TENSOR_OBJ_DECLARE(
  _frontend_frontend_2_Clip_output_0_scratch1, AI_STATIC,
  24, 0x1,
  AI_SHAPE_INIT(4, 1, 4, 959, 1), AI_STRIDE_INIT(4, 1, 1, 4, 3836),
  1, &_frontend_frontend_2_Clip_output_0_scratch1_array, &_frontend_frontend_2_Clip_output_0_scratch1_array_intq)

/* Tensor #25 */
AI_TENSOR_OBJ_DECLARE(
  _frontend_frontend_2_Clip_output_0_weights, AI_STATIC,
  25, 0x1,
  AI_SHAPE_INIT(4, 1, 24, 1, 4), AI_STRIDE_INIT(4, 1, 1, 4, 96),
  1, &_frontend_frontend_2_Clip_output_0_weights_array, &_frontend_frontend_2_Clip_output_0_weights_array_intq)

/* Tensor #26 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_0_net_net_0_Conv_output_0_bias, AI_STATIC,
  26, 0x0,
  AI_SHAPE_INIT(4, 1, 24, 1, 1), AI_STRIDE_INIT(4, 4, 4, 96, 96),
  1, &_tcn_layers_0_net_net_0_Conv_output_0_bias_array, NULL)

/* Tensor #27 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_0_net_net_0_Conv_output_0_output, AI_STATIC,
  27, 0x1,
  AI_SHAPE_INIT(4, 1, 24, 320, 1), AI_STRIDE_INIT(4, 1, 1, 24, 7680),
  1, &_tcn_layers_0_net_net_0_Conv_output_0_output_array, &_tcn_layers_0_net_net_0_Conv_output_0_output_array_intq)

/* Tensor #28 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_0_net_net_0_Conv_output_0_scratch0, AI_STATIC,
  28, 0x0,
  AI_SHAPE_INIT(4, 1, 745, 1, 1), AI_STRIDE_INIT(4, 1, 1, 745, 745),
  1, &_tcn_layers_0_net_net_0_Conv_output_0_scratch0_array, NULL)

/* Tensor #29 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_0_net_net_0_Conv_output_0_weights, AI_STATIC,
  29, 0x1,
  AI_SHAPE_INIT(4, 24, 7, 1, 1), AI_STRIDE_INIT(4, 1, 24, 24, 168),
  1, &_tcn_layers_0_net_net_0_Conv_output_0_weights_array, &_tcn_layers_0_net_net_0_Conv_output_0_weights_array_intq)

/* Tensor #30 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_0_net_net_3_Clip_output_0_bias, AI_STATIC,
  30, 0x0,
  AI_SHAPE_INIT(4, 1, 24, 1, 1), AI_STRIDE_INIT(4, 4, 4, 96, 96),
  1, &_tcn_layers_0_net_net_3_Clip_output_0_bias_array, NULL)

/* Tensor #31 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_0_net_net_3_Clip_output_0_output, AI_STATIC,
  31, 0x1,
  AI_SHAPE_INIT(4, 1, 24, 320, 1), AI_STRIDE_INIT(4, 1, 1, 24, 7680),
  1, &_tcn_layers_0_net_net_3_Clip_output_0_output_array, &_tcn_layers_0_net_net_3_Clip_output_0_output_array_intq)

/* Tensor #32 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_0_net_net_3_Clip_output_0_scratch0, AI_STATIC,
  32, 0x0,
  AI_SHAPE_INIT(4, 1, 336, 1, 1), AI_STRIDE_INIT(4, 1, 1, 336, 336),
  1, &_tcn_layers_0_net_net_3_Clip_output_0_scratch0_array, NULL)

/* Tensor #33 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_0_net_net_3_Clip_output_0_weights, AI_STATIC,
  33, 0x1,
  AI_SHAPE_INIT(4, 24, 1, 1, 24), AI_STRIDE_INIT(4, 1, 24, 576, 576),
  1, &_tcn_layers_0_net_net_3_Clip_output_0_weights_array, &_tcn_layers_0_net_net_3_Clip_output_0_weights_array_intq)

/* Tensor #34 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_0_net_net_5_Mul_output_0_output, AI_STATIC,
  34, 0x1,
  AI_SHAPE_INIT(4, 1, 24, 320, 1), AI_STRIDE_INIT(4, 1, 1, 24, 7680),
  1, &_tcn_layers_0_net_net_5_Mul_output_0_output_array, &_tcn_layers_0_net_net_5_Mul_output_0_output_array_intq)

/* Tensor #35 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_0_net_net_5_avg_pool_GlobalAveragePool_output_0_output, AI_STATIC,
  35, 0x1,
  AI_SHAPE_INIT(4, 1, 24, 1, 1), AI_STRIDE_INIT(4, 1, 1, 24, 24),
  1, &_tcn_layers_0_net_net_5_avg_pool_GlobalAveragePool_output_0_output_array, &_tcn_layers_0_net_net_5_avg_pool_GlobalAveragePool_output_0_output_array_intq)

/* Tensor #36 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_bias, AI_STATIC,
  36, 0x0,
  AI_SHAPE_INIT(4, 1, 12, 1, 1), AI_STRIDE_INIT(4, 4, 4, 48, 48),
  1, &_tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_bias_array, NULL)

/* Tensor #37 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_output, AI_STATIC,
  37, 0x1,
  AI_SHAPE_INIT(4, 1, 12, 1, 1), AI_STRIDE_INIT(4, 1, 1, 12, 12),
  1, &_tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_output_array, &_tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_output_array_intq)

/* Tensor #38 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_scratch0, AI_STATIC,
  38, 0x0,
  AI_SHAPE_INIT(4, 1, 84, 1, 1), AI_STRIDE_INIT(4, 2, 2, 168, 168),
  1, &_tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_scratch0_array, NULL)

/* Tensor #39 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_weights, AI_STATIC,
  39, 0x1,
  AI_SHAPE_INIT(4, 24, 12, 1, 1), AI_STRIDE_INIT(4, 1, 24, 288, 288),
  1, &_tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_weights_array, &_tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_weights_array_intq)

/* Tensor #40 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_0_net_net_5_fc_fc_2_MatMul_output_0_output, AI_STATIC,
  40, 0x1,
  AI_SHAPE_INIT(4, 1, 24, 1, 1), AI_STRIDE_INIT(4, 1, 1, 24, 24),
  1, &_tcn_layers_0_net_net_5_fc_fc_2_MatMul_output_0_output_array, &_tcn_layers_0_net_net_5_fc_fc_2_MatMul_output_0_output_array_intq)

/* Tensor #41 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_0_net_net_5_fc_fc_2_MatMul_output_0_scratch0, AI_STATIC,
  41, 0x0,
  AI_SHAPE_INIT(4, 1, 132, 1, 1), AI_STRIDE_INIT(4, 2, 2, 264, 264),
  1, &_tcn_layers_0_net_net_5_fc_fc_2_MatMul_output_0_scratch0_array, NULL)

/* Tensor #42 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_0_net_net_5_fc_fc_2_MatMul_output_0_weights, AI_STATIC,
  42, 0x1,
  AI_SHAPE_INIT(4, 12, 24, 1, 1), AI_STRIDE_INIT(4, 1, 12, 288, 288),
  1, &_tcn_layers_0_net_net_5_fc_fc_2_MatMul_output_0_weights_array, &_tcn_layers_0_net_net_5_fc_fc_2_MatMul_output_0_weights_array_intq)

/* Tensor #43 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_0_net_net_5_fc_fc_3_HardSigmoid_output_0_output, AI_STATIC,
  43, 0x1,
  AI_SHAPE_INIT(4, 1, 24, 1, 1), AI_STRIDE_INIT(4, 1, 1, 24, 24),
  1, &_tcn_layers_0_net_net_5_fc_fc_3_HardSigmoid_output_0_output_array, &_tcn_layers_0_net_net_5_fc_fc_3_HardSigmoid_output_0_output_array_intq)

/* Tensor #44 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_1_net_net_0_Conv_output_0_0_0__tcn_layers_1_net_net_3_Clip_output_0_conversion_output, AI_STATIC,
  44, 0x1,
  AI_SHAPE_INIT(4, 1, 24, 320, 1), AI_STRIDE_INIT(4, 1, 1, 24, 7680),
  1, &_tcn_layers_1_net_net_0_Conv_output_0_0_0__tcn_layers_1_net_net_3_Clip_output_0_conversion_output_array, &_tcn_layers_1_net_net_0_Conv_output_0_0_0__tcn_layers_1_net_net_3_Clip_output_0_conversion_output_array_intq)

/* Tensor #45 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_1_net_net_0_Conv_output_0_bias, AI_STATIC,
  45, 0x0,
  AI_SHAPE_INIT(4, 1, 24, 1, 1), AI_STRIDE_INIT(4, 4, 4, 96, 96),
  1, &_tcn_layers_1_net_net_0_Conv_output_0_bias_array, NULL)

/* Tensor #46 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_1_net_net_0_Conv_output_0_output, AI_STATIC,
  46, 0x0,
  AI_SHAPE_INIT(4, 1, 24, 320, 1), AI_STRIDE_INIT(4, 4, 4, 96, 30720),
  1, &_tcn_layers_1_net_net_0_Conv_output_0_output_array, NULL)

/* Tensor #47 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_1_net_net_0_Conv_output_0_weights, AI_STATIC,
  47, 0x0,
  AI_SHAPE_INIT(4, 1, 7, 1, 24), AI_STRIDE_INIT(4, 1, 24, 24, 24),
  1, &_tcn_layers_1_net_net_0_Conv_output_0_weights_array, NULL)

/* Tensor #48 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_1_net_net_3_Clip_output_0_bias, AI_STATIC,
  48, 0x0,
  AI_SHAPE_INIT(4, 1, 24, 1, 1), AI_STRIDE_INIT(4, 4, 4, 96, 96),
  1, &_tcn_layers_1_net_net_3_Clip_output_0_bias_array, NULL)

/* Tensor #49 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_1_net_net_3_Clip_output_0_output, AI_STATIC,
  49, 0x1,
  AI_SHAPE_INIT(4, 1, 24, 320, 1), AI_STRIDE_INIT(4, 1, 1, 24, 7680),
  1, &_tcn_layers_1_net_net_3_Clip_output_0_output_array, &_tcn_layers_1_net_net_3_Clip_output_0_output_array_intq)

/* Tensor #50 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_1_net_net_3_Clip_output_0_scratch0, AI_STATIC,
  50, 0x0,
  AI_SHAPE_INIT(4, 1, 336, 1, 1), AI_STRIDE_INIT(4, 1, 1, 336, 336),
  1, &_tcn_layers_1_net_net_3_Clip_output_0_scratch0_array, NULL)

/* Tensor #51 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_1_net_net_3_Clip_output_0_weights, AI_STATIC,
  51, 0x1,
  AI_SHAPE_INIT(4, 24, 1, 1, 24), AI_STRIDE_INIT(4, 1, 24, 576, 576),
  1, &_tcn_layers_1_net_net_3_Clip_output_0_weights_array, &_tcn_layers_1_net_net_3_Clip_output_0_weights_array_intq)

/* Tensor #52 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_1_net_net_5_Mul_output_0_output, AI_STATIC,
  52, 0x1,
  AI_SHAPE_INIT(4, 1, 24, 320, 1), AI_STRIDE_INIT(4, 1, 1, 24, 7680),
  1, &_tcn_layers_1_net_net_5_Mul_output_0_output_array, &_tcn_layers_1_net_net_5_Mul_output_0_output_array_intq)

/* Tensor #53 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_1_net_net_5_avg_pool_GlobalAveragePool_output_0_output, AI_STATIC,
  53, 0x1,
  AI_SHAPE_INIT(4, 1, 24, 1, 1), AI_STRIDE_INIT(4, 1, 1, 24, 24),
  1, &_tcn_layers_1_net_net_5_avg_pool_GlobalAveragePool_output_0_output_array, &_tcn_layers_1_net_net_5_avg_pool_GlobalAveragePool_output_0_output_array_intq)

/* Tensor #54 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_1_net_net_5_fc_fc_1_Clip_output_0_output, AI_STATIC,
  54, 0x1,
  AI_SHAPE_INIT(4, 1, 12, 1, 1), AI_STRIDE_INIT(4, 1, 1, 12, 12),
  1, &_tcn_layers_1_net_net_5_fc_fc_1_Clip_output_0_output_array, &_tcn_layers_1_net_net_5_fc_fc_1_Clip_output_0_output_array_intq)

/* Tensor #55 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_1_net_net_5_fc_fc_1_Clip_output_0_scratch0, AI_STATIC,
  55, 0x0,
  AI_SHAPE_INIT(4, 1, 84, 1, 1), AI_STRIDE_INIT(4, 2, 2, 168, 168),
  1, &_tcn_layers_1_net_net_5_fc_fc_1_Clip_output_0_scratch0_array, NULL)

/* Tensor #56 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_1_net_net_5_fc_fc_1_Clip_output_0_weights, AI_STATIC,
  56, 0x1,
  AI_SHAPE_INIT(4, 24, 12, 1, 1), AI_STRIDE_INIT(4, 1, 24, 288, 288),
  1, &_tcn_layers_1_net_net_5_fc_fc_1_Clip_output_0_weights_array, &_tcn_layers_1_net_net_5_fc_fc_1_Clip_output_0_weights_array_intq)

/* Tensor #57 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_1_net_net_5_fc_fc_2_MatMul_output_0_output, AI_STATIC,
  57, 0x1,
  AI_SHAPE_INIT(4, 1, 24, 1, 1), AI_STRIDE_INIT(4, 1, 1, 24, 24),
  1, &_tcn_layers_1_net_net_5_fc_fc_2_MatMul_output_0_output_array, &_tcn_layers_1_net_net_5_fc_fc_2_MatMul_output_0_output_array_intq)

/* Tensor #58 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_1_net_net_5_fc_fc_2_MatMul_output_0_scratch0, AI_STATIC,
  58, 0x0,
  AI_SHAPE_INIT(4, 1, 132, 1, 1), AI_STRIDE_INIT(4, 2, 2, 264, 264),
  1, &_tcn_layers_1_net_net_5_fc_fc_2_MatMul_output_0_scratch0_array, NULL)

/* Tensor #59 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_1_net_net_5_fc_fc_2_MatMul_output_0_weights, AI_STATIC,
  59, 0x1,
  AI_SHAPE_INIT(4, 12, 24, 1, 1), AI_STRIDE_INIT(4, 1, 12, 288, 288),
  1, &_tcn_layers_1_net_net_5_fc_fc_2_MatMul_output_0_weights_array, &_tcn_layers_1_net_net_5_fc_fc_2_MatMul_output_0_weights_array_intq)

/* Tensor #60 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_1_net_net_5_fc_fc_3_HardSigmoid_output_0_output, AI_STATIC,
  60, 0x1,
  AI_SHAPE_INIT(4, 1, 24, 1, 1), AI_STRIDE_INIT(4, 1, 1, 24, 24),
  1, &_tcn_layers_1_net_net_5_fc_fc_3_HardSigmoid_output_0_output_array, &_tcn_layers_1_net_net_5_fc_fc_3_HardSigmoid_output_0_output_array_intq)

/* Tensor #61 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_2_net_net_0_Conv_output_0_0_0__tcn_layers_2_net_net_3_Clip_output_0_conversion_output, AI_STATIC,
  61, 0x1,
  AI_SHAPE_INIT(4, 1, 24, 320, 1), AI_STRIDE_INIT(4, 1, 1, 24, 7680),
  1, &_tcn_layers_2_net_net_0_Conv_output_0_0_0__tcn_layers_2_net_net_3_Clip_output_0_conversion_output_array, &_tcn_layers_2_net_net_0_Conv_output_0_0_0__tcn_layers_2_net_net_3_Clip_output_0_conversion_output_array_intq)

/* Tensor #62 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_2_net_net_0_Conv_output_0_output, AI_STATIC,
  62, 0x0,
  AI_SHAPE_INIT(4, 1, 24, 320, 1), AI_STRIDE_INIT(4, 4, 4, 96, 30720),
  1, &_tcn_layers_2_net_net_0_Conv_output_0_output_array, NULL)

/* Tensor #63 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_2_net_net_0_Conv_output_0_weights, AI_STATIC,
  63, 0x0,
  AI_SHAPE_INIT(4, 1, 7, 1, 24), AI_STRIDE_INIT(4, 1, 24, 24, 24),
  1, &_tcn_layers_2_net_net_0_Conv_output_0_weights_array, NULL)

/* Tensor #64 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_2_net_net_3_Clip_output_0_bias, AI_STATIC,
  64, 0x0,
  AI_SHAPE_INIT(4, 1, 24, 1, 1), AI_STRIDE_INIT(4, 4, 4, 96, 96),
  1, &_tcn_layers_2_net_net_3_Clip_output_0_bias_array, NULL)

/* Tensor #65 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_2_net_net_3_Clip_output_0_output, AI_STATIC,
  65, 0x1,
  AI_SHAPE_INIT(4, 1, 24, 320, 1), AI_STRIDE_INIT(4, 1, 1, 24, 7680),
  1, &_tcn_layers_2_net_net_3_Clip_output_0_output_array, &_tcn_layers_2_net_net_3_Clip_output_0_output_array_intq)

/* Tensor #66 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_2_net_net_3_Clip_output_0_scratch0, AI_STATIC,
  66, 0x0,
  AI_SHAPE_INIT(4, 1, 336, 1, 1), AI_STRIDE_INIT(4, 1, 1, 336, 336),
  1, &_tcn_layers_2_net_net_3_Clip_output_0_scratch0_array, NULL)

/* Tensor #67 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_2_net_net_3_Clip_output_0_weights, AI_STATIC,
  67, 0x1,
  AI_SHAPE_INIT(4, 24, 1, 1, 24), AI_STRIDE_INIT(4, 1, 24, 576, 576),
  1, &_tcn_layers_2_net_net_3_Clip_output_0_weights_array, &_tcn_layers_2_net_net_3_Clip_output_0_weights_array_intq)

/* Tensor #68 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_2_net_net_5_Mul_output_0_output, AI_STATIC,
  68, 0x1,
  AI_SHAPE_INIT(4, 1, 24, 320, 1), AI_STRIDE_INIT(4, 1, 1, 24, 7680),
  1, &_tcn_layers_2_net_net_5_Mul_output_0_output_array, &_tcn_layers_2_net_net_5_Mul_output_0_output_array_intq)

/* Tensor #69 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_2_net_net_5_avg_pool_GlobalAveragePool_output_0_output, AI_STATIC,
  69, 0x1,
  AI_SHAPE_INIT(4, 1, 24, 1, 1), AI_STRIDE_INIT(4, 1, 1, 24, 24),
  1, &_tcn_layers_2_net_net_5_avg_pool_GlobalAveragePool_output_0_output_array, &_tcn_layers_2_net_net_5_avg_pool_GlobalAveragePool_output_0_output_array_intq)

/* Tensor #70 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_2_net_net_5_fc_fc_1_Clip_output_0_output, AI_STATIC,
  70, 0x1,
  AI_SHAPE_INIT(4, 1, 12, 1, 1), AI_STRIDE_INIT(4, 1, 1, 12, 12),
  1, &_tcn_layers_2_net_net_5_fc_fc_1_Clip_output_0_output_array, &_tcn_layers_2_net_net_5_fc_fc_1_Clip_output_0_output_array_intq)

/* Tensor #71 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_2_net_net_5_fc_fc_1_Clip_output_0_scratch0, AI_STATIC,
  71, 0x0,
  AI_SHAPE_INIT(4, 1, 84, 1, 1), AI_STRIDE_INIT(4, 2, 2, 168, 168),
  1, &_tcn_layers_2_net_net_5_fc_fc_1_Clip_output_0_scratch0_array, NULL)

/* Tensor #72 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_2_net_net_5_fc_fc_1_Clip_output_0_weights, AI_STATIC,
  72, 0x1,
  AI_SHAPE_INIT(4, 24, 12, 1, 1), AI_STRIDE_INIT(4, 1, 24, 288, 288),
  1, &_tcn_layers_2_net_net_5_fc_fc_1_Clip_output_0_weights_array, &_tcn_layers_2_net_net_5_fc_fc_1_Clip_output_0_weights_array_intq)

/* Tensor #73 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_2_net_net_5_fc_fc_2_MatMul_output_0_output, AI_STATIC,
  73, 0x1,
  AI_SHAPE_INIT(4, 1, 24, 1, 1), AI_STRIDE_INIT(4, 1, 1, 24, 24),
  1, &_tcn_layers_2_net_net_5_fc_fc_2_MatMul_output_0_output_array, &_tcn_layers_2_net_net_5_fc_fc_2_MatMul_output_0_output_array_intq)

/* Tensor #74 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_2_net_net_5_fc_fc_2_MatMul_output_0_scratch0, AI_STATIC,
  74, 0x0,
  AI_SHAPE_INIT(4, 1, 132, 1, 1), AI_STRIDE_INIT(4, 2, 2, 264, 264),
  1, &_tcn_layers_2_net_net_5_fc_fc_2_MatMul_output_0_scratch0_array, NULL)

/* Tensor #75 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_2_net_net_5_fc_fc_2_MatMul_output_0_weights, AI_STATIC,
  75, 0x1,
  AI_SHAPE_INIT(4, 12, 24, 1, 1), AI_STRIDE_INIT(4, 1, 12, 288, 288),
  1, &_tcn_layers_2_net_net_5_fc_fc_2_MatMul_output_0_weights_array, &_tcn_layers_2_net_net_5_fc_fc_2_MatMul_output_0_weights_array_intq)

/* Tensor #76 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_2_net_net_5_fc_fc_3_HardSigmoid_output_0_output, AI_STATIC,
  76, 0x1,
  AI_SHAPE_INIT(4, 1, 24, 1, 1), AI_STRIDE_INIT(4, 1, 1, 24, 24),
  1, &_tcn_layers_2_net_net_5_fc_fc_3_HardSigmoid_output_0_output_array, &_tcn_layers_2_net_net_5_fc_fc_3_HardSigmoid_output_0_output_array_intq)

/* Tensor #77 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_3_net_net_0_Conv_output_0_0_0__tcn_layers_3_net_net_3_Clip_output_0_conversion_output, AI_STATIC,
  77, 0x1,
  AI_SHAPE_INIT(4, 1, 24, 320, 1), AI_STRIDE_INIT(4, 1, 1, 24, 7680),
  1, &_tcn_layers_3_net_net_0_Conv_output_0_0_0__tcn_layers_3_net_net_3_Clip_output_0_conversion_output_array, &_tcn_layers_3_net_net_0_Conv_output_0_0_0__tcn_layers_3_net_net_3_Clip_output_0_conversion_output_array_intq)

/* Tensor #78 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_3_net_net_0_Conv_output_0_output, AI_STATIC,
  78, 0x0,
  AI_SHAPE_INIT(4, 1, 24, 320, 1), AI_STRIDE_INIT(4, 4, 4, 96, 30720),
  1, &_tcn_layers_3_net_net_0_Conv_output_0_output_array, NULL)

/* Tensor #79 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_3_net_net_0_Conv_output_0_weights, AI_STATIC,
  79, 0x0,
  AI_SHAPE_INIT(4, 1, 7, 1, 24), AI_STRIDE_INIT(4, 1, 24, 24, 24),
  1, &_tcn_layers_3_net_net_0_Conv_output_0_weights_array, NULL)

/* Tensor #80 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_3_net_net_3_Clip_output_0_bias, AI_STATIC,
  80, 0x0,
  AI_SHAPE_INIT(4, 1, 24, 1, 1), AI_STRIDE_INIT(4, 4, 4, 96, 96),
  1, &_tcn_layers_3_net_net_3_Clip_output_0_bias_array, NULL)

/* Tensor #81 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_3_net_net_3_Clip_output_0_output, AI_STATIC,
  81, 0x1,
  AI_SHAPE_INIT(4, 1, 24, 320, 1), AI_STRIDE_INIT(4, 1, 1, 24, 7680),
  1, &_tcn_layers_3_net_net_3_Clip_output_0_output_array, &_tcn_layers_3_net_net_3_Clip_output_0_output_array_intq)

/* Tensor #82 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_3_net_net_3_Clip_output_0_scratch0, AI_STATIC,
  82, 0x0,
  AI_SHAPE_INIT(4, 1, 336, 1, 1), AI_STRIDE_INIT(4, 1, 1, 336, 336),
  1, &_tcn_layers_3_net_net_3_Clip_output_0_scratch0_array, NULL)

/* Tensor #83 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_3_net_net_3_Clip_output_0_weights, AI_STATIC,
  83, 0x1,
  AI_SHAPE_INIT(4, 24, 1, 1, 24), AI_STRIDE_INIT(4, 1, 24, 576, 576),
  1, &_tcn_layers_3_net_net_3_Clip_output_0_weights_array, &_tcn_layers_3_net_net_3_Clip_output_0_weights_array_intq)

/* Tensor #84 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_3_net_net_5_Mul_output_0_output, AI_STATIC,
  84, 0x1,
  AI_SHAPE_INIT(4, 1, 24, 320, 1), AI_STRIDE_INIT(4, 1, 1, 24, 7680),
  1, &_tcn_layers_3_net_net_5_Mul_output_0_output_array, &_tcn_layers_3_net_net_5_Mul_output_0_output_array_intq)

/* Tensor #85 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_3_net_net_5_avg_pool_GlobalAveragePool_output_0_output, AI_STATIC,
  85, 0x1,
  AI_SHAPE_INIT(4, 1, 24, 1, 1), AI_STRIDE_INIT(4, 1, 1, 24, 24),
  1, &_tcn_layers_3_net_net_5_avg_pool_GlobalAveragePool_output_0_output_array, &_tcn_layers_3_net_net_5_avg_pool_GlobalAveragePool_output_0_output_array_intq)

/* Tensor #86 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_3_net_net_5_fc_fc_1_Clip_output_0_output, AI_STATIC,
  86, 0x1,
  AI_SHAPE_INIT(4, 1, 12, 1, 1), AI_STRIDE_INIT(4, 1, 1, 12, 12),
  1, &_tcn_layers_3_net_net_5_fc_fc_1_Clip_output_0_output_array, &_tcn_layers_3_net_net_5_fc_fc_1_Clip_output_0_output_array_intq)

/* Tensor #87 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_3_net_net_5_fc_fc_1_Clip_output_0_scratch0, AI_STATIC,
  87, 0x0,
  AI_SHAPE_INIT(4, 1, 84, 1, 1), AI_STRIDE_INIT(4, 2, 2, 168, 168),
  1, &_tcn_layers_3_net_net_5_fc_fc_1_Clip_output_0_scratch0_array, NULL)

/* Tensor #88 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_3_net_net_5_fc_fc_1_Clip_output_0_weights, AI_STATIC,
  88, 0x1,
  AI_SHAPE_INIT(4, 24, 12, 1, 1), AI_STRIDE_INIT(4, 1, 24, 288, 288),
  1, &_tcn_layers_3_net_net_5_fc_fc_1_Clip_output_0_weights_array, &_tcn_layers_3_net_net_5_fc_fc_1_Clip_output_0_weights_array_intq)

/* Tensor #89 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_3_net_net_5_fc_fc_2_MatMul_output_0_output, AI_STATIC,
  89, 0x1,
  AI_SHAPE_INIT(4, 1, 24, 1, 1), AI_STRIDE_INIT(4, 1, 1, 24, 24),
  1, &_tcn_layers_3_net_net_5_fc_fc_2_MatMul_output_0_output_array, &_tcn_layers_3_net_net_5_fc_fc_2_MatMul_output_0_output_array_intq)

/* Tensor #90 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_3_net_net_5_fc_fc_2_MatMul_output_0_scratch0, AI_STATIC,
  90, 0x0,
  AI_SHAPE_INIT(4, 1, 132, 1, 1), AI_STRIDE_INIT(4, 2, 2, 264, 264),
  1, &_tcn_layers_3_net_net_5_fc_fc_2_MatMul_output_0_scratch0_array, NULL)

/* Tensor #91 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_3_net_net_5_fc_fc_2_MatMul_output_0_weights, AI_STATIC,
  91, 0x1,
  AI_SHAPE_INIT(4, 12, 24, 1, 1), AI_STRIDE_INIT(4, 1, 12, 288, 288),
  1, &_tcn_layers_3_net_net_5_fc_fc_2_MatMul_output_0_weights_array, &_tcn_layers_3_net_net_5_fc_fc_2_MatMul_output_0_weights_array_intq)

/* Tensor #92 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_3_net_net_5_fc_fc_3_HardSigmoid_output_0_output, AI_STATIC,
  92, 0x1,
  AI_SHAPE_INIT(4, 1, 24, 1, 1), AI_STRIDE_INIT(4, 1, 1, 24, 24),
  1, &_tcn_layers_3_net_net_5_fc_fc_3_HardSigmoid_output_0_output_array, &_tcn_layers_3_net_net_5_fc_fc_3_HardSigmoid_output_0_output_array_intq)

/* Tensor #93 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_4_net_net_0_Conv_output_0_0_0__tcn_layers_4_net_net_3_Clip_output_0_conversion_output, AI_STATIC,
  93, 0x1,
  AI_SHAPE_INIT(4, 1, 24, 320, 1), AI_STRIDE_INIT(4, 1, 1, 24, 7680),
  1, &_tcn_layers_4_net_net_0_Conv_output_0_0_0__tcn_layers_4_net_net_3_Clip_output_0_conversion_output_array, &_tcn_layers_4_net_net_0_Conv_output_0_0_0__tcn_layers_4_net_net_3_Clip_output_0_conversion_output_array_intq)

/* Tensor #94 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_4_net_net_0_Conv_output_0_output, AI_STATIC,
  94, 0x0,
  AI_SHAPE_INIT(4, 1, 24, 320, 1), AI_STRIDE_INIT(4, 4, 4, 96, 30720),
  1, &_tcn_layers_4_net_net_0_Conv_output_0_output_array, NULL)

/* Tensor #95 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_4_net_net_0_Conv_output_0_weights, AI_STATIC,
  95, 0x0,
  AI_SHAPE_INIT(4, 1, 7, 1, 24), AI_STRIDE_INIT(4, 1, 24, 24, 24),
  1, &_tcn_layers_4_net_net_0_Conv_output_0_weights_array, NULL)

/* Tensor #96 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_4_net_net_3_Clip_output_0_bias, AI_STATIC,
  96, 0x0,
  AI_SHAPE_INIT(4, 1, 24, 1, 1), AI_STRIDE_INIT(4, 4, 4, 96, 96),
  1, &_tcn_layers_4_net_net_3_Clip_output_0_bias_array, NULL)

/* Tensor #97 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_4_net_net_3_Clip_output_0_output, AI_STATIC,
  97, 0x1,
  AI_SHAPE_INIT(4, 1, 24, 320, 1), AI_STRIDE_INIT(4, 1, 1, 24, 7680),
  1, &_tcn_layers_4_net_net_3_Clip_output_0_output_array, &_tcn_layers_4_net_net_3_Clip_output_0_output_array_intq)

/* Tensor #98 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_4_net_net_3_Clip_output_0_scratch0, AI_STATIC,
  98, 0x0,
  AI_SHAPE_INIT(4, 1, 336, 1, 1), AI_STRIDE_INIT(4, 1, 1, 336, 336),
  1, &_tcn_layers_4_net_net_3_Clip_output_0_scratch0_array, NULL)

/* Tensor #99 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_4_net_net_3_Clip_output_0_weights, AI_STATIC,
  99, 0x1,
  AI_SHAPE_INIT(4, 24, 1, 1, 24), AI_STRIDE_INIT(4, 1, 24, 576, 576),
  1, &_tcn_layers_4_net_net_3_Clip_output_0_weights_array, &_tcn_layers_4_net_net_3_Clip_output_0_weights_array_intq)

/* Tensor #100 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_4_net_net_5_Mul_output_0_output, AI_STATIC,
  100, 0x1,
  AI_SHAPE_INIT(4, 1, 24, 320, 1), AI_STRIDE_INIT(4, 1, 1, 24, 7680),
  1, &_tcn_layers_4_net_net_5_Mul_output_0_output_array, &_tcn_layers_4_net_net_5_Mul_output_0_output_array_intq)

/* Tensor #101 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_4_net_net_5_avg_pool_GlobalAveragePool_output_0_output, AI_STATIC,
  101, 0x1,
  AI_SHAPE_INIT(4, 1, 24, 1, 1), AI_STRIDE_INIT(4, 1, 1, 24, 24),
  1, &_tcn_layers_4_net_net_5_avg_pool_GlobalAveragePool_output_0_output_array, &_tcn_layers_4_net_net_5_avg_pool_GlobalAveragePool_output_0_output_array_intq)

/* Tensor #102 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_4_net_net_5_fc_fc_1_Clip_output_0_output, AI_STATIC,
  102, 0x1,
  AI_SHAPE_INIT(4, 1, 12, 1, 1), AI_STRIDE_INIT(4, 1, 1, 12, 12),
  1, &_tcn_layers_4_net_net_5_fc_fc_1_Clip_output_0_output_array, &_tcn_layers_4_net_net_5_fc_fc_1_Clip_output_0_output_array_intq)

/* Tensor #103 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_4_net_net_5_fc_fc_1_Clip_output_0_scratch0, AI_STATIC,
  103, 0x0,
  AI_SHAPE_INIT(4, 1, 84, 1, 1), AI_STRIDE_INIT(4, 2, 2, 168, 168),
  1, &_tcn_layers_4_net_net_5_fc_fc_1_Clip_output_0_scratch0_array, NULL)

/* Tensor #104 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_4_net_net_5_fc_fc_1_Clip_output_0_weights, AI_STATIC,
  104, 0x1,
  AI_SHAPE_INIT(4, 24, 12, 1, 1), AI_STRIDE_INIT(4, 1, 24, 288, 288),
  1, &_tcn_layers_4_net_net_5_fc_fc_1_Clip_output_0_weights_array, &_tcn_layers_4_net_net_5_fc_fc_1_Clip_output_0_weights_array_intq)

/* Tensor #105 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_4_net_net_5_fc_fc_2_MatMul_output_0_output, AI_STATIC,
  105, 0x1,
  AI_SHAPE_INIT(4, 1, 24, 1, 1), AI_STRIDE_INIT(4, 1, 1, 24, 24),
  1, &_tcn_layers_4_net_net_5_fc_fc_2_MatMul_output_0_output_array, &_tcn_layers_4_net_net_5_fc_fc_2_MatMul_output_0_output_array_intq)

/* Tensor #106 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_4_net_net_5_fc_fc_2_MatMul_output_0_scratch0, AI_STATIC,
  106, 0x0,
  AI_SHAPE_INIT(4, 1, 132, 1, 1), AI_STRIDE_INIT(4, 2, 2, 264, 264),
  1, &_tcn_layers_4_net_net_5_fc_fc_2_MatMul_output_0_scratch0_array, NULL)

/* Tensor #107 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_4_net_net_5_fc_fc_2_MatMul_output_0_weights, AI_STATIC,
  107, 0x1,
  AI_SHAPE_INIT(4, 12, 24, 1, 1), AI_STRIDE_INIT(4, 1, 12, 288, 288),
  1, &_tcn_layers_4_net_net_5_fc_fc_2_MatMul_output_0_weights_array, &_tcn_layers_4_net_net_5_fc_fc_2_MatMul_output_0_weights_array_intq)

/* Tensor #108 */
AI_TENSOR_OBJ_DECLARE(
  _tcn_layers_4_net_net_5_fc_fc_3_HardSigmoid_output_0_output, AI_STATIC,
  108, 0x1,
  AI_SHAPE_INIT(4, 1, 24, 1, 1), AI_STRIDE_INIT(4, 1, 1, 24, 24),
  1, &_tcn_layers_4_net_net_5_fc_fc_3_HardSigmoid_output_0_output_array, &_tcn_layers_4_net_net_5_fc_fc_3_HardSigmoid_output_0_output_array_intq)

/* Tensor #109 */
AI_TENSOR_OBJ_DECLARE(
  input_output, AI_STATIC,
  109, 0x1,
  AI_SHAPE_INIT(4, 1, 1, 960, 1), AI_STRIDE_INIT(4, 1, 1, 1, 960),
  1, &input_output_array, &input_output_array_intq)



/**  Layer declarations section  **********************************************/


AI_TENSOR_CHAIN_OBJ_DECLARE(
  _frame_head_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_Add_4_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_frame_head_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_frame_head_Conv_output_0_weights, &_frame_head_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_frame_head_Conv_output_0_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  _frame_head_Conv_output_0_layer, 195,
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
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_Add_4_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_boundary_head_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_boundary_head_Conv_output_0_weights, &_boundary_head_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_boundary_head_Conv_output_0_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  _boundary_head_Conv_output_0_layer, 196,
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
  _Add_4_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_Add_3_output_0_output, &_tcn_layers_4_net_net_5_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_Add_4_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _Add_4_output_0_layer, 192,
  ELTWISE_INTEGER_TYPE, 0x0, NULL,
  eltwise_integer, forward_eltwise_integer_INT8,
  &_Add_4_output_0_chain,
  NULL, &_boundary_head_Conv_output_0_layer, AI_STATIC, 
  .operation = ai_sum_f32, 
  .buffer_operation = ai_sum_buffer_INT8, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _tcn_layers_4_net_net_5_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_tcn_layers_4_net_net_3_Clip_output_0_output, &_tcn_layers_4_net_net_5_fc_fc_3_HardSigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_4_net_net_5_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _tcn_layers_4_net_net_5_Mul_output_0_layer, 189,
  ELTWISE_INTEGER_TYPE, 0x0, NULL,
  eltwise_integer, forward_eltwise_integer_INT8,
  &_tcn_layers_4_net_net_5_Mul_output_0_chain,
  NULL, &_Add_4_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_INT8, 
)


AI_STATIC_CONST ai_i8 _tcn_layers_4_net_net_5_fc_fc_3_HardSigmoid_output_0_nl_params_data[] = { -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -127, -124, -122, -119, -117, -114, -111, -109, -106, -104, -101, -98, -96, -93, -91, -88, -86, -83, -80, -78, -75, -73, -70, -68, -65, -62, -60, -57, -55, -52, -49, -47, -44, -42, -39, -37, -34, -31, -29, -26, -24, -21, -19, -16, -13, -11, -8, -6, -3, -1, 2, 5, 7, 10, 12, 15, 18, 20, 23, 25, 28, 30, 33, 36, 38, 41, 43, 46, 48, 51, 54, 56, 59, 61, 64, 67, 69, 72, 74, 77, 79, 82, 85, 87, 90, 92, 95, 97, 100, 103, 105, 108, 110, 113, 116, 118, 121, 123, 126, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127 };
AI_ARRAY_OBJ_DECLARE(
    _tcn_layers_4_net_net_5_fc_fc_3_HardSigmoid_output_0_nl_params, AI_ARRAY_FORMAT_S8,
    _tcn_layers_4_net_net_5_fc_fc_3_HardSigmoid_output_0_nl_params_data, _tcn_layers_4_net_net_5_fc_fc_3_HardSigmoid_output_0_nl_params_data, 256, AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(
  _tcn_layers_4_net_net_5_fc_fc_3_HardSigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_4_net_net_5_fc_fc_2_MatMul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_4_net_net_5_fc_fc_3_HardSigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _tcn_layers_4_net_net_5_fc_fc_3_HardSigmoid_output_0_layer, 183,
  NL_TYPE, 0x0, NULL,
  nl, forward_nl_integer,
  &_tcn_layers_4_net_net_5_fc_fc_3_HardSigmoid_output_0_chain,
  NULL, &_tcn_layers_4_net_net_5_Mul_output_0_layer, AI_STATIC, 
  .nl_params = &_tcn_layers_4_net_net_5_fc_fc_3_HardSigmoid_output_0_nl_params, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _tcn_layers_4_net_net_5_fc_fc_2_MatMul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_4_net_net_5_fc_fc_1_Clip_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_4_net_net_5_fc_fc_2_MatMul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_tcn_layers_4_net_net_5_fc_fc_2_MatMul_output_0_weights, &_tcn_layers_0_net_net_0_Conv_output_0_bias),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_4_net_net_5_fc_fc_2_MatMul_output_0_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  _tcn_layers_4_net_net_5_fc_fc_2_MatMul_output_0_layer, 180,
  DENSE_TYPE, 0x0, NULL,
  dense, forward_dense_integer_SSSA_ch,
  &_tcn_layers_4_net_net_5_fc_fc_2_MatMul_output_0_chain,
  NULL, &_tcn_layers_4_net_net_5_fc_fc_3_HardSigmoid_output_0_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _tcn_layers_4_net_net_5_fc_fc_1_Clip_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_4_net_net_5_avg_pool_GlobalAveragePool_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_4_net_net_5_fc_fc_1_Clip_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_tcn_layers_4_net_net_5_fc_fc_1_Clip_output_0_weights, &_tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_bias),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_4_net_net_5_fc_fc_1_Clip_output_0_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  _tcn_layers_4_net_net_5_fc_fc_1_Clip_output_0_layer, 177,
  DENSE_TYPE, 0x0, NULL,
  dense, forward_dense_integer_SSSA_ch,
  &_tcn_layers_4_net_net_5_fc_fc_1_Clip_output_0_chain,
  NULL, &_tcn_layers_4_net_net_5_fc_fc_2_MatMul_output_0_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _tcn_layers_4_net_net_5_avg_pool_GlobalAveragePool_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_4_net_net_3_Clip_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_4_net_net_5_avg_pool_GlobalAveragePool_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _tcn_layers_4_net_net_5_avg_pool_GlobalAveragePool_output_0_layer, 171,
  POOL_TYPE, 0x0, NULL,
  pool, forward_ap_integer_INT8,
  &_tcn_layers_4_net_net_5_avg_pool_GlobalAveragePool_output_0_chain,
  NULL, &_tcn_layers_4_net_net_5_fc_fc_1_Clip_output_0_layer, AI_STATIC, 
  .pool_size = AI_SHAPE_2D_INIT(320, 1), 
  .pool_stride = AI_SHAPE_2D_INIT(320, 1), 
  .pool_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _tcn_layers_4_net_net_3_Clip_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_4_net_net_0_Conv_output_0_0_0__tcn_layers_4_net_net_3_Clip_output_0_conversion_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_4_net_net_3_Clip_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_tcn_layers_4_net_net_3_Clip_output_0_weights, &_tcn_layers_4_net_net_3_Clip_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_4_net_net_3_Clip_output_0_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  _tcn_layers_4_net_net_3_Clip_output_0_layer, 168,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_pw_sssa8_ch,
  &_tcn_layers_4_net_net_3_Clip_output_0_chain,
  NULL, &_tcn_layers_4_net_net_5_avg_pool_GlobalAveragePool_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _tcn_layers_4_net_net_0_Conv_output_0_0_0__tcn_layers_4_net_net_3_Clip_output_0_conversion_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_4_net_net_0_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_4_net_net_0_Conv_output_0_0_0__tcn_layers_4_net_net_3_Clip_output_0_conversion_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _tcn_layers_4_net_net_0_Conv_output_0_0_0__tcn_layers_4_net_net_3_Clip_output_0_conversion_layer, 165,
  NL_TYPE, 0x0, NULL,
  nl, node_convert,
  &_tcn_layers_4_net_net_0_Conv_output_0_0_0__tcn_layers_4_net_net_3_Clip_output_0_conversion_chain,
  NULL, &_tcn_layers_4_net_net_3_Clip_output_0_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _tcn_layers_4_net_net_0_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_Add_3_output_0_0_0__tcn_layers_4_net_net_0_Conv_output_0_conversion_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_tcn_layers_4_net_net_0_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_tcn_layers_4_net_net_0_Conv_output_0_weights, &_tcn_layers_1_net_net_0_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _tcn_layers_4_net_net_0_Conv_output_0_layer, 165,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32_group,
  &_tcn_layers_4_net_net_0_Conv_output_0_chain,
  NULL, &_tcn_layers_4_net_net_0_Conv_output_0_0_0__tcn_layers_4_net_net_3_Clip_output_0_conversion_layer, AI_STATIC, 
  .groups = 24, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(16, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 48, 0, 48), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _Add_3_output_0_0_0__tcn_layers_4_net_net_0_Conv_output_0_conversion_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_Add_3_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_Add_3_output_0_0_0__tcn_layers_4_net_net_0_Conv_output_0_conversion_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _Add_3_output_0_0_0__tcn_layers_4_net_net_0_Conv_output_0_conversion_layer, 162,
  NL_TYPE, 0x0, NULL,
  nl, node_convert,
  &_Add_3_output_0_0_0__tcn_layers_4_net_net_0_Conv_output_0_conversion_chain,
  NULL, &_tcn_layers_4_net_net_0_Conv_output_0_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _Add_3_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_Add_2_output_0_output, &_tcn_layers_3_net_net_5_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_Add_3_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _Add_3_output_0_layer, 162,
  ELTWISE_INTEGER_TYPE, 0x0, NULL,
  eltwise_integer, forward_eltwise_integer_INT8,
  &_Add_3_output_0_chain,
  NULL, &_Add_3_output_0_0_0__tcn_layers_4_net_net_0_Conv_output_0_conversion_layer, AI_STATIC, 
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
  _tcn_layers_3_net_net_5_Mul_output_0_layer, 159,
  ELTWISE_INTEGER_TYPE, 0x0, NULL,
  eltwise_integer, forward_eltwise_integer_INT8,
  &_tcn_layers_3_net_net_5_Mul_output_0_chain,
  NULL, &_Add_3_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_INT8, 
)


AI_STATIC_CONST ai_i8 _tcn_layers_3_net_net_5_fc_fc_3_HardSigmoid_output_0_nl_params_data[] = { -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -125, -122, -119, -116, -113, -110, -108, -105, -102, -99, -96, -93, -90, -87, -84, -82, -79, -76, -73, -70, -67, -64, -61, -58, -55, -53, -50, -47, -44, -41, -38, -35, -32, -29, -27, -24, -21, -18, -15, -12, -9, -6, -3, -1, 2, 5, 8, 11, 14, 17, 20, 23, 26, 28, 31, 34, 37, 40, 43, 46, 49, 52, 54, 57, 60, 63, 66, 69, 72, 75, 78, 81, 83, 86, 89, 92, 95, 98, 101, 104, 107, 109, 112, 115, 118, 121, 124, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127 };
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
  _tcn_layers_3_net_net_5_fc_fc_3_HardSigmoid_output_0_layer, 153,
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
  _tcn_layers_3_net_net_5_fc_fc_2_MatMul_output_0_layer, 150,
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
  _tcn_layers_3_net_net_5_fc_fc_1_Clip_output_0_layer, 147,
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
  _tcn_layers_3_net_net_5_avg_pool_GlobalAveragePool_output_0_layer, 141,
  POOL_TYPE, 0x0, NULL,
  pool, forward_ap_integer_INT8,
  &_tcn_layers_3_net_net_5_avg_pool_GlobalAveragePool_output_0_chain,
  NULL, &_tcn_layers_3_net_net_5_fc_fc_1_Clip_output_0_layer, AI_STATIC, 
  .pool_size = AI_SHAPE_2D_INIT(320, 1), 
  .pool_stride = AI_SHAPE_2D_INIT(320, 1), 
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
  _tcn_layers_3_net_net_3_Clip_output_0_layer, 138,
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
  _tcn_layers_3_net_net_0_Conv_output_0_0_0__tcn_layers_3_net_net_3_Clip_output_0_conversion_layer, 135,
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
  _tcn_layers_3_net_net_0_Conv_output_0_layer, 135,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32_group,
  &_tcn_layers_3_net_net_0_Conv_output_0_chain,
  NULL, &_tcn_layers_3_net_net_0_Conv_output_0_0_0__tcn_layers_3_net_net_3_Clip_output_0_conversion_layer, AI_STATIC, 
  .groups = 24, 
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
  _Add_2_output_0_0_0__tcn_layers_3_net_net_0_Conv_output_0_conversion_layer, 132,
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
  _Add_2_output_0_layer, 132,
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
  _tcn_layers_2_net_net_5_Mul_output_0_layer, 129,
  ELTWISE_INTEGER_TYPE, 0x0, NULL,
  eltwise_integer, forward_eltwise_integer_INT8,
  &_tcn_layers_2_net_net_5_Mul_output_0_chain,
  NULL, &_Add_2_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_INT8, 
)


AI_STATIC_CONST ai_i8 _tcn_layers_2_net_net_5_fc_fc_3_HardSigmoid_output_0_nl_params_data[] = { -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -127, -125, -123, -121, -119, -117, -115, -113, -111, -109, -107, -105, -103, -102, -100, -98, -96, -94, -92, -90, -88, -86, -84, -82, -80, -78, -76, -74, -72, -70, -68, -67, -65, -63, -61, -59, -57, -55, -53, -51, -49, -47, -45, -43, -41, -39, -37, -35, -34, -32, -30, -28, -26, -24, -22, -20, -18, -16, -14, -12, -10, -8, -6, -4, -2, -1, 1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31, 33, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52, 54, 56, 58, 60, 62, 64, 66, 67, 69, 71, 73, 75, 77, 79, 81, 83, 85, 87, 89, 91, 93, 95, 97, 99, 101, 102, 104, 106, 108, 110, 112, 114, 116, 118, 120, 122, 124, 126, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127 };
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
  _tcn_layers_2_net_net_5_fc_fc_3_HardSigmoid_output_0_layer, 123,
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
  _tcn_layers_2_net_net_5_fc_fc_2_MatMul_output_0_layer, 120,
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
  _tcn_layers_2_net_net_5_fc_fc_1_Clip_output_0_layer, 117,
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
  _tcn_layers_2_net_net_5_avg_pool_GlobalAveragePool_output_0_layer, 111,
  POOL_TYPE, 0x0, NULL,
  pool, forward_ap_integer_INT8,
  &_tcn_layers_2_net_net_5_avg_pool_GlobalAveragePool_output_0_chain,
  NULL, &_tcn_layers_2_net_net_5_fc_fc_1_Clip_output_0_layer, AI_STATIC, 
  .pool_size = AI_SHAPE_2D_INIT(320, 1), 
  .pool_stride = AI_SHAPE_2D_INIT(320, 1), 
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
  _tcn_layers_2_net_net_3_Clip_output_0_layer, 108,
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
  _tcn_layers_2_net_net_0_Conv_output_0_0_0__tcn_layers_2_net_net_3_Clip_output_0_conversion_layer, 105,
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
  _tcn_layers_2_net_net_0_Conv_output_0_layer, 105,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32_group,
  &_tcn_layers_2_net_net_0_Conv_output_0_chain,
  NULL, &_tcn_layers_2_net_net_0_Conv_output_0_0_0__tcn_layers_2_net_net_3_Clip_output_0_conversion_layer, AI_STATIC, 
  .groups = 24, 
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
  _Add_1_output_0_0_0__tcn_layers_2_net_net_0_Conv_output_0_conversion_layer, 102,
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
  _Add_1_output_0_layer, 102,
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
  _tcn_layers_1_net_net_5_Mul_output_0_layer, 99,
  ELTWISE_INTEGER_TYPE, 0x0, NULL,
  eltwise_integer, forward_eltwise_integer_INT8,
  &_tcn_layers_1_net_net_5_Mul_output_0_chain,
  NULL, &_Add_1_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_INT8, 
)


AI_STATIC_CONST ai_i8 _tcn_layers_1_net_net_5_fc_fc_3_HardSigmoid_output_0_nl_params_data[] = { -114, -113, -112, -110, -109, -108, -106, -105, -104, -103, -101, -100, -99, -98, -96, -95, -94, -93, -91, -90, -89, -88, -86, -85, -84, -83, -81, -80, -79, -77, -76, -75, -74, -72, -71, -70, -69, -67, -66, -65, -64, -62, -61, -60, -59, -57, -56, -55, -53, -52, -51, -50, -48, -47, -46, -45, -43, -42, -41, -40, -38, -37, -36, -35, -33, -32, -31, -30, -28, -27, -26, -24, -23, -22, -21, -19, -18, -17, -16, -14, -13, -12, -11, -9, -8, -7, -6, -4, -3, -2, -1, 1, 2, 3, 5, 6, 7, 8, 10, 11, 12, 13, 15, 16, 17, 18, 20, 21, 22, 23, 25, 26, 27, 29, 30, 31, 32, 34, 35, 36, 37, 39, 40, 41, 42, 44, 45, 46, 47, 49, 50, 51, 52, 54, 55, 56, 58, 59, 60, 61, 63, 64, 65, 66, 68, 69, 70, 71, 73, 74, 75, 76, 78, 79, 80, 82, 83, 84, 85, 87, 88, 89, 90, 92, 93, 94, 95, 97, 98, 99, 100, 102, 103, 104, 105, 107, 108, 109, 111, 112, 113, 114, 116, 117, 118, 119, 121, 122, 123, 124, 126, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127 };
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
  _tcn_layers_1_net_net_5_fc_fc_3_HardSigmoid_output_0_layer, 93,
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
  _tcn_layers_1_net_net_5_fc_fc_2_MatMul_output_0_layer, 90,
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
  _tcn_layers_1_net_net_5_fc_fc_1_Clip_output_0_layer, 87,
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
  _tcn_layers_1_net_net_5_avg_pool_GlobalAveragePool_output_0_layer, 81,
  POOL_TYPE, 0x0, NULL,
  pool, forward_ap_integer_INT8,
  &_tcn_layers_1_net_net_5_avg_pool_GlobalAveragePool_output_0_chain,
  NULL, &_tcn_layers_1_net_net_5_fc_fc_1_Clip_output_0_layer, AI_STATIC, 
  .pool_size = AI_SHAPE_2D_INIT(320, 1), 
  .pool_stride = AI_SHAPE_2D_INIT(320, 1), 
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
  _tcn_layers_1_net_net_3_Clip_output_0_layer, 78,
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
  _tcn_layers_1_net_net_0_Conv_output_0_0_0__tcn_layers_1_net_net_3_Clip_output_0_conversion_layer, 75,
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
  _tcn_layers_1_net_net_0_Conv_output_0_layer, 75,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32_group,
  &_tcn_layers_1_net_net_0_Conv_output_0_chain,
  NULL, &_tcn_layers_1_net_net_0_Conv_output_0_0_0__tcn_layers_1_net_net_3_Clip_output_0_conversion_layer, AI_STATIC, 
  .groups = 24, 
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
  _Add_output_0_0_0__tcn_layers_1_net_net_0_Conv_output_0_conversion_layer, 72,
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
  _Add_output_0_layer, 72,
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
  _tcn_layers_0_net_net_5_Mul_output_0_layer, 69,
  ELTWISE_INTEGER_TYPE, 0x0, NULL,
  eltwise_integer, forward_eltwise_integer_INT8,
  &_tcn_layers_0_net_net_5_Mul_output_0_chain,
  NULL, &_Add_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_INT8, 
)


AI_STATIC_CONST ai_i8 _tcn_layers_0_net_net_5_fc_fc_3_HardSigmoid_output_0_nl_params_data[] = { -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -127, -125, -123, -122, -120, -118, -116, -114, -112, -110, -109, -107, -105, -103, -101, -99, -97, -96, -94, -92, -90, -88, -86, -84, -82, -81, -79, -77, -75, -73, -71, -69, -68, -66, -64, -62, -60, -58, -56, -55, -53, -51, -49, -47, -45, -43, -41, -40, -38, -36, -34, -32, -30, -28, -27, -25, -23, -21, -19, -17, -15, -14, -12, -10, -8, -6, -4, -2, -1, 1, 3, 5, 7, 9, 11, 13, 14, 16, 18, 20, 22, 24, 26, 27, 29, 31, 33, 35, 37, 39, 40, 42, 44, 46, 48, 50, 52, 54, 55, 57, 59, 61, 63, 65, 67, 68, 70, 72, 74, 76, 78, 80, 81, 83, 85, 87, 89, 91, 93, 95, 96, 98, 100, 102, 104, 106, 108, 109, 111, 113, 115, 117, 119, 121, 122, 124, 126, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127 };
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
  _tcn_layers_0_net_net_5_fc_fc_3_HardSigmoid_output_0_layer, 63,
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
  _tcn_layers_0_net_net_5_fc_fc_2_MatMul_output_0_layer, 60,
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
  _tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_layer, 57,
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
  _tcn_layers_0_net_net_5_avg_pool_GlobalAveragePool_output_0_layer, 51,
  POOL_TYPE, 0x0, NULL,
  pool, forward_ap_integer_INT8,
  &_tcn_layers_0_net_net_5_avg_pool_GlobalAveragePool_output_0_chain,
  NULL, &_tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_layer, AI_STATIC, 
  .pool_size = AI_SHAPE_2D_INIT(320, 1), 
  .pool_stride = AI_SHAPE_2D_INIT(320, 1), 
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
  _tcn_layers_0_net_net_3_Clip_output_0_layer, 48,
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
  _tcn_layers_0_net_net_0_Conv_output_0_layer, 45,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_dw_sssa8_ch,
  &_tcn_layers_0_net_net_0_Conv_output_0_chain,
  NULL, &_tcn_layers_0_net_net_3_Clip_output_0_layer, AI_STATIC, 
  .groups = 24, 
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
  _expand_expand_2_Clip_output_0_layer, 42,
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
  _frontend_frontend_2_Clip_output_0_layer, 39,
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
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 9696, 1, 1),
    9696, NULL, NULL),
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 69120, 1, 1),
    69120, NULL, NULL),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK_IN_NUM, &input_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK_OUT_NUM, &_boundary_head_Conv_output_0_output, &_frame_head_Conv_output_0_output),
  &_frontend_frontend_2_Clip_output_0_layer, 0x741f2333, NULL)

#else

AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_ARRAY_OBJ_INIT_STATIC(
  	AI_FLAG_NONE, 1,
    AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
      AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 9696, 1, 1),
      9696, NULL, NULL)
  ),
  AI_BUFFER_ARRAY_OBJ_INIT_STATIC(
  	AI_FLAG_NONE, 1,
    AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
      AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 69120, 1, 1),
      69120, NULL, NULL)
  ),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK_IN_NUM, &input_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK_OUT_NUM, &_boundary_head_Conv_output_0_output, &_frame_head_Conv_output_0_output),
  &_frontend_frontend_2_Clip_output_0_layer, 0x741f2333, NULL)

#endif	/*(AI_TOOLS_API_VERSION < AI_TOOLS_API_VERSION_1_5)*/



/******************************************************************************/
AI_DECLARE_STATIC
ai_bool network_configure_activations(
  ai_network* net_ctx, const ai_network_params* params)
{
  AI_ASSERT(net_ctx)

  if (ai_platform_get_activations_map(g_network_activations_map, 1, params)) {
    /* Updating activations (byte) offsets */
    
    input_output_array.data = AI_PTR(g_network_activations_map[0] + 37096);
    input_output_array.data_start = AI_PTR(g_network_activations_map[0] + 37096);
    _frontend_frontend_2_Clip_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 38056);
    _frontend_frontend_2_Clip_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 38056);
    _frontend_frontend_2_Clip_output_0_scratch1_array.data = AI_PTR(g_network_activations_map[0] + 33260);
    _frontend_frontend_2_Clip_output_0_scratch1_array.data_start = AI_PTR(g_network_activations_map[0] + 33260);
    _frontend_frontend_2_Clip_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 38400);
    _frontend_frontend_2_Clip_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 38400);
    _expand_expand_2_Clip_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 39680);
    _expand_expand_2_Clip_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 39680);
    _expand_expand_2_Clip_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 30720);
    _expand_expand_2_Clip_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 30720);
    _tcn_layers_0_net_net_0_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 29972);
    _tcn_layers_0_net_net_0_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 29972);
    _tcn_layers_0_net_net_0_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 38400);
    _tcn_layers_0_net_net_0_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 38400);
    _tcn_layers_0_net_net_3_Clip_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 46080);
    _tcn_layers_0_net_net_3_Clip_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 46080);
    _tcn_layers_0_net_net_3_Clip_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 23040);
    _tcn_layers_0_net_net_3_Clip_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 23040);
    _tcn_layers_0_net_net_5_avg_pool_GlobalAveragePool_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 46392);
    _tcn_layers_0_net_net_5_avg_pool_GlobalAveragePool_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 46392);
    _tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 38400);
    _tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 38400);
    _tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 38568);
    _tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 38568);
    _tcn_layers_0_net_net_5_fc_fc_2_MatMul_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 38580);
    _tcn_layers_0_net_net_5_fc_fc_2_MatMul_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 38580);
    _tcn_layers_0_net_net_5_fc_fc_2_MatMul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 46392);
    _tcn_layers_0_net_net_5_fc_fc_2_MatMul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 46392);
    _tcn_layers_0_net_net_5_fc_fc_3_HardSigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 23016);
    _tcn_layers_0_net_net_5_fc_fc_3_HardSigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 23016);
    _tcn_layers_0_net_net_5_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 23040);
    _tcn_layers_0_net_net_5_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 23040);
    _Add_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 30720);
    _Add_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 30720);
    _Add_output_0_0_0__tcn_layers_1_net_net_0_Conv_output_0_conversion_output_array.data = AI_PTR(g_network_activations_map[0] + 38400);
    _Add_output_0_0_0__tcn_layers_1_net_net_0_Conv_output_0_conversion_output_array.data_start = AI_PTR(g_network_activations_map[0] + 38400);
    _tcn_layers_1_net_net_0_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 0);
    _tcn_layers_1_net_net_0_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    _tcn_layers_1_net_net_0_Conv_output_0_0_0__tcn_layers_1_net_net_3_Clip_output_0_conversion_output_array.data = AI_PTR(g_network_activations_map[0] + 38400);
    _tcn_layers_1_net_net_0_Conv_output_0_0_0__tcn_layers_1_net_net_3_Clip_output_0_conversion_output_array.data_start = AI_PTR(g_network_activations_map[0] + 38400);
    _tcn_layers_1_net_net_3_Clip_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 0);
    _tcn_layers_1_net_net_3_Clip_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    _tcn_layers_1_net_net_3_Clip_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 336);
    _tcn_layers_1_net_net_3_Clip_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 336);
    _tcn_layers_1_net_net_5_avg_pool_GlobalAveragePool_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 0);
    _tcn_layers_1_net_net_5_avg_pool_GlobalAveragePool_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    _tcn_layers_1_net_net_5_fc_fc_1_Clip_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 24);
    _tcn_layers_1_net_net_5_fc_fc_1_Clip_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 24);
    _tcn_layers_1_net_net_5_fc_fc_1_Clip_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 192);
    _tcn_layers_1_net_net_5_fc_fc_1_Clip_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 192);
    _tcn_layers_1_net_net_5_fc_fc_2_MatMul_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 8016);
    _tcn_layers_1_net_net_5_fc_fc_2_MatMul_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 8016);
    _tcn_layers_1_net_net_5_fc_fc_2_MatMul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 0);
    _tcn_layers_1_net_net_5_fc_fc_2_MatMul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    _tcn_layers_1_net_net_5_fc_fc_3_HardSigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 24);
    _tcn_layers_1_net_net_5_fc_fc_3_HardSigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 24);
    _tcn_layers_1_net_net_5_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 8016);
    _tcn_layers_1_net_net_5_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 8016);
    _Add_1_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 0);
    _Add_1_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    _Add_1_output_0_0_0__tcn_layers_2_net_net_0_Conv_output_0_conversion_output_array.data = AI_PTR(g_network_activations_map[0] + 7680);
    _Add_1_output_0_0_0__tcn_layers_2_net_net_0_Conv_output_0_conversion_output_array.data_start = AI_PTR(g_network_activations_map[0] + 7680);
    _tcn_layers_2_net_net_0_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 38400);
    _tcn_layers_2_net_net_0_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 38400);
    _tcn_layers_2_net_net_0_Conv_output_0_0_0__tcn_layers_2_net_net_3_Clip_output_0_conversion_output_array.data = AI_PTR(g_network_activations_map[0] + 7680);
    _tcn_layers_2_net_net_0_Conv_output_0_0_0__tcn_layers_2_net_net_3_Clip_output_0_conversion_output_array.data_start = AI_PTR(g_network_activations_map[0] + 7680);
    _tcn_layers_2_net_net_3_Clip_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 15360);
    _tcn_layers_2_net_net_3_Clip_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 15360);
    _tcn_layers_2_net_net_3_Clip_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 15696);
    _tcn_layers_2_net_net_3_Clip_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 15696);
    _tcn_layers_2_net_net_5_avg_pool_GlobalAveragePool_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 7680);
    _tcn_layers_2_net_net_5_avg_pool_GlobalAveragePool_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 7680);
    _tcn_layers_2_net_net_5_fc_fc_1_Clip_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 7704);
    _tcn_layers_2_net_net_5_fc_fc_1_Clip_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 7704);
    _tcn_layers_2_net_net_5_fc_fc_1_Clip_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 7872);
    _tcn_layers_2_net_net_5_fc_fc_1_Clip_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 7872);
    _tcn_layers_2_net_net_5_fc_fc_2_MatMul_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 7884);
    _tcn_layers_2_net_net_5_fc_fc_2_MatMul_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 7884);
    _tcn_layers_2_net_net_5_fc_fc_2_MatMul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 7680);
    _tcn_layers_2_net_net_5_fc_fc_2_MatMul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 7680);
    _tcn_layers_2_net_net_5_fc_fc_3_HardSigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 7704);
    _tcn_layers_2_net_net_5_fc_fc_3_HardSigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 7704);
    _tcn_layers_2_net_net_5_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 7728);
    _tcn_layers_2_net_net_5_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 7728);
    _Add_2_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 61440);
    _Add_2_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 61440);
    _Add_2_output_0_0_0__tcn_layers_3_net_net_0_Conv_output_0_conversion_output_array.data = AI_PTR(g_network_activations_map[0] + 0);
    _Add_2_output_0_0_0__tcn_layers_3_net_net_0_Conv_output_0_conversion_output_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    _tcn_layers_3_net_net_0_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 30720);
    _tcn_layers_3_net_net_0_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 30720);
    _tcn_layers_3_net_net_0_Conv_output_0_0_0__tcn_layers_3_net_net_3_Clip_output_0_conversion_output_array.data = AI_PTR(g_network_activations_map[0] + 0);
    _tcn_layers_3_net_net_0_Conv_output_0_0_0__tcn_layers_3_net_net_3_Clip_output_0_conversion_output_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    _tcn_layers_3_net_net_3_Clip_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 7680);
    _tcn_layers_3_net_net_3_Clip_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 7680);
    _tcn_layers_3_net_net_3_Clip_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 8016);
    _tcn_layers_3_net_net_3_Clip_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 8016);
    _tcn_layers_3_net_net_5_avg_pool_GlobalAveragePool_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 0);
    _tcn_layers_3_net_net_5_avg_pool_GlobalAveragePool_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    _tcn_layers_3_net_net_5_fc_fc_1_Clip_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 24);
    _tcn_layers_3_net_net_5_fc_fc_1_Clip_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 24);
    _tcn_layers_3_net_net_5_fc_fc_1_Clip_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 192);
    _tcn_layers_3_net_net_5_fc_fc_1_Clip_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 192);
    _tcn_layers_3_net_net_5_fc_fc_2_MatMul_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 204);
    _tcn_layers_3_net_net_5_fc_fc_2_MatMul_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 204);
    _tcn_layers_3_net_net_5_fc_fc_2_MatMul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 0);
    _tcn_layers_3_net_net_5_fc_fc_2_MatMul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    _tcn_layers_3_net_net_5_fc_fc_3_HardSigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 24);
    _tcn_layers_3_net_net_5_fc_fc_3_HardSigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 24);
    _tcn_layers_3_net_net_5_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 48);
    _tcn_layers_3_net_net_5_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 48);
    _Add_3_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 61440);
    _Add_3_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 61440);
    _Add_3_output_0_0_0__tcn_layers_4_net_net_0_Conv_output_0_conversion_output_array.data = AI_PTR(g_network_activations_map[0] + 0);
    _Add_3_output_0_0_0__tcn_layers_4_net_net_0_Conv_output_0_conversion_output_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    _tcn_layers_4_net_net_0_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 30720);
    _tcn_layers_4_net_net_0_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 30720);
    _tcn_layers_4_net_net_0_Conv_output_0_0_0__tcn_layers_4_net_net_3_Clip_output_0_conversion_output_array.data = AI_PTR(g_network_activations_map[0] + 0);
    _tcn_layers_4_net_net_0_Conv_output_0_0_0__tcn_layers_4_net_net_3_Clip_output_0_conversion_output_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    _tcn_layers_4_net_net_3_Clip_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 7680);
    _tcn_layers_4_net_net_3_Clip_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 7680);
    _tcn_layers_4_net_net_3_Clip_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 8016);
    _tcn_layers_4_net_net_3_Clip_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 8016);
    _tcn_layers_4_net_net_5_avg_pool_GlobalAveragePool_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 0);
    _tcn_layers_4_net_net_5_avg_pool_GlobalAveragePool_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    _tcn_layers_4_net_net_5_fc_fc_1_Clip_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 24);
    _tcn_layers_4_net_net_5_fc_fc_1_Clip_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 24);
    _tcn_layers_4_net_net_5_fc_fc_1_Clip_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 192);
    _tcn_layers_4_net_net_5_fc_fc_1_Clip_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 192);
    _tcn_layers_4_net_net_5_fc_fc_2_MatMul_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 204);
    _tcn_layers_4_net_net_5_fc_fc_2_MatMul_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 204);
    _tcn_layers_4_net_net_5_fc_fc_2_MatMul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 0);
    _tcn_layers_4_net_net_5_fc_fc_2_MatMul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    _tcn_layers_4_net_net_5_fc_fc_3_HardSigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 24);
    _tcn_layers_4_net_net_5_fc_fc_3_HardSigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 24);
    _tcn_layers_4_net_net_5_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 48);
    _tcn_layers_4_net_net_5_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 48);
    _Add_4_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 7728);
    _Add_4_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 7728);
    _boundary_head_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 0);
    _boundary_head_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    _boundary_head_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 96);
    _boundary_head_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 96);
    _frame_head_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 0);
    _frame_head_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    _frame_head_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 416);
    _frame_head_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 416);
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
    _expand_expand_2_Clip_output_0_bias_array.data = AI_PTR(g_network_weights_map[0] + 208);
    _expand_expand_2_Clip_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 208);
    _tcn_layers_0_net_net_0_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _tcn_layers_0_net_net_0_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[0] + 304);
    _tcn_layers_0_net_net_0_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 304);
    _tcn_layers_0_net_net_0_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _tcn_layers_0_net_net_0_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[0] + 472);
    _tcn_layers_0_net_net_0_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 472);
    _tcn_layers_0_net_net_3_Clip_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _tcn_layers_0_net_net_3_Clip_output_0_weights_array.data = AI_PTR(g_network_weights_map[0] + 568);
    _tcn_layers_0_net_net_3_Clip_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 568);
    _tcn_layers_0_net_net_3_Clip_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _tcn_layers_0_net_net_3_Clip_output_0_bias_array.data = AI_PTR(g_network_weights_map[0] + 1144);
    _tcn_layers_0_net_net_3_Clip_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 1144);
    _tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_weights_array.data = AI_PTR(g_network_weights_map[0] + 1240);
    _tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 1240);
    _tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_bias_array.data = AI_PTR(g_network_weights_map[0] + 1528);
    _tcn_layers_0_net_net_5_fc_fc_1_Clip_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 1528);
    _tcn_layers_0_net_net_5_fc_fc_2_MatMul_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _tcn_layers_0_net_net_5_fc_fc_2_MatMul_output_0_weights_array.data = AI_PTR(g_network_weights_map[0] + 1576);
    _tcn_layers_0_net_net_5_fc_fc_2_MatMul_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 1576);
    _tcn_layers_1_net_net_0_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _tcn_layers_1_net_net_0_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[0] + 1864);
    _tcn_layers_1_net_net_0_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 1864);
    _tcn_layers_1_net_net_0_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _tcn_layers_1_net_net_0_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[0] + 2536);
    _tcn_layers_1_net_net_0_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 2536);
    _tcn_layers_1_net_net_3_Clip_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _tcn_layers_1_net_net_3_Clip_output_0_weights_array.data = AI_PTR(g_network_weights_map[0] + 2632);
    _tcn_layers_1_net_net_3_Clip_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 2632);
    _tcn_layers_1_net_net_3_Clip_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _tcn_layers_1_net_net_3_Clip_output_0_bias_array.data = AI_PTR(g_network_weights_map[0] + 3208);
    _tcn_layers_1_net_net_3_Clip_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 3208);
    _tcn_layers_1_net_net_5_fc_fc_1_Clip_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _tcn_layers_1_net_net_5_fc_fc_1_Clip_output_0_weights_array.data = AI_PTR(g_network_weights_map[0] + 3304);
    _tcn_layers_1_net_net_5_fc_fc_1_Clip_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 3304);
    _tcn_layers_1_net_net_5_fc_fc_2_MatMul_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _tcn_layers_1_net_net_5_fc_fc_2_MatMul_output_0_weights_array.data = AI_PTR(g_network_weights_map[0] + 3592);
    _tcn_layers_1_net_net_5_fc_fc_2_MatMul_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 3592);
    _tcn_layers_2_net_net_0_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _tcn_layers_2_net_net_0_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[0] + 3880);
    _tcn_layers_2_net_net_0_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 3880);
    _tcn_layers_2_net_net_3_Clip_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _tcn_layers_2_net_net_3_Clip_output_0_weights_array.data = AI_PTR(g_network_weights_map[0] + 4552);
    _tcn_layers_2_net_net_3_Clip_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 4552);
    _tcn_layers_2_net_net_3_Clip_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _tcn_layers_2_net_net_3_Clip_output_0_bias_array.data = AI_PTR(g_network_weights_map[0] + 5128);
    _tcn_layers_2_net_net_3_Clip_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 5128);
    _tcn_layers_2_net_net_5_fc_fc_1_Clip_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _tcn_layers_2_net_net_5_fc_fc_1_Clip_output_0_weights_array.data = AI_PTR(g_network_weights_map[0] + 5224);
    _tcn_layers_2_net_net_5_fc_fc_1_Clip_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 5224);
    _tcn_layers_2_net_net_5_fc_fc_2_MatMul_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _tcn_layers_2_net_net_5_fc_fc_2_MatMul_output_0_weights_array.data = AI_PTR(g_network_weights_map[0] + 5512);
    _tcn_layers_2_net_net_5_fc_fc_2_MatMul_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 5512);
    _tcn_layers_3_net_net_0_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _tcn_layers_3_net_net_0_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[0] + 5800);
    _tcn_layers_3_net_net_0_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 5800);
    _tcn_layers_3_net_net_3_Clip_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _tcn_layers_3_net_net_3_Clip_output_0_weights_array.data = AI_PTR(g_network_weights_map[0] + 6472);
    _tcn_layers_3_net_net_3_Clip_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 6472);
    _tcn_layers_3_net_net_3_Clip_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _tcn_layers_3_net_net_3_Clip_output_0_bias_array.data = AI_PTR(g_network_weights_map[0] + 7048);
    _tcn_layers_3_net_net_3_Clip_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 7048);
    _tcn_layers_3_net_net_5_fc_fc_1_Clip_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _tcn_layers_3_net_net_5_fc_fc_1_Clip_output_0_weights_array.data = AI_PTR(g_network_weights_map[0] + 7144);
    _tcn_layers_3_net_net_5_fc_fc_1_Clip_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 7144);
    _tcn_layers_3_net_net_5_fc_fc_2_MatMul_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _tcn_layers_3_net_net_5_fc_fc_2_MatMul_output_0_weights_array.data = AI_PTR(g_network_weights_map[0] + 7432);
    _tcn_layers_3_net_net_5_fc_fc_2_MatMul_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 7432);
    _tcn_layers_4_net_net_0_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _tcn_layers_4_net_net_0_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[0] + 7720);
    _tcn_layers_4_net_net_0_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 7720);
    _tcn_layers_4_net_net_3_Clip_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _tcn_layers_4_net_net_3_Clip_output_0_weights_array.data = AI_PTR(g_network_weights_map[0] + 8392);
    _tcn_layers_4_net_net_3_Clip_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 8392);
    _tcn_layers_4_net_net_3_Clip_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _tcn_layers_4_net_net_3_Clip_output_0_bias_array.data = AI_PTR(g_network_weights_map[0] + 8968);
    _tcn_layers_4_net_net_3_Clip_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 8968);
    _tcn_layers_4_net_net_5_fc_fc_1_Clip_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _tcn_layers_4_net_net_5_fc_fc_1_Clip_output_0_weights_array.data = AI_PTR(g_network_weights_map[0] + 9064);
    _tcn_layers_4_net_net_5_fc_fc_1_Clip_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 9064);
    _tcn_layers_4_net_net_5_fc_fc_2_MatMul_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _tcn_layers_4_net_net_5_fc_fc_2_MatMul_output_0_weights_array.data = AI_PTR(g_network_weights_map[0] + 9352);
    _tcn_layers_4_net_net_5_fc_fc_2_MatMul_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 9352);
    _boundary_head_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _boundary_head_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[0] + 9640);
    _boundary_head_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 9640);
    _boundary_head_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _boundary_head_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[0] + 9664);
    _boundary_head_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 9664);
    _frame_head_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _frame_head_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[0] + 9668);
    _frame_head_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 9668);
    _frame_head_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _frame_head_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[0] + 9692);
    _frame_head_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 9692);
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
      
      .n_macc            = 1577754,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .params            = AI_STRUCT_INIT,
      .activations       = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0x741f2333,
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
      
      .n_macc            = 1577754,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .map_signature     = AI_MAGIC_SIGNATURE,
      .map_weights       = AI_STRUCT_INIT,
      .map_activations   = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0x741f2333,
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

