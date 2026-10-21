void showMainScreen() {
  cls();
  screen = 0;
  if (TricasterName == "") {
    Serial.println("tricaster name is blank, set one in webconfig");
    M5.Display.fillScreen(YELLOW);
    M5.Display.setTextColor(BLACK, YELLOW);
    M5.Display.setTextSize(2);
    M5.Display.setCursor(0, 35);
    M5.Display.println(" Tricaster name is");
    M5.Display.println(" blank. Set one in");
    M5.Display.println(" webconfig at:");
    M5.Display.print(" ");
    M5.Display.println(WiFi.localIP());
  } else {
    switch (currentState) {
      case 0:
        showTallySafe();
        break;
      case 1:
        showTallyLive();
        break;
      case 2:
        if (!justLive) {
          showTallyPreview();
          break;
        } else {
          showTallySafe();
          break;
        }
      default:
        showTallySafe();
        break;
    }
  }
}

void showNetworkScreen() {
  cls();
  screen = 1;
  screenRotation = 3;
  M5.Display.setRotation(3); 
  M5.Display.setCursor(10,10);
  M5.Display.setTextSize(2);
  M5.Display.print("SSID:");
  M5.Display.println(WiFi.SSID());
  M5.Display.println();
  M5.Display.println(" IP Address:");
  M5.Display.print(" ");
  M5.Display.println(WiFi.localIP());
  M5.Display.println();
  M5.Display.println(" Wifi Strength:");
  M5.Display.print(" ");
  M5.Display.print(rssi);
  M5.Display.print(" dBm ");
  M5.Display.println((rssiLabel()));
}

void showTallyScreen() {
  cls();
  screen = 2;
  screenRotation = 3;
  M5.Display.setRotation(3); 
  M5.Display.setTextSize(8);
  if (tallyLength == 1) {
    M5.Display.setCursor(100,25);
  } else {
    M5.Display.setCursor(80,25);
  }
  M5.Display.println(tallyNumber);
  M5.Display.setTextSize(2);
  M5.Display.setCursor(10, 90);
  M5.Display.println("Hold to");
  M5.Display.setCursor(10, 115);
  M5.Display.println("reset");
  M5.Display.drawLine(125, 100, 125, 120, WHITE);
  M5.Display.drawTriangle(125, 130, 115, 120, 135, 120, WHITE);
  M5.Display.fillTriangle(125, 130, 115, 120, 135, 120, WHITE);
}

void showBrightnessScreen() {
  cls();
  screen = 3;
  screenRotation = 3;
  M5.Display.setRotation(3); 
  M5.Display.setTextSize(2);
  M5.Display.fillScreen(WHITE);
  M5.Display.setTextColor(BLACK, WHITE);
  M5.Display.setCursor(70, 30);
  M5.Display.println("Brightness");
  M5.Display.setTextSize(3);
  M5.Display.setCursor(105, 65);
  M5.Display.print(brightness);
  M5.Display.println("%");
  M5.Display.drawLine(125, 100, 125, 120, BLACK);
  M5.Display.drawTriangle(125, 130, 115, 120, 135, 120, BLACK);
  M5.Display.fillTriangle(125, 130, 115, 120, 135, 120, BLACK);
}

void showModeScreen() {
  cls();
  screen = 4;
  screenRotation = 3;
  M5.Display.setRotation(3); 
  M5.Display.setTextSize(2);
  M5.Display.fillScreen(WHITE);
  M5.Display.setTextColor(BLACK, WHITE);
  M5.Display.setCursor(35, 30);
  M5.Display.println("Word or number?");
  if (tallyMode == 1) {
    M5.Display.setCursor(50, 65);
    M5.Display.println("Tally Number");
  } else if (tallyMode == 0) {
    if (justLive == 1) {
      M5.Display.setCursor(65, 65);
      M5.Display.println("LIVE-SAFE");
    } else if (justLive == 0) {
      M5.Display.setCursor(45, 65);
      M5.Display.println("LIVE-PRE-SAFE");
    }
  }
  M5.Display.drawLine(125, 100, 125, 120, BLACK);
  M5.Display.drawTriangle(125, 130, 115, 120, 135, 120, BLACK);
  M5.Display.fillTriangle(125, 130, 115, 120, 135, 120, BLACK);
}

void showJustliveScreen() {
  cls();
  screen = 5;
  screenRotation = 3;
  M5.Display.setRotation(3); 
  M5.Display.setTextSize(2);
  M5.Display.fillScreen(WHITE);
  M5.Display.setTextColor(BLACK, WHITE);
  M5.Display.setCursor(65, 30);
  M5.Display.println("Just live?");
  if (justLive == 1) {
    M5.Display.setCursor(65, 65);
    M5.Display.println("LIVE-SAFE");
  } else if (justLive == 0) {
    M5.Display.setCursor(45, 65);
    M5.Display.println("LIVE-PRE-SAFE");
  }
  M5.Display.drawLine(125, 100, 125, 120, BLACK);
  M5.Display.drawTriangle(125, 130, 115, 120, 135, 120, BLACK);
  M5.Display.fillTriangle(125, 130, 115, 120, 135, 120, BLACK);
}

void showAPScreen() {
  cls();
  screen = 9;
  M5.Display.fillScreen(YELLOW);
  M5.Display.setTextColor(BLACK, YELLOW);
  M5.Display.setTextSize(1);
  M5.Display.println(" Unable to connect to WiFi");
  M5.Display.println();
  M5.Display.println(" Please connect to:");
  M5.Display.println();
  M5.Display.print(" SSID: ");
  M5.Display.println(apSsid);
  M5.Display.println(" Pwd: 12345678");
  M5.Display.println();
  M5.Display.println(" Open http://192.168.4.1");
  M5.Display.println(" in a browser to");
  M5.Display.println(" configure the settings");
}

void cls() {
  M5.Display.fillScreen(TFT_BLACK);
  M5.Display.setCursor(0,0);
  M5.Display.setTextColor(WHITE, BLACK);
}

void showBattLevel() {
  M5.Display.setCursor(10,10);
  M5.Display.setTextSize(2);
  M5.Display.print("Batt: ");
  M5.Display.print(M5.Power.getBatteryLevel());
  M5.Display.println("%   ");
}

void showSignalStrength() {
  if (screen == 1) {
    Serial.print("RSSI: ");
    Serial.print(WiFi.RSSI());
    Serial.print(" ");
    Serial.println(rssiLabel());
    showNetworkScreen();
  } else if ((screen == 0) && (screenRotation == 1 || screenRotation == 3)) {
    M5.Display.setCursor(130, 110);
    M5.Display.println(rssiLabel());
  } else if ((screen == 0) && (screenRotation == 0 || screenRotation == 2)) {
    M5.Display.setCursor(10, 210);
    M5.Display.println(rssiLabel());
  }
}
