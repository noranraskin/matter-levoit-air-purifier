/*
 * Levoit Core 300S UART Protocol Types
 *
 * Constants and structures for the binary UART protocol between
 * the ESP32 and the secondary MCU. Based on reverse engineering from:
 * - https://github.com/acvigue/esphome-levoit-air-purifier
 * - https://github.com/mulcmu/esphome-levoit-core300s
 */

#pragma once

#include <stdint.h>

/* ── UART Configuration ── */
#define LEVOIT_UART_TX_PIN       17
#define LEVOIT_UART_RX_PIN       16
#define LEVOIT_UART_BAUD_RATE    115200
#define LEVOIT_UART_NUM          UART_NUM_1

/* ── Protocol Constants ── */
#define LEVOIT_HEADER_BYTE       0xA5
#define LEVOIT_PKT_SEND          0x22
#define LEVOIT_PKT_ACK           0x12
#define LEVOIT_PKT_ERROR         0x52

/* ── Payload Type Constants (Core 300S) ── */
#define LEVOIT_PT_STATUS_REQUEST      0x013140
#define LEVOIT_PT_STATUS_RESPONSE     0x013040
#define LEVOIT_PT_AUTO_STATUS         0x016040
#define LEVOIT_PT_SET_POWER_STATE     0x0100A0
#define LEVOIT_PT_SET_FAN_MODE        0x01E0A5
#define LEVOIT_PT_SET_FAN_MANUAL      0x0160A2
#define LEVOIT_PT_SET_FAN_AUTO_MODE   0x01E6A5
#define LEVOIT_PT_SET_SCREEN_BRIGHT   0x0105A1
#define LEVOIT_PT_SET_DISPLAY_LOCK    0x0100D1
#define LEVOIT_PT_SET_RESET_FILTER    0x01E4A5
#define LEVOIT_PT_SET_WIFI_LED        0x0129A1
#define LEVOIT_PT_SET_FILTER_LED      0x01E2A5
#define LEVOIT_PT_SET_NIGHTLIGHT      0x0103A0
#define LEVOIT_PT_TIMER_STATUS        0x0165A2
#define LEVOIT_PT_SET_TIMER_TIME      0x0164A2
#define LEVOIT_PT_TIMER_START_CLEAR   0x0166A2

/* ── Fan Modes ── */
typedef enum {
    LEVOIT_FAN_MODE_MANUAL = 0x00,
    LEVOIT_FAN_MODE_SLEEP  = 0x01,
    LEVOIT_FAN_MODE_AUTO   = 0x02,
} levoit_fan_mode_t;

/* ── Fan Speeds (Manual Mode) ── */
typedef enum {
    LEVOIT_FAN_SPEED_OFF  = 0x00,
    LEVOIT_FAN_SPEED_LOW  = 0x01,
    LEVOIT_FAN_SPEED_MED  = 0x02,
    LEVOIT_FAN_SPEED_HIGH = 0x03,
} levoit_fan_speed_t;

/* ── Auto Mode Sub-types ── */
typedef enum {
    LEVOIT_AUTO_DEFAULT   = 0x00,
    LEVOIT_AUTO_QUIET     = 0x01,
    LEVOIT_AUTO_EFFICIENT = 0x02,
} levoit_auto_mode_t;

/* ── WiFi LED Modes ── */
typedef enum {
    LEVOIT_WIFI_LED_OFF   = 0x00,
    LEVOIT_WIFI_LED_ON    = 0x01,
    LEVOIT_WIFI_LED_BLINK = 0x02,
} levoit_wifi_led_t;

/* ── CADR Values (CFM) for Filter Life Tracking ── */
#define LEVOIT_CADR_SLEEP  37
#define LEVOIT_CADR_LOW    60
#define LEVOIT_CADR_MED    80
#define LEVOIT_CADR_HIGH   141

/* Filter lifetime: 6 months × 30 days × 24 hours × 60 min = 259200 minutes at High speed */
#define LEVOIT_FILTER_LIFETIME_MINUTES  259200
/* Total filter capacity in CFM·minutes */
#define LEVOIT_FILTER_TOTAL_CAPACITY    (LEVOIT_FILTER_LIFETIME_MINUTES * LEVOIT_CADR_HIGH)

/* ── Device Status (parsed from status response) ── */
typedef struct {
    bool     power_on;
    levoit_fan_mode_t  fan_mode;
    levoit_fan_speed_t fan_speed;       /* Current fan speed (0-3, 255=off) */
    levoit_fan_speed_t manual_speed;    /* Selected manual speed */
    uint8_t  screen_brightness;         /* 0x00=off, 0x64=full */
    bool     screen_on;
    bool     display_locked;
    uint8_t  air_quality;               /* 0-255 AQI value */
    uint16_t pm25_raw;                  /* Raw PM2.5 × 10. 0xFFFF = sensor error */
    levoit_auto_mode_t auto_mode;
} levoit_status_t;

/* ── Callback type for status updates ── */
typedef void (*levoit_status_cb_t)(const levoit_status_t *status, void *user_data);
