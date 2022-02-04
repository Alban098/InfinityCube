#include "InputManager.h"

InputManager::InputManager(uint8_t fps, EffectManager* effectManager, ScreenManager* screenManager) { 
  this->effectManager = effectManager;
  this->screenManager = screenManager;
  this->frametime = 1000/fps;
  pinMode(Params::JOY_SW_PIN, INPUT);
  pinMode(A0, INPUT);
}

void InputManager::frame() {
  if (millis() - lastFrame > (unsigned long)frametime) {
    uint16_t x = readX();
    bool sw = readSW();

    uint8_t tmp, delta;

    if (sw && is_button_free) {
      screenManager->setCursorPos((screenManager->getCursorPos() + 1) % 5);
      screenManager->awake();
      is_button_free = false;
    } else if (!sw) {
      is_button_free = true;
    }
    
    switch(screenManager->getCursorPos()) {
      case 0:
        if (x > 550) {
          delta = map(x - 550, 0, 474, 0, 7);
          Serial.println(delta);
          tmp = min(effectManager->getMasterBrightness() + delta, 255);
          effectManager->setMasterBrightness(tmp);
          screenManager->awake();
          is_joystick_free = false;
        } else if (x < 474) {
          delta = map(x, 0, 474, 7, 0);
          tmp = max(effectManager->getMasterBrightness() - delta, 0);
          effectManager->setMasterBrightness(tmp);
          screenManager->awake();
          is_joystick_free = false;
        } else if (x > 480 && x < 544 && !is_joystick_free) {
          is_joystick_free = true;
        }
        break;
      case 1:
        if (x > 550) {
          delta = map(x - 550, 0, 474, 0, 7);
          tmp = min(effectManager->getEffectSpeed() + delta, 255);
          effectManager->setEffectSpeed(tmp);
          screenManager->awake();
          is_joystick_free = false;
        } else if (x < 474) {
          delta = map(x, 0, 474, 7, 0);
          tmp = max(effectManager->getEffectSpeed() - delta, 0);
          effectManager->setEffectSpeed(tmp);
          screenManager->awake();
          is_joystick_free = false;
        } else if (x > 480 && x < 544 && !is_joystick_free) {
          is_joystick_free = true;
        }
        break;
      case 2:
        if (x > 550) {
          delta = map(x - 550, 0, 474, 0, 7);
          tmp = min(effectManager->getEffectIntensity() + delta, 255);
          effectManager->setEffectIntensity(tmp);
          screenManager->awake();
          is_joystick_free = false;
        } else if (x < 474) {
          delta = map(x, 0, 474, 7, 0);
          tmp = max(effectManager->getEffectIntensity() - delta, 0);
          effectManager->setEffectIntensity(tmp);
          screenManager->awake();
          is_joystick_free = false;
        } else if (x > 480 && x < 544 && !is_joystick_free) {
          is_joystick_free = true;
        }
        break;
      case 3:
        if (x > 1000 && is_joystick_free) {
          tmp = (effectManager->getEffectId() + 1) % (Params::NB_EFFECTS - 1);
          effectManager->selectEffect(tmp);
          screenManager->awake();
          is_joystick_free = false;
        } else if (x < 24 && is_joystick_free) {
          tmp = (effectManager->getEffectId() - 1) % (Params::NB_EFFECTS - 1);
          effectManager->selectEffect(tmp);
          screenManager->awake();
          is_joystick_free = false;
        } else if (x > 480 && x < 544 && !is_joystick_free) {
          is_joystick_free = true;
        }
        break;
      case 4:
        if (x > 1000 && is_joystick_free) {
          tmp = (effectManager->getPaletteId() + 1) % (Params::NB_PALETTES - 1);
          effectManager->selectPalette(tmp);
          screenManager->awake();
          is_joystick_free = false;
        } else if (x < 24 && is_joystick_free) {
          tmp = (effectManager->getPaletteId() - 1) % (Params::NB_PALETTES - 1);
          effectManager->selectPalette(tmp);
          screenManager->awake();
          is_joystick_free = false;
        } else if (x > 480 && x < 544 && !is_joystick_free) {
          is_joystick_free = true;
        }
        break;
    }
    lastFrame = millis();
    
  }
}

uint16_t InputManager::readX() {
  return analogRead(A0);
}

bool InputManager::readSW() {
  return digitalRead(Params::JOY_SW_PIN) == LOW;
}
