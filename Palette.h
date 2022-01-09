#pragma once

#include <string>

class Palette {
  private:
    String label;
    CRGBPalette16 palette;

  public:
    Palette(String label, const CRGB &c00) {
      this->label = label;
      this->palette = CRGBPalette16(c00); 
    }
    
    Palette(String label, const CRGB &c00, const CRGB &c01) {
      this->label = label;
      this->palette = CRGBPalette16(c00, c01); 
    }
    
    Palette(String label, const CRGB &c00, const CRGB &c01, const CRGB &c02) {
      this->label = label;
      this->palette = CRGBPalette16(c00, c01, c02); 
    }
    
    Palette(String label, CRGBPalette16 pal) {
      this->label = label;
      this->palette = pal;
    }
    
    virtual ~Palette() {}

    void setColor(uint32_t color0) { this->palette = CRGBPalette16(CRGB(color0)); }
    void setColor(uint32_t color0, uint32_t color1) { this->palette = CRGBPalette16(CRGB(color0), CRGB(color1)); }
    void setColor(uint32_t color0, uint32_t color1, uint32_t color2) { this->palette = CRGBPalette16(CRGB(color0), CRGB(color1), CRGB(color2)); }

    CRGBPalette16 getPalette() { return this->palette; }
    String getLabel() { return label; }
};
