#include "ApiServer.h"

#define SSID_ADDR       64
#define PASSWORD_ADDR   96
#define IP_ADDR         160
#define GATE_ADDR       164
#define MASK_ADDR       168

ApiServer::ApiServer(EffectManager* effectManager, InputManager* inputManager) {
  this->effectManager = effectManager;
}

void ApiServer::start() {
  EEPROMUtils::init();
  WiFi.mode(WIFI_STA);

  EEPROMUtils::readIP(IP_ADDR, net_ip);
  IPAddress local_IP = IPAddress(net_ip[0], net_ip[1], net_ip[2], net_ip[3]);
  delay(50);
  EEPROMUtils::readIP(GATE_ADDR, net_gateway);
  IPAddress gateway = IPAddress(net_gateway[0], net_gateway[1], net_gateway[2], net_gateway[3]);
  delay(50);
  EEPROMUtils::readIP(MASK_ADDR, net_mask);
  IPAddress mask = IPAddress(net_mask[0], net_mask[1], net_mask[2], net_mask[3]);
  delay(50);

  if (!WiFi.config(local_IP, gateway, mask, IPAddress(8, 8, 8, 8), IPAddress(8, 8, 4, 4)))
    Serial.println("Static Addressing Failed to configure");
  
  EEPROMUtils::readString(SSID_ADDR, net_ssid);
  delay(50);
  EEPROMUtils::readString(PASSWORD_ADDR, net_pass);
  Serial.println(net_ssid);
  Serial.println(net_pass);
  Serial.println(local_IP);
  Serial.println(gateway);
  Serial.println(mask);

  WiFi.begin(net_ssid, net_pass);
  uint8_t connection_attempts = 0;
  while (WiFi.status() != WL_CONNECTED && connection_attempts < Params::MAX_WIFI_ATTEMPTS) {
    delay(500);
    Serial.print(".");
    connection_attempts++;
  }

  if (WiFi.status() == WL_NO_SSID_AVAIL || WiFi.status() == WL_CONNECT_FAILED) {
    WiFi.disconnect();
    WiFi.mode(WIFI_AP);
    Serial.println("Unable to connect to Wifi, please use Integrated Access Point ('InfinityCube', '123456789')");
    WiFi.softAP("InfinityCube", "123456789");
    Serial.print("Access Point IP : ");
    Serial.println(WiFi.softAPIP());  
  } else {
    Serial.println("");
    Serial.print("IP : ");
    Serial.println(WiFi.localIP());
  }

  std::function<void(AsyncWebServerRequest *request)> postHandler = std::bind(&ApiServer::handlePost, this, std::placeholders::_1);
  std::function<void(AsyncWebServerRequest *request)> getHandler = std::bind(&ApiServer::handleGet, this, std::placeholders::_1);
  std::function<void(AsyncWebServerRequest *request)> setupHandler = std::bind(&ApiServer::handleSetup, this, std::placeholders::_1);
  std::function<void(AsyncWebServerRequest *request)> calibrateHandler = std::bind(&ApiServer::handleCalibrate, this, std::placeholders::_1);
   
  server.on("/api", HTTP_POST, postHandler);
  server.on("/api", HTTP_GET, getHandler);
  server.on("/setup", HTTP_GET, setupHandler);
  server.on("/calibrate", HTTP_GET, calibrateHandler);
  
  server.begin();
}

