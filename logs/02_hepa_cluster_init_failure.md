```
I (929) chip[DL]: NVS set: chip-counters/reboot-count = 1 (0x1)
I (929) chip[DL]: NVS set: chip-config/unique-id = "A70617C1122C173E"
I (939) BTDM_INIT: BT controller compile version [045a658]
I (939) BTDM_INIT: Using main XTAL as clock source
I (949) BTDM_INIT: Bluetooth MAC: XX:XX:XX:XX:XX:XX
I (949) phy_init: phy_version 4863,a3a4459,Oct 28 2025,14:30:06
W (959) phy_init: failed to load RF calibration data (0x1102), falling back to full calibration
I (1019) phy_init: Saving new calibration data due to checksum failure or outdated calibration data, mode(2)
I (1299) CHIP[DL]: BLE host-controller synced
E (1809) chip[DL]: Long dispatch time: 869 ms, for event type 2
I (1809) chip[DL]: Starting ESP WiFi layer
I (1809) wifi:mode : sta (XX:XX:XX:XX:XX:XX)
I (1809) wifi:enable tsf
I (1809) chip[DL]: Posting ESPSystemEvent: Wifi Event with eventId : 43
W (1819) wifi:Haven't to connect to a suitable AP now!
I (1819) chip[DL]: Done driving station state, nothing else to do...
I (1869) chip[DMG]: AccessControl: initializing
I (1879) chip[DMG]: Examples::AccessControlDelegate::Init
I (1879) chip[DMG]: AccessControl: setting
I (1889) chip[DMG]: DefaultAclStorage: initializing
I (1889) chip[DMG]: DefaultAclStorage: 0 entries loaded
I (1899) chip[SVR]: WARNING: mTestEventTriggerDelegate is null
I (1909) chip[DIS]: Updating services using commissioning mode 1
I (1909) chip[DIS]: CHIP minimal mDNS started advertising.
I (1909) chip[DIS]: Advertise commission parameter vendorID=65521 productID=32769 discriminator=3840/15 cm=1 cp=0 jf=0
I (1919) chip[DIS]: CHIP minimal mDNS configured as 'Commissionable node device'; instance name: 56C09DDCE7C94CEA.
I (1929) chip[DIS]: mDNS service published: _matterc._udp
I (1939) chip[IN]: CASE Server enabling CASE session setups
I (1939) chip[SVR]: Joining Multicast groups
I (1949) chip[SVR]: Server Listening...
I (1949) chip[DMG]: AccessControlCluster: initializing

E (1919) data_model: get_val_internal(1022): Attribute is not managed by esp matter data model
E (1959) ResourceMonitoring: GetClusterConfig(57): Failed to get DegradationDirection
E (1959) chip[SVR]: Failed to get config for Cluster 113

I (1969) chip[ZCL]: Boot reason: 1
I (1969) chip[ZCL]: Toggle ep3 on/off from state 1 to 0
I (1979) app_driver: Display: OFF
I (1979) levoit_uart: Set screen brightness: 0 (stub)
I (1989) chip[ZCL]: Off completed. reset OnTime to  0
I (1989) chip[ZCL]: Boot reason: 1
I (1989) chip[ZCL]: Endpoint 4 On/off already set to new value
I (1999) chip[DL]: WIFI_EVENT_STA_START
W (1999) wifi:Haven't to connect to a suitable AP now!
I (2009) data_model: Cannot find minimum unused endpoint_id, try to find in the previous namespace
I (2009) data_model: Failed to open node namespace
I (2019) app_main: Matter stack started successfully
I (2019) app_main: Endpoints: AirPurifier=1, AirQuality=2, DisplayPower=3, DisplayLock=4
I (2019) chip[DL]: Done driving station state, nothing else to do...
I (2059) chip[DL]: Configuring CHIPoBLE advertising (interval 25 ms, connectable)
I (2089) chip[DL]: CHIPoBLE advertising started
I (2089) app_main: Commissioning window opened
```