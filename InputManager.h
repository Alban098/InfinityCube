#pragma once

#include "EffectManager.h"

class InputManager {
  private:
    EffectManager* effectManager;
    uint32_t lastFrame = 0;
    uint32_t frametime = 0;
    uint16_t null_pt = 2048;
    bool is_joystick_free = true;
    bool is_button_free = true;
    /*
    0 -> Brightness
    1 -> Effect speed
    2 -> Effect intensity
    3 -> Effects
    4 -> Palettes
    */
    uint8_t selected_mode = 0;

    uint16_t readX();
    bool readSW();
    
  public:
    InputManager(uint8_t fps, EffectManager* effectManager);
    ~InputManager() {}
  
    void frame();
    void calibrate();
};
