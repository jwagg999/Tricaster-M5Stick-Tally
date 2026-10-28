void handle_root() {
  String HEADER = "<!DOCTYPE html><html lang='en'><head><meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no, shrink-to-fit=no'><title>Tricaster M5Stick-C Tally</title><style>";
  HEADER += "@import url(https://fonts.googleapis.com/css2?family=Open+Sans&display=swap);.wrapper,input[type=text],input[type=number],input[type=submit],select{width:100%;box-sizing:border-box}body,html{background:#2b2b2b;color:#eee;padding:0;margin:0;font-family:'Open Sans',verdana,sans-serif}.wrapper{padding:10px}.wrapper h1{text-align:center}input[type=text],input[type=number],select{margin-bottom:10px}input,select{background-color:#6d6d6d;color:#f0f0f0;border:1px solid #000;font-size:18px;height:35px;padding:0 5px}input[type=submit]{height:50px;margin:0 auto}@media screen and (min-width:600px){.wrapper{width:600px;margin:0 auto}}";
  HEADER += "</style></head><body><div class='wrapper'>";

  String FOOTER = "</div></body></html>";

  String tally = String(tallyNumber);
  String just_live = String(justLive);
  String bright = String(brightness);
  String _mode = String(tallyMode);
  String HTML = HEADER;
    
  HTML += "<div class=wrapper data-theme=light>";
    HTML += "<h1>Tricaster M5Stick Tally Settings</h1>";

    HTML += "<form action=/save id=frmData method=post onsubmit=return!1>";
      HTML += "<div>SSID1:<br><input id=ssid1 type=text value='" + (String)wifi_ssid1 + "'name=ssid1></div>";
      HTML += "<div>Password1:<br><input id=pass1 type=text value='" + (String)wifi_pass1 + "'name=pass1></div>";
      HTML += "<div>SSID2:<br><input id=ssid2 type=text value='" + (String)wifi_ssid2 + "'name=ssid2></div>";
      HTML += "<div>Password2:<br><input id=pass2 type=text value='" + (String)wifi_pass2 + "'name=pass2></div>";
      HTML += "<div>SSID3:<br><select id=ssid3><option disabled selected>Scanning wifi...</option></select></div>";
      HTML += "<div class=ssid3Div style=display:none>Hidden SSID3 Name:<br><input id=ssid3 type=text value='" + (String)wifi_ssid3 + "'name=ssid3></div>";
      HTML += "<div>Password3:<br><input id=pass3 type=text value='" + (String)wifi_pass3 + "'name=pass3></div>";
      HTML += "<div>Tricaster Name:<br><input id=tricastername type=text value='" + (String)TricasterName + "'name=tricastername></div>";
      HTML += "<div>Reconnect interval (in seconds, 0 means no reconnection interval):<br><input id=conn_int type=number value='" + (String)connectInterval + "'name=conn_int></div>";
      HTML += "<div>Tally Number:<br><input id=tally_num type=number value='" + tally + "'name=tally_num max=1000 min=1></div>";
      HTML += "<div>Brightness:<br><select id=drpBright name=bright><option value=5>5%</option><option value=20>20%</option><option value=40>40%</option><option value=60>60%</option><option value=80>80%</option><option value=100>100%</option></select></div>";
      HTML += "<div>Mode:<br><select id=drpMode name=mode><option value=0>Text (SAFE, PRE, LIVE)</option><option value=1>Tally Number</option></select></div>";
      HTML += "<div>Just Live:<br><select id=drpJustLive name=just_live><option value=0>Live-Pre-Safe</option><option value=1>Live-Safe</option></select></div>";
      HTML += "<input id=btnSave type=submit value=SAVE class='btn btn-primary'>";
    HTML += "</form>";

    HTML += "<h2>Reconnect to Tricaster</h2>";

    HTML += "<form action=/reconnect id=frmReconnect method=post onsubmit=return!1>";
      HTML += "<input id=btnReconnect type=submit value=RECONNECT>";
    HTML += "</form>";

  HTML += "</div>";

  HTML += "<script>";
 
  HTML += "const btnSave = document.querySelector('#btnSave');";
  HTML += "const btnReconnect = document.querySelector('#btnReconnect');";
  HTML += "const drpBright = document.querySelector('#drpBright');";
  HTML += "const ssid3Select = document.querySelector('#ssid3');";
  HTML += "const drpJustLive = document.querySelector('#drpJustLive');";
  HTML += "const drpMode = document.querySelector('#drpMode');";
  HTML += "drpBright.value = '" + bright + "';";
  HTML += "drpJustLive.value = '" + just_live + "';";
  HTML += "drpMode.value = '" + _mode + "';";

    HTML += "btnSave.addEventListener('click', async function(e){"; // start btnSave.addEventListener
    HTML += "e.preventDefault();";
    HTML += "const ssid1 = document.querySelector('#ssid1').value;";
    HTML += "const pass1 = document.querySelector('#pass1').value;";
    HTML += "const ssid2 = document.querySelector('#ssid2').value;";
    HTML += "const pass2 = document.querySelector('#pass2').value;";
    HTML += "let ssid3 = document.querySelector('#ssid3').value;";
    HTML += "if(ssid3 === '__hidden__'){ ssid3 = document.querySelector('#ssid3').value; }";
    HTML += "const pass3 = document.querySelector('#pass3').value;";
    HTML += "const tricastername = document.querySelector('#tricastername').value;";
    HTML += "const frmData = document.querySelector('#frmData');";
    HTML += "const tally_num = document.querySelector('#tally_num').value;";
    HTML += "const bright = drpBright.value;";
    HTML += "const mode = drpMode.value;";
    HTML += "const just_live = drpJustLive.value;";
    HTML += "const conn_int = parseInt(document.querySelector('#conn_int').value, 10) || 0;";
    HTML += "let formData = new FormData();";
    HTML += "formData.append('ssid1', ssid1.trim());";
    HTML += "formData.append('pass1',pass1.trim());";
    HTML += "formData.append('ssid2', ssid2.trim());";
    HTML += "formData.append('pass2',pass2.trim());";
    HTML += "formData.append('ssid3', ssid3.trim());";
    HTML += "formData.append('pass3',pass3.trim());";
    HTML += "formData.append('tricastername', tricastername.trim());";
    HTML += "formData.append('tally_num', tally_num);";
    HTML += "formData.append('conn_int', conn_int);";
    HTML += "formData.append('bright', bright);";
    HTML += "formData.append('mode', mode);";
    HTML += "formData.append('just_live', just_live);";
    HTML += "btnSave.setAttribute('disabled', '');";
    HTML += "const res = await fetch('/save', { method: 'POST', cache: 'no-cache', referrerPolicy: 'no-referrer', body: formData });";
    HTML += "if(res.status === 200){ btnSave.value = 'SETTINGS SAVED!'; await setTimeout(()=>{btnSave.value = 'SAVE';}, 3000); }";
    HTML += "btnSave.removeAttribute('disabled');";
    HTML += "});"; // end btnSave.addEventListener

  HTML += "btnReconnect.addEventListener('click', function(e){ e.preventDefault(); fetch('/reconnect'); });";

  HTML += "ssid3Select.addEventListener('change', e => { const val = e.target.value; const ssid3cd = document.querySelector('.ssid3CustomDiv'); if(val === '__hidden__'){ ssid3cd.style.display = 'block'; } else { ssid3cd.style.display = 'none'; } });";

    HTML += "document.addEventListener('DOMContentLoaded', async function(){"; // start document.addEventListener
    HTML += "const res = await fetch('/scanNetwork');";

      HTML += "res.text().then(text=>{"; // start res.text
      HTML += "let networks = [text];";
      HTML += "let str = '';";
      HTML += "if(text.indexOf('|||') !== -1){ networks = text.split('|||'); }";
      HTML += "let sel = document.getElementById('ssid3');";
      HTML += "sel.innerHTML = '';";
      HTML += "let existingNetwork = '';";

        HTML += "networks.forEach(network => {"; // start networks.forEach
        HTML += "let opt = document.createElement('option');";
        HTML += "opt.appendChild( document.createTextNode(network) );";
        HTML += "opt.value = network;";
        HTML += "if('" + (String)wifi_ssid3 + "' === network){ existingNetwork = network; }";
        HTML += "sel.appendChild(opt);";
        HTML += "});"; // end networks.forEach

      HTML += "let opt = document.createElement('option');";
      HTML += "opt.appendChild( document.createTextNode('Hidden network') );";
      HTML += "opt.value = '__hidden__';";
      HTML += "sel.appendChild(opt);";
      HTML += "if(existingNetwork !== ''){ sel.value = existingNetwork; }";
      HTML += "});"; // end res.text

    HTML += "});"; // end document.addEventListener

  HTML += "</script>";

  HTML += FOOTER;

  server.send(200, "text/html", HTML);
}

void handle_save() {
  String message = "";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); ++i) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(200, "text/plain", message);

  String tally = server.arg("tally_num");
  String bright = server.arg("bright");
  String just_live = server.arg("just_live");
  String _mode = server.arg("mode");
  String conn_int = server.arg("conn_int");

  // save values in preferences
  preferences.begin("TricasterTally", false);

    wifi_ssid1 = server.arg("ssid1");
    wifi_pass1 = server.arg("pass1");
    preferences.putString("wifi_ssid1", &(wifi_ssid1[0]));
    preferences.putString("wifi_pass1", &(wifi_pass1[0]));
    Serial.println("PUT WIFI_SSID1 & WIFI_PASS1 " + wifi_ssid1);

    wifi_ssid2 = server.arg("ssid2");
    wifi_pass2 = server.arg("pass2");
    preferences.putString("wifi_ssid2", &(wifi_ssid2[0]));
    preferences.putString("wifi_pass2", &(wifi_pass2[0]));
    Serial.println("PUT WIFI_SSID2 & WIFI_PASS2 " + wifi_ssid2);

    wifi_ssid3 = server.arg("ssid3");
    wifi_pass3 = server.arg("pass3");
    preferences.putString("wifi_ssid3", &(wifi_ssid3[0]));
    preferences.putString("wifi_pass3", &(wifi_pass3[0]));
    Serial.println("PUT WIFI_SSID3 & WIFI_PASS3 " + wifi_ssid3);

    TricasterName = server.arg("tricastername");
    preferences.putString("tricaster_name", &(TricasterName[0]));
    Serial.println("PUT TRICASTER NAME " + TricasterName);

    tallyNumber = std::atoi(tally.c_str());
    preferences.putUInt("tally", tallyNumber);
    Serial.println("PUT TALLY NR " + String(tallyNumber));

    connectInterval = std::atoi(conn_int.c_str());
    preferences.putUInt("conn_int", connectInterval);
    Serial.println("PUT CONN INT " + String(connectInterval));

    brightness = std::atoi(bright.c_str());
    preferences.putUInt("bright", brightness);
    Serial.println("PUT BRIGHT " + String(brightness));

    justLive = std::atoi(just_live.c_str());
    preferences.putUInt("just_live", justLive);
    Serial.println("PUT justLive " + String(justLive));

    tallyMode = std::atoi(_mode.c_str());
    preferences.putUInt("mode", tallyMode);
    Serial.println("PUT MODE " + String(tallyMode));
    
  preferences.end();
  Serial.println("preferences saved, rebooting");
  ESP.restart(); // Reboot
}

void handleReconnect() {
  connectToTricaster(false);
  server.send(200, "text/plain", "success");
}

void handleScanNetwork() {
  int numSsid3 = WiFi.scanNetworks();
  if (numSsid3 == -1) {
    return;
  } else {
    String retStr = "";
    for (int thisNet = 0; thisNet<numSsid3; ++thisNet) {
      if (thisNet == 0){
        retStr += WiFi.SSID(thisNet);
      } else {
        retStr += "|||" + WiFi.SSID(thisNet);
      }
    }
    server.send(200, "text/plain", retStr);
  }
}

void startServer() {
  server.on("/", handle_root);
  server.on("/save", handle_save);
  server.on("/reconnect", handleReconnect);
  server.on("/scanNetwork", handleScanNetwork);
  server.begin();
  Serial.println("HTTP server started");
  Serial.println();
}
