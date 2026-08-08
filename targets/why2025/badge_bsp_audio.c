// SPDX-FileCopyrightText: 2025 Nicolai Electronics
// SPDX-License-Identifier: MIT

#include <stdint.h>
#include "bsp/audio.h"
#include "driver/gpio.h"
#include "driver/i2s_std.h"
#include "esp_check.h"
#include "esp_err.h"
#include "why2025_hardware.h"

static char const* TAG = "BSP: audio";

static i2s_chan_handle_t       i2s_handle              = NULL;

static esp_err_t initialize_i2s(uint32_t rate) {
    i2s_chan_config_t chan_cfg = I2S_CHANNEL_DEFAULT_CONFIG(0, I2S_ROLE_MASTER);

    esp_err_t res = i2s_new_channel(&chan_cfg, &i2s_handle, NULL);
    if (res != ESP_OK) {
        return res;
    }

    i2s_std_config_t i2s_config = {
        .clk_cfg  = I2S_STD_CLK_DEFAULT_CONFIG(rate),
        .slot_cfg = I2S_STD_PHILIPS_SLOT_DEFAULT_CONFIG(I2S_DATA_BIT_WIDTH_16BIT, I2S_SLOT_MODE_STEREO),
        .gpio_cfg =
            {
                .mclk = BSP_I2S_MCLK,
                .bclk = BSP_I2S_BCLK,
                .ws   = BSP_I2S_WS,
                .dout = BSP_I2S_DOUT,
                .din  = I2S_GPIO_UNUSED,
                .invert_flags =
                    {
                        .mclk_inv = false,
                        .bclk_inv = false,
                        .ws_inv   = false,
                    },
            },
    };

    res = i2s_channel_init_std_mode(i2s_handle, &i2s_config);
    if (res != ESP_OK) {
        return res;
    }

    res = i2s_channel_enable(i2s_handle);
    if (res != ESP_OK) {
        return res;
    }

    return ESP_OK;
}

esp_err_t bsp_audio_set_rate(uint32_t rate) {
    i2s_std_clk_config_t clk_config = I2S_STD_CLK_DEFAULT_CONFIG(rate);
    return i2s_channel_reconfig_std_clock(i2s_handle, &clk_config);
}

esp_err_t bsp_audio_initialize() {
    ESP_RETURN_ON_ERROR(gpio_set_direction(BSP_AMP_SHDW, GPIO_MODE_OUTPUT), TAG, "Failed to set amplifier pin");
    bsp_audio_set_amplifier(false);
    return initialize_i2s(44100);
}

esp_err_t bsp_audio_set_amplifier(bool enable) {
    return gpio_set_level(BSP_AMP_SHDW, enable);
}

esp_err_t bsp_audio_get_i2s_handle(i2s_chan_handle_t* out_handle) {
    if (out_handle == NULL) {
        return ESP_ERR_INVALID_ARG;
    }
    *out_handle = i2s_handle;
    return ESP_OK;
}