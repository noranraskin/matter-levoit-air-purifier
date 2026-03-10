/*
 * Levoit Core 300S UART Driver
 *
 * Public API for communicating with the Levoit secondary MCU
 * over the binary UART protocol.
 */

#pragma once

#include <esp_err.h>
#include "levoit_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initialize the Levoit UART driver.
 *
 * Sets up UART peripheral, creates FreeRTOS tasks for RX/TX processing,
 * and begins listening for status updates from the secondary MCU.
 *
 * @param status_cb  Callback invoked on each status update from MCU.
 * @param user_data  Opaque pointer passed to status_cb.
 * @return ESP_OK on success.
 */
esp_err_t levoit_uart_init(levoit_status_cb_t status_cb, void *user_data);

/**
 * Set the power state of the device.
 *
 * @param on  true = power on, false = power off.
 */
esp_err_t levoit_set_power(bool on);

/**
 * Set the fan operating mode.
 *
 * @param mode  LEVOIT_FAN_MODE_MANUAL, LEVOIT_FAN_MODE_SLEEP, or LEVOIT_FAN_MODE_AUTO.
 */
esp_err_t levoit_set_fan_mode(levoit_fan_mode_t mode);

/**
 * Set the fan speed in manual mode.
 *
 * @param speed  LEVOIT_FAN_SPEED_LOW, LEVOIT_FAN_SPEED_MED, or LEVOIT_FAN_SPEED_HIGH.
 */
esp_err_t levoit_set_fan_speed(levoit_fan_speed_t speed);

/**
 * Set the screen brightness.
 *
 * @param brightness  0x00 = off, 0x64 = full brightness.
 */
esp_err_t levoit_set_screen_brightness(uint8_t brightness);

/**
 * Set the display lock state.
 *
 * @param locked  true = locked, false = unlocked.
 */
esp_err_t levoit_set_display_lock(bool locked);

/**
 * Reset the filter usage counter.
 */
esp_err_t levoit_reset_filter(void);

/**
 * Set the WiFi status LED on the device.
 *
 * @param mode  LEVOIT_WIFI_LED_OFF, LEVOIT_WIFI_LED_ON, or LEVOIT_WIFI_LED_BLINK.
 */
esp_err_t levoit_set_wifi_led(levoit_wifi_led_t mode);

/**
 * Request a status update from the MCU.
 * The response will arrive asynchronously via the status callback.
 */
esp_err_t levoit_request_status(void);

#ifdef __cplusplus
}
#endif
