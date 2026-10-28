/*
* Forked from Guido Visser's vMix-M5Stick-Tally-Light,
* customized for Tricaster by Joe Wagg
*/

#include <M5Unified.h>
#include <M5GFX.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoWebsockets.h>
#include <WebServer.h>
#include <Preferences.h>
#include <ESPmDNS.h>

using namespace websockets;

Preferences preferences;
WebsocketsClient wsclient;
WiFiClient webclient;
HTTPClient http;

WebServer server(80);

String swVer = "26.0";
String TricasterIP = "";
String apSsid = "";
int TricasterPort = 80;
int tallyLength = 1; // do not change, # of digits in tally number
int currentState = 0;
int newState = 0;
int screenRotation = 3;
int status = WL_IDLE_STATUS;
long rssi = -100;
char screen = 0;
bool connectedToTricaster = false;
bool apEnabled = false;
float accX = 0;
float accY = 0;
float accZ = 0;

// Time measure
int keepalive = 0;
unsigned long lastAccelCheck = 0;
unsigned long lastBattCheck = 0;
unsigned long lastSignalCheck = 0; // wifi signal strength, used only near end of loop()
unsigned long lastTCCheck = 0; // tricaster connection
unsigned long lastWifiCheck = 0; // used only near end of loop()

// DON'T CHANGE THESE VARIABLES, YOU CAN CHANGE THEM IN THE WEB UI
String wifi_ssid1 = "";
String wifi_pass1 = "";
String wifi_ssid2 = "";
String wifi_pass2 = "";
String wifi_ssid3 = "";
String wifi_pass3 = "";
String TricasterName = "";
int tallyNumber = 1;
int brightness = 100;
int connectInterval = 0; // Tricaster reconnect interval in seconds
int tallyMode = 0; // 0 for words like SAFE, PRE and LIVE. 1 for tally number with changing background
int justLive = 0; // When 1, PRE is not used. Just SAFE and LIVE
// DON'T CHANGE THESE VARIABLES, YOU CAN CHANGE THEM IN THE WEB UI

void setup() {
  setCpuFrequencyMhz(80); // Slower clock speed to save battery, Thanks Irvin Cee
  Serial.begin(115200);
  auto cfg = M5.config();
  cfg.internal_imu = true;
  M5.begin(cfg);
  M5.Imu.init();
  M5.Display.begin();
  delay(100);
  loadSettings();

  cls();
  M5.Display.setRotation(screenRotation);
  M5.Display.setTextSize(1);
  M5.Display.println(" Tricaster M5Stick Tally");
  M5.Display.println(" version " + swVer);
  M5.Display.println(" by Joe Wagg");
  M5.Display.println();
  M5.Display.println(" based on vMix M5Stick-C Tally");
  M5.Display.println(" by Guido Visser");

  startWiFi();
  startServer();
  if (TricasterName != "") {
    startMDNS();
    if (TricasterIP == "0.0.0.0") {
      showNoTricasterScreen();
    } else {
      connectToTricaster(false);
    }
  }
  if (!apEnabled && screen != 8) {
    showMainScreen();
  }
}

