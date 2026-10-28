#include <Arduino.h>
#if !defined(CONFIG_IDF_TARGET_ESP32S3) && !defined(CONFIG_IDF_TARGET_ESP32S2)
#include "USB.h"
USBClass USB;
#endif
