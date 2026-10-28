#include "HIZMOS_common.h"

#ifndef LED_BUILTIN
#define LED_BUILTIN 2
#endif

// Feedback animation when transmitting IR
void showTransmitFeedback(const char* name, const char* detail) {
  digitalWrite(LED_BUILTIN, HIGH);
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_6x12_tf);
  u8g2.drawFrame(0, 0, 128, 64);
  u8g2.drawStr(12, 14, ">>> IR SENDING <<<");
  u8g2.setFont(u8g2_font_7x14_tf);
  u8g2.drawStr(10, 34, name);
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.drawStr(10, 52, detail);
  u8g2.sendBuffer();
  delay(180);
  digitalWrite(LED_BUILTIN, LOW);
}

// ============================================================
// UNIVERSAL REMOTES MAIN MENU
// ============================================================
void handlesuniversalremotemenu() {
  const char* menuItems[] = {"TV REMOTE", "AC REMOTE", "PROJECTOR", "CAMERAS"};
  const int menuLength = sizeof(menuItems) / sizeof(menuItems[0]);
  const int visibleItems = 3;

  static int selectedItem = 0;
  static int scrollOffset = 0;
  static unsigned long lastInputTime = 0;

  if (millis() - lastInputTime > 150) {
    if (digitalRead(BTN_UP) == LOW) {
      selectedItem--;
      if (selectedItem < 0) selectedItem = menuLength - 1;
      scrollOffset = constrain(selectedItem - visibleItems + 1, 0, menuLength - visibleItems);
      lastInputTime = millis();
    }

    if (digitalRead(BTN_DOWN) == LOW) {
      selectedItem++;
      if (selectedItem >= menuLength) selectedItem = 0;
      scrollOffset = constrain(selectedItem - visibleItems + 1, 0, menuLength - visibleItems);
      lastInputTime = millis();
    }

    if (digitalRead(BTN_SELECT) == LOW) {
      delay(200);
      while (digitalRead(BTN_SELECT) == LOW);
      switch (selectedItem) {
        case 0: runTVRemote(); break;
        case 1: runACRemote(); break;
        case 2: runProjectorRemote(); break;
        case 3: runCameraRemote(); break;
      }
      lastInputTime = millis();
    }
  }

  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_7x14_tf);

  for (int i = 0; i < visibleItems; i++) {
    int menuIndex = i + scrollOffset;
    if (menuIndex >= menuLength) break;

    int y = i * 20 + 16;
    if (menuIndex == selectedItem) {
      u8g2.drawRBox(4, y - 12, 120, 16, 4);
      u8g2.setDrawColor(0);
      u8g2.drawStr(10, y, menuItems[menuIndex]);
      u8g2.setDrawColor(1);
    } else {
      u8g2.drawStr(10, y, menuItems[menuIndex]);
    }
  }

  int barX = 124;
  int spacing = 64 / menuLength;
  for (int i = 0; i < menuLength; i++) {
    int dotY = i * spacing + spacing / 2;
    if (i == selectedItem) {
      u8g2.drawBox(barX, dotY - 3, 3, 6);
    } else {
      u8g2.drawPixel(barX + 1, dotY);
    }
  }

  u8g2.sendBuffer();
}

// ============================================================
// 1. TV REMOTE (Single & Universal Brute Force)
// ============================================================
void sendSingleTVCode(uint8_t protocol, uint16_t address, uint32_t command) {
  if (protocol == 0) {
    IrSender.sendSamsung(address, command, 1);
  } else if (protocol == 1) {
    IrSender.sendNEC(address, command, 1);
  } else if (protocol == 2) {
    IrSender.sendSony(address, command, 2, 12);
  } else if (protocol == 3) {
    IrSender.sendRC5(address, command, 1);
  } else if (protocol == 4) {
    IrSender.sendPanasonic(address, command, 1);
  }
}

