#include "Effects.h"

void Rainbow::renderTo(CRGB* leds, uint32_t frameTime) {
  float speedFactor = effectManager->getEffectSpeed()/2.55;
  currentHue += 255 * frameTime / 50000.0 * speedFactor;
  if (currentHue > 255) currentHue -= 255;
  fill_rainbow(leds, Params::NUM_PIXELS, (uint8_t)currentHue, effectManager->getEffectIntensity()/10);
}

void Solid::renderTo(CRGB* leds, uint32_t frameTime) {
  for (int i = 0; i < Params::NUM_PIXELS; i++)
    leds[i] = ColorFromPalette(effectManager->getPalette()->getPalette(), 0xEF * i / Params::NUM_PIXELS, 255);    
}

void Strobe::renderTo(CRGB* leds, uint32_t frameTime) {
  float speedFactor = effectManager->getEffectSpeed()/2.55;
  strobe_cnt += frameTime / 100.0 * speedFactor;
  if (strobe_cnt > 10) {
    if (strobe_on) {
      for (int i = 0; i < Params::NUM_PIXELS; i++)
        leds[i] = ColorFromPalette(effectManager->getPalette()->getPalette(), 0xEF * i / Params::NUM_PIXELS, 255);     
    } else {
        fill_solid(leds, Params::NUM_PIXELS, CRGB::Black);
    }
    strobe_cnt = 0;
    strobe_on = !strobe_on;
  }
}

void StrobeRandom::renderTo(CRGB* leds, uint32_t frameTime) {
  float speedFactor = effectManager->getEffectSpeed()/2.55;
  strobe_cnt += frameTime / 100.0 * speedFactor;
  if (strobe_cnt > 10) {
    if (strobe_on) {
        fill_solid(leds, Params::NUM_PIXELS, CHSV(random8(),255,255));
    } else {
        fill_solid(leds, Params::NUM_PIXELS, CRGB::Black);
    }
    strobe_cnt = 0;
    strobe_on = !strobe_on;
  }
}

void Blink::renderTo(CRGB* leds, uint32_t frameTime) {
  float speedFactor = effectManager->getEffectSpeed()/2.55;
  blink_cnt += frameTime / 1500.0 * speedFactor;
  if (blink_cnt > 10) {
    if (snd) {
        fill_solid(leds, Params::NUM_PIXELS, CRGB(effectManager->getPrimaryColor()));
    } else {
        fill_solid(leds, Params::NUM_PIXELS, CRGB(effectManager->getSecondaryColor()));
    }
    blink_cnt = 0;
    snd = !snd;
  }
}

void BlinkPal::renderTo(CRGB* leds, uint32_t frameTime) {
  float speedFactor = effectManager->getEffectSpeed()/2.55;
  blink_cnt += frameTime / 1500.0 * speedFactor;
  if (blink_cnt > 10) {
    if (snd) {
      for (int i = 0; i < Params::NUM_PIXELS; i++)
        leds[i] = ColorFromPalette(effectManager->getPalette()->getPalette(), 0xEF * i / Params::NUM_PIXELS, 255);
    } else {
      fill_solid(leds, Params::NUM_PIXELS, CRGB(effectManager->getPrimaryColor()));
    }
    blink_cnt = 0;
    snd = !snd;
  }
}

void Breath::renderTo(CRGB* leds, uint32_t frameTime) {
  float speedFactor = effectManager->getEffectSpeed()/2.55;
  for (int i = 0; i < Params::NUM_PIXELS; i++)
    leds[i] = blend(CRGB(effectManager->getPrimaryColor()), CRGB(effectManager->getSecondaryColor()), sin8_C(millis() * frameTime/5000.0 * speedFactor));
}

void BreathPal::renderTo(CRGB* leds, uint32_t frameTime) {
  float speedFactor = effectManager->getEffectSpeed()/2.55;
  for (int i = 0; i < Params::NUM_PIXELS; i++)
    leds[i] = blend(CRGB(effectManager->getPrimaryColor()), ColorFromPalette(effectManager->getPalette()->getPalette(), 0xEF * i / Params::NUM_PIXELS), sin8_C(millis() * frameTime/5000.0 * speedFactor));
}

void Wipe::renderTo(CRGB* leds, uint32_t frameTime) {
  float speedFactor = effectManager->getEffectSpeed()/2.55;
  wipe_cnt += frameTime / 25.0 * speedFactor;
  if (wipe_cnt > 10) {
    if (current_size > Params::NUM_PIXELS) {
      current_size = 0;
      fill_solid(leds, Params::NUM_PIXELS, CRGB::Black);
    }
    current_size += wipe_cnt / 10;
    uint8_t s = min(Params::NUM_PIXELS, (uint16_t)(max(current_size, 0)));
    for (int i = 0; i < s; i++)
      leds[i] = ColorFromPalette(effectManager->getPalette()->getPalette(), 0xEF * i / Params::NUM_PIXELS, 255);
    wipe_cnt = 0;
  }
}

void WipeRandom::renderTo(CRGB* leds, uint32_t frameTime) {
  float speedFactor = effectManager->getEffectSpeed()/2.55;
  wipe_cnt += frameTime / 25.0 * speedFactor;
  if (wipe_cnt > 10) {
    current_size += wipe_cnt / 10;
    fill_solid(leds,  min(Params::NUM_PIXELS, (uint16_t)(max(current_size, 0))), current_color);
    wipe_cnt = 0;
    if (current_size > Params::NUM_PIXELS) {
      current_size = 0;
      current_color = CHSV(random8(), 255, 255);
    }
  }
}

void Sweep::renderTo(CRGB* leds, uint32_t frameTime) {
  float speedFactor = effectManager->getEffectSpeed()/2.55;
  sweep_cnt += frameTime / 25.0 * speedFactor;
  if (sweep_cnt > 10) {
    if (forward)current_size += sweep_cnt / 10;
    else current_size -= sweep_cnt / 10;
    fill_solid(leds, Params::NUM_PIXELS, CRGB::Black);
    uint8_t s = min(Params::NUM_PIXELS, (uint16_t)(max(current_size, 0)));
    for (int i = 0; i < s; i++)
      leds[i] = ColorFromPalette(effectManager->getPalette()->getPalette(), 0xEF * i / Params::NUM_PIXELS, 255);
    sweep_cnt = 0;
    Serial.println(current_size);
    if (current_size > Params::NUM_PIXELS || current_size < 0)
      forward = !forward;
  }
}

void SweepRandom::renderTo(CRGB* leds, uint32_t frameTime) {
  float speedFactor = effectManager->getEffectSpeed()/2.55;
  sweep_cnt += frameTime / 25.0 * speedFactor;
  if (sweep_cnt > 10) {
    if (forward) current_size += sweep_cnt / 10;
    else current_size -= sweep_cnt / 10;
    fill_solid(leds, Params::NUM_PIXELS, CRGB::Black);
    fill_solid(leds, min(Params::NUM_PIXELS, (uint16_t)(max(current_size, 0))), current_color);
    sweep_cnt = 0;
    if (current_size > Params::NUM_PIXELS || current_size < 0)
      forward = !forward;
    if (current_size < 0)
      current_color = CHSV(random8(), 255, 255);
  }
}

void Dynamic::renderTo(CRGB* leds, uint32_t frameTime) {
  float speedFactor = effectManager->getEffectSpeed()/2.55;
  dyn_cnt += frameTime / 1000.0 * speedFactor;
  if (dyn_cnt > 10) {
    fill_solid(leds, Params::NUM_PIXELS, CRGB::Black);
    for (int i = 0; i < effectManager->getEffectIntensity() / 255.0 * Params::NUM_PIXELS; i++)
      leds[random8(Params::NUM_PIXELS)] = CHSV(random8(), 255, 255);
    dyn_cnt = 0;
  }
}

void DynamicPal::renderTo(CRGB* leds, uint32_t frameTime) {
  float speedFactor = effectManager->getEffectSpeed()/2.55;
  dyn_cnt += frameTime / 1000.0 * speedFactor;
  if (dyn_cnt > 10) {
    fill_solid(leds, Params::NUM_PIXELS, CRGB::Black);
    for (int i = 0; i < effectManager->getEffectIntensity() / 255.0 * Params::NUM_PIXELS; i++) {
      int index = random16(Params::NUM_PIXELS);
      leds[index] = ColorFromPalette(effectManager->getPalette()->getPalette(), 0xEF * index / Params::NUM_PIXELS); 
    }
    dyn_cnt = 0;
  }
}

