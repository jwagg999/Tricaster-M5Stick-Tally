void startWiFi() {
  int wifiTimeout = 0;
  Serial.println("starting wifi");
  M5.Display.setCursor(37, 100);
  M5.Display.println("Waiting for WiFi...");
  M5.Display.setCursor(57, 118);

  WiFi.mode(WIFI_STA);
  int n = WiFi.scanNetworks();
  if (n == 0) {
    M5.Display.println("No networks found");
  } else {
    for (int i = 0; i < n; ++i) {
      if ((WiFi.SSID(i) == wifi_ssid1) && (WiFi.status() != WL_CONNECTED)) {
        WiFi.begin(wifi_ssid1.c_str(), wifi_pass1.c_str());
        wifiTimeout = 0;
        while (WiFi.status() != WL_CONNECTED) {
          delay(1000);
          ++wifiTimeout;
          if (wifiTimeout == 10) {
            break;
          }
        }
      }
      if ((WiFi.SSID(i) == wifi_ssid2) && (WiFi.status() != WL_CONNECTED)) {
        WiFi.begin(wifi_ssid2.c_str(), wifi_pass2.c_str());
        wifiTimeout = 0;
        while (WiFi.status() != WL_CONNECTED) {
          delay(1000);
          ++wifiTimeout;
          if (wifiTimeout == 10) {
            break;
          }
        }
      }
      if ((WiFi.SSID(i) == wifi_ssid3) && (WiFi.status() != WL_CONNECTED)) {
        WiFi.begin(wifi_ssid3.c_str(), wifi_pass3.c_str());
        wifiTimeout = 0;
        while (WiFi.status() != WL_CONNECTED) {
          delay(1000);
          ++wifiTimeout;
          if (wifiTimeout == 10) {
            break;
          }
        }
      }
    }
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("Successfully connected to network: ");
    Serial.print(WiFi.SSID());
    Serial.print(" using address ");
    Serial.println(WiFi.localIP());
    cls();
    M5.Display.setTextSize(2);
    M5.Display.println(" WiFi connected to");
    M5.Display.print(" ");
    M5.Display.println(WiFi.SSID());
    M5.Display.println(" IP address: ");
    M5.Display.print(" ");
    M5.Display.println(WiFi.localIP());
    delay(3000);
    cls();
  } else {
    Serial.println("Wifi connection failed, start local wifi");
    Serial.println();
    startLocalWiFi();
  }
  Serial.println();
  delay(100);
}

// This starts the M5Stick as a WiFi Access Point so you can configure it
void startLocalWiFi() {
  uint8_t mac[6];
  WiFi.macAddress(mac);
  apSsid = "TCTally-" + String(mac[3], HEX) + String(mac[4], HEX) + String(mac[5], HEX);
  WiFi.mode(WIFI_AP);
  if (!WiFi.softAP(apSsid.c_str(), "12345678")) {
    Serial.println("Soft AP creation failed.");
    while (true);
  }
  apEnabled = true;
  Serial.println("local wifi started");
  Serial.println("Showing AP screen");
  showAPScreen();
}

void startMDNS() {
  String hostname;
  IPAddress serverIP;
  int count = 0;
  uint8_t mac[6];
  WiFi.macAddress(mac);
  hostname = "TCTally-" + String(mac[3], HEX) + String(mac[4], HEX) + String(mac[5], HEX);
  if (!MDNS.begin(hostname)) {
    Serial.println("mDNS failed");
    while(true);
  }
  Serial.println("mDNS started");
  Serial.println("Set host name to " + hostname);
  MDNS.addService("_http", "_tcp", 80);
  Serial.print("mDNS Resolving " + TricasterName + "... ");
  while ((serverIP.toString() == "0.0.0.0") && (count < 5)) {
    ++count;
    delay(250);
    serverIP = MDNS.queryHost(TricasterName);
  }
  TricasterIP = serverIP.toString();
  Serial.println(TricasterIP);
  Serial.println();
}

String rssiLabel() {
    rssi = WiFi.RSSI();
    if (rssi > -67) {
      return "(strong) ";
    } else if (rssi < -67 && rssi > -85) {
      return "(average)";
    } else if (rssi < -85) {
      return "(weak)   ";
    }
}
