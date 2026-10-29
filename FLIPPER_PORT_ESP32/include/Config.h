#pragma once
#include <Arduino.h>

/*
 * ============================================================================
 * FLIPPER_PORT_ESP32 - Hardware & System Configuration
 * Created by Ranjith
 * Project: FLIPPER_PORT_ESP32
 * Target: ESP32 Dev Module + 2.8" SPI TFT (ILI9341 + XPT2046)
 * ============================================================================
 */

// Hardware GPIO Definitions
#define PIN_TFT_BL     32  // TFT Backlight control (Active HIGH)
#define PIN_SD_CS      12  // MicroSD Chip Select (Shared SPI bus, held HIGH)
#define PIN_TOUCH_CS   21  // Touch Controller Chip Select (Shared SPI bus)
#define PIN_TFT_CS     17  // TFT Display Chip Select
#define PIN_TFT_RST     5  // TFT Display Reset
#define PIN_TFT_DC     16  // TFT Data / Command
#define PIN_TFT_MOSI   23  // SPI Master Out Slave In
#define PIN_TFT_MISO   19  // SPI Master In Slave Out
#define PIN_TFT_SCLK   18  // SPI Serial Clock

// System Strings
#define PROTOWARE_BRAND        "PROTOX"
#define PROTOWARE_PROJECT      "FLIPPER_PORT_ESP32"
#define PROTOWARE_OS_NAME      "FLIPPER_PORT_ESP32 OS"
#define PROTOWARE_VERSION      "1.0.0"
#define PROTOWARE_BUILD_DATE   "2026.09"

// UI Layout Dimensions (Responsive)
#define STATUS_BAR_HEIGHT      24
#define BOTTOM_BAR_HEIGHT      28

// Timing & Animation
#define BOOT_ANIMATION_MS      2200
#define DEMO_MODE_CYCLE_MS     3500
#define TOUCH_DEBOUNCE_MS        60
#define TOUCH_LONG_PRESS_MS     600
