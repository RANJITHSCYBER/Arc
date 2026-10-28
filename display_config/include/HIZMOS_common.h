#pragma once

#include <Arduino.h>
#include <stdint.h>
#include <vector>
#include <U8g2lib.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Adafruit_NeoPixel.h>
#include <SD.h>
#include <Update.h>
#include <WiFi.h>
#include <Wire.h>
#include <IRremote.h>
#include <BleMouse.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <esp_wifi.h>
#include "USB.h"
#include "USBHIDKeyboard.h"
#include "ELECHOUSE_CC1101_SRC_DRV.h"

// Display & Button Pin Definitions
#ifndef I2C_SDA
#define I2C_SDA 21
#define I2C_SCL 22

#define BUTTON_PIN_UP      26
#define BUTTON_PIN_DOWN    33
#define BUTTON_PIN_CENTER  32
#define BUTTON_PIN_LEFT    25
#define BUTTON_PIN_RIGHT   27

#define BTN_UP     BUTTON_PIN_UP
#define BTN_DOWN   BUTTON_PIN_DOWN
#define BTN_SELECT BUTTON_PIN_RIGHT
#define BTN_BACK   BUTTON_PIN_LEFT
#define BTN_LEFT   BUTTON_PIN_LEFT
#define BTN_RIGHT  BUTTON_PIN_RIGHT
#define BTN_CENTER BUTTON_PIN_CENTER

#define LED_PIN    2
#define LED_COUNT  1

#define irsenderpin  4
#define irrecivepin  35
#define SD_DETECT_PIN 0

// nRF24 Pins
#define NRF_SCK   18
#define NRF_MISO  19
#define NRF_MOSI  23
#define CE1_PIN   17
#define CSN1_PIN  5
#define CE2_PIN   17
#define CSN2_PIN  5

// CC1101 Pins
#define cc1101_SCK   14
#define cc1101_MISO  12
#define cc1101_MOSI  13
#define CC1101_CS    15
#define CC1101_GDO0  16
#define CC1101_GDO2  34
#define CC1101_2_CS    15
#define CC1101_2_GDO0  16
#define CC1101_2_GDO2  34

// SD Card Pins
#define SD_SCK    14
#define SD_MISO   12
#define SD_MOSI   13
#define SD_CS     15

#define JAM_DURATION 500
#endif

#ifndef BLESCANNER_DEVICE_DEFINED
#define BLESCANNER_DEVICE_DEFINED
struct blescanner_Device {
  String name;
  String address;
  int rssi;
  String manufacturer;
  String deviceType;
};
#endif

// Global Hardware Instances & Variables
extern U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2;
extern Adafruit_NeoPixel pixel;
extern RF24 radio1;
extern RF24 radio2;
extern SPIClass RADIO_SPI;
extern SPIClass SD_SPI;
extern BleMouse mouse_ble;
extern USBHIDKeyboard Keyboard;
extern IRrecv irrecv;
extern IRsend irsend;
extern decode_results results;
extern BLEScan* blescanner_pBLEScan;
extern std::vector<blescanner_Device> blescanner_devices;
extern int blescanner_selectedIndex;

extern int batteryPercent;
extern bool sdOK;
extern bool inhizmosmenu;
extern int autoImageIndex;
extern int manualImageIndex;
extern bool autoMode;

extern int wifi_selectedIndex;
extern int wifi_networkCount;
extern bool wifi_showInfo;

// Function Prototypes
void setColor(uint8_t r, uint8_t g, uint8_t b);
void runLoop(void (*func)());
bool isButtonPressed(int btn);
bool selectPressed();
void displayImage(const uint8_t* image);
void displaymainanim(const uint8_t* image, int batteryPercent, bool sdOK);
void handleButtons();
void autoModeCheck();
void handlemainmenu();
void lazyInitCC1101(uint8_t which);
void checksysdevices();
void drawstartinfo();
void activateSD();
void deactivateSD();
void deactivateNRF1();
void deactivateNRF2();
void loading();
void drawnosdcard();
String wifi_encryptionType(wifi_auth_mode_t encryption);
void claculaterloop();
void pomdorotimerloop();
void updateTimer();
void wavecreator();
void snakeSetup();
void snakeLoop();
void readSDfiles();
void drawMenu();
void flasherloop();
void spacegame();
void scanningwifi();
void updateSnifferGraph();
void setupSnifferGraph();
void blescanner_scan();
void blescanner_drawMenu();
void blescanner();
void blemouse();
void drawHistogram();
void SPECTRUMANALYZER();
void JAMMINGCC1101();
void drawBruteForce();
void drawSettingsMenu();
void nrfscanner();
void nrfjammer();
void jammspecchannel();
void i2cscanner();
void recvIR();
void hidkeyboard();
void hidscriptmenu();
void sdformater();
void showsdinfo();
void restartesp();
void about();
void handlesuniversalremotemenu();
void runTVRemote();
void runACRemote();
void runProjectorRemote();
void runCameraRemote();
void listIRFiles();
void runBeaconSpammer();
void runCaptivePortal();
void runDeauthDetector();
void runPasswordGenerator();
void hidInit();
void handlenfcmenu();
void runNFCReadTag();
void runNFCWriteData();
void runNFCSavedTags();
void runNFCEmulateTag();
void runNFCP2P();

