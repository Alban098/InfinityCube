#include "ApiServer.h"

#define SSID_ADDR       64
#define PASSWORD_ADDR   96
#define IP_ADDR         160
#define GATE_ADDR       164
#define MASK_ADDR       168

ApiServer::ApiServer(EffectManager* manager) {
  this->effectManager = manager;
}

void ApiServer::start() {
  EEPROMUtils::init();
  
  uint8_t i[4] = {0, 0, 0, 0};
  uint8_t g[4] = {0, 0, 0, 0};
  uint8_t m[4] = {0, 0, 0, 0};
  EEPROMUtils::readIP(IP_ADDR, i);
  delay(50);
  EEPROMUtils::readIP(GATE_ADDR, g);
  delay(50);
  EEPROMUtils::readIP(MASK_ADDR, m);
  delay(50);
  IPAddress local_IP = IPAddress(i[0], i[1], i[2], i[3]);
  IPAddress gateway = IPAddress(g[0], g[1], g[2], g[3]);
  IPAddress mask = IPAddress(m[0], m[1], m[2], m[3]);

  if (!WiFi.config(local_IP, gateway, mask, IPAddress(8, 8, 8, 8), IPAddress(8, 8, 4, 4)))
    Serial.println("Static Addressing Failed to configure");
  
  char netw[64];
  EEPROMUtils::readString(SSID_ADDR, netw);
  delay(50);
  char pass[64];
  EEPROMUtils::readString(PASSWORD_ADDR, pass);
  Serial.println(netw);
  Serial.println(pass);
  Serial.println(local_IP);
  Serial.println(gateway);
  Serial.println(mask);

  WiFi.begin(netw, pass);
  uint8_t connection_attempts = 0;
  while (WiFi.status() != WL_CONNECTED && connection_attempts < Params::MAX_WIFI_ATTEMPTS) {
    delay(500);
    Serial.print(".");
    connection_attempts++;
  }

  if (WiFi.status() != WL_CONNECTED) {
    WiFi.disconnect();
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
   
  server.on("/api", HTTP_POST, postHandler);
  server.on("/api", HTTP_GET, getHandler);
  server.on("/setup", HTTP_GET, setupHandler);
  
  server.begin();
}

AsyncResponseStream* ApiServer::generateStatusJson(AsyncWebServerRequest *request) {
  AsyncResponseStream *response = request->beginResponseStream("application/json");
  response->addHeader("type","status");
  DynamicJsonDocument doc(2048);
  doc[Params::PARAM_EFFECT] = effectManager->getEffectId();
  doc[Params::PARAM_COLOR_0] = effectManager->getPrimaryColor();
  doc[Params::PARAM_COLOR_1] = effectManager->getSecondaryColor();
  doc[Params::PARAM_COLOR_2] = effectManager->getTertiaryColor();
  doc[Params::PARAM_SPEED] = effectManager->getEffectSpeed();
  doc[Params::PARAM_INTENSITY] = effectManager->getEffectIntensity();
  doc[Params::PARAM_BRIGHTNESS] = effectManager->getMasterBrightness();
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
  for(uint8_t i=0; i<paramsNr; i++){
    AsyncWebParameter* p = request->getParam(i);
    Serial.println(p->name());
    if (strcmp(p->name().c_str(), Params::PARAM_STATUS) == 0) {
      request->send(generateStatusJson(request));
      break;
    } else if (strcmp(p->name().c_str(), Params::PARAM_EFFECT_LIST) == 0) {
      request->send(generateEffectsJson(request));
      break;
    } else if (strcmp(p->name().c_str(), Params::PARAM_PALETTE_LIST) == 0) {
      request->send(generatePalettesJson(request));
      break;
    }
  }
  request->send(request->beginResponse_P(200, "text/html", "coucou"));
}

void ApiServer::handlePost(AsyncWebServerRequest *request) {
  int paramsNr = request->params();
  for(int i=0; i<paramsNr; i++){
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

void ApiServer::handleSetup(AsyncWebServerRequest *request) {
  uint8_t paramsNr = request->params();
  if (paramsNr > 0) {
    for(uint8_t i=0; i<paramsNr; i++){
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
    AsyncWebServerResponse *response = request->beginResponse_P(200, "text/html", HTMLPages::WIFI_FORM);
    request->send(response);
  }
}
