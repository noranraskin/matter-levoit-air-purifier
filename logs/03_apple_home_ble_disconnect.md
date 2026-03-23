```
I (11299) chip[DL]: BLE GAP connection established (con 0)
I (11299) chip[DL]: CHIPoBLE advertising stopped
I (12049) CHIP[DL]: Write request received for CHIPoBLE RX characteristic con 0 16
I (12049) chip[BLE]: local and remote recv window sizes = 5
I (12049) chip[BLE]: selected BTP version 4
I (12049) chip[BLE]: using BTP fragment sizes rx 244 / tx 244.
I (12319) chip[DL]: Write request/command received for CHIPoBLE TX CCCD characteristic (con 0 ) indicate = 1
I (12319) chip[DL]: CHIPoBLE subscribe received
I (12319) NimBLE: GATT procedure initiated: indicate; 
I (12329) NimBLE: att_handle=18

I (12379) chip[DL]: Confirm received for CHIPoBLE TX characteristic indication (con 0) status= 14 
I (12379) CHIP[DL]: Write request received for CHIPoBLE RX characteristic con 0 16
I (12399) chip[EM]: >>>[E:9141r S:0 M:201001768] (U) Msg RX from 0:XXXXXXXXXXXXXXXX [0000] to 0000000000000000 --- Type 0000:20 (SecureChannel:PBKDFParamRequest) (B:98)
I (12409) chip[EM]: <<<[E:9141r S:0 M:249082221] (U) Msg TX from 0000000000000000 to 0:XXXXXXXXXXXXXXXX[0000] [BLE] --- Type 0000:21 (SecureChannel:PBKDFParamResponse) (B:154)

I (12429) chip[SVR]: Commissioning session establishment step started
I (12529) chip[EM]: >>>[E:9141r S:0 M:201001769] (U) Msg RX from 0:XXXXXXXXXXXXXXXX [0000] to 0000000000000000 --- Type 0000:22 (SecureChannel:PASE_Pake1) (B:92)
I (13489) chip[EM]: <<<[E:9141r S:0 M:249082222] (U) Msg TX from 0000000000000000 to 0:XXXXXXXXXXXXXXXX[0000] [BLE] --- Type 0000:23 (SecureChannel:PASE_Pake2) (B:127)
I (13629) chip[EM]: >>> [E:9141r S:0 M:201001770] (U) Msg RX from 0:XXXXXXXXXXXXXXXX [0000] to 0000000000000000 --- Type 0000:24 (SecureChannel:PASE_Pake3) (B:59)
I (13639) chip[EM]: <<<[E:9141r S:0 M:249082223] (U) Msg TX from 0000000000000000 to 0:XXXXXXXXXXXXXXXX [0000] [BLE] --- Type 0000:40 (SecureChannel:StatusReport) (B:30)

I (13659) chip[SC]: SecureSession[0x3ffc5ff8, LSID:XXXXX]: State change 'kEstablishing' --> 'kActive'
I (13669) chip[SVR]: Commissioning completed session establishment step
I (13669) chip[DIS]: Updating services using commissioning mode 0
I (13679) chip[DIS]: CHIP minimal mDNS started advertising.
I (13689) chip[SVR]: Device completed Rendezvous process
I (13689) app_main: Commissioning session started
I (13689) app_main: Commissioning window closed

I (13829) chip[EM]: >>>[E:9142r S:XXXXX M:17392966] (S) Msg RX from 0:FFFFFFFB00000000 [0000] to 0000000000000000 --- Type 0001:02 (IM:ReadRequest) (B:136)
E (13849) chip[DMG]: Fail to retrieve data, roll back and encode status on clusterId: 0x0000_0030, attributeId: 0x0000_000Cerr = 586
I (13859) chip[EM]: <<<[E:9142r S:XXXXX M:90628201] (S) Msg TX from 0000000000000000 to 0:FFFFFFFB00000000 [0000] [BLE] --- Type 0001:05 (IM:ReportData) (B:253)

I (14019) chip[EM]: >>>[E:9143r S:XXXXX M:17392967] (S) Msg RX from 0:FFFFFFFB00000000 [0000] to 0000000000000000 --- Type 0001:02 (IM:ReadRequest) (B:128)
E (14039) chip[DMG]: Read request on unknown cluster - no data version available
E (14039) chip[DMG]: Fail to retrieve data, roll back and encode status on clusterId: 0x0000_0046, attributeId: 0x0000_0002err = 5c3
E (14059) chip[DMG]: Read request on unknown cluster - no data version available
E (14059) chip[DMG]: Fail to retrieve data, roll back and encode status on clusterId: 0x0000_0046, attributeId: 0x0000_0001err = 5c3
E (14069) chip[DMG]: Read request on unknown cluster - no data version available
E (14079) chip[DMG]: Fail to retrieve data, roll back and encode status on clusterId: 0x0000_0046, attributeId: 0x0000_0000err = 5c3
I (14129) chip[EM]: <<<[E:9143r S:XXXXX M:90628202] (S) Msg TX from 0000000000000000 to 0:FFFFFFFB00000000 [0000] [BLE] --- Type 0001:05 (IM:ReportData) (B:414)

I (15099) chip[DL]: Confirm received for CHIPoBLE TX characteristic indication (con 0) status= 7 
I (15109) chip[DL]: Write request/command received for CHIPoBLE TX CCCD characteristic (con 0 ) indicate = 0
I (15119) chip[DL]: CHIPoBLE unsubscribe received
I (15119) chip[DL]: BLE GAP connection terminated (con 0 reason 0x208)
I (15109) chip[BLE]: Releasing end point's BLE connection back to application.
I (15129) chip[DL]: Closing BLE GATT connection (con 0)
E (15139) chip[DL]: ble_gap_terminate() failed: 48
I (15139) esp_matter_core: BLE Disconnected
```