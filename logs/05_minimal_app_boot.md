```
I (786) heap_init: At 4009DBA8 len 00002458 (9 KiB): IRAM
I (792) heap_init: At 3FF80000 len 00002000 (8 KiB): RTCRAM
I (798) spi_flash: detected chip: generic
I (801) spi_flash: flash io: dio
I (808) main_task: Started on CPU0
I (808) main_task: Calling app_main()

I (815) app_main: Initializing NVS flash...
I (820) app_main: NVS init successful.
I (828) app_driver: Initializing minimal stubs
I (828) app_main: Air Purifier endpoint created: 1

I (868) wifi:wifi driver task: 3ffdba10, prio:23, stack:6656, core=0
I (868) wifi:wifi firmware version: 1ac82cd
I (868) wifi:wifi certification version: v7.0
I (878) wifi:config NVS flash: enabled
I (878) wifi:config nano formatting: disabled
I (958) BTDM_INIT: BT controller compile version [045a658]
I (958) BTDM_INIT: Bluetooth MAC: XX:XX:XX:XX:XX:XX
I (968) phy_init: phy_version 4863,a3a4459,Oct 28 2025,14:30:06

I (1808) chip[DL]: Starting ESP WiFi layer
I (1808) wifi:mode : sta (XX:XX:XX:XX:XX:XX)
I (1868) chip[DMG]: AccessControl: initializing
I (1878) chip[DMG]: DefaultAclStorage: 0 entries loaded
I (1908) chip[DIS]: Updating services using commissioning mode 1
I (1908) chip[DIS]: CHIP minimal mDNS started advertising.
I (1918) chip[DIS]: Advertise commission parameter vendorID=65521 productID=32769 discriminator=3840/15 cm=1 cp=0 jf=0
I (1928) chip[DIS]: mDNS service published: _matterc._udp

I (1978) app_main: Matter stack started successfully
I (1988) app_main: Endpoints: AirPurifier=1
I (2048) chip[DL]: CHIPoBLE advertising started
I (2048) app_main: Commissioning window opened

> I (26888) chip[DL]: BLE GAP connection established (con 0)
I (26888) chip[DL]: CHIPoBLE advertising stopped
I (28348) chip[EM]: >>>[E:20746r S:0 M:170375956] (U) Msg RX from 0:XXXXXXXXXXXXXXXX [0000] ... Type 0000:20 (SecureChannel:PBKDFParamRequest)
I (28368) chip[EM]: <<<[E:20746r S:0 M:31714826] (U) Msg TX from 0000000000000000 to 0:XXXXXXXXXXXXXXXX ... Type 0000:21 (SecureChannel:PBKDFParamResponse)
I (28388) chip[SVR]: Commissioning session establishment step started
I (29588) chip[SC]: SecureSession[0x3ffc5ff8, LSID:XXXXX]: State change 'kEstablishing' --> 'kActive'
I (29608) app_main: Commissioning session started
I (29608) app_main: Commissioning window closed

I (29658) chip[EM]: >>>[E:20747r S:XXXXX M:198146354] (S) Msg RX from 0:XXXXXXXXXXXXXXXX [0000] ... Type 0001:02 (IM:ReadRequest)
I (29688) chip[EM]: <<<[E:20747r S:XXXXX M:44630158] (S) Msg TX from 0000000000000000 to 0:XXXXXXXXXXXXXXXX ... Type 0001:05 (IM:ReportData)

I (31098) chip[DL]: CHIPoBLE unsubscribe received
I (31098) chip[DL]: BLE GAP connection terminated (con 0 reason 0x208)
I (31118) esp_matter_core: BLE Disconnected

I (89608) chip[FS]: Fail-safe timer expired
E (89608) chip[SVR]: Failsafe timer expired
I (89608) chip[SC]: SecureSession[0x3ffc5ff8, LSID:XXXXX]: State change 'kActive' --> 'kPendingEviction'
I (89688) app_main: Commissioning failed, fail safe timer expired
I (89738) app_main: Commissioning window opened
```