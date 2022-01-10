#include "EffectManager.h"

void EffectManager::init() {
  FastLED.addLeds<WS2812B, Params::LED_PIN, GRB>(leds, Params::NUM_PIXELS).setCorrection(TypicalLEDStrip);
  setMasterBrightness(brightness);
  for (int i = 0; i < getNbEffects(); i++)
    effects[i]->linkManager(this);
}

void EffectManager::frame() {
  if (brightness > 0) {
    if (millis() - lastFrame > (unsigned long)frametime) {
      effects[effect]->renderTo(leds, frametime);
      for (int i = 0; i < sizeof DISABLED_PIXELS / sizeof DISABLED_PIXELS[0]; i++)
        leds[DISABLED_PIXELS[i]] = CRGB::Black;
      FastLED.show();
      lastFrame = millis();
    }
  }
}

uint8_t EffectManager::getPaletteId() { 
  return this->palette;
}

Palette* EffectManager::getPalette() {
  return palettes[palette];
}

void EffectManager::selectPalette(uint8_t palette) { 
  this->palette = min(Params::NB_PALETTES, max(palette, (uint8_t)0));
}

uint8_t EffectManager::getEffectId() { 
  return this->effect;
}

Effect* EffectManager::getEffect() {
  return effects[effect];
}

void EffectManager::selectEffect(uint8_t effect) { 
  this->effect = min(Params::NB_EFFECTS, max(effect, (uint8_t)0));
}

uint8_t EffectManager::getMasterBrightness() {
  return this->brightness;
}

void EffectManager::setMasterBrightness(uint8_t brightness) {
  this->brightness = min((uint8_t)255, max(brightness, (uint8_t)0));
  if (this->brightness == 0) {
    fill_solid(leds, Params::NUM_PIXELS, CRGB::Black);
    FastLED.show();
  }
  FastLED.setBrightness(this->brightness / 255.0 * Params::MAX_BRIGHTNESS);
}

uint32_t EffectManager::getPrimaryColor() {
  return this->primaryColor;
}

void EffectManager::setPrimaryColor(uint32_t color) {
  this->primaryColor = min((uint32_t)0xFFFFFF, max(color, (uint32_t)0));
  getPalette("Primary Color")->setColor(primaryColor);
  getPalette("Dual Colors")->setColor(primaryColor, secondaryColor);
  getPalette("Tri Colors")->setColor(primaryColor, secondaryColor, tertiaryColor);
}

uint32_t EffectManager::getSecondaryColor() {
  return this->secondaryColor;
}

void EffectManager::setSecondaryColor(uint32_t color) {
  this->secondaryColor = min((uint32_t)0xFFFFFF, max(color, (uint32_t)0));
  getPalette("Dual Colors")->setColor(primaryColor, secondaryColor);
  getPalette("Tri Colors")->setColor(primaryColor, secondaryColor, tertiaryColor);
}

uint32_t EffectManager::getTertiaryColor() {
  return this->tertiaryColor;
}

void EffectManager::setTertiaryColor(uint32_t color) {
  this->tertiaryColor = min((uint32_t)0xFFFFFF, max(color, (uint32_t)0));
  getPalette("Tri Colors")->setColor(primaryColor, secondaryColor, tertiaryColor);
}

uint8_t EffectManager::getEffectSpeed() {
  return this->effectSpeed;
}

void EffectManager::setEffectSpeed(uint8_t spd) {
  this->effectSpeed = min((uint8_t)255, max(spd, (uint8_t)0));;
}

uint8_t EffectManager::getEffectIntensity() {
  return this->effectIntensity;
}

void EffectManager::setEffectIntensity(uint8_t intensity) {
  this->effectIntensity = min((uint8_t)255, max(intensity, (uint8_t)0));;
}

uint8_t EffectManager::getNbPalettes() {
  return Params::NB_PALETTES;
}

uint8_t EffectManager::getNbEffects() {
  return Params::NB_EFFECTS;
}

Palette* EffectManager::getPalette(String name) {
  for (int i = 0; i < getNbPalettes(); i++) {
    if (strcmp(palettes[i]->getLabel().c_str(), name.c_str()) == 0)
      return palettes[i]; 
  }
  return new Palette("EMPTY", CRGB::Black);
}

Palette* EffectManager::getPalette(uint8_t id) {
  return palettes[id]; 
}

Effect* EffectManager::getEffect(uint8_t id) {  
  return effects[id]; 
}
