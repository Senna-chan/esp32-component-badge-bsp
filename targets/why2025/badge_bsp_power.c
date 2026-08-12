#include <stdbool.h>
#include <stdint.h>
#include "bsp/power.h"
#include "bsp/tanmatsu.h"
#include "esp_check.h"
#include "esp_err.h"
#include "tanmatsu_coprocessor.h"

static char const* TAG = "BSP: power";

bsp_radio_state_t current_state = BSP_POWER_RADIO_STATE_APPLICATION;

esp_err_t bsp_power_initialize(void) {
    return ESP_OK;
}

esp_err_t bsp_power_get_radio_state(bsp_radio_state_t* out_state) {
    *out_state = current_state;
    return ESP_OK;
}

esp_err_t bsp_power_set_radio_state(bsp_radio_state_t state) {
    switch (state) {
        case BSP_POWER_RADIO_STATE_OFF:
        default:
            return ESP_ERR_NOT_SUPPORTED;

        case BSP_POWER_RADIO_STATE_BOOTLOADER:
            current_state = state;
            break;
        case BSP_POWER_RADIO_STATE_APPLICATION:
            current_state = state;
            break;
    }
    return ESP_OK;
}