#pragma once
#include <stdint.h>

class Params {
  public:
    static const uint16_t NUM_PIXELS        = 190;
    static const uint8_t LED_PIN            = 4;
    static const uint8_t NB_EFFECTS         = 21;
    static const uint8_t NB_PALETTES        = 49;
    static const uint8_t FPS                = 60;
    static const uint8_t BRIGHTNESS         = 0;
    static const uint8_t MAX_WIFI_ATTEMPTS  = 25;
    static const uint8_t MAX_BRIGHTNESS     = 255;
    
    static const uint32_t DEFAULT_PRIMARY_COLOR    = 0xFF0000;
    static const uint32_t DEFAULT_SECONDARY_COLOR  = 0x00FF00;
    static const uint32_t DEFAULT_TERTIARY_COLOR   = 0x0000FF;

    static const char* PARAM_PAL;
    static const char* PARAM_EFFECT;
    static const char* PARAM_COLOR_0;
    static const char* PARAM_COLOR_1;
    static const char* PARAM_COLOR_2;
    static const char* PARAM_SPEED;     
    static const char* PARAM_INTENSITY;         
    static const char* PARAM_BRIGHTNESS;
    static const char* PARAM_NET_SSID;
    static const char* PARAM_NET_PASS;
    static const char* PARAM_NET_IP;
    static const char* PARAM_NET_GATEWAY;
    static const char* PARAM_NET_MASK;

    static const char* PARAM_STATUS;
    static const char* PARAM_EFFECT_LIST;
    static const char* PARAM_PALETTE_LIST;
};
