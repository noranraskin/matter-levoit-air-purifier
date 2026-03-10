/*
 * Matter Levoit Core 300S Air Purifier — Main Entry Point
 *
 * Creates the Matter data model with:
 *   Endpoint 1: Air Purifier (Fan Control + On/Off + HEPA Filter + Mode Select)
 *   Endpoint 2: Air Quality Sensor (Air Quality + PM2.5 Concentration)
 *   Endpoint 3: Display Power (On/Off Plugin Unit)
 *   Endpoint 4: Display Lock (On/Off Plugin Unit)
 */

#include <esp_err.h>
#include <esp_log.h>
#include <nvs_flash.h>

#include <esp_matter.h>
#include <esp_matter_console.h>
#include <esp_matter_ota.h>

#include <common_macros.h>
#include <app_priv.h>

#include <app/server/CommissioningWindowManager.h>
#include <app/server/Server.h>

static const char *TAG = "app_main";

using namespace esp_matter;
using namespace esp_matter::attribute;
using namespace esp_matter::endpoint;
using namespace esp_matter::cluster;
using namespace chip::app::Clusters;

/* ── Endpoint IDs (filled in during setup) ── */
uint16_t air_purifier_endpoint_id = 0;
uint16_t air_quality_sensor_endpoint_id = 0;
uint16_t display_power_endpoint_id = 0;
uint16_t display_lock_endpoint_id = 0;

/* ── Event Callback ── */
static void app_event_cb(const ChipDeviceEvent *event, intptr_t arg)
{
    switch (event->Type)
    {
    case chip::DeviceLayer::DeviceEventType::kInterfaceIpAddressChanged:
        ESP_LOGI(TAG, "Interface IP Address changed");
        break;

    case chip::DeviceLayer::DeviceEventType::kCommissioningComplete:
        ESP_LOGI(TAG, "Commissioning complete");
        break;

    case chip::DeviceLayer::DeviceEventType::kFailSafeTimerExpired:
        ESP_LOGI(TAG, "Commissioning failed, fail safe timer expired");
        break;

    case chip::DeviceLayer::DeviceEventType::kCommissioningSessionStarted:
        ESP_LOGI(TAG, "Commissioning session started");
        break;

    case chip::DeviceLayer::DeviceEventType::kCommissioningWindowOpened:
        ESP_LOGI(TAG, "Commissioning window opened");
        break;

    case chip::DeviceLayer::DeviceEventType::kCommissioningWindowClosed:
        ESP_LOGI(TAG, "Commissioning window closed");
        break;

    case chip::DeviceLayer::DeviceEventType::kFabricRemoved:
    {
        ESP_LOGI(TAG, "Fabric removed successfully");
        if (chip::Server::GetInstance().GetFabricTable().FabricCount() == 0)
        {
            chip::CommissioningWindowManager &commissionMgr =
                chip::Server::GetInstance().GetCommissioningWindowManager();
            constexpr auto kTimeoutSeconds =
                chip::System::Clock::Seconds16(COMMISSIONING_TIMEOUT_S);
            if (!commissionMgr.IsCommissioningWindowOpen())
            {
                CHIP_ERROR err = commissionMgr.OpenBasicCommissioningWindow(
                    kTimeoutSeconds,
                    chip::CommissioningWindowAdvertisement::kDnssdOnly);
                if (err != CHIP_NO_ERROR)
                {
                    ESP_LOGE(TAG, "Failed to open commissioning window, err:%" CHIP_ERROR_FORMAT, err.Format());
                }
            }
        }
        break;
    }

    case chip::DeviceLayer::DeviceEventType::kFabricWillBeRemoved:
        ESP_LOGI(TAG, "Fabric will be removed");
        break;

    case chip::DeviceLayer::DeviceEventType::kFabricUpdated:
        ESP_LOGI(TAG, "Fabric is updated");
        break;

    case chip::DeviceLayer::DeviceEventType::kFabricCommitted:
        ESP_LOGI(TAG, "Fabric is committed");
        break;

    case chip::DeviceLayer::DeviceEventType::kBLEDeinitialized:
        ESP_LOGI(TAG, "BLE deinitialized and memory reclaimed");
        break;

    default:
        break;
    }
}

