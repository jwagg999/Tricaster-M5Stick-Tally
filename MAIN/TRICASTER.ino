bool connectToTricaster(bool recursive) {
  cls();
  if (TricasterName != "") {
    Serial.print("Connecting to Tricaster ");
    Serial.print(TricasterName);
    Serial.print(" at IP ");
    Serial.print(TricasterIP); // found with mDNS in setup()
    Serial.print("... ");
    M5.Display.setTextSize(1);
    M5.Display.println("Connecting to Tricaster...");
  
    if (wsclient.connect(TricasterIP, TricasterPort, "/v1/change_notifications")) {
      connectedToTricaster = true;
      Serial.println("connected");
      Serial.println();
      M5.Display.println("Connected to Tricaster!");
      getTallyData(); // for initial display
      showMainScreen();
      return true;
    } else {
      if (recursive) {
        return false;
      }
      char tryCount = 0;
      cls();
      M5.Display.setTextSize(1);
      M5.Display.println("Could not connect to Tricaster");
      M5.Display.println("Retrying: 0/3");
      bool retry = false;
      for (uint8_t i = 0; i < 3; ++i) {
        Serial.print(i);
        retry = retryConnectionTricaster(i);
        if (!retry) {
          return true;
        }
      }
      connectedToTricaster = false;
      Serial.println("FAILED");
      noConnectionToTricaster();
      return false;
    }
  }
}

void singleReconnect() {
  cls();
  M5.Display.setTextSize(1);
  M5.Display.println("Connecting to Tricaster...");
  if (wsclient.connect(TricasterIP, TricasterPort, "/v1/change_notifications")) {
    lastTCCheck = millis();
    connectedToTricaster = true;
    M5.Display.println("Connected to Tricaster!");
    showMainScreen();
  } else {
    lastTCCheck = millis();
  }
}

bool retryConnectionTricaster(int tryCount) {
  cls();
  M5.Display.setTextSize(1);
  M5.Display.println("Couldn't connect to Tricaster");
  M5.Display.print("Retrying: ");
  M5.Display.print(tryCount);
  M5.Display.print("/3");
  delay(1000);
  if (connectToTricaster(true)) {
    return false;
  } else {
    return true;
  }
}

void noConnectionToTricaster() {
  cls();
  M5.Display.setTextSize(1);
  M5.Display.fillScreen(YELLOW);
  M5.Display.setTextColor(BLACK, YELLOW);
  M5.Display.println("Couldn't connect to Tricaster");
  M5.Display.println();
  M5.Display.println("Tricaster is closed");
  M5.Display.println("or check settings");
  M5.Display.println();
  M5.Display.print("http://");
  M5.Display.println(WiFi.localIP());
  M5.Display.println();
  M5.Display.println("Press BtnB to reconnect");
}

void getTallyData() {
 if (http.begin(webclient, "http://" + String(TricasterIP) + "/v1/dictionary?key=tally")) {
    int httpCode = http.GET();
    if (httpCode > 0) {
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
        String payload = http.getString();
        if (payload.indexOf("input" + String(tallyNumber) + "\" index=\"" + String(tallyNumber - 1) + "\" on_pgm=\"true") > 0) { // Tricaster input numbers start at 0
          newState = 1; //Live
          if (currentState != newState) {
            Serial.println("Camera " + String(tallyNumber) + " is Live");
          }
        }
        if (payload.indexOf("input" + String(tallyNumber) + "\" index=\"" + String(tallyNumber - 1) + "\" on_pgm=\"false\" on_prev=\"true") > 0) {
          newState = 2; //Preview
          if (currentState != newState) {
            Serial.println("Camera " + String(tallyNumber) + " is Pre");
          }
        }
        if (payload.indexOf("input" + String(tallyNumber) + "\" index=\"" + String(tallyNumber - 1) + "\" on_pgm=\"false\" on_prev=\"false") > 0) {
          newState = 0; //Safe
          if (currentState != newState) {
            Serial.println("Camera " + String(tallyNumber) + " is Safe");
          }
        }
        if (currentState != newState) {
          currentState = newState;
          showMainScreen();
        }
      } else {
          Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

    http.end();

    } else {
      Serial.println("[HTTP] Unable to connect");
    }
  }
}
