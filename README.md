
# Matter Implementation for the Levoit Core 300S Air Purifier

⚠️ **WARNING: CURRENTLY NOT WORKING / WORK IN PROGRESS** ⚠️

This project aims to replace the factory firmware (or ESPHome firmware) on the Levoit Core 300S Air Purifier's ESP32 module with a native, standalone Matter integration using `esp-idf` and `esp-matter`. 

Currently, the device compiles and boots, but **Matter commissioning fails**. We are stuck at the BLE provisioning stage. This repository is published in its current state in hopes that someone with deep `esp-matter` or `matter` knowledge can help debug the pairing process.

## Current Status & Known Issues

During development, we stripped the application down from its full intended feature set (Air Purifier, Air Quality Sensor, Display endpoints) to a bare minimum (just Root + Basic Air Purifier endpoint) to isolate the commissioning failure, but the issue persists. 

Here is a structured list of the major hurdles and bugs encountered so far:

### 1. Persistent Commissioning Aborts (BLE Disconnects)
**The Problem:** The device successfully advertises over BLE and begins the commissioning process (PASE secure session establishes perfectly). However, right after establishing the secure channel, the Matter controller (both Apple Home and `chip-tool`) reads two clusters and then actively disconnects BLE (reason `0x208` or `0x213`). The controller never sends Wi-Fi credentials or the `ArmFailSafe` command. The failsafe timer on the ESP32 eventually expires (60s).
**What we tried:** 
* Cleared stale KVS state from `chip-tool`.
* Added NVS initialization error recovery to ensure the flash isn't corrupted.
* Disabled the Mode Select cluster, which is strict about mandatory supported modes.
* Increased the `MAX_DYNAMIC_ENDPOINT_COUNT` to 8 to leave room for hidden system endpoints.
* Disabled `CONFIG_ESP_WIFI_SOFTAP_SUPPORT` in alignment with working SDK examples.
* **Logs:** [See `chip-tool` pairing timeout logs](docs/logs/04_chip_tool_pairing_timeout.md)

### 2. Apple HomeKit Ecosystem Rejection
**The Problem:** Trying to commission the device using the Home Assistant Companion App on iOS silently fails.
**Cause:** The iOS app routes commissioning through Apple's native Matter framework. Currently, Apple Home does not support the Matter Air Purifier device type (`0x002D`). When it encounters the unknown device type, it silently drops the BLE connection.
**Workaround:** Commission using Home Assistant's Web UI directly, or use `chip-tool` to test.
* **Logs:** [See Apple Home BLE disconnect logs](docs/logs/03_apple_home_ble_disconnect.md)

### 3. HEPA Filter Monitoring Initialization Bug
**The Problem:** When adding the HEPA Filter Monitoring cluster (`0x0071`), the ESP32 threw `Failed to get DegradationDirection` and cluster initialization failed at boot.
**Cause:** A quirk in the `esp-matter` SDK. The `create_degradation_direction()` function flags the attribute with `ATTRIBUTE_FLAG_MANAGED_INTERNALLY`, but the `GetClusterConfig()` init callback attempts to read it using `get_val_internal()`, which explicitly rejects internally managed attributes.
**Workaround:** Implemented a custom `HepaFilterDelegate` inherited from `ResourceMonitoring::Delegate` and manually configured the condition feature map. 
* **Logs:**[See HEPA cluster init failure logs](docs/logs/02_hepa_cluster_init_failure.md)

### 4. Custom Pairing Codes and Kconfig Quirks
**The Problem:** Attempting to set custom setup PINs and Discriminators via `sdkconfig` fails.
**Cause:** The ESP32 port of `connectedhomeip` does not expose test setup Kconfig symbols natively like other platforms do. It falls back to the CHIP defaults.
**Workaround:** You must use the default hardcoded CHIP credentials for testing:
* **Passcode:** `20202021`
* **Discriminator:** `3840` (`0xF00`)

---

## Hardware Disassembly
Instructions taken from the `esphome-levoit-air-purifier` project:
1. Place the purifier upside down and remove the base cover and filter to expose 8 screws (4 have washers).
2. Remove all 8 screws *(be careful, as these are made out of a soft metal and strip easily)*.
3. Using a plastic pry tool, slide in between the tabs.
4. Separate the base and top sleeve.
5. Unplug the logic board to access the ESP32 module.

## Build and Flash
This project requires [ESP-IDF](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/) and the [ESP-Matter SDK](https://docs.espressif.com/projects/esp-matter/en/latest/esp32/).

```bash
# Set your target
idf.py set-target esp32

# Build the firmware
idf.py build

# Flash and open the serial monitor
idf.py flash monitor
```
(Note: If you run into NimBLE missing directory errors during set-target, run `git submodule update --init --recursive` in your esp-idf folder).

Commissioning
After flashing the ESP32, a 15-minute commissioning window will open over BLE. Because of the Kconfig limitations mentioned above, use the default pairing code:

Manual Pairing Code: 34970112332 (Or use Passcode 20202021 / Discriminator 3840)

Using chip-tool:

```bash
chip-tool pairing ble-wifi 1 "YOUR_WIFI_SSID" "YOUR_WIFI_PASSWORD" 20202021 3840
```

## Credits & Acknowledgements
This project would not be possible without the reverse-engineering efforts from the Home Assistant / ESPHome community.

UART protocol reverse engineering and original ESPHome implementation inspired by: acvigue/esphome-levoit-air-purifier

CADR rates and filter life calculation tracking logic inspired by:mulcmu/esphome-levoit-core300s
