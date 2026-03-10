/*
 * Matter Levoit Core 300S Air Purifier — Driver
 *
 * Bridges Matter attribute changes to Levoit UART commands  and
 * Levoit status updates back to Matter attribute updates.
 *
 * TODO: Implement the actual UART command dispatch in Phase 3.
 */

#include <esp_log.h>
#include <esp_matter.h>
#include <app_priv.h>
#include <levoit_uart.h>

using namespace chip::app::Clusters;
using namespace esp_matter;

static const char *TAG = "app_driver";

/* ── Levoit UART status callback ── */

static void levoit_status_update_cb(const levoit_status_t *status, void *user_data)
{
    ESP_LOGI(TAG, "Status update from MCU: power=%d, mode=%d, speed=%d, aqi=%d, pm25_raw=%d",
             status->power_on, status->fan_mode, status->fan_speed,
             status->air_quality, status->pm25_raw);

    /*
     * TODO: Update Matter attributes from the UART status.
     *
     * - Update Fan Control: FanMode, SpeedCurrent, PercentCurrent
     * - Update On/Off cluster (air purifier endpoint)
     * - Update Air Quality cluster (air quality sensor endpoint)
     * - Update PM2.5 Concentration Measurement
     * - Update Display Power and Display Lock endpoints
     * - Update Mode Select CurrentMode
     * - Check for rapid power toggle → factory reset
     * - Track filter usage based on current fan speed CADR
     */
}

/* ── Driver Init ── */

app_driver_handle_t app_driver_levoit_init(void)
{
    ESP_LOGI(TAG, "Initializing Levoit UART driver");
    levoit_uart_init(levoit_status_update_cb, NULL);
    return NULL; /* No opaque handle needed for UART driver */
}

/* ── Attribute Update Handler ── */

esp_err_t app_driver_attribute_update(app_driver_handle_t driver_handle, uint16_t endpoint_id,
                                      uint32_t cluster_id, uint32_t attribute_id,
                                      esp_matter_attr_val_t *val)
{
    /* ── Air Purifier Endpoint ── */
    if (endpoint_id == air_purifier_endpoint_id)
    {
        if (cluster_id == OnOff::Id && attribute_id == OnOff::Attributes::OnOff::Id)
        {
            ESP_LOGI(TAG, "Air Purifier power: %s", val->val.b ? "ON" : "OFF");
            return levoit_set_power(val->val.b);
        }
        if (cluster_id == FanControl::Id)
        {
            if (attribute_id == FanControl::Attributes::FanMode::Id)
            {
                uint8_t fan_mode = val->val.u8;
                ESP_LOGI(TAG, "Fan mode set to: %d", fan_mode);
                /*
                 * Matter FanModeEnum: 0=Off, 1=Low, 2=Medium, 3=High, 5=Auto
                 * TODO: Map to Levoit commands:
                 * - Off → levoit_set_power(false)
                 * - Low/Med/High → levoit_set_fan_mode(MANUAL) + levoit_set_fan_speed(speed)
                 * - Auto → levoit_set_fan_mode(AUTO)
                 */
                return ESP_OK;
            }
            if (attribute_id == FanControl::Attributes::SpeedSetting::Id)
            {
                ESP_LOGI(TAG, "Speed setting: %d", val->val.u8);
                /* TODO: Map speed 1-3 → levoit_set_fan_speed() */
                return ESP_OK;
            }
        }
        if (cluster_id == ModeSelect::Id && attribute_id == ModeSelect::Attributes::CurrentMode::Id)
        {
            uint8_t mode = val->val.u8;
            ESP_LOGI(TAG, "Mode select: %d (0=Manual, 1=Sleep, 2=Auto)", mode);
            /* TODO: Map to levoit_set_fan_mode() */
            return ESP_OK;
        }
    }

    /* ── Display Power Endpoint ── */
    if (endpoint_id == display_power_endpoint_id)
    {
        if (cluster_id == OnOff::Id && attribute_id == OnOff::Attributes::OnOff::Id)
        {
            ESP_LOGI(TAG, "Display: %s", val->val.b ? "ON" : "OFF");
            return levoit_set_screen_brightness(val->val.b ? 0x64 : 0x00);
        }
    }

    /* ── Display Lock Endpoint ── */
    if (endpoint_id == display_lock_endpoint_id)
    {
        if (cluster_id == OnOff::Id && attribute_id == OnOff::Attributes::OnOff::Id)
        {
            ESP_LOGI(TAG, "Display lock: %s", val->val.b ? "LOCKED" : "UNLOCKED");
            return levoit_set_display_lock(val->val.b);
        }
    }

    return ESP_OK;
}
