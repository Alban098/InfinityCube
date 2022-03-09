#pragma once

#define FASTLED_INTERRUPT_RETRY_COUNT 0
#define FASTLED_ESP8266_RAW_PIN_ORDER

#include "EffectManager.h"
#include "Palette.h"
#include "Effect.h"
#include "Params.h"
#include <FastLED.h>

class EffectManager;

class Rainbow : public Effect {
   private:
    float currentHue = 0.0;

   public:
    Rainbow() : Effect() { this->label = "Rainbow"; }
    ~Rainbow() {}

    void renderTo(CRGB* leds, uint32_t frameTime) override;
};

class Rainbow3DV : public Effect {
   private:
    float currentHue = 0.0;

   public:
    Rainbow3DV() : Effect() { this->label = "Rainbow 3D V."; }
    ~Rainbow3DV() {}

    void renderTo(CRGB* leds, uint32_t frameTime) override;
};

class Rainbow3DH : public Effect {
   private:
    float currentHue = 0.0;

   public:
    Rainbow3DH() : Effect() { this->label = "Rainbow 3D H."; }
    ~Rainbow3DH() {}

    void renderTo(CRGB* leds, uint32_t frameTime) override;
};


class Solid : public Effect {
   public:
    Solid() : Effect() { this->label = "Solid"; }
    ~Solid() {}
    
   
    void renderTo(CRGB* leds, uint32_t frameTime) override;
};

class Strobe : public Effect {
  private:
    float strobe_cnt = 0;
    bool strobe_on = false;

  public:
    Strobe() : Effect() { this->label = "Strobe"; }
    ~Strobe() {}
  
    void renderTo(CRGB* leds, uint32_t frameTime) override;
};


class StrobeRandom : public Effect {
  private:
    float strobe_cnt = 0;
    bool strobe_on = false;

  public:
    StrobeRandom() : Effect() { this->label = "Strobe Random"; }
    ~StrobeRandom() {}
  
    void renderTo(CRGB* leds, uint32_t frameTime) override;
};

class Blink : public Effect {
  private:
    float blink_cnt = 0;
    bool snd = false;

  public:
    Blink() : Effect() { this->label = "Blink"; }
    ~Blink() {}
  
    void renderTo(CRGB* leds, uint32_t frameTime) override;
};

class BlinkPal : public Effect {
  private:
    float blink_cnt = 0;
    bool snd = false;

  public:
    BlinkPal() : Effect() { this->label = "Blink Palette"; }
    ~BlinkPal() {}
  
    void renderTo(CRGB* leds, uint32_t frameTime) override;
};

class Breath : public Effect {
  public:
    Breath() : Effect() { this->label = "Breath"; }
    ~Breath() {}
  
    void renderTo(CRGB* leds, uint32_t frameTime) override;
};

class BreathPal : public Effect {
  public:
    BreathPal() : Effect() { this->label = "Breath Palette"; }
    ~BreathPal() {}
  
    void renderTo(CRGB* leds, uint32_t frameTime) override;
};

class Wipe : public Effect {
  private:
    int current_size = 0;
    float wipe_cnt = 0;
    
  public:
    Wipe() : Effect() { this->label = "Wipe"; }
    ~Wipe() {}
  
    void renderTo(CRGB* leds, uint32_t frameTime) override;
};

class WipeRandom : public Effect {
  private:
    int current_size = 0;
    float wipe_cnt = 0;
    CHSV current_color = CHSV(random8(), 255, 255);
    
  public:
    WipeRandom() : Effect() { this->label = "Wipe Random"; }
    ~WipeRandom() {}
  
    void renderTo(CRGB* leds, uint32_t frameTime) override;
};

class Sweep : public Effect {
  private:
    int current_size = 0;
    float sweep_cnt = 0;
    bool forward = true;
    
  public:
    Sweep() : Effect() { this->label = "Sweep"; }
    ~Sweep() {}
  
    void renderTo(CRGB* leds, uint32_t frameTime) override;
};

class SweepRandom : public Effect {
  private:
    int current_size = 0;
    float sweep_cnt = 0;
    bool forward = true;
    CHSV current_color = CHSV(random8(), 255, 255);
    
  public:
    SweepRandom() : Effect() { this->label = "Sweep Random"; }
    ~SweepRandom() {}
  
