void loadSettings() {
  preferences.begin("TricasterTally", false);
  
  if (preferences.getString("wifi_ssid1").length() > 0) {
    wifi_ssid1 = preferences.getString("wifi_ssid1");
    wifi_pass1 = preferences.getString("wifi_pass1");
    Serial.println("loaded SSID1: " + wifi_ssid1);
  } else {
    Serial.println("SSID1 empty, not loaded");
  }
  
  if (preferences.getString("wifi_ssid2").length() > 0) {
    wifi_ssid2 = preferences.getString("wifi_ssid2");
    wifi_pass2 = preferences.getString("wifi_pass2");
    Serial.println("loaded SSID2: " + wifi_ssid2);
  } else {
    Serial.println("SSID2 empty, not loaded");
  }
  
  if (preferences.getString("wifi_ssid3").length() > 0) {
    wifi_ssid3 = preferences.getString("wifi_ssid3");
    wifi_pass3 = preferences.getString("wifi_pass3");
    Serial.println("loaded SSID3: " + wifi_ssid3);
  } else {
    Serial.println("SSID3 empty, not loaded");
  }

  if (preferences.getString("tricaster_name").length() > 0) {
    TricasterName = preferences.getString("tricaster_name");
    Serial.println("loaded Tricaster: " + TricasterName);
  } else {
    Serial.println("Tricaster name empty, not loaded");
  }

  if (preferences.getUInt("tally")) {
    tallyNumber = preferences.getUInt("tally");
  } else {
    tallyNumber = 1;
  }
  if (tallyNumber > 9) {
    tallyLength = 2;
  }
  Serial.println("loaded Tally: " + String(tallyNumber));

  if (preferences.getUInt("bright")) {
    brightness = preferences.getUInt("bright");
  } else {
    brightness = 100;
  }
  M5.Display.setBrightness(brightTo255(brightness));
  Serial.println("loaded brightness: " + String(brightness));

  connectInterval = preferences.getUInt("conn_int");
  Serial.println("loaded conn_int: " + String(connectInterval));

  justLive = preferences.getUInt("just_live") || justLive;
  Serial.println("loaded just_live: " + String(justLive));

  tallyMode = preferences.getUInt("mode") || tallyMode;
  Serial.println("loaded mode: " + String(tallyMode));

  preferences.end();
  Serial.println("settings loaded");
  Serial.println();
}

void resetSettings() {
  preferences.begin("TricasterTally", false);
  
  preferences.putString("wifi_ssid1", "");
  preferences.putString("wifi_pass1", "");
  preferences.putString("wifi_ssid2", "");
  preferences.putString("wifi_pass2", "");
  preferences.putString("wifi_ssid3", "");
  preferences.putString("wifi_pass3", "");
  preferences.putString("tricaster_name", "");
  preferences.putUInt("tally", 1);
  preferences.putUInt("bright", 100);
  preferences.putUInt("conn_int", 0);
  preferences.putUInt("just_live", 0);
  preferences.putUInt("mode", 0);
  preferences.end();

  Serial.println("Settings are reset, rebooting");
  ESP.restart(); //Thanks to Babbit on Tricaster forums!
}

void increaseTally() {
  ++tallyNumber;
  if (tallyNumber > 9) {
    tallyLength = 2;
  }
  preferences.begin("TricasterTally", false);
  preferences.putUInt("tally", tallyNumber);
  preferences.end();
}

void resetTally() {
  tallyNumber = 1;
  tallyLength = 1;
  preferences.begin("TricasterTally", false);
  preferences.putUInt("tally", tallyNumber);
  preferences.end();
}

void saveBrightness() {
  preferences.begin("TricasterTally", false);
  preferences.putUInt("bright", brightness);
  preferences.end();
}

void saveMode() {
  preferences.begin("TricasterTally", false);
  preferences.putUInt("mode", tallyMode);
  preferences.end();
}

void saveJustlive() {
  preferences.begin("TricasterTally", false);
  preferences.putUInt("just_live", justLive);
  preferences.end();
}

int brightTo255(int brt) {
  switch (brt) {
    case 5:
      return 60;
      break;
    case 20:
      return 90;
      break;
    case 40:
      return 120;
      break;
    case 60:
      return 160;
      break;
    case 80:
      return 200;
      break;
    case 100:
      return 255;
      break;
  }
}

