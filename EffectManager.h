#pragma once

#define FASTLED_INTERRUPT_RETRY_COUNT 0
#define FASTLED_ESP8266_RAW_PIN_ORDER

#include <FastLED.h>
#include "Effect.h"
#include "Palette.h"
#include "Params.h"

class EffectManager {
  public:
      static Effect* effects[Params::NB_EFFECTS];
      static Palette* palettes[Params::NB_PALETTES];

  private:
    constexpr static const uint16_t DISABLED_PIXELS[] = {};
    CRGB leds[Params::NUM_PIXELS];
    uint8_t brightness;
    uint8_t palette;
    uint8_t effect;
    uint32_t lastFrame;
    uint32_t frametime;
    uint32_t primaryColor;
    uint32_t secondaryColor;
    uint32_t tertiaryColor;
    uint8_t effectSpeed;
    uint8_t effectIntensity;

  public:
    EffectManager(uint8_t fps, uint8_t brightness, uint32_t primaryColor, uint32_t secondaryColor, uint32_t tertiaryColor) {
      this->palette = 0;
      this->effect = 0;
      this->lastFrame = millis();
      this->frametime = 1000/fps;
      this->brightness = brightness;
      this->primaryColor = primaryColor;
      this->secondaryColor = secondaryColor;
      this->tertiaryColor = tertiaryColor;
      this->effectSpeed = 128;
      this->effectIntensity = 128;
      setPrimaryColor(primaryColor);
      setSecondaryColor(secondaryColor);
      setTertiaryColor(tertiaryColor);
    }
    
    virtual ~EffectManager() {}

    void init();
    void frame();
  
    uint8_t getPaletteId();
    Palette* getPalette();
    void selectPalette(uint8_t palette);
    uint8_t getEffectId();
    Effect* getEffect();
    void selectEffect(uint8_t effect);
    uint8_t getMasterBrightness();
    void setMasterBrightness(uint8_t brightness);
    uint32_t getPrimaryColor();
    void setPrimaryColor(uint32_t color);
    uint32_t getSecondaryColor();
    void setSecondaryColor(uint32_t color);
    uint32_t getTertiaryColor();
    void setTertiaryColor(uint32_t color);
    uint8_t getEffectSpeed();
    void setEffectSpeed(uint8_t spd);
    uint8_t getEffectIntensity();
    void setEffectIntensity(uint8_t intensity);
    uint8_t getNbPalettes();
    uint8_t getNbEffects();
    Palette* getPalette(String name);
    Palette* getPalette(uint8_t id);
    Effect* getEffect(String name);
    Effect* getEffect(uint8_t id);
};