void runUniversalTVPowerCycle() {
  const char* brands[] = {
    "Samsung", "LG TV", "Sony 12b", "Philips RC5", "Panasonic",
    "Toshiba", "Sharp", "Vizio", "Hisense", "TCL", "RCA", "Hitachi"
  };
  const uint8_t protos[] = {0, 1, 2, 3, 4, 1, 1, 1, 1, 1, 1, 1};
  const uint16_t addrs[] = {0x0707, 0x0004, 0x0001, 0x0000, 0x4004, 0x0002, 0x0001, 0x0008, 0xDF00, 0x0040, 0x0006, 0x0050};
  const uint32_t cmds[]  = {0x02, 0x08, 0x15, 0x0C, 0x0100BCBD, 0x02, 0x11, 0x02, 0x02, 0x12, 0x08, 0x0C};
  const int totalCodes = sizeof(brands) / sizeof(brands[0]);

  for (int i = 0; i < totalCodes; i++) {
    if (digitalRead(BTN_BACK) == LOW || digitalRead(BUTTON_PIN_CENTER) == LOW) {
      delay(200);
      break;
    }

    int progress = ((i + 1) * 100) / totalCodes;
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_7x14_tf);
    u8g2.drawStr(10, 16, "UNIVERSAL OFF");
    u8g2.drawFrame(10, 24, 108, 12);
    u8g2.drawBox(12, 26, (104 * progress) / 100, 8);
    u8g2.setFont(u8g2_font_6x10_tf);
    char buf[32];
    snprintf(buf, sizeof(buf), "%s (%d%%)", brands[i], progress);
    u8g2.drawStr(10, 50, buf);
    u8g2.drawStr(10, 62, "CENTER to cancel");
    u8g2.sendBuffer();

    digitalWrite(LED_BUILTIN, HIGH);
    sendSingleTVCode(protos[i], addrs[i], cmds[i]);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(150);
  }
}

void runTVRemote() {
  const char* tvItems[] = {
    "ALL TVs (UNIVERSAL)",
    "POWER: Samsung",
    "POWER: LG / NEC",
    "POWER: Sony",
    "POWER: Philips RC5",
    "VOL + (ALL)",
    "VOL - (ALL)",
    "MUTE (ALL)",
    "CH + (ALL)",
    "CH - (ALL)",
    "INPUT / SOURCE"
  };
  const int totalItems = sizeof(tvItems) / sizeof(tvItems[0]);
  const int visible = 4;
  int selected = 0;
  int offset = 0;

  while (true) {
    if (digitalRead(BTN_BACK) == LOW || digitalRead(BUTTON_PIN_CENTER) == LOW) {
      delay(200);
      while (digitalRead(BTN_BACK) == LOW || digitalRead(BUTTON_PIN_CENTER) == LOW);
      break;
    }

    if (digitalRead(BTN_UP) == LOW) {
      selected--;
      if (selected < 0) selected = totalItems - 1;
      offset = constrain(selected - visible + 1, 0, totalItems - visible);
      delay(150);
    }
    if (digitalRead(BTN_DOWN) == LOW) {
      selected++;
      if (selected >= totalItems) selected = 0;
      offset = constrain(selected - visible + 1, 0, totalItems - visible);
      delay(150);
    }

    if (digitalRead(BTN_SELECT) == LOW) {
      delay(200);
      while (digitalRead(BTN_SELECT) == LOW);

      switch (selected) {
        case 0:
          runUniversalTVPowerCycle();
          break;
        case 1:
          showTransmitFeedback("SAMSUNG POWER", "0x0707:0x02");
          IrSender.sendSamsung(0x0707, 0x02, 1);
          break;
        case 2:
          showTransmitFeedback("LG / NEC POWER", "0x0004:0x08");
          IrSender.sendNEC(0x04, 0x08, 1);
          break;
        case 3:
          showTransmitFeedback("SONY POWER", "12-bit 0x01:0x15");
          IrSender.sendSony(0x01, 0x15, 2, 12);
          break;
        case 4:
          showTransmitFeedback("PHILIPS POWER", "RC5 0x00:0x0C");
          IrSender.sendRC5(0x00, 0x0C, 1);
          break;
        case 5:
          showTransmitFeedback("VOLUME +", "Samsung+LG+Sony");
          IrSender.sendSamsung(0x0707, 0x07, 1); delay(40);
          IrSender.sendNEC(0x04, 0x02, 1); delay(40);
          IrSender.sendSony(0x01, 0x12, 2, 12);
          break;
        case 6:
          showTransmitFeedback("VOLUME -", "Samsung+LG+Sony");
          IrSender.sendSamsung(0x0707, 0x0B, 1); delay(40);
          IrSender.sendNEC(0x04, 0x03, 1); delay(40);
          IrSender.sendSony(0x01, 0x13, 2, 12);
          break;
        case 7:
          showTransmitFeedback("MUTE", "Samsung+LG+Sony");
          IrSender.sendSamsung(0x0707, 0x0F, 1); delay(40);
          IrSender.sendNEC(0x04, 0x09, 1); delay(40);
          IrSender.sendSony(0x01, 0x14, 2, 12);
          break;
        case 8:
          showTransmitFeedback("CHANNEL +", "Samsung+LG+Sony");
          IrSender.sendSamsung(0x0707, 0x12, 1); delay(40);
          IrSender.sendNEC(0x04, 0x00, 1); delay(40);
          IrSender.sendSony(0x01, 0x10, 2, 12);
          break;
        case 9:
          showTransmitFeedback("CHANNEL -", "Samsung+LG+Sony");
          IrSender.sendSamsung(0x0707, 0x10, 1); delay(40);
          IrSender.sendNEC(0x04, 0x01, 1); delay(40);
          IrSender.sendSony(0x01, 0x11, 2, 12);
          break;
        case 10:
          showTransmitFeedback("SOURCE / INPUT", "Samsung+LG+Sony");
          IrSender.sendSamsung(0x0707, 0x01, 1); delay(40);
          IrSender.sendNEC(0x04, 0x0B, 1); delay(40);
          IrSender.sendSony(0x01, 0x25, 2, 12);
          break;
      }
    }

    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_6x10_tf);
    u8g2.drawStr(0, 8, "TV REMOTE [SELECT=SEND]");

    for (int i = 0; i < visible; i++) {
      int idx = i + offset;
      if (idx >= totalItems) break;
      int y = 20 + i * 13;

      if (idx == selected) {
        u8g2.drawRBox(0, y - 9, 124, 12, 2);
        u8g2.setDrawColor(0);
        u8g2.drawStr(4, y, tvItems[idx]);
        u8g2.setDrawColor(1);
      } else {
        u8g2.drawStr(4, y, tvItems[idx]);
      }
    }

    u8g2.sendBuffer();
    delay(20);
  }
}

// ============================================================
// 2. AC REMOTE (Air Conditioner Controller)
// ============================================================
void runACRemote() {
  static int acTemp = 24;
  static int acMode = 0; // 0: COOL, 1: HEAT, 2: FAN, 3: AUTO
  static int acFan = 0;  // 0: AUTO, 1: LOW, 2: MED, 3: HIGH
  static bool acPower = false;
  const char* modeNames[] = {"COOL", "HEAT", "FAN", "AUTO"};
  const char* fanNames[] = {"AUTO", "LOW", "MED", "HIGH"};

  const char* acItems[] = {
    "POWER TOGGLE",
    "TEMP +1 C",
    "TEMP -1 C",
    "MODE TOGGLE",
    "FAN TOGGLE",
    "TRANSMIT STATE",
    "UNIVERSAL AC OFF"
  };
  const int totalItems = sizeof(acItems) / sizeof(acItems[0]);
  const int visible = 4;
  int selected = 0;
  int offset = 0;

  while (true) {
    if (digitalRead(BTN_BACK) == LOW || digitalRead(BUTTON_PIN_CENTER) == LOW) {
      delay(200);
      while (digitalRead(BTN_BACK) == LOW || digitalRead(BUTTON_PIN_CENTER) == LOW);
      break;
    }

    if (digitalRead(BTN_UP) == LOW) {
      selected--;
      if (selected < 0) selected = totalItems - 1;
      offset = constrain(selected - visible + 1, 0, totalItems - visible);
      delay(150);
    }
    if (digitalRead(BTN_DOWN) == LOW) {
      selected++;
      if (selected >= totalItems) selected = 0;
      offset = constrain(selected - visible + 1, 0, totalItems - visible);
      delay(150);
    }

    if (digitalRead(BTN_SELECT) == LOW) {
      delay(200);
      while (digitalRead(BTN_SELECT) == LOW);

      switch (selected) {
        case 0:
          acPower = !acPower;
          showTransmitFeedback(acPower ? "AC POWER ON" : "AC POWER OFF", "LG / Samsung AC");
          IrSender.sendLG(0x88, acPower ? 0x00 : 0xC0, 1);
          break;
        case 1:
          if (acTemp < 30) acTemp++;
          showTransmitFeedback("TEMP UP", (String(acTemp) + " C").c_str());
          IrSender.sendLG(0x88, 0x08 | (acTemp - 15), 1);
          break;
        case 2:
          if (acTemp > 16) acTemp--;
          showTransmitFeedback("TEMP DOWN", (String(acTemp) + " C").c_str());
          IrSender.sendLG(0x88, 0x08 | (acTemp - 15), 1);
          break;
        case 3:
          acMode = (acMode + 1) % 4;
          showTransmitFeedback("MODE CHANGE", modeNames[acMode]);
          IrSender.sendLG(0x88, 0x08, 1);
          break;
        case 4:
          acFan = (acFan + 1) % 4;
          showTransmitFeedback("FAN SPEED", fanNames[acFan]);
          IrSender.sendLG(0x88, 0x04, 1);
          break;
        case 5:
          showTransmitFeedback("SENDING AC STATE", (String(modeNames[acMode]) + " " + String(acTemp) + "C").c_str());
          IrSender.sendLG(0x88, 0x08 | (acTemp - 15), 1);
          break;
        case 6:
          showTransmitFeedback("UNIVERSAL AC OFF", "LG+Samsung+Gree");
          IrSender.sendLG(0x88, 0xC0, 1); delay(100);
          IrSender.sendSamsung(0x02, 0xC0, 1); delay(100);
          IrSender.sendNEC(0x00, 0x08, 1);
          break;
      }
    }

    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_6x10_tf);
    char statusBuf[32];
    snprintf(statusBuf, sizeof(statusBuf), "AC:%s %dC %s", acPower ? "ON" : "OFF", acTemp, modeNames[acMode]);
    u8g2.drawStr(0, 8, statusBuf);

    for (int i = 0; i < visible; i++) {
      int idx = i + offset;
      if (idx >= totalItems) break;
      int y = 20 + i * 13;

      if (idx == selected) {
        u8g2.drawRBox(0, y - 9, 124, 12, 2);
        u8g2.setDrawColor(0);
        u8g2.drawStr(4, y, acItems[idx]);
        u8g2.setDrawColor(1);
      } else {
        u8g2.drawStr(4, y, acItems[idx]);
      }
    }

    u8g2.sendBuffer();
    delay(20);
  }
}

