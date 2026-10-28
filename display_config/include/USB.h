#pragma once
#include <Arduino.h>

#if !defined(CONFIG_IDF_TARGET_ESP32S3) && !defined(CONFIG_IDF_TARGET_ESP32S2)
// Compatibility stub for classic ESP32 (no native USB OTG)
class USBClass {
public:
    void begin() {}
};

extern USBClass USB;
#endif
