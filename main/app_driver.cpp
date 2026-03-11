/*
 * Matter Levoit Core 300S Air Purifier — Driver (MINIMAL STUB)
 *
 * This file is a placeholder for the full driver that will bridge
 * Matter attribute changes to Levoit UART commands. For the minimal
 * commissioning build, no UART communication is needed.
 *
 * TODO (Phase 3): Implement actual UART command dispatch.
 */

#include <esp_log.h>
#include <app_priv.h>

static const char *TAG = "app_driver";

/* ── Driver Init (stub) ── */
app_driver_handle_t app_driver_levoit_init(void)
{
    ESP_LOGI(TAG, "Levoit driver init (stub — no UART in minimal build)");
    return NULL;
}

/* ── Attribute Update Handler (stub) ── */
esp_err_t app_driver_attribute_update(app_driver_handle_t driver_handle, uint16_t endpoint_id,
                                      uint32_t cluster_id, uint32_t attribute_id,
                                      esp_matter_attr_val_t *val)
{
    ESP_LOGI(TAG, "Attribute update: ep=%d cluster=0x%04lx attr=0x%04lx",
             endpoint_id, (unsigned long)cluster_id, (unsigned long)attribute_id);
    return ESP_OK;
}