// ============================================================
// 3. PROJECTOR REMOTE
// ============================================================
void runProjectorRemote() {
  const char* projItems[] = {
    "POWER ON (Epson/BenQ)",
    "POWER OFF (Double)",
    "SOURCE / INPUT",
    "MENU",
    "KEYSTONE +",
    "KEYSTONE -",
    "BLANK SCREEN",
    "UNIVERSAL OFF"
  };
  const int totalItems = sizeof(projItems) / sizeof(projItems[0]);
  const int visible = 4;
  int selected = 0;
  int offset = 0;

  while (true) {
    if (digitalRead(BTN_BACK) == LOW || digitalRead(BUTTON_PIN_CENTER) == LOW) {
      delay(200);
      while (digitalRead(BTN_BACK) == LOW || digitalRead(BUTTON_PIN_CENTER) == LOW);
      break;
    }

    if (digitalRead(BTN_UP) == LOW) {
      selected--;
      if (selected < 0) selected = totalItems - 1;
      offset = constrain(selected - visible + 1, 0, totalItems - visible);
      delay(150);
    }
    if (digitalRead(BTN_DOWN) == LOW) {
      selected++;
      if (selected >= totalItems) selected = 0;
      offset = constrain(selected - visible + 1, 0, totalItems - visible);
      delay(150);
    }

    if (digitalRead(BTN_SELECT) == LOW) {
      delay(200);
      while (digitalRead(BTN_SELECT) == LOW);

      switch (selected) {
        case 0:
          showTransmitFeedback("PROJECTOR ON", "Epson/BenQ/Optoma");
          IrSender.sendNEC(0x41, 0x01, 1); delay(50);
          IrSender.sendNEC(0x00, 0x0C, 1); delay(50);
          IrSender.sendNEC(0x32, 0x02, 1);
          break;
        case 1:
          showTransmitFeedback("PROJECTOR OFF x1", "Sending confirmation");
          IrSender.sendNEC(0x41, 0x02, 1); delay(50);
          IrSender.sendNEC(0x00, 0x0C, 1);
          delay(400);
          showTransmitFeedback("PROJECTOR OFF x2", "Confirmed Power Off");
          IrSender.sendNEC(0x41, 0x02, 1); delay(50);
          IrSender.sendNEC(0x00, 0x0C, 1);
          break;
        case 2:
          showTransmitFeedback("SOURCE / INPUT", "Cycle HDMI/VGA");
          IrSender.sendNEC(0x41, 0x45, 1); delay(50);
          IrSender.sendNEC(0x00, 0x05, 1);
          break;
        case 3:
          showTransmitFeedback("PROJECTOR MENU", "NEC 0x41:0x03");
          IrSender.sendNEC(0x41, 0x03, 1);
          break;
        case 4:
          showTransmitFeedback("KEYSTONE +", "NEC 0x41:0x10");
          IrSender.sendNEC(0x41, 0x10, 1);
          break;
        case 5:
          showTransmitFeedback("KEYSTONE -", "NEC 0x41:0x11");
          IrSender.sendNEC(0x41, 0x11, 1);
          break;
        case 6:
          showTransmitFeedback("BLANK SCREEN", "Mute Display");
          IrSender.sendNEC(0x41, 0x0A, 1);
          break;
        case 7:
          showTransmitFeedback("UNIVERSAL PROJ OFF", "Epson+BenQ+Optoma");
          IrSender.sendNEC(0x41, 0x02, 1); delay(100);
          IrSender.sendNEC(0x00, 0x0C, 1); delay(100);
          IrSender.sendNEC(0x32, 0x02, 1);
          break;
      }
    }

    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_6x10_tf);
    u8g2.drawStr(0, 8, "PROJECTOR REMOTE");

    for (int i = 0; i < visible; i++) {
      int idx = i + offset;
      if (idx >= totalItems) break;
      int y = 20 + i * 13;

      if (idx == selected) {
        u8g2.drawRBox(0, y - 9, 124, 12, 2);
        u8g2.setDrawColor(0);
        u8g2.drawStr(4, y, projItems[idx]);
        u8g2.setDrawColor(1);
      } else {
        u8g2.drawStr(4, y, projItems[idx]);
      }
    }

    u8g2.sendBuffer();
    delay(20);
  }
}

