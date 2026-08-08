
// SPDX-License-Identifier: MIT

// Private include file, not intended to be included by end users

#pragma once

// Internal I2C bus
#define BSP_I2C_BUS     0
#define BSP_I2C_SDA_PIN 18
#define BSP_I2C_SCL_PIN 20


#define BSP_KBD_INT       2
#define BSP_KBD_SCL       BSP_I2C_SCL_PIN
#define BSP_KBD_SDA       BSP_I2C_SDA_PIN
#define BSP_KBD_RST       -1


// MIPI DSI display
#define BSP_DSI_LDO_CHAN       3
#define BSP_DSI_LDO_VOLTAGE_MV 2500
#define BSP_LCD_RESET_PIN      17  // Note: low for normal operation, high for reset

// Audio pins
#define BSP_I2S_MCLK  I2S_GPIO_UNUSED
#define BSP_I2S_BCLK  26  // MAX BCLK
#define BSP_I2S_DOUT  27   // MAX DIN
#if defined CONFIG_BSP_WHY2025_AUDIOREMAPED
#define BSP_I2S_WS    38   // MAX LRCLK or 37
#define BSP_AMP_SHDW  37 // MAX AMP PIN
#else
#define BSP_I2S_WS    24   // MAX LRCLK or 37
#define BSP_AMP_SHDW  25 // MAX AMP PIN
#endif
