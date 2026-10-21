Tricaster M5Stick Tally Light

Features

- Press on M5 button will toggle between 6 screens:
    1.  The actual status of the tally (a tally status change will default back to this screen)
    2.  Network screen, showing the current IP Address so you can access the Web UI
    3.  Show the tally input number that is set for the unit and change it using the side button
    4.  The brightness screen. You can use the side button on this screen to toggle through the 6 different settings
    5.  The mode screen, use the side button to display input number or LIVE-PRE-SAFE
    6.  The justlive screen, use the side button to display LIVE-PRE-SAFE or LIVE-SAFE
- The side button will reconnect to Tricaster when on main screen
- Holding the same button when on main screen will reset ALL settings
- Data is saved to memory, will be remembered after device is turned off
- Webserver with Dark Web UI for easy configuration
- Automatic wifi scanning to easily select your wifi network
- Access Point mode when not connected to a WiFi network
- Battery indicator
- Landscape & Portrait mode using accelerometer
- Set an interval to automatically reconnect to Tricaster if disconnected

---

* Uploading the code to the stick

- Follow the tutorial on the [M5Stack website](https://docs.m5stack.com/#/en/arduino/arduino_development).

- Copy the libraries used by this project (found in the libs folder) to your system. The default path is: %userprofile%\Documents\Arduino\libraries

- Upload to your device.

- Follow the instructions on the LCD.

* Configuring the stick

- Once the code is uploaded to the stick, wait until it's in AP (Access Point) mode.
- Grab a phone and connect to the 'TCTally-xxxxxx' wifi network, the password is: '12345678'.
- Open your browser and go to: 'http://192.168.4.1', this will open up the Web UI.
    1. Enter the SSID and password of the wifi networks you want to connect to.
    2. Enter the network name (not the IP) of the Tricaster.
    3. Enter how often to try reconnecting to the Tricaster.
    4. Remaining settings are optional at this point and can be set with the device buttons.
- Hit the save button.
- The stick will restart with the given information.

* Fields explained

** SSID1 & SSID2 **

Manually enter 1 or 2 networks.

** SSID3 **

A select dropdown which shows a list of the wifi networks found.

** Hidden SSID Name **

This field only shows when you select 'Hidden network' in the SSID list. 
Type in the SSID that you want to connect to.

The software will try to connect to these networks in order (1 then 2 then 3).

** Tricaster Name **

Fill in the network name (not the IP) of the Tricaster. 

** Reconnect interval **

Input is in seconds. This will try to reconnect to Tricaster every 'x' seconds after the interval has passed when it's disconnected. This will loop if the connection cannot be established. 

WARNING: Since the stick is single threaded, when the stick tries to reconnect to Tricaster, the Web UI is not accessible! 

Example: When set to '10' it will try to reconnect to Tricaster every 10 seconds after connection was unsuccessful.

** Tally Number **

This field corresponds to the input number in Tricaster.

** Brightness **

Set the brightness of the LCD. Options to choose from:
* 5%
* 20%
* 40%
* 60%
* 80%
* 100%

NOTE: Obviously, the battery will drain faster when the brightness is set to a high value. I recommend setting it at 60%.

** Just Live **

'true': The stick only shows when the configured input is safe or live.

'false': The stick shows when the configured input is safe, in preview, or live.

** Mode **

'Text (SAFE, PRE, LIVE)': Show the textual representation of the status of the configured input(s).

'Tally Number': Show the configured tally number and only update the background color when the status changes.

