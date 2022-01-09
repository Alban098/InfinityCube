#pragma once

class EffectManager;

class Effect {
  protected:
    String label;
    EffectManager* effectManager;

   public:
    Effect() { this->effectManager = effectManager; }
    virtual ~Effect() {}
        
    virtual void renderTo(CRGB* leds, uint32_t frameTime) {}
  
    String getLabel() { return label; }
    void linkManager(EffectManager* manager) { this->effectManager = manager; }
};
