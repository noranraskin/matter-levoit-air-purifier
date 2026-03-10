/*
 * Matter Levoit Core 300S Air Purifier — Private Definitions
 */

#pragma once

#include <esp_err.h>
#include <esp_matter.h>
#include "levoit_types.h"

/* ── Endpoint IDs (assigned at runtime) ── */
extern uint16_t air_purifier_endpoint_id;
extern uint16_t air_quality_sensor_endpoint_id;
extern uint16_t display_power_endpoint_id;
extern uint16_t display_lock_endpoint_id;

/* ── Factory Reset via Rapid Power Toggle ── */
#define FACTORY_RESET_TOGGLE_COUNT  10
#define FACTORY_RESET_WINDOW_MS     15000

/* ── Commissioning Window Timeout ── */
#define COMMISSIONING_TIMEOUT_S     300

/* ── AQI Linear Mapping Thresholds (0-255 → 6 bands) ── */
#define AQI_BAND_SIZE               43  /* ~256/6 */

typedef void *app_driver_handle_t;

/**
 * Initialize the Levoit UART driver and register the status callback.
 */
app_driver_handle_t app_driver_levoit_init(void);

/**
 * Handle Matter attribute updates by sending the corresponding UART command.
 *
 * Called from the PRE_UPDATE attribute callback for every attribute write.
 */
esp_err_t app_driver_attribute_update(app_driver_handle_t driver_handle, uint16_t endpoint_id,
                                      uint32_t cluster_id, uint32_t attribute_id,
                                      esp_matter_attr_val_t *val);
