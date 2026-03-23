## ESP32 Device Log
```
I (26888) chip[DL]: BLE GAP connection established (con 0)
I (26888) chip[DL]: CHIPoBLE advertising stopped
I (27818) CHIP[DL]: Write request received for CHIPoBLE RX characteristic con 0 16
I (28178) chip[DL]: Write request/command received for CHIPoBLE TX CCCD characteristic (con 0 ) indicate = 1
I (28178) chip[DL]: CHIPoBLE subscribe received

I (28348) chip[EM]: >>>[E:20746r S:0 M:170375956] (U) Msg RX from 0:XXXXXXXXXXXXXXXX [0000] to 0000000000000000 --- Type 0000:20 (SecureChannel:PBKDFParamRequest) (B:98)
I (28368) chip[EM]: <<<[E:20746r S:0 M:31714826] (U) Msg TX from 0000000000000000 to 0:XXXXXXXXXXXXXXXX [0000] [BLE] --- Type 0000:21 (SecureChannel:PBKDFParamResponse) (B:154)

I (28488) chip[EM]: >>>[E:20746r S:0 M:170375957] (U) Msg RX from 0:XXXXXXXXXXXXXXXX [0000] to 0000000000000000 --- Type 0000:22 (SecureChannel:PASE_Pake1) (B:92)
I (29438) chip[EM]: <<<[E:20746r S:0 M:31714827] (U) Msg TX from 0000000000000000 to 0:XXXXXXXXXXXXXXXX [0000] [BLE] --- Type 0000:23 (SecureChannel:PASE_Pake2) (B:127)
I (29548) chip[EM]: >>>[E:20746r S:0 M:170375958] (U) Msg RX from 0:XXXXXXXXXXXXXXXX [0000] to 0000000000000000 --- Type 0000:24 (SecureChannel:PASE_Pake3) (B:59)
I (29568) chip[EM]: <<<[E:20746r S:0 M:31714828] (U) Msg TX from 0000000000000000 to 0:XXXXXXXXXXXXXXXX[0000] [BLE] --- Type 0000:40 (SecureChannel:StatusReport) (B:30)

I (29588) chip[SC]: SecureSession[0x3ffc5ff8, LSID:XXXXX]: State change 'kEstablishing' --> 'kActive'
I (29588) chip[SVR]: Commissioning completed session establishment step
I (29608) app_main: Commissioning session started
I (29608) app_main: Commissioning window closed

I (31078) chip[DL]: Confirm received for CHIPoBLE TX characteristic indication (con 0) status= 7 
I (31088) chip[DL]: Write request/command received for CHIPoBLE TX CCCD characteristic (con 0 ) indicate = 0
I (31098) chip[DL]: CHIPoBLE unsubscribe received
I (31098) chip[DL]: BLE GAP connection terminated (con 0 reason 0x208)
I (31108) chip[DL]: Closing BLE GATT connection (con 0)
I (31118) esp_matter_core: BLE Disconnected

I (89608) chip[FS]: Fail-safe timer expired
E (89608) chip[SVR]: Failsafe timer expired
I (89608) chip[SC]: SecureSession[0x3ffc5ff8, LSID:XXXXX]: State change 'kActive' --> 'kPendingEviction'
E (89628) chip[SVR]: Commissioning failed (attempt 1): 32
I (89688) app_main: Commissioning failed, fail safe timer expired
I (89738) app_main: Commissioning window opened
```

## chip-tool Controller Log (macOS)
```
[1773236741.605][XXXXX:XXXXX:main] [FP] Fabric index 0x1 was retrieved from storage. Compressed FabricId 0xXXXXXXXXXXXXXXXX, FabricId 0xXXXXXXXXXXXXXXXX, NodeId 0xXXXXXXXXXXXXXXXX, VendorId 0xFFF1
[1773236741.622][XXXXX:XXXXX:chip] [CTL] Joined the fabric at index 1. Fabric ID is 0x0000000000000001[1773236741.627] [XXXXX:XXXXX:chip] [BLE] ConnectionDelegate NewConnection with discriminator list:[ 3840 (long, 0xf00) ][1773236747.017] [XXXXX:XXXXX:chip] [BLE] Connecting to device 0xXXXXXXXXXXXX with discriminator: 3840[1773236751.307] [XXXXX:XXXXX:chip] [IN] SecureSession[0xXXXXXXXXX]: Allocated Type:1 LSID:56078[1773236751.307] [XXXXX:XXXXX:chip] [SC] Assigned local session key ID 56078
[1773236751.307][XXXXX:XXXXX:chip] [EM] <<<[E:6424i S:0 M:244272354] (U) Msg TX from XXXXXXXXXXXXXXXX to 0:0000000000000000 [0000] [BLE] --- Type 0000:20 (SecureChannel:PBKDFParamRequest) (B:98)[1773236751.307] [XXXXX:XXXXX:chip][IN] Message appended to BLE send queue
[1773236751.307] [XXXXX:XXXXX:chip] [SC] Sent PBKDF param request[II:500ms AI:300ms AT:4000ms)[1773236751.316] [XXXXX:XXXXX:chip] [BLE] Failed to write characteristic: @
[1773236751.316][XXXXX:XXXXX:chip] [IN] Failed to establish BLE connection: src/platform/Darwin/BleConnectionDelegateImpl.mm:541: Ble Error 0x00000407: GATT write characteristic operation failed
[1773236751.316][XXXXX:XXXXX:chip] [IN] Clearing BLE pending packets.[1773236751.316] [XXXXX:XXXXX:chip] [BLE] Auto-closing end point's BLE connection.

[1773236783.311][XXXXX:XXXXX:chip] [SC] PASESession timed out while waiting for a response from the peer. Expected message type was 33
[1773236783.312][XXXXX:XXXXX:chip] [TOO] Secure Pairing Failed[1773236783.312] [XXXXX:XXXXX:chip] [DIS] Closing all BLE connections[1773236783.312] [XXXXX:XXXXX:chip][TOO] Pairing Failure: src/protocols/secure_channel/PASESession.cpp:310: CHIP Error 0x00000032: Timeout[1773236783.315] [XXXXX:XXXXX:main] [TOO] Run command failure: src/protocols/secure_channel/PASESession.cpp:310: CHIP Error 0x00000032: Timeout
```