#pragma once

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "EffectManager.h"
#include <Adafruit_SSD1306.h>


class ScreenManager {
  private:
    EffectManager* effectManager;
    Adafruit_SSD1306* display;
    uint8_t cursor_pos = 0;
    uint32_t lastFrame = 0;
    uint32_t frametime = 0;
    int32_t sleep_cnt = Params::SLEEP_DELAY;
    bool sleeping = false;
    
    void fill();
    void drawSlider(uint8_t x, uint8_t y, uint8_t value);
    void drawLayout();
    void drawIndicator(uint8_t line);
    
  public:
    ScreenManager(uint8_t fps, EffectManager* effectManager, Adafruit_SSD1306* display);
    ~ScreenManager() {}

    void frame();
    void awake();
    uint8_t getCursorPos() { return cursor_pos; }
    void setCursorPos(uint8_t cursor_pos) { this->cursor_pos = cursor_pos; } 
};