/* ── Identify Callback ── */
static esp_err_t app_identification_cb(identification::callback_type_t type, uint16_t endpoint_id,
                                       uint8_t effect_id, uint8_t effect_variant, void *priv_data)
{
    ESP_LOGI(TAG, "Identification callback: type: %u, effect: %u, variant: %u", type, effect_id, effect_variant);
    return ESP_OK;
}

/* ── Attribute Update Callback ── */
static esp_err_t app_attribute_update_cb(attribute::callback_type_t type, uint16_t endpoint_id,
                                         uint32_t cluster_id, uint32_t attribute_id,
                                         esp_matter_attr_val_t *val, void *priv_data)
{
    if (type == PRE_UPDATE)
    {
        app_driver_handle_t driver_handle = (app_driver_handle_t)priv_data;
        return app_driver_attribute_update(driver_handle, endpoint_id, cluster_id, attribute_id, val);
    }
    return ESP_OK;
}

/* ── Main ── */
extern "C" void app_main()
{
    esp_err_t err = ESP_OK;

    /* Initialize NVS */
    nvs_flash_init();

    /* Initialize Levoit UART driver */
    app_driver_handle_t levoit_handle = app_driver_levoit_init();

    /* ────────────────────────────────────────────────────────────
     *  Create Matter Node (Root Node on Endpoint 0)
     * ──────────────────────────────────────────────────────────── */
    node::config_t node_config;
    node_t *node = node::create(&node_config, app_attribute_update_cb, app_identification_cb);
    ABORT_APP_ON_FAILURE(node != nullptr, ESP_LOGE(TAG, "Failed to create Matter node"));

    /* ────────────────────────────────────────────────────────────
     *  Endpoint 1: Air Purifier
     *  - Fan Control cluster (mandatory for air purifier device type)
     *  - On/Off cluster (master power)
     *  - HEPA Filter Monitoring cluster
     *  - Mode Select cluster (Manual / Sleep / Auto)
     * ──────────────────────────────────────────────────────────── */
    {
        air_purifier::config_t config;
        config.fan_control.fan_mode = 0;          /* Off */
        config.fan_control.fan_mode_sequence = 0; /* Off/Low/Med/High/Auto */
        config.fan_control.percent_setting = 0;
        config.fan_control.percent_current = 0;

        endpoint_t *ep = air_purifier::create(node, &config, ENDPOINT_FLAG_NONE, levoit_handle);
        ABORT_APP_ON_FAILURE(ep != nullptr, ESP_LOGE(TAG, "Failed to create air purifier endpoint"));
        air_purifier_endpoint_id = endpoint::get_id(ep);
        ESP_LOGI(TAG, "Air Purifier endpoint created: %d", air_purifier_endpoint_id);

        /* Add Multi-Speed feature (3 speeds: Low, Med, High) */
        cluster_t *fan_cluster = cluster::get(ep, FanControl::Id);
        ABORT_APP_ON_FAILURE(fan_cluster != nullptr, ESP_LOGE(TAG, "Failed to get fan control cluster"));

        fan_control::feature::multi_speed::config_t multispeed;
        multispeed.speed_max = 3;
        multispeed.speed_setting = 0;
        multispeed.speed_current = 0;
        fan_control::feature::multi_speed::add(fan_cluster, &multispeed);

        /* Add Auto feature */
        fan_control::feature::fan_auto::add(fan_cluster);

        /* Add On/Off cluster for master power */
        on_off::config_t on_off_config;
        on_off_config.on_off = false;
        on_off::create(ep, &on_off_config, CLUSTER_FLAG_SERVER);

        /* Add HEPA Filter Monitoring cluster */
        hepa_filter_monitoring::config_t hepa_config;
        hepa_config.delegate = nullptr;
        hepa_filter_monitoring::create(ep, &hepa_config, CLUSTER_FLAG_SERVER);

        /* Add Mode Select cluster (Operating Mode: Manual / Sleep / Auto) */
        mode_select::config_t mode_config;
        snprintf(mode_config.description, sizeof(mode_config.description), "Operating Mode");
        mode_config.current_mode = 0; /* Manual */
        mode_select::create(ep, &mode_config, CLUSTER_FLAG_SERVER);

        /*
         * TODO: Add supported modes to Mode Select cluster
         * The supported_modes attribute needs to be populated with:
         *   Mode 0: "Manual"
         *   Mode 1: "Sleep"
         *   Mode 2: "Auto"
         * This requires using the mode_select delegate or direct attribute manipulation.
         */
    }

    /* ────────────────────────────────────────────────────────────
     *  Endpoint 2: Air Quality Sensor
     *  - Air Quality cluster
     *  - PM2.5 Concentration Measurement cluster
     * ──────────────────────────────────────────────────────────── */
    {
        air_quality_sensor::config_t config;

        endpoint_t *ep = air_quality_sensor::create(node, &config, ENDPOINT_FLAG_NONE, nullptr);
        ABORT_APP_ON_FAILURE(ep != nullptr, ESP_LOGE(TAG, "Failed to create air quality sensor endpoint"));
        air_quality_sensor_endpoint_id = endpoint::get_id(ep);
        ESP_LOGI(TAG, "Air Quality Sensor endpoint created: %d", air_quality_sensor_endpoint_id);

        /* Add PM2.5 Concentration Measurement cluster */
        pm25_concentration_measurement::config_t pm25_config;
        pm25_config.measurement_medium = 0; /* Air */
        /* Enable numeric measurement feature for actual µg/m³ values */
        pm25_config.feature_flags = concentration_measurement::feature::numeric_measurement::get_id();
        pm25_config.features.numeric_measurement.measurement_unit = 0; /* PPM — mapped to µg/m³ in practice */
        pm25_concentration_measurement::create(ep, &pm25_config, CLUSTER_FLAG_SERVER);
    }

    /* ────────────────────────────────────────────────────────────
     *  Endpoint 3: Display Power (On/Off Plugin Unit)
     * ──────────────────────────────────────────────────────────── */
    {
        on_off_plugin_unit::config_t config;
        config.on_off.on_off = true; /* Display on by default */

        endpoint_t *ep = on_off_plugin_unit::create(node, &config, ENDPOINT_FLAG_NONE, levoit_handle);
        ABORT_APP_ON_FAILURE(ep != nullptr, ESP_LOGE(TAG, "Failed to create display power endpoint"));
        display_power_endpoint_id = endpoint::get_id(ep);
        ESP_LOGI(TAG, "Display Power endpoint created: %d", display_power_endpoint_id);
    }

    /* ────────────────────────────────────────────────────────────
     *  Endpoint 4: Display Lock (On/Off Plugin Unit)
     * ──────────────────────────────────────────────────────────── */
    {
        on_off_plugin_unit::config_t config;
        config.on_off.on_off = false; /* Not locked by default */

        endpoint_t *ep = on_off_plugin_unit::create(node, &config, ENDPOINT_FLAG_NONE, levoit_handle);
        ABORT_APP_ON_FAILURE(ep != nullptr, ESP_LOGE(TAG, "Failed to create display lock endpoint"));
        display_lock_endpoint_id = endpoint::get_id(ep);
        ESP_LOGI(TAG, "Display Lock endpoint created: %d", display_lock_endpoint_id);
    }

    /* ────────────────────────────────────────────────────────────
     *  Start Matter
     * ──────────────────────────────────────────────────────────── */
    err = esp_matter::start(app_event_cb);
    ABORT_APP_ON_FAILURE(err == ESP_OK, ESP_LOGE(TAG, "Failed to start Matter, err:%d", err));

    ESP_LOGI(TAG, "Matter stack started successfully");
    ESP_LOGI(TAG, "Endpoints: AirPurifier=%d, AirQuality=%d, DisplayPower=%d, DisplayLock=%d",
             air_purifier_endpoint_id, air_quality_sensor_endpoint_id,
             display_power_endpoint_id, display_lock_endpoint_id);

    /* ── Console commands (for development) ── */
#if CONFIG_ENABLE_CHIP_SHELL
    esp_matter::console::diagnostics_register_commands();
    esp_matter::console::wifi_register_commands();
    esp_matter::console::factoryreset_register_commands();
    esp_matter::console::attribute_register_commands();
    esp_matter::console::init();
#endif

    /* ── Main loop ── */
    while (true)
    {
        vTaskDelay(10000 / portTICK_PERIOD_MS);
    }
}
