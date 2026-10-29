#pragma once
#include <Arduino.h>

enum ScreenId {
    SCREEN_BOOT = 0,
    SCREEN_HOME,
    SCREEN_FILES,
    SCREEN_FILES_SUBFOLDER,
    SCREEN_WIFI,
    SCREEN_TOOLS,
    SCREEN_TOOLS_TERMINAL,
    SCREEN_TOOLS_GPIO,
    SCREEN_TOOLS_SERIAL,
    SCREEN_TOOLS_SYSINFO,
    SCREEN_FIRMWARE,
    SCREEN_GAMES,
    SCREEN_GAMES_DETAIL,
    SCREEN_SYSTEM,
    SCREEN_SETTINGS,
    SCREEN_SETTINGS_THEME,
    SCREEN_SETTINGS_BRIGHTNESS,
    SCREEN_SETTINGS_INTERFACE,
    SCREEN_DEMO_MODE,
    SCREEN_COUNT
};

class NavigationManager {
private:
    static const uint8_t MAX_STACK = 16;
    ScreenId historyStack[MAX_STACK];
    int8_t stackPointer;
    ScreenId currentScreen;
    bool redrawRequired;
    bool modalActive;

public:
    NavigationManager();

    void init();
    void goToScreen(ScreenId next);
    void goBack();
    void goHome();

    ScreenId getCurrentScreen() const { return currentScreen; }
    ScreenId getPreviousScreen() const;

    bool needsRedraw() const { return redrawRequired; }
    void triggerRedraw() { redrawRequired = true; }
    void clearRedraw() { redrawRequired = false; }

    bool isModalActive() const { return modalActive; }
    void setModalActive(bool active) { modalActive = active; }
};

extern NavigationManager nav;