    void renderTo(CRGB* leds, uint32_t frameTime) override;
};

class Dynamic : public Effect {
  private:
    float dyn_cnt = 0;
    
  public:
    Dynamic() : Effect() { this->label = "Dynamic"; }
    ~Dynamic() {}
  
    void renderTo(CRGB* leds, uint32_t frameTime) override;
};

class DynamicPal : public Effect {
  private:
    float dyn_cnt = 0;
    
  public:
    DynamicPal() : Effect() { this->label = "Dynamic Palette"; }
    ~DynamicPal() {}
  
    void renderTo(CRGB* leds, uint32_t frameTime) override;
};

class ColorLoop : public Effect {
   private:
    float currentHue = 0.0;

   public:
    ColorLoop() : Effect() { this->label = "ColorLoop"; }
    ~ColorLoop() {}

    void renderTo(CRGB* leds, uint32_t frameTime) override;
};

class Scan : public Effect {
  private:
    int current_pos = 0;
    float scan_cnt = 0;
    
  public:
    Scan() : Effect() { this->label = "Scan"; }
    ~Scan() {}
  
    void renderTo(CRGB* leds, uint32_t frameTime) override;
};

class Running : public Effect {
  private:
    float current_phase = 0;
  public:
    Running() : Effect() { this->label = "Running"; }
    ~Running() {}
  
    void renderTo(CRGB* leds, uint32_t frameTime) override;
};

class RunningSharp : public Effect {
  private:
    float current_phase = 0;
  public:
    RunningSharp() : Effect() { this->label = "Running Sharp"; }
    ~RunningSharp() {}
  
    void renderTo(CRGB* leds, uint32_t frameTime) override;
};

class FireFlicker : public Effect {
  public:
    FireFlicker() : Effect() { this->label = "Fire Flicker"; }
    ~FireFlicker() {}
  
    void renderTo(CRGB* leds, uint32_t frameTime) override;
};

class ColorTwinkle : public Effect {
  private:
    float twinkle_cnt = 0;
    
  public:
    ColorTwinkle() : Effect() { this->label = "Color Twinkle"; }
    ~ColorTwinkle() {}
  
    void renderTo(CRGB* leds, uint32_t frameTime) override;
};

class PaletteTwinkle : public Effect {
  private:
    float twinkle_cnt = 0;
    
  public:
    PaletteTwinkle() : Effect() { this->label = "Palette Twinkle"; }
    ~PaletteTwinkle() {}
  
    void renderTo(CRGB* leds, uint32_t frameTime) override;
};

class Scan3DH : public Effect {
  private:
    float plane = 0;
    int8_t dir = 1;
    
  public:
    Scan3DH() : Effect() { this->label = "Scan 3D H."; }
    ~Scan3DH() {}
  
    void renderTo(CRGB* leds, uint32_t frameTime) override;
};

class Scan3DV : public Effect {
  private:
    float plane = 0;
    int8_t dir = 1;
    
  public:
    Scan3DV() : Effect() { this->label = "Scan 3D V."; }
    ~Scan3DV() {}
  
    void renderTo(CRGB* leds, uint32_t frameTime) override;
};

class PalScan3DH : public Effect {
  private:
    float plane = 0;
    int8_t dir = 1;
    
  public:
    PalScan3DH() : Effect() { this->label = "Scan 3D Pal H."; }
    ~PalScan3DH() {}
  
    void renderTo(CRGB* leds, uint32_t frameTime) override;
};

class PalScan3DV : public Effect {
  private:
    float plane = 0;
    int8_t dir = 1;
    
  public:
    PalScan3DV() : Effect() { this->label = "Scan 3D Pal V."; }
    ~PalScan3DV() {}
  
    void renderTo(CRGB* leds, uint32_t frameTime) override;
};

class Sin3D : public Effect {
  private:
    float t = 0;
    
  public:
    Sin3D() : Effect() { this->label = "Sin 3D"; }
    ~Sin3D() {}
  
    void renderTo(CRGB* leds, uint32_t frameTime) override;
};

class PalSin3D : public Effect {
  private:
    float t = 0;
    
  public:
    PalSin3D() : Effect() { this->label = "Pal Sin 3D"; }
    ~PalSin3D() {}
  
    void renderTo(CRGB* leds, uint32_t frameTime) override;
};