void loop() {
  M5.update();
  if (M5.BtnA.wasClicked()) {
    switch (screen) {
      case 0:
        Serial.println("Showing network screen");
        showNetworkScreen();
        break;
      case 1:
        Serial.println("Showing tally screen");
        showTallyScreen();
        break;
      case 2:
        Serial.println("Showing brightness screen");
        showBrightnessScreen();
        break;
      case 3:
        Serial.println("Showing mode screen");
        showModeScreen();
        break;
      case 4:
        Serial.println("Showing justlive screen");
        showJustliveScreen();
        break;
      case 5:
        Serial.println("Showing main screen");
        showMainScreen();
        break;
      case 8:
        showNoTricasterScreen();
        break;
      case 9:
        showAPScreen();
        break;
      default:
        Serial.println("Showing main screen");
        showMainScreen();
        break;        
    }
  }

  if (millis() > lastAccelCheck + 1000) {
    lastAccelCheck = millis();
    if (screen == 0) {
      M5.Imu.getAccel(&accX, &accY, &accZ);
      if (accX > 0.70) {
        if (screenRotation != 1) {
          screenRotation = 1;
          M5.Display.setRotation(1);
          showMainScreen();
        }
      } else if (accX < -0.70) {
        if (screenRotation != 3) {
          screenRotation = 3;
          M5.Display.setRotation(3);
          showMainScreen();
        }
      }
      if (accY > 0.70){
        if (screenRotation != 0) {
          screenRotation = 0;
          M5.Display.setRotation(0);
          showMainScreen();
        }
      } else if (accY < -0.70) {
        if (screenRotation != 2) {
          screenRotation = 2;
          M5.Display.setRotation(2);
          showMainScreen();
        }
      }
    }
  }

  if (M5.BtnB.wasClicked() && screen == 0) {
    connectToTricaster(false);
  }

  if (M5.BtnB.wasHold() && screen == 0) {
    if (!webclient.connected()) {
      resetSettings();
    } else {
      cls();
      M5.Display.setTextSize(2);
      M5.Display.println("No need to reset");
      M5.Display.println("You're connected");
      delay(3000);
      showMainScreen();
    }
  }

  if (M5.BtnB.wasClicked() && screen == 2) {
    increaseTally();
    showTallyScreen();
  }

  if (M5.BtnB.wasHold() && screen == 2) {
    resetTally();
    showTallyScreen();
  }
  
  if (M5.BtnB.wasClicked() && screen == 3) {
    switch (brightness) {
      case 100:
        brightness = 5;
        break;
      case 5:
        brightness = 20;
        break;
      case 20:
        brightness = 40;
        break;
      case 40:
        brightness = 60;
        break;
      case 60:
        brightness = 80;
        break;
      case 80:
        brightness = 100;
        break;
      default:
        brightness = 100;
    }
    M5.Display.setBrightness(brightTo255(brightness));
    saveBrightness();
    showBrightnessScreen();
  }

  if (M5.BtnB.wasClicked() && screen == 4) {
    switch (tallyMode) {
      case 0:
        tallyMode = 1;
        break;
      case 1:
        tallyMode = 0;
        break;
      default:
        tallyMode = 0;
        break;
    }
    showModeScreen();
  }

  if (M5.BtnB.wasClicked() && screen == 5) {
    switch (justLive) {
      case 0:
        justLive = 1;
        break;
      case 1:
        justLive = 0;
        break;
      default:
        justLive = 0;
        break;
    }
    showJustliveScreen();
  }

  if (millis() > lastBattCheck + 5000) {
    if (screen == 0 && !apEnabled) {
      lastBattCheck = millis();
      showBattLevel();
    }
  }

  if (millis() > lastSignalCheck + 2000) {
    lastSignalCheck = millis();
    showSignalStrength();
  }

  if (wsclient.available()) {
    if (millis() - keepalive > 10000) { // keep websocket connection active
      keepalive = millis();
      wsclient.ping();
    }
    wsclient.poll();
    wsclient.onMessage([&](WebsocketsMessage message) {
      if (message.data() == "tally") {
        getTallyData();
      }
    });
  }

  if (connectInterval != 0 && !wsclient.available() && !apEnabled && TricasterIP != "0.0.0.0" && (millis() > lastTCCheck + (connectInterval * 1000))) { // check websocket & reconnect to tricaster
    webclient.stop();
    Serial.println("reconnecting to tricaster, based on given interval");
    singleReconnect();
  }
  
  if (!WiFi.isConnected() && !apEnabled && millis() > lastWifiCheck + 10000) {
    webclient.stop();
    lastWifiCheck = millis();
    Serial.println("lost wifi connection");
    startWiFi();
  }

  server.handleClient();
  delay(25);
}

