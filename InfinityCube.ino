#define FASTLED_INTERRUPT_RETRY_COUNT 0
#define FASTLED_ESP8266_RAW_PIN_ORDER

#include <stdlib.h>
#include <string>
#include "EffectManager.h"
#include "ScreenManager.h"
#include "InputManager.h"
#include "Params.h"
#include "Effects.h"
#include "ApiServer.h"
#include <FastLED.h>
#include "Palettes.h"

#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB

Effect* EffectManager::effects[Params::NB_EFFECTS] = {
    new Solid(),
    new Rainbow(),
    new Strobe(),
    new StrobeRandom(),
    new Blink(),
    new BlinkPal(),
    new Breath(),
    new BreathPal(),
    new Wipe(),
    new WipeRandom(),
    new Sweep(),
    new SweepRandom(),
    new Dynamic(),
    new DynamicPal(),
    new ColorLoop(),
    new Scan(),
    new Running(),
    new RunningSharp(),
    new FireFlicker(),
    new ColorTwinkle(),
    new PaletteTwinkle()
};
        
Palette* EffectManager::palettes[Params::NB_PALETTES] = {
    new Palette("Primary Color", LINEARBLEND, CRGB(Params::DEFAULT_PRIMARY_COLOR)),
    new Palette("Dual Colors", LINEARBLEND, CRGB(Params::DEFAULT_PRIMARY_COLOR), CRGB(Params::DEFAULT_SECONDARY_COLOR)),
    new Palette("Tri Colors", LINEARBLEND, CRGB(Params::DEFAULT_PRIMARY_COLOR), CRGB(Params::DEFAULT_SECONDARY_COLOR), CRGB(Params::DEFAULT_TERTIARY_COLOR)),
    new Palette("Rainbow", LINEARBLEND, GMT_rainbow_gp),
    new Palette("Vintage 57", LINEARBLEND, es_vintage_57_gp),
    new Palette("Vintage 01", LINEARBLEND, es_vintage_01_gp),
    new Palette("Rivendell", LINEARBLEND, es_rivendell_15_gp),
    new Palette("RGI", LINEARBLEND, rgi_15_gp),
    new Palette("Retro2", LINEARBLEND, retro2_16_gp),
    new Palette("Analogous", LINEARBLEND, Analogous_1_gp),
    new Palette("Pink Splash", LINEARBLEND, es_pinksplash_08_gp),
    new Palette("Ocean Breeze", LINEARBLEND, es_ocean_breeze_036_gp),
    new Palette("Departure", NOBLEND, departure_gp),
    new Palette("Landscape 64", LINEARBLEND, es_landscape_64_gp),
    new Palette("Landscape 33", LINEARBLEND, es_landscape_33_gp),
    new Palette("Rainbow Sherbet", LINEARBLEND, rainbowsherbet_gp),
    new Palette("Hult 65", LINEARBLEND, gr65_hult_gp),
    new Palette("Hult 64", LINEARBLEND, gr64_hult_gp),
    new Palette("Dry Wet", LINEARBLEND, GMT_drywet_gp),
    new Palette("IB15", LINEARBLEND, ib15_gp),
    new Palette("Tertiary", LINEARBLEND, Tertiary_01_gp),
    new Palette("Lava", LINEARBLEND, lava_gp),
    new Palette("Fierce Ice", LINEARBLEND, fierce_ice_gp),
    new Palette("Colorfull", LINEARBLEND, Colorfull_gp),
    new Palette("Pink Purple", LINEARBLEND, Pink_Purple_gp),
    new Palette("Sunset Real", LINEARBLEND, Sunset_Real_gp),
    new Palette("Sunset Yellow", LINEARBLEND, Sunset_Yellow_gp),
    new Palette("Beech", LINEARBLEND, Beech_gp),
    new Palette("Another Sunset", LINEARBLEND, Another_Sunset_gp),
    new Palette("Autumn", LINEARBLEND, es_autumn_19_gp),
    new Palette("BBMW", LINEARBLEND, BlacK_Blue_Magenta_White_gp),
    new Palette("BMR", LINEARBLEND, BlacK_Magenta_Red_gp),
    new Palette("BMRY", LINEARBLEND, BlacK_Red_Magenta_Yellow_gp),
    new Palette("BCY", LINEARBLEND, Blue_Cyan_Yellow_gp),
    new Palette("Temperature", NOBLEND, temperature_gp),
    new Palette("Retro Clown", LINEARBLEND, retro_clown_gp),
    new Palette("Candy", LINEARBLEND, candy_gp),
    new Palette("Toxy Reaf", LINEARBLEND, toxy_reaf_gp),
    new Palette("Fairy Reaf", LINEARBLEND, fairy_reaf_gp),
    new Palette("Semi Blue", LINEARBLEND, semi_blue_gp),
    new Palette("Pink Candy", LINEARBLEND, pink_candy_gp),
    new Palette("Red Reaf", LINEARBLEND, red_reaf_gp),
    new Palette("Aqua Flash", LINEARBLEND, aqua_flash_gp),
    new Palette("Yellow Blue Hot", LINEARBLEND, yelblu_hot_gp),
    new Palette("Lite Light", LINEARBLEND, lite_light_gp),
    new Palette("Red Flash", LINEARBLEND, red_flash_gp),
    new Palette("Blink Red", LINEARBLEND, blink_red_gp),
    new Palette("Red Shift", LINEARBLEND, red_shift_gp),
    new Palette("Red Tide", LINEARBLEND, red_tide_gp),
    new Palette("Candy 2", LINEARBLEND, candy2_gp),
    new Palette("Spectral 8", NOBLEND, Spectral_08_gp),
    new Palette("Christmas", LINEARBLEND, bhw2_xmas_gp),
    new Palette("France", LINEARBLEND, bhw3_41_gp),
    new Palette("Christmas Candy", LINEARBLEND, christmas_candy_gp)
};

Adafruit_SSD1306 display(128, 64, &Wire, 4);

EffectManager effectManager = EffectManager(Params::FPS, Params::BRIGHTNESS, Params::DEFAULT_PRIMARY_COLOR, Params::DEFAULT_SECONDARY_COLOR, Params::DEFAULT_TERTIARY_COLOR);
ScreenManager screenManager = ScreenManager(30, &effectManager, &display);
InputManager inputManager = InputManager(30, &effectManager, &screenManager);
ApiServer server = ApiServer(&effectManager, &inputManager);

void setup() {
  Serial.begin(115200);
  effectManager.init(); 
  inputManager.calibrate();
  server.start();
}

void loop(){
  inputManager.frame();
  screenManager.frame();
  effectManager.frame();
}
