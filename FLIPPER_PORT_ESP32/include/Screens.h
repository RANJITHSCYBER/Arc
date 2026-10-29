#pragma once
#include <Arduino.h>
#include <TFT_eSPI.h>
#include "Navigation.h"
#include "UIElements.h"
#include "TouchManager.h"
#include "Theme.h"
#include "Config.h"

extern TFT_eSPI tft;

class Screens {
public:
    static void init();

    // Render methods for each screen
    static void renderBoot();
    static void renderHome();
    static void renderFiles();
    static void renderFilesSubfolder();
    static void renderWifi();
    static void renderTools();
    static void renderToolsTerminal();
    static void renderToolsGPIO();
    static void renderToolsSerial();
    static void renderToolsSysInfo();
    static void renderFirmware();
    static void renderGames();
    static void renderGamesDetail();
    static void renderSystem();
    static void renderSettings();
    static void renderSettingsTheme();
    static void renderSettingsBrightness();
    static void renderSettingsInterface();
    static void renderDemoMode();

    // Touch event handlers for each screen
    static void handleTouchBoot();
    static void handleTouchHome();
    static void handleTouchFiles();
    static void handleTouchFilesSubfolder();
    static void handleTouchWifi();
    static void handleTouchTools();
    static void handleTouchToolsTerminal();
    static void handleTouchToolsGPIO();
    static void handleTouchToolsSerial();
    static void handleTouchToolsSysInfo();
    static void handleTouchFirmware();
    static void handleTouchGames();
    static void handleTouchGamesDetail();
    static void handleTouchSystem();
    static void handleTouchSettings();
    static void handleTouchSettingsTheme();
    static void handleTouchSettingsBrightness();
    static void handleTouchSettingsInterface();
    static void handleTouchDemoMode();

    // Active screen dispatcher
    static void renderCurrent();
    static void handleTouch();

    // Dynamic animation & periodic background updates
    static void update();
};
