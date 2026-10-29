#pragma once
#include <Arduino.h>
#include <TFT_eSPI.h>
#include "Icons.h"
#include "Theme.h"
#include "Config.h"

extern TFT_eSPI tft;

struct Rect {
    int16_t x;
    int16_t y;
    int16_t w;
    int16_t h;
};

class UIElements {
public:
    static void drawStatusBar(const char* title, bool wifiConnected = true, bool sdPresent = true, const char* timeStr = "21:45");
    static void drawBottomBar(bool showBack = true, bool showHome = true, bool showSettings = true);

    static void drawCard(int16_t x, int16_t y, int16_t w, int16_t h, const char* label, IconType icon, bool pressed);
    static void drawButton(int16_t x, int16_t y, int16_t w, int16_t h, const char* label, uint16_t color, bool pressed);
    static void drawListItem(int16_t x, int16_t y, int16_t w, int16_t h, const char* title, const char* subtitle, IconType icon, bool selected, bool pressed);
    static void drawSlider(int16_t x, int16_t y, int16_t w, int16_t h, int16_t val, int16_t minVal, int16_t maxVal, const char* label);
    static void drawProgressBar(int16_t x, int16_t y, int16_t w, int16_t h, int16_t percent, uint16_t color);

    static void drawModal(const char* title, const char* message, const char* btnLeft, const char* btnRight, uint16_t accentCol);
    static void dismissModal();

    // Standard Hit-Test Rectangles for Global Bars
    static Rect getBackBtnRect();
    static Rect getHomeBtnRect();
    static Rect getSettingsBtnRect();
    static Rect getModalLeftBtnRect();
    static Rect getModalRightBtnRect();
};