void ColorLoop::renderTo(CRGB* leds, uint32_t frameTime) {
  float speedFactor = effectManager->getEffectSpeed()/2.55;
  currentHue += 255 * frameTime / 50000.0 * speedFactor;
  if (currentHue > 255) currentHue -= 255;
  fill_solid(leds, Params::NUM_PIXELS, CHSV((uint8_t)currentHue, 255, 255));
}

void Scan::renderTo(CRGB* leds, uint32_t frameTime) {
  float speedFactor = effectManager->getEffectSpeed()/2.55;
  scan_cnt += frameTime / 40.0 * speedFactor;
  if (scan_cnt > 10) {
    current_pos += scan_cnt / 10;
    fill_solid(leds, Params::NUM_PIXELS, CRGB::Black);
    for (int i = 0; i < effectManager->getEffectIntensity() / 255.0 * (Params::NUM_PIXELS / 2); i++) {
      uint16_t index = (current_pos + i) % Params::NUM_PIXELS;
      leds[index] = ColorFromPalette(effectManager->getPalette()->getPalette(), 0xEF * index / Params::NUM_PIXELS); 
    }
    scan_cnt = 0;
    if (current_pos > Params::NUM_PIXELS)
      current_pos -= Params::NUM_PIXELS;
  }
}

void Running::renderTo(CRGB* leds, uint32_t frameTime) {
  float speedFactor = effectManager->getEffectSpeed()/2.55;
  current_phase += 255 * frameTime / 20000.0 * speedFactor;
  for (int i = 0; i < Params::NUM_PIXELS; i++)
  leds[i] = ColorFromPalette(effectManager->getPalette()->getPalette(), 0xEF * i / Params::NUM_PIXELS, sin8_C(i * 255.0/Params::NUM_PIXELS * effectManager->getEffectIntensity()/5 + current_phase)); 
}

void RunningSharp::renderTo(CRGB* leds, uint32_t frameTime) {
  float speedFactor = effectManager->getEffectSpeed()/2.55;
  current_phase += 255 * frameTime / 20000.0 * speedFactor;
  for (int i = 0; i < Params::NUM_PIXELS; i++) {
    uint8_t b = sin8_C(i * 255.0/Params::NUM_PIXELS * effectManager->getEffectIntensity()/5 + current_phase);
    if (b > 128) b = 255;
    else b = 0;
    leds[i] = ColorFromPalette(effectManager->getPalette()->getPalette(), 0xEF * i / Params::NUM_PIXELS, b); 
  }
}

void FireFlicker::renderTo(CRGB* leds, uint32_t frameTime) {
  for (int i = 0; i < Params::NUM_PIXELS; i++) {
    leds[i] = ColorFromPalette(effectManager->getPalette()->getPalette(), 0xEF * i / Params::NUM_PIXELS, 255 - random8(effectManager->getEffectIntensity()/2)); 
  }
}

void ColorTwinkle::renderTo(CRGB* leds, uint32_t frameTime) {
  float speedFactor = (effectManager->getEffectSpeed())/5.1;
  twinkle_cnt += frameTime / 50.0 * speedFactor + effectManager->getEffectIntensity() / 10;
  uint8_t cnt_threshold = 10 + random8(10);
  fadeToBlackBy(leds, Params::NUM_PIXELS, frameTime);
  if (twinkle_cnt > cnt_threshold ) {
    for (int i = 0; i < twinkle_cnt / cnt_threshold; i++)
      leds[random16(Params::NUM_PIXELS)] = CHSV(random8(), 255, 255);
    twinkle_cnt = 0;
  }
}

void PaletteTwinkle::renderTo(CRGB* leds, uint32_t frameTime) {
  float speedFactor = (effectManager->getEffectSpeed())/5.1;
  twinkle_cnt += frameTime / 50.0 * speedFactor + effectManager->getEffectIntensity() / 10;
  uint8_t cnt_threshold = 10 + random8(10);
  fadeToBlackBy(leds, Params::NUM_PIXELS, frameTime);
  if (twinkle_cnt > cnt_threshold ) {
    for (int i = 0; i < twinkle_cnt / cnt_threshold; i++) {
      uint16_t index = random16(Params::NUM_PIXELS);
      leds[index] = ColorFromPalette(effectManager->getPalette()->getPalette(), 0xEF * index / Params::NUM_PIXELS);
    }
    twinkle_cnt = 0;
  }
}
