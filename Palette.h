#pragma once

#include <string>
#include <FastLED.h>

class Palette {
  private:
    String label;
    CRGBPalette16 palette;
    TBlendType blend_type;

  public:
    Palette(String label, TBlendType blend_type, const CRGB &c00) {
      this->label = label;
      this->blend_type = blend_type;
      this->palette = CRGBPalette16(c00); 
    }
    
    Palette(String label, TBlendType blend_type, const CRGB &c00, const CRGB &c01) {
      this->label = label;
      this->blend_type = blend_type;
      this->palette = CRGBPalette16(c00, c01); 
    }
    
    Palette(String label, TBlendType blend_type, const CRGB &c00, const CRGB &c01, const CRGB &c02) {
      this->label = label;
      this->blend_type = blend_type;
      this->palette = CRGBPalette16(c00, c01, c02); 
    }
    
    Palette(String label, TBlendType blend_type, CRGBPalette16 pal) {
      this->label = label;
      this->blend_type = blend_type;
      this->palette = pal;
    }

    virtual ~Palette() {}

    void setColor(uint32_t color0) { this->palette = CRGBPalette16(CRGB(color0)); }
    void setColor(uint32_t color0, uint32_t color1) { this->palette = CRGBPalette16(CRGB(color0), CRGB(color1)); }
    void setColor(uint32_t color0, uint32_t color1, uint32_t color2) { this->palette = CRGBPalette16(CRGB(color0), CRGB(color1), CRGB(color2)); }
    CRGB sample(uint8_t index, uint8_t brightness) { return ColorFromPalette(this->palette, index, brightness, this->blend_type); }
    String getLabel() { return label; }
};
