/*

# FLIPPER_PORT_ESP32 Development Journal
### Created by Ranjith
### Project: FLIPPER_PORT_ESP32

An open-source multi-tool and RF exploration device inspired by the Flipper Zero, ported to the ESP32 platform.

## Project Vision & Motivation
The goal of FLIPPER_PORT_ESP32 is to create a versatile, accessible multi-tool for security researchers, hardware developers, students, and hobbyists. By combining powerful ESP32 hardware with open-source modular expansion (CC1101, NRF24L01, IR, SD card, OLED, and BadUSB), FLIPPER_PORT_ESP32 delivers an affordable yet capable penetration testing and electronics toolkit.

## Features Overview

### 1. Sub-GHz (CC1101)
- Frequency analyzer and spectrum visualization
- Raw signal recording and playback
- Configurable modulation (ASK/OOK, 2-FSK, 4-FSK, GFSK, MSK)
- Sub-GHz transmitter and RF testing utilities

### 2. 2.4 GHz RF (nRF24L01)
- 2.4 GHz spectrum scanner
- Channel packet analyzer and counter
- Targeted channel RF analysis and diagnostics

### 3. Wi-Fi Tools
- Wi-Fi 802.11 b/g/n AP scanner with live RSSI
- Deauthentication testing tool
- Beacon frame spammer / SSID spoofer
- Probe request sniffer and packet analyzer
- Captive portal simulation

### 4. Bluetooth Low Energy (BLE)
- BLE device scanner with RSSI and manufacturer decoding
- BLE mouse emulation
- BLE beacon advertiser & spoofing experiments

### 5. Infrared (IR)
- IR receiver and signal decoder (NEC, Sony, RC5, RC6, Samsung, etc.)
- Raw signal capture and save to SD card
- Universal remotes for TVs, AC units, and multimedia equipment

### 6. BadUSB & HID
- USB keyboard emulation
- Automated HID script execution (DuckyScript syntax)
- Preset payloads and custom script launcher

### 7. Hardware & Expansion
- I2C bus address scanner
- GPIO pin testing and voltage status
- MicroSD card file manager (browser, rename, delete, format)

### 8. Mini Apps & Utilities
- Interactive Scientific/Basic Calculator
- Secure Password Generator
- Pomodoro Productivity Timer
- Safe Mode toggle (disables all RF transmissions)
- NeoPixel RGB Flashlight with customizable colors
- Retro Games: Snake, Space Shooter

## Hardware Architecture & Design
- Microcontroller: ESP32 Dual-Core Tensilica Xtensa 32-bit LX6 @ 240 MHz
- Display: 1.3" / 0.96" I2C OLED (SSD1306 / SH1106 via U8g2)
- Sub-GHz Transceiver: Texas Instruments CC1101 via dedicated SPI
- 2.4 GHz Transceiver: Nordic Semiconductor NRF24L01+ via SPI
- Storage: MicroSD Card reader via SPI
- Infrared: 940nm IR transmitter LED + VS1838B IR receiver sensor
- Indicators: WS2812B NeoPixel RGB LED + Onboard status LEDs
- Controls: 5-way D-pad navigation buttons (Up, Down, Left/Back, Right/Select, Center)

## Development Challenges & Solutions
1. **SPI Bus Multiplexing**: Co-locating multiple high-speed SPI devices (dual NRF24, CC1101, SD card) on shared/split buses required careful Chip Select (CS) isolation and timing configuration.
2. **Firmware Modularity**: Implementing diverse protocols (Wi-Fi promiscuous mode, BLE, Sub-GHz, IR) without memory collisions required modular partitioning and efficient memory management.
3. **Display Responsiveness**: High-framerate U8g2 rendering with non-blocking button state machines ensure a responsive UI across all menus.

*/
