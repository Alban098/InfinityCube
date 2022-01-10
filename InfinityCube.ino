#define FASTLED_INTERRUPT_RETRY_COUNT 0
#define FASTLED_ESP8266_RAW_PIN_ORDER

#include <stdlib.h>
#include <string>
#include "EffectManager.h"
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
    new Palette("Primary Color", CRGB(Params::DEFAULT_PRIMARY_COLOR)),
    new Palette("Dual Colors", CRGB(Params::DEFAULT_PRIMARY_COLOR), CRGB(Params::DEFAULT_SECONDARY_COLOR)),
    new Palette("Tri Colors", CRGB(Params::DEFAULT_PRIMARY_COLOR), CRGB(Params::DEFAULT_SECONDARY_COLOR), CRGB(Params::DEFAULT_TERTIARY_COLOR)),
    new Palette("Vintage 57", es_vintage_57_gp),
    new Palette("Vintage 01", es_vintage_01_gp),
    new Palette("Rivendell", es_rivendell_15_gp),
    new Palette("RGI", rgi_15_gp),
    new Palette("Retro2", retro2_16_gp),
    new Palette("Analogous", Analogous_1_gp),
    new Palette("Pink Splash", es_pinksplash_08_gp),
    new Palette("Ocean Breeze", es_ocean_breeze_036_gp),
    new Palette("Departure", departure_gp),
    new Palette("Landscape 64", es_landscape_64_gp),
    new Palette("Landscape 33", es_landscape_33_gp),
    new Palette("Rainbow Sherbet", rainbowsherbet_gp),
    new Palette("Hult 65", gr65_hult_gp),
    new Palette("Hult 64", gr64_hult_gp),
    new Palette("Dry Wet", GMT_drywet_gp),
    new Palette("IB15", ib15_gp),
    new Palette("Tertiary", Tertiary_01_gp),
    new Palette("Lava", lava_gp),
    new Palette("Fierce Ice", fierce_ice_gp),
    new Palette("Colorfull", Colorfull_gp),
    new Palette("Pink Purple", Pink_Purple_gp),
    new Palette("Sunset Real", Sunset_Real_gp),
    new Palette("Sunset Yellow", Sunset_Yellow_gp),
    new Palette("Beech", Beech_gp),
    new Palette("Another Sunset", Another_Sunset_gp),
    new Palette("Autumn", es_autumn_19_gp),
    new Palette("Black Blue Magenta White", BlacK_Blue_Magenta_White_gp),
    new Palette("Black Magenta Red", BlacK_Magenta_Red_gp),
    new Palette("Black Magenta Red Yellow", BlacK_Red_Magenta_Yellow_gp),
    new Palette("Blue Cyan Yellow", Blue_Cyan_Yellow_gp),
    new Palette("Temperature", temperature_gp),
    new Palette("Retro Clown", retro_clown_gp),
    new Palette("Candy", candy_gp),
    new Palette("Toxy Reaf", toxy_reaf_gp),
    new Palette("Fairy Reaf", fairy_reaf_gp),
    new Palette("Semi Blue", semi_blue_gp),
    new Palette("Pink Candy", pink_candy_gp),
    new Palette("Red Reaf", red_reaf_gp),
    new Palette("Aqua Flash", aqua_flash_gp),
    new Palette("Yellow Blue Hot", yelblu_hot_gp),
    new Palette("Lite Light", lite_light_gp),
    new Palette("Red Flash", red_flash_gp),
    new Palette("Blink Red", blink_red_gp),
    new Palette("Red Shift", red_shift_gp),
    new Palette("Red Tide", red_tide_gp),
    new Palette("Candy 2", candy2_gp)
};

EffectManager effectManager = EffectManager(Params::FPS, Params::BRIGHTNESS, Params::DEFAULT_PRIMARY_COLOR, Params::DEFAULT_SECONDARY_COLOR, Params::DEFAULT_TERTIARY_COLOR);
ApiServer server = ApiServer(&effectManager);

void setup() {
  Serial.begin(115200);
  effectManager.init(); 
  server.start();
}

void loop(){
  effectManager.frame();
}
