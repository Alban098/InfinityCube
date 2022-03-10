# Infinity Cube Lamp

<p align="center">
    <img src="/images/v2.jpg" width="70%">
</p>


A kind of lightweight ESP32/ESP8266 webserver API and a [NodeJS](https://nodejs.org/en/) web UI to control an Infinity Cube built with 144 leds/m WS2812B Led Strip ! 

## ⚙️Features

- 28 effects and 54 palettes
	- Some effects are calculated using 3D coords of the cube's edges (for maximum satisfaction)
- Customizable effect speed and intensity
- 3 customizable palettes 
- Simple UI with color, effect and network settings
- Access Point and station mode - automatic failsafe AP see [ApiServer](./ApiServer.cpp)
- Ability to disable leds on the strip to avoid overheating (in my case I disabled leds behind the corner covers)
- Possibility to rescale the brightness range
- Controllable using integrated Joystick
- Possibility to use an I2C 128x64 screen to monitor status (with configurable auto sleep)
## 📲 Quick start

### Required libraries

* [x] [FastLED](https://github.com/FastLED/FastLED)
* [x] [ArduinoJson](https://arduinojson.org/)
* [x] [WiFi](https://www.arduino.cc/en/Reference/WiFi)
* [x] [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer)
* [x] [AsyncTCP](https://github.com/me-no-dev/AsyncTCP) (for ESP32) or [ESPAsyncTCP](https://github.com/me-no-dev/ESPAsyncTCP) (for ESP8266)

### How to

- Upload the InfinityCube code to your ESP, it will fail to connect to WiFi and setup an AP
- Connect to the AP with default credentials `InfinityCube` and `123456789`
- Access the config page at `http://{ESP_IP}/setup` (usually `192.168.4.1`, but the IP is printed over serial)
- Configure your Wifi settings
- That's it, you can now access your ESP over your network

## 💾 Communicate without the Web UI

The API is exposed over 2 endpoints
- `http://{ESP_IP}/setup` : for Wifi configuration
- `http://{ESP_IP}/api` : for light control
  - GET : `http://{ESP_IP}/api?palettes=0` to get the list of palettes as JSON
  ```yaml 
  {
      "Primary Color": 0,
      "Dual Colors": 1,
      "Tri Colors": 2,
      "Vintage 57": 3,
           ...
  }
  ```
  - GET : `http://{ESP_IP}/api?effects=0` to get the list of effects as JSON
  ```yaml
  {
      "Solid": 0,
      "Rainbow": 1,
      "Strobe": 2,
      "Strobe Random": 3,
           ...
  }
  ```
  - GET : `http://{ESP_IP}/api?status=0` to get the current state as JSON
  ```yaml
  {
      "effect": 0,
      "palette": 0,
      "primary_color": 16711680,
      "secondary_color": 65280,
      "tertiary_color": 255,
      "speed": 128,
      "intensity": 128,
      "brightness": 0,
      "net_ssid": "SSID",
      "net_pass": "PASS",
      "net_ip": "192.168.0.1",
      "net_gateway": "192.168.0.254",
      "net_mask": "255.255.255.0"
  }
  ```
  - POST : `http://{ESP_IP}/api` a POST request to that endpoint with JSON Object containing one of the following field will modify it and return the new status (same as previous request)
  ```yaml
  {
      "effect": 0,                /* The current effect, will roll over if overflow                                       */
      "palette": 0,               /* The current palette, will roll over if overflow                                      */
      "primary_color": 16711680,  /* The primary color as a 24bit RGB value as an unsigned int                            */
      "secondary_color": 65280,   /* The secondary color as a 24bit RGB value as an unsigned int                          */
      "tertiary_color": 255,      /* The tertiary color as a 24bit RGB value as an unsigned int                           */
      "speed": 128,               /* The effect speed as an unsigned 8 bit value, will therefore roll over if > 255       */
      "intensity": 128,           /* The effect intensity as an unsigned 8 bit value, will therefore roll over if > 255   */
      "brightness": 0             /* The master brightness as an unsigned 8 bit value, will therefore roll over if > 255  */
  }
  ```
## 💾 Communicate using the Web UI

- Deploy the NodeJS server 
- Change the API IP in the top right corner (or for permanent change, edit it in [Api.js](/web_app/utils/Api.js))
- You can now control the leds

<p align="center">
    <img src="/images/webUI.PNG" width="100%">
</p>

## ⚙️Integrated Screen

<p align="center">
    <img src="/images/screen.png" width="70%">
</p>

## Legacy

### Frame v2

<p align="center">
    <img src="/images/v2.jpg" width="70%">
</p>

### Frame v1

<p align="center">
    <img src="/images/v1.jpg" width="70%">
</p>


## Thanks

### ESP :

* [FastLED](https://github.com/FastLED/FastLED)
* [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer)
* [WLED](https://github.com/Aircoookie/WLED/)

### Web UI :

* [Axios](https://github.com/axios/axios)
* [LiquidJS](https://liquidjs.com/)
* [Bootstrap ColorPicker](https://github.com/itsjavi/bootstrap-colorpicker/)

## Licence

Licensed under the MIT license  

*Disclaimer:*   
If you are sensitive to photosensitive epilepsy it is not recommended that you use this software.  
In case you still want to try, don't use strobe, lighting or noise modes or high effect speed settings.
As per the MIT license, I assume no liability for any damage to you or any other person or equipment.  