AsyncResponseStream* ApiServer::generateStatusJson(AsyncWebServerRequest *request) {
  AsyncResponseStream *response = request->beginResponseStream("application/json");
  response->addHeader("type","status");
  DynamicJsonDocument doc(2048);
  doc[Params::PARAM_EFFECT] = effectManager->getEffectId();
  doc[Params::PARAM_PAL] = effectManager->getPaletteId();
  doc[Params::PARAM_COLOR_0] = effectManager->getPrimaryColor();
  doc[Params::PARAM_COLOR_1] = effectManager->getSecondaryColor();
  doc[Params::PARAM_COLOR_2] = effectManager->getTertiaryColor();
  doc[Params::PARAM_SPEED] = effectManager->getEffectSpeed();
  doc[Params::PARAM_INTENSITY] = effectManager->getEffectIntensity();
  doc[Params::PARAM_BRIGHTNESS] = effectManager->getMasterBrightness();
  doc[Params::PARAM_NET_SSID] = net_ssid;
  doc[Params::PARAM_NET_PASS] = "********";
  doc[Params::PARAM_NET_IP] = WiFi.localIP();
  doc[Params::PARAM_NET_GATEWAY] = WiFi.gatewayIP();
  doc[Params::PARAM_NET_MASK] = WiFi.subnetMask();
  String output;
  serializeJson(doc, output);
  response->print(output);
  return response;
}

AsyncResponseStream* ApiServer::generateEffectsJson(AsyncWebServerRequest *request) {
  AsyncResponseStream *response = request->beginResponseStream("application/json");
  response->addHeader("type","effects");
  DynamicJsonDocument doc(2048);
  for (uint8_t i = 0; i < effectManager->getNbEffects(); i++) {
    doc[effectManager->getEffect(i)->getLabel()] = i;
  }
  String output = "";
  serializeJson(doc, output);
  response->print(output);
  return response;
}

AsyncResponseStream* ApiServer::generatePalettesJson(AsyncWebServerRequest *request) {
  AsyncResponseStream *response = request->beginResponseStream("application/json");
  response->addHeader("type","palettes");
  DynamicJsonDocument doc(2048);
  for (uint8_t i = 0; i < effectManager->getNbPalettes(); i++) {
    doc[effectManager->getPalette(i)->getLabel()] = i;
  }
  String output = "";
  serializeJson(doc, output);
  response->print(output);
  return response;
}

void ApiServer::handleGet(AsyncWebServerRequest *request) {
  uint8_t paramsNr = request->params();
  for(uint8_t i = 0; i<paramsNr; i++){
    AsyncWebParameter* p = request->getParam(i);
    if (strcmp(p->name().c_str(), Params::PARAM_STATUS) == 0) {
      request->send(generateStatusJson(request));
      return;
    } else if (strcmp(p->name().c_str(), Params::PARAM_EFFECT_LIST) == 0) {
      request->send(generateEffectsJson(request));
      return;
    } else if (strcmp(p->name().c_str(), Params::PARAM_PALETTE_LIST) == 0) {
      request->send(generatePalettesJson(request));
      return;
    }
  }
  request->send(generateStatusJson(request));
}

void ApiServer::handlePost(AsyncWebServerRequest *request) {
  int paramsNr = request->params();
  for(int i = 0; i<paramsNr; i++){
    AsyncWebParameter* p = request->getParam(i);
    if (strcmp(p->name().c_str(), Params::PARAM_PAL) == 0) {
      effectManager->selectPalette(atoi(p->value().c_str()) % effectManager->getNbPalettes());
    } else if (strcmp(p->name().c_str(), Params::PARAM_EFFECT) == 0) {
      effectManager->selectEffect(atoi(p->value().c_str()) % effectManager->getNbEffects());
    } else if (strcmp(p->name().c_str(), Params::PARAM_BRIGHTNESS) == 0) {
      effectManager->setMasterBrightness(atoi(p->value().c_str()) & 255);
    } else if (strcmp(p->name().c_str(), Params::PARAM_COLOR_0) == 0) {
      effectManager->setPrimaryColor(atoi(p->value().c_str()));
    } else if (strcmp(p->name().c_str(), Params::PARAM_COLOR_1) == 0) {
      effectManager->setSecondaryColor(atoi(p->value().c_str()));
    } else if (strcmp(p->name().c_str(), Params::PARAM_COLOR_2) == 0) {
      effectManager->setTertiaryColor(atoi(p->value().c_str()));
    } else if (strcmp(p->name().c_str(), Params::PARAM_SPEED) == 0) {
      effectManager->setEffectSpeed(atoi(p->value().c_str()));
    } else if (strcmp(p->name().c_str(), Params::PARAM_INTENSITY) == 0) {
      effectManager->setEffectIntensity(atoi(p->value().c_str()));
    }
  }
  request->send(generateStatusJson(request));
}

