#pragma once

#include "EffectManager.h"
#include "InputManager.h"
#include "ESPAsyncWebServer.h"
#include "AsyncJson.h"
#include "ArduinoJson.h"
#include "EEPROMUtils.h"
#include "HTMLPages.h"

class ApiServer {
  private:
    AsyncWebServer server = AsyncWebServer(80);
    InputManager* inputManager;
    char net_ssid[64];
    char net_pass[64];
    uint8_t net_ip[4] = {0, 0, 0, 0};
    uint8_t net_gateway[4] = {0, 0, 0, 0};
    uint8_t net_mask[4] = {0, 0, 0, 0};
    
    EffectManager* effectManager;
    AsyncResponseStream* generateStatusJson(AsyncWebServerRequest *request);
    AsyncResponseStream* generateEffectsJson(AsyncWebServerRequest *request);
    AsyncResponseStream* generatePalettesJson(AsyncWebServerRequest *request);
    void handleGet(AsyncWebServerRequest *request);
    void handlePost(AsyncWebServerRequest *request);
    void handleCalibrate(AsyncWebServerRequest *request);
    void handleSetup(AsyncWebServerRequest *request);

    void(* resetFunc) (void) = 0;

  public:
    ApiServer(EffectManager* effectManager, InputManager* inputManager);

    void start();
};
