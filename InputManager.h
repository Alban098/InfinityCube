#pragma once

#include "EffectManager.h"
#include "ScreenManager.h"

class InputManager {
  private:
    EffectManager* effectManager;
    ScreenManager* screenManager;
    uint32_t lastFrame = 0;
    uint32_t frametime = 0;
    bool is_joystick_free = true;
    bool is_button_free = true;

    uint16_t readX();
    bool readSW();
    
  public:
    InputManager(uint8_t fps, EffectManager* effectManager, ScreenManager* screenManager);
    ~InputManager() {}
  
    void frame();
};