void ApiServer::handleCalibrate(AsyncWebServerRequest *request) {
  inputManager->calibrate();
  request->send(request->beginResponse_P(200, "text/html", "success"));
}

void ApiServer::handleSetup(AsyncWebServerRequest *request) {
  uint8_t paramsNr = request->params();
  if (paramsNr > 0) {
    for(uint8_t i = 0; i<paramsNr; i++){
      AsyncWebParameter* p = request->getParam(i);
      if (strcmp(p->name().c_str(), "ssid") == 0) {
        EEPROMUtils::writeString(SSID_ADDR, p->value().c_str());
      } else if (strcmp(p->name().c_str(), "password") == 0) {
        EEPROMUtils::writeString(PASSWORD_ADDR, p->value().c_str());
      } else if (strcmp(p->name().c_str(), "ip_0") == 0) {
        EEPROMUtils::writeInt(IP_ADDR, atoi(p->value().c_str()));
      } else if (strcmp(p->name().c_str(), "ip_1") == 0) {
        EEPROMUtils::writeInt(IP_ADDR + 1, atoi(p->value().c_str()));
      } else if (strcmp(p->name().c_str(), "ip_2") == 0) {
        EEPROMUtils::writeInt(IP_ADDR + 2, atoi(p->value().c_str()));
      } else if (strcmp(p->name().c_str(), "ip_3") == 0) {
        EEPROMUtils::writeInt(IP_ADDR + 3, atoi(p->value().c_str()));
      } else if (strcmp(p->name().c_str(), "gateway_0") == 0) {
        EEPROMUtils::writeInt(GATE_ADDR, atoi(p->value().c_str()));
      } else if (strcmp(p->name().c_str(), "gateway_1") == 0) {
        EEPROMUtils::writeInt(GATE_ADDR + 1, atoi(p->value().c_str()));
      } else if (strcmp(p->name().c_str(), "gateway_2") == 0) {
        EEPROMUtils::writeInt(GATE_ADDR + 2, atoi(p->value().c_str()));
      } else if (strcmp(p->name().c_str(), "gateway_3") == 0) {
        EEPROMUtils::writeInt(GATE_ADDR + 3, atoi(p->value().c_str()));
      } else if (strcmp(p->name().c_str(), "mask_0") == 0) {
        EEPROMUtils::writeInt(MASK_ADDR, atoi(p->value().c_str()));
      } else if (strcmp(p->name().c_str(), "mask_1") == 0) {
        EEPROMUtils::writeInt(MASK_ADDR + 1, atoi(p->value().c_str()));
      } else if (strcmp(p->name().c_str(), "mask_2") == 0) {
        EEPROMUtils::writeInt(MASK_ADDR + 2, atoi(p->value().c_str()));
      } else if (strcmp(p->name().c_str(), "mask_3") == 0) {
        EEPROMUtils::writeInt(MASK_ADDR + 3, atoi(p->value().c_str()));
      }
    }
    EEPROMUtils::commit();
    AsyncWebServerResponse *response = request->beginResponse_P(200, "text/html", HTMLPages::WIFI_CONFIRMATION);
    request->send(response);
    resetFunc();
  } else {
    char buf[2048];
    sprintf(buf, HTMLPages::WIFI_FORM, net_ssid, "********", net_ip[0], net_ip[1], net_ip[2], net_ip[3], net_gateway[0], net_gateway[1], net_gateway[2], net_gateway[3], net_mask[0], net_mask[1], net_mask[2], net_mask[3]); 
    AsyncWebServerResponse *response = request->beginResponse_P(200, "text/html", buf);
    request->send(response);
  }
}
