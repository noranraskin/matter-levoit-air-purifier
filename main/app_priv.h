/*
 * Matter Levoit Core 300S Air Purifier — Private Definitions
 */

#pragma once

#include <esp_err.h>
#include <esp_matter.h>

/* ── Endpoint IDs (assigned at runtime) ── */
extern uint16_t air_purifier_endpoint_id;
/* TODO: Re-enable when adding endpoints back
extern uint16_t air_quality_sensor_endpoint_id;
extern uint16_t display_power_endpoint_id;
extern uint16_t display_lock_endpoint_id;
*/

typedef void *app_driver_handle_t;

/**
 * Initialize the Levoit UART driver (stub in minimal build).
 */
app_driver_handle_t app_driver_levoit_init(void);

/**
 * Handle Matter attribute updates (stub in minimal build).
 */
esp_err_t app_driver_attribute_update(app_driver_handle_t driver_handle, uint16_t endpoint_id,
                                      uint32_t cluster_id, uint32_t attribute_id,
                                      esp_matter_attr_val_t *val);
