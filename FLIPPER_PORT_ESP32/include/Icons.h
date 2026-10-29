#pragma once
#include <Arduino.h>
#include <TFT_eSPI.h>

extern TFT_eSPI tft;

enum IconType {
    ICON_HOME,
    ICON_FILE,
    ICON_FOLDER,
    ICON_WIFI,
    ICON_BLUETOOTH,
    ICON_TOOLS,
    ICON_FLASH,
    ICON_GAME,
    ICON_SETTINGS,
    ICON_SYSTEM,
    ICON_BACK,
    ICON_BATTERY,
    ICON_SD,
    ICON_TERMINAL,
    ICON_CHECK,
    ICON_CLOSE,
    ICON_SIGNAL
};

// Vector drawing routines (x, y are center or top-left depending on routine, size is outer bounding box)
void drawIcon(IconType type, int16_t x, int16_t y, int16_t size, uint16_t color);

void drawHomeIcon(int16_t x, int16_t y, int16_t size, uint16_t color);
void drawFileIcon(int16_t x, int16_t y, int16_t size, uint16_t color);
void drawFolderIcon(int16_t x, int16_t y, int16_t size, uint16_t color);
void drawWifiIcon(int16_t x, int16_t y, int16_t size, uint16_t color);
void drawBluetoothIcon(int16_t x, int16_t y, int16_t size, uint16_t color);
void drawToolsIcon(int16_t x, int16_t y, int16_t size, uint16_t color);
void drawFlashIcon(int16_t x, int16_t y, int16_t size, uint16_t color);
void drawGameIcon(int16_t x, int16_t y, int16_t size, uint16_t color);
void drawSettingsIcon(int16_t x, int16_t y, int16_t size, uint16_t color);
void drawSystemIcon(int16_t x, int16_t y, int16_t size, uint16_t color);
void drawBackIcon(int16_t x, int16_t y, int16_t size, uint16_t color);
void drawBatteryIcon(int16_t x, int16_t y, int16_t size, uint16_t color);
void drawSDIcon(int16_t x, int16_t y, int16_t size, uint16_t color);
void drawTerminalIcon(int16_t x, int16_t y, int16_t size, uint16_t color);
void drawCheckIcon(int16_t x, int16_t y, int16_t size, uint16_t color);
void drawCloseIcon(int16_t x, int16_t y, int16_t size, uint16_t color);
