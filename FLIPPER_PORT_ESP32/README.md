# FLIPPER_PORT_ESP32

![Platform](https://img.shields.io/badge/Platform-ESP32-blue?logo=espressif)
![Framework](https://img.shields.io/badge/Framework-Arduino-teal?logo=arduino)
![IDE](https://img.shields.io/badge/IDE-PlatformIO-orange?logo=platformio)
![Author](https://img.shields.io/badge/Created%20by-Ranjith-success)
![License](https://img.shields.io/badge/License-MIT-green)

An open-source multi-tool firmware for the **ESP32** microcontroller inspired by the **Flipper Zero**. Designed for penetration testers, embedded engineers, cybersecurity researchers, and hardware hobbyists.

---

## 📖 Table of Contents

- [Overview](#-overview)
- [Key Features](#-key-features)
- [Hardware & Bill of Materials (BOM)](#-hardware--bill-of-materials-bom)
- [Pinout & Wiring Guide](#-pinout--wiring-guide)
- [Project Architecture](#-project-architecture)
- [Getting Started](#-getting-started)
- [Screen Configuration](#-screen-configuration)
- [Navigation & Controls](#-navigation--controls)
- [Disclaimer & Safety](#-disclaimer--safety)
- [Credits](#-credits)

---

## ⚡ Overview

**FLIPPER_PORT_ESP32** is a modular, standalone firmware turning an off-the-shelf ESP32 development board into an interactive multi-protocol device. Equipped with Sub-GHz, 2.4 GHz RF, Wi-Fi, BLE, Infrared, BadUSB, and an SD card file manager, it operates independently with a high-contrast 128x64 OLED display and a 5-button navigation interface.

---

## 🚀 Key Features

### 📡 1. Sub-GHz Radio (CC1101)
- **Multi-Frequency Support**: 315 MHz, 433.92 MHz, 868 MHz, 915 MHz.
- **Spectrum Analyzer**: Real-time signal strength and RF spectrum visualization.
- **Raw Signal Capture**: Capture, save, and analyze raw RF waveforms.
- **Signal Replay**: Transmit captured signals or custom frequency packets.
- **Configurable Modulation**: Support for ASK/OOK, 2-FSK, 4-FSK, GFSK, and MSK.
- **RF Jammer Utility**: Targeted frequency jamming tests for RF resilience auditing.

### 📶 2. 2.4 GHz Radio (nRF24L01+)
- **2.4 GHz Band Scanner**: Continuous sweep across 128 channels in the 2.4 GHz spectrum.
- **Packet Analyzer & Counter**: Real-time packet throughput statistics.
- **Channel Stress Utility**: Channel-specific noise generation and transmission verification.

### 🌐 3. Wi-Fi Auditing & Tools
- **Access Point Scanner**: Scans 802.11 b/g/n networks, displaying SSID, BSSID, RSSI, channel, and encryption.
- **Promiscuous Mode Packet Analyzer**: Captures management and data packets.
- **Deauthentication Auditing**: Test network disconnect behaviors against standard 802.11 frame handling.
- **Beacon Spammer**: Generate multi-SSID broadcast beacons for wireless range evaluation.
- **Probe Request Monitor**: Detect broadcast probe requests from nearby client devices.
- **Captive Portal Simulation**: Educational captive portal framework for social-engineering security tests.

### 🔵 4. Bluetooth Low Energy (BLE)
- **BLE Scanner**: Scans nearby advertising peripherals, showing device names, MAC addresses, RSSI, and vendor payloads.
- **BLE Virtual Mouse**: Emulates a wireless Bluetooth mouse for human-interface testing.
- **BLE Beacon Advertiser**: Broadcasts test advertising packets and simulated beacon profiles.

### 📺 5. Infrared (IR)
- **IR Receiver & Decoder**: 38 kHz receiver decoding NEC, Sony, Samsung, RC5, RC6, and raw pulse formats.
- **Signal Saving & Playback**: Record received codes onto MicroSD card storage for later transmission.
- **Universal Remotes**: Pre-loaded database of common power, volume, and mute codes for TVs, AC units, and projectors.

### ⌨️ 6. BadUSB & HID Keystroke Injection
- **USB Keyboard Emulation**: High-speed automated keystroke injection via USB HID.
- **DuckyScript / HID Script Launcher**: Execute scripts directly from the MicroSD card.
- **Built-in Presets**: Quick demonstration scripts, system diagnostic shortcuts, and payload automation.

### 💾 7. MicroSD File Manager
- **FAT32 File Browser**: Navigate folders, view files, rename files, and delete logs directly on the device.
- **SD Card Formatter**: Quick format tool for card initialization in the field.
- **Storage Diagnostics**: View total capacity, free space, and cluster information.

### 🔌 8. Hardware & GPIO Utilities
- **I2C Bus Scanner**: Scans all 127 I2C addresses and prints active device addresses.
- **GPIO Pin Tester**: Test pin logic levels, pull-up/pull-down states, and digital outputs.
- **System Information**: Real-time display of CPU frequency, free heap memory, flash size, and chip revision.

### 🎮 9. Mini Apps & Retro Games
- **Scientific / Basic Calculator**: Fast on-screen arithmetic tool.
- **Password Generator**: Configurable random password generator with mixed character sets.
- **Pomodoro Timer**: Productivity countdown timer with display notifications.
- **Flashlight App**: WS2812B NeoPixel RGB LED flashlight with selectable color modes.
- **Safe Mode**: Toggle to immediately lock down and disable all RF transmission functions for legal compliance.
- **Games**: Classic **Snake** and **Space Shooter** with score tracking.

---

## 🛠️ Hardware & Bill of Materials (BOM)

| Component | Recommended Model | Purpose |
|:---|:---|:---|
| **Microcontroller** | ESP32 Dev Module (ESP-WROOM-32 / ESP32-S3) | Core processing, Wi-Fi, BLE, and logic |
| **Display** | 1.3" (SH1106) or 0.96" (SSD1306) I2C OLED (128x64) | Primary graphical user interface |
| **Sub-GHz Transceiver** | TI CC1101 Module (SPI with SMA Antenna) | Sub-GHz RX/TX (300-928 MHz) |
| **2.4 GHz Transceiver** | Nordic nRF24L01+ Module (SPI) | 2.4 GHz spectrum scanning and analysis |
| **Infrared Transmitter** | 940nm High-Power IR LED + Transistor Driver | Infrared transmission |
| **Infrared Receiver** | VS1838B (38 kHz IR Demodulator) | Infrared reception and decoding |
| **Storage** | MicroSD SPI Card Reader Module | File storage, scripts, and logs |
| **Status LED** | WS2812B NeoPixel RGB LED | Status indicators and flashlight |
| **Navigation** | 5x Tactile Push Buttons (D-Pad + Center) | Menu navigation and control |
| **Power** | 3.7V Li-Po Battery + TP4056 USB-C Charging Board | Portable power supply |

---

## 📌 Pinout & Wiring Guide

All default pin assignments are defined in [`include/HIZMOS_common.h`](include/HIZMOS_common.h):

### Display (I2C)
| Display Pin | ESP32 GPIO | Description |
|:---|:---|:---|
| `SDA` | **GPIO 21** | I2C Serial Data |
| `SCL` | **GPIO 22** | I2C Serial Clock |
| `VCC` | `3.3V` / `5V` | Power supply |
| `GND` | `GND` | Ground |

### Navigation Buttons (Active LOW - Internal Pull-Up)
| Button | ESP32 GPIO | Function |
|:---|:---|:---|
| **UP** | **GPIO 26** | Move cursor up / Increment value |
| **DOWN** | **GPIO 33** | Move cursor down / Decrement value |
| **LEFT / BACK** | **GPIO 25** | Return to previous menu / Back |
| **RIGHT / SELECT** | **GPIO 27** | Enter menu / Confirm selection |
| **CENTER** | **GPIO 32** | Action / Toggle |

### Sub-GHz Module (CC1101 - SPI)
| CC1101 Pin | ESP32 GPIO | Description |
|:---|:---|:---|
| `SCK` | **GPIO 14** | Shared SPI Clock |
| `MISO` | **GPIO 12** | Shared SPI Master In Slave Out |
| `MOSI` | **GPIO 13** | Shared SPI Master Out Slave In |
| `CSN / CS` | **GPIO 15** | CC1101 Chip Select |
| `GDO0` | **GPIO 16** | CC1101 Data Input/Output 0 |
| `GDO2` | **GPIO 34** | CC1101 Data Output 2 |

### 2.4 GHz Module (nRF24L01+ - SPI)
| nRF24 Pin | ESP32 GPIO | Description |
|:---|:---|:---|
| `SCK` | **GPIO 18** | High-Speed Radio SPI Clock |
| `MISO` | **GPIO 19** | High-Speed Radio SPI MISO |
| `MOSI` | **GPIO 23** | High-Speed Radio SPI MOSI |
| `CE` | **GPIO 17** | Chip Enable Activate RX/TX |
| `CSN` | **GPIO 5** | SPI Chip Select |

### MicroSD Card (SPI)
| SD Card Pin | ESP32 GPIO | Description |
|:---|:---|:---|
| `SCK` | **GPIO 14** | Shared SPI Clock |
| `MISO` | **GPIO 12** | Shared SPI MISO |
| `MOSI` | **GPIO 13** | Shared SPI MOSI |
| `CS` | **GPIO 15** | SD Card Chip Select |

### Infrared & Peripherals
| Peripheral | ESP32 GPIO | Description |
|:---|:---|:---|
| **IR Transmitter** | **GPIO 4** | 940nm IR LED modulation driver |
| **IR Receiver** | **GPIO 35** | VS1838B demodulated output (Input only) |
| **NeoPixel LED** | **GPIO 2** | WS2812B RGB Data Line |

---

## 📂 Project Architecture

```
FLIPPER_PORT_ESP32/
├── include/
│   ├── Config.h                  # Hardware configuration & system defines
│   ├── HIZMOS_common.h           # Global pin mapping, libraries & extern definitions
│   ├── Icons.h                   # Bitmap icons for menus and UI elements
│   ├── Screens.h                 # Screen render functions and prototypes
│   └── Theme.h                   # Color palettes & UI styling
├── src/
│   ├── HIZMOS_OLED_U8G2lib.ino   # Main setup(), loop(), and display driver init
│   ├── mainmenu.ino              # Primary application carousel & icon menu
│   ├── mainmenu.h                # Main menu header & image tables
│   ├── about-logic.ino           # System about screen
│   ├── apps-menu.ino             # Apps launcher (Calculator, Games, etc.)
│   ├── bad-usb-menu.ino          # BadUSB injection payloads & keyboard menus
│   ├── ble-menu.ino              # BLE tools and attack functions
│   ├── ble-mouse.ino             # Bluetooth LE mouse emulation
│   ├── ble-scanner.ino           # Bluetooth device discovery engine
│   ├── calculater.ino            # Interactive calculator app
│   ├── check-sys-devices.ino     # Hardware health checking engine
│   ├── dolphinreactions.h        # Tamagotchi-style mascot animations
│   ├── ELECHOUSE_CC1101_SRC_DRV  # Low-level CC1101 register driver (.cpp/.h)
│   ├── files-menu.ino            # SD card file browser & explorer
│   ├── globalvars-funcs.ino      # Common rendering routines & boot screens
│   ├── gpio-menu.ino             # GPIO pin testing interface
│   ├── hid-keyboard.ino          # Virtual keyboard emulation
│   ├── hid-script.ino            # DuckyScript interpreter
│   ├── i2c-scanner.ino           # I2C bus scanner
│   ├── infrared-menu.ino         # IR transmission and reception menu
│   ├── INFRARED-READ-SAVED.ino   # IR recorder & SD signal storage
│   ├── nrf-jammer.ino            # 2.4 GHz channel stress tool
│   ├── nrf-scanner.ino           # 2.4 GHz spectrum scanner
│   ├── nrf-tools.ino             # nRF24 utilities
│   ├── packet-analyzer.ino       # Wi-Fi promiscuous packet sniffer
│   ├── password-generator.ino    # Random cryptographic password generator
│   ├── pomdoro-timer.ino         # Pomodoro productivity tool
│   ├── restart-logic.ino         # ESP32 software reboot logic
│   ├── sd-formater.ino           # SD card formatting utility
│   ├── sd-info.ino               # SD card capacity & filesystem information
│   ├── setteings-menu.ino        # Device preferences & safe mode toggle
│   ├── snake-game.ino            # Retro Snake game
│   ├── space-game.ino            # Retro Space Shooter game
│   ├── sub-ghz-menu.ino          # Sub-GHz UI navigation
│   ├── subghz.ino                # CC1101 RF transmission and spectrum routines
│   ├── universal-remotes.ino     # Multi-device IR remote control database
│   ├── wifi-extra-tools.ino      # Beacon spoofer and probe request monitoring
│   ├── wifi-menu.ino             # Wi-Fi tool selector
│   └── wifi-scanning.ino         # Access point detection & RSSI monitor
├── platformio.ini                # PlatformIO build settings & dependencies
└── README.md                     # Project documentation
```

---

## 🚀 Getting Started

### 1. Prerequisites
- [VS Code](https://code.visualstudio.com/) with the [PlatformIO IDE Extension](https://platformio.org/install/ide?install=vscode) installed.
- USB data cable connected to the ESP32.
- A FAT32-formatted MicroSD card (optional, needed for BadUSB scripts and IR signal saving).

### 2. Clone / Open Project
Open the folder `FLIPPER_PORT_ESP32` in VS Code / PlatformIO:
```bash
cd FLIPPER_PORT_ESP32
```

### 3. Build & Flash
Use PlatformIO CLI or the VS Code PlatformIO sidebar:

```bash
# Build firmware
pio run

# Upload to ESP32
pio run --target upload

# Open Serial Monitor (115200 baud)
pio device monitor
```

---

## 🖥️ Screen Configuration

The firmware supports both **1.3" (SH1106)** and **0.96" / 1.54" (SSD1306)** I2C OLED displays.

To select your display, open [`src/HIZMOS_OLED_U8G2lib.ino`](src/HIZMOS_OLED_U8G2lib.ino) and uncomment the matching constructor:

```cpp
// For 1.3" SH1106 I2C OLED (Default):
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

// For 0.96" or 1.54" SSD1306 I2C OLED:
// U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);
```

---

## 🕹️ Navigation & Controls

| Button | Action |
|:---|:---|
| **UP (`GPIO 26`)** | Scroll up / Previous item / Move character up |
| **DOWN (`GPIO 33`)** | Scroll down / Next item / Move character down |
| **LEFT / BACK (`GPIO 25`)** | Back to previous menu / Cancel / Exit app |
| **RIGHT / SELECT (`GPIO 27`)** | Select item / Enter submenu / Confirm |
| **CENTER (`GPIO 32`)** | Execute action / Action trigger |

---

## ⚠️ Disclaimer & Safety

> [!IMPORTANT]
> This project is designed strictly for **educational, academic research, and authorized penetration testing purposes**. 
> - Always obtain prior written authorization before performing any wireless or network testing against equipment or networks you do not own.
> - Ensure your RF transmissions comply with your regional radio frequency regulations and ISM band limits (e.g., FCC, CE, ITU).
> - Enable **Safe Mode** in the settings menu when operating in sensitive environments to guarantee RF transmission silence.
> - The author assumes no liability for misuse, damages, or violations caused by operating this software.

---

## 👤 Credits

- **Project**: `FLIPPER_PORT_ESP32`
- **Created by**: **Ranjith**
- Built with open-source libraries: [U8g2](https://github.com/olikraus/u8g2), [RF24](https://github.com/nRF24/RF24), [IRremote](https://github.com/Arduino-IRremote/Arduino-IRremote), [Adafruit NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel), [ESP32 BLE Mouse](https://github.com/T-vK/ESP32-BLE-Mouse).