// ============================================================
// 4. CAMERA REMOTE (DSLR & Mirrorless Shutter Trigger)
// ============================================================
void runCameraRemote() {
  const char* camItems[] = {
    "ALL (MULTI-TRIGGER)",
    "CANON (INSTANT)",
    "CANON (2s DELAY)",
    "NIKON (INSTANT)",
    "SONY (INSTANT)",
    "PENTAX (INSTANT)"
  };
  const int totalItems = sizeof(camItems) / sizeof(camItems[0]);
  const int visible = 4;
  int selected = 0;
  int offset = 0;

  const uint16_t canonInstant[] = { 488, 7324, 488 };
  const uint16_t canon2s[]      = { 488, 5360, 488 };
  const uint16_t nikonShutter[] = { 2000, 27830, 390, 1580, 410, 3580, 400 };
  const uint16_t pentaxShutter[]= { 13000, 3000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000 };

  while (true) {
    if (digitalRead(BTN_BACK) == LOW || digitalRead(BUTTON_PIN_CENTER) == LOW) {
      delay(200);
      while (digitalRead(BTN_BACK) == LOW || digitalRead(BUTTON_PIN_CENTER) == LOW);
      break;
    }

    if (digitalRead(BTN_UP) == LOW) {
      selected--;
      if (selected < 0) selected = totalItems - 1;
      offset = constrain(selected - visible + 1, 0, totalItems - visible);
      delay(150);
    }
    if (digitalRead(BTN_DOWN) == LOW) {
      selected++;
      if (selected >= totalItems) selected = 0;
      offset = constrain(selected - visible + 1, 0, totalItems - visible);
      delay(150);
    }

    if (digitalRead(BTN_SELECT) == LOW) {
      delay(200);
      while (digitalRead(BTN_SELECT) == LOW);

      switch (selected) {
        case 0:
          showTransmitFeedback("MULTI-TRIGGER!", "Canon+Nikon+Sony");
          IrSender.sendRaw(canonInstant, sizeof(canonInstant) / sizeof(canonInstant[0]), 33);
          delay(80);
          IrSender.sendRaw(nikonShutter, sizeof(nikonShutter) / sizeof(nikonShutter[0]), 38);
          delay(80);
          IrSender.sendSony(0x1E3A, 0x2D, 2, 20);
          delay(80);
          IrSender.sendRaw(pentaxShutter, sizeof(pentaxShutter) / sizeof(pentaxShutter[0]), 38);
          break;
        case 1:
          showTransmitFeedback("CANON SHUTTER", "Instant 33kHz");
          IrSender.sendRaw(canonInstant, sizeof(canonInstant) / sizeof(canonInstant[0]), 33);
          break;
        case 2:
          showTransmitFeedback("CANON 2s TIMER", "2-Sec Delay 33kHz");
          IrSender.sendRaw(canon2s, sizeof(canon2s) / sizeof(canon2s[0]), 33);
          break;
        case 3:
          showTransmitFeedback("NIKON SHUTTER", "Instant 38kHz");
          IrSender.sendRaw(nikonShutter, sizeof(nikonShutter) / sizeof(nikonShutter[0]), 38);
          break;
        case 4:
          showTransmitFeedback("SONY SHUTTER", "SIRCS 20-bit 0x1E3A");
          IrSender.sendSony(0x1E3A, 0x2D, 2, 20);
          break;
        case 5:
          showTransmitFeedback("PENTAX SHUTTER", "Instant 38kHz");
          IrSender.sendRaw(pentaxShutter, sizeof(pentaxShutter) / sizeof(pentaxShutter[0]), 38);
          break;
      }
    }

    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_6x10_tf);
    u8g2.drawStr(0, 8, "CAMERA REMOTE (SHUTTER)");

    for (int i = 0; i < visible; i++) {
      int idx = i + offset;
      if (idx >= totalItems) break;
      int y = 20 + i * 13;

      if (idx == selected) {
        u8g2.drawRBox(0, y - 9, 124, 12, 2);
        u8g2.setDrawColor(0);
        u8g2.drawStr(4, y, camItems[idx]);
        u8g2.setDrawColor(1);
      } else {
        u8g2.drawStr(4, y, camItems[idx]);
      }
    }

    u8g2.sendBuffer();
    delay(20);
  }
}
