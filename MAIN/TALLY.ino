void showTallyLive() {
  M5.Display.fillScreen(RED);
  M5.Display.setTextColor(WHITE, RED);
  if (tallyMode == 0 && (screenRotation == 1 || screenRotation == 3)) {
    M5.Display.setCursor(30, 38);
    M5.Display.setTextSize(8);
    M5.Display.println("LIVE");
    M5.Display.setCursor(10, 110);
    M5.Display.setTextSize(2);
    M5.Display.println("Camera " + String(tallyNumber));
  } else if (tallyMode == 0 && (screenRotation == 0 || screenRotation == 2)) {
    M5.Display.setCursor(10, 93);
    M5.Display.setTextSize(5);
    M5.Display.println("LIVE");
    M5.Display.setCursor(10, 180);
    M5.Display.setTextSize(2);
    M5.Display.println("Camera " + String(tallyNumber));
  } else if (tallyMode == 1) {
    showTallyNumbers();
  }
  showBattLevel();
  showSignalStrength();
}

void showTallyPreview() {
  M5.Display.fillScreen(GREEN);
  M5.Display.setTextColor(BLACK, GREEN);
  if (tallyMode == 0 && !justLive && (screenRotation == 1 || screenRotation == 3)) {
    M5.Display.setCursor(50, 38);
    M5.Display.setTextSize(8);
    M5.Display.println("PRE");
    M5.Display.setCursor(10, 110);
    M5.Display.setTextSize(2);
    M5.Display.println("Camera " + String(tallyNumber));
  } else if (tallyMode == 0 && !justLive && (screenRotation == 0 || screenRotation == 2)) {
    M5.Display.setCursor(25, 93);
    M5.Display.setTextSize(5);
    M5.Display.println("PRE");
    M5.Display.setCursor(10, 180);
    M5.Display.setTextSize(2);
    M5.Display.println("Camera " + String(tallyNumber));
  } else if (tallyMode == 1) {
    showTallyNumbers();
  }
  showBattLevel();
  showSignalStrength();
}

void showTallySafe() {
  M5.Display.fillScreen(BLACK);
  M5.Display.setTextColor(WHITE, BLACK);
  if (tallyMode == 0 && (screenRotation == 1 || screenRotation == 3)) {
    M5.Display.setCursor(30, 38);
    M5.Display.setTextSize(8);
    M5.Display.println("SAFE");
    M5.Display.setCursor(10, 110);
    M5.Display.setTextSize(2);
    M5.Display.println("Camera " + String(tallyNumber));
  } else if (tallyMode == 0 && (screenRotation == 0 || screenRotation == 2)) {
    M5.Display.setCursor(8, 93);
    M5.Display.setTextSize(5);
    M5.Display.println("SAFE");
    M5.Display.setCursor(10, 180);
    M5.Display.setTextSize(2);
    M5.Display.println("Camera " + String(tallyNumber));
  } else if (tallyMode == 1) {
    showTallyNumbers();
  }
  showBattLevel();
  showSignalStrength();
}

void showTallyNumbers() {
  int x;
  int y;
  if (screenRotation == 1 || screenRotation == 3) {  
    x = 105;
    y = 39;
    if (tallyLength == 2) {
      x = 75;
    }
    M5.Display.setTextSize(8);
  } else {
    x = 40;
    y = 80;
    if (tallyLength == 2) {
      x = 10;
    }
    M5.Display.setTextSize(10);
  }
  M5.Display.setCursor(x, y);
  M5.Display.println(tallyNumber);
  showBattLevel();
  showSignalStrength();
}

