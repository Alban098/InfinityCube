#include "ScreenManager.h"

ScreenManager::ScreenManager(uint8_t fps, EffectManager* effectManager, Adafruit_SSD1306* display) {
  this->effectManager = effectManager;
  this->display = display;
  display->begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display->clearDisplay();
  display->setTextSize(1);
  display->setTextColor(SSD1306_WHITE);
  this->frametime = 1000/fps;
}

void ScreenManager::awake() {
  sleeping = false;
  sleep_cnt = Params::SLEEP_DELAY;
}

void ScreenManager::frame() {
  if (millis() - lastFrame > (unsigned long)frametime) {
    if (sleep_cnt <= 0) {
      sleeping = true;
      sleep_cnt = Params::SLEEP_DELAY;
      display->clearDisplay();
      display->display();
    }
    if (!sleeping) {
      display->clearDisplay();
      fill();
      sleep_cnt -= millis() - lastFrame;
      display->display();
    }
    lastFrame = millis();
  }
}

void ScreenManager::fill() {
  drawLayout();
  drawSlider(32, 17, effectManager->getMasterBrightness());
  drawSlider(32, 27, effectManager->getEffectSpeed());
  drawSlider(32, 37, effectManager->getEffectIntensity());
  drawIndicator((cursor_pos + 2) * 10);
  display->setCursor(32, 46);
  display->write(effectManager->getEffect()->getLabel().c_str());
  display->setCursor(32, 56);
  display->write(effectManager->getPalette()->getLabel().c_str());
}

void ScreenManager::drawSlider(uint8_t x, uint8_t y, uint8_t value) {
  uint8_t mapped = x + map(value, 0, 255, 0, 87);
  display->drawLine(x + 1, y + 2, x + 86, y + 2, SSD1306_WHITE);
  display->drawLine(x + 1, y + 4, x + 86, y + 4, SSD1306_WHITE);
  display->drawPixel(x, y + 3, SSD1306_WHITE);
  display->drawPixel(x + 87, y + 3, SSD1306_WHITE);
  display->drawLine(x,  y + 3, mapped, y + 3, SSD1306_WHITE);
  display->drawLine(mapped, y, mapped, y + 5, SSD1306_WHITE);
  display->drawLine(mapped - 1, y, mapped + 1, y, SSD1306_WHITE);
  display->drawLine(mapped - 1, y + 5, mapped + 1, y + 5, SSD1306_WHITE);
}

void ScreenManager::drawLayout() {
  display->setCursor(13, 4);
  display->write("Infinity Cube 1.0");
  display->setCursor(7, 16);
  display->write("Brt:");
  display->setCursor(7, 26);
  display->write("Spd:");
  display->setCursor(7, 36);
  display->write("Int:");
  display->setCursor(7, 46);
  display->write("Eff:");
  display->setCursor(7, 56);
  display->write("Pal:");
}

void ScreenManager::drawIndicator(uint8_t line) {
  display->drawLine(1, line, 4, line, SSD1306_WHITE);
  display->drawLine(123, line, 126, line, SSD1306_WHITE);
  display->drawPixel(2, line + 2, SSD1306_WHITE);
  display->drawPixel(2, line - 2, SSD1306_WHITE);
  display->drawPixel(3, line + 1, SSD1306_WHITE);
  display->drawPixel(3, line - 1, SSD1306_WHITE);
  display->drawPixel(125, line + 2, SSD1306_WHITE);
  display->drawPixel(125, line - 2, SSD1306_WHITE);
  display->drawPixel(124, line + 1, SSD1306_WHITE);
  display->drawPixel(124, line - 1, SSD1306_WHITE);
}
