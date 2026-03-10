/*
 * Levoit Core 300S UART Driver — Stub Implementation
 *
 * TODO: Port the UART protocol from the ESPHome component.
 * This stub provides the API surface so the project compiles.
 * See IMPLEMENTATION_PLAN_DOCS.md Phase 2 for porting details.
 */

#include <esp_log.h>
#include "levoit_uart.h"

static const char *TAG = "levoit_uart";

static levoit_status_cb_t s_status_cb = NULL;
static void *s_user_data = NULL;

esp_err_t levoit_uart_init(levoit_status_cb_t status_cb, void *user_data)
{
    ESP_LOGI(TAG, "Levoit UART driver init (stub)");
    s_status_cb = status_cb;
    s_user_data = user_data;

    /* TODO: Initialize UART peripheral on GPIO16/17 at 115200 baud */
    /* TODO: Create FreeRTOS tasks for RX queue, TX queue, maintenance */

    return ESP_OK;
}

esp_err_t levoit_set_power(bool on)
{
    ESP_LOGI(TAG, "Set power: %s (stub)", on ? "ON" : "OFF");
    /* TODO: Send SET_POWER_STATE command via UART */
    return ESP_OK;
}

esp_err_t levoit_set_fan_mode(levoit_fan_mode_t mode)
{
    ESP_LOGI(TAG, "Set fan mode: %d (stub)", mode);
    /* TODO: Send SET_FAN_MODE command via UART */
    return ESP_OK;
}

esp_err_t levoit_set_fan_speed(levoit_fan_speed_t speed)
{
    ESP_LOGI(TAG, "Set fan speed: %d (stub)", speed);
    /* TODO: Send SET_FAN_MANUAL command via UART */
    return ESP_OK;
}

esp_err_t levoit_set_screen_brightness(uint8_t brightness)
{
    ESP_LOGI(TAG, "Set screen brightness: %d (stub)", brightness);
    /* TODO: Send SET_SCREEN_BRIGHTNESS command via UART */
    return ESP_OK;
}

esp_err_t levoit_set_display_lock(bool locked)
{
    ESP_LOGI(TAG, "Set display lock: %s (stub)", locked ? "LOCKED" : "UNLOCKED");
    /* TODO: Send SET_DISPLAY_LOCK command via UART */
    return ESP_OK;
}

esp_err_t levoit_reset_filter(void)
{
    ESP_LOGI(TAG, "Reset filter (stub)");
    /* TODO: Send SET_RESET_FILTER command via UART */
    return ESP_OK;
}

esp_err_t levoit_set_wifi_led(levoit_wifi_led_t mode)
{
    ESP_LOGI(TAG, "Set WiFi LED: %d (stub)", mode);
    /* TODO: Send SET_WIFI_STATUS_LED command via UART */
    return ESP_OK;
}

esp_err_t levoit_request_status(void)
{
    ESP_LOGI(TAG, "Request status (stub)");
    /* TODO: Send STATUS_REQUEST command via UART */
    return ESP_OK;
}
