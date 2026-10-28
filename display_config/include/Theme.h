#pragma once
#include <Arduino.h>

// Theme Identifier
enum ThemeID {
    THEME_CYBER = 0,
    THEME_DARK,
    THEME_LIGHT,
    THEME_MINIMAL,
    THEME_COUNT
};

// Color Palette Definition (RGB565 format)
struct ThemeColors {
    uint16_t bg;
    uint16_t surface;
    uint16_t surfacePressed;
    uint16_t border;
    uint16_t borderGlow;
    uint16_t accent;
    uint16_t accentSecondary;
    uint16_t textPrimary;
    uint16_t textSecondary;
    uint16_t danger;
    uint16_t success;
    uint16_t barBg;
};

// Global active theme reference
extern ThemeColors currentTheme;
extern ThemeID activeThemeID;

// Theme Manager API
void initTheme();
void setTheme(ThemeID id);
const char* getThemeName(ThemeID id);
