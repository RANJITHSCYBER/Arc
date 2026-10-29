#pragma once
#include <Arduino.h>
#include <TFT_eSPI.h>

extern TFT_eSPI tft;

class TouchManager {
private:
    int16_t touchX;
    int16_t touchY;
    int16_t lastReleaseX;
    int16_t lastReleaseY;
    bool pressed;
    bool prevPressed;
    bool justPressedFlag;
    bool justReleasedFlag;
    unsigned long pressStartTime;
    unsigned long lastTouchTime;

public:
    TouchManager();

    void init();
    void update();

    bool isPressed() const { return pressed; }
    bool justPressed() const { return justPressedFlag; }
    bool justReleased() const { return justReleasedFlag; }

    int16_t getX() const { return touchX; }
    int16_t getY() const { return touchY; }
    int16_t getReleaseX() const { return lastReleaseX; }
    int16_t getReleaseY() const { return lastReleaseY; }

    bool isInside(int16_t x, int16_t y, int16_t rx, int16_t ry, int16_t rw, int16_t rh) const;
    bool wasClicked(int16_t rx, int16_t ry, int16_t rw, int16_t rh) const;
    bool isBeingPressed(int16_t rx, int16_t ry, int16_t rw, int16_t rh) const;
};

extern TouchManager touchMgr;
