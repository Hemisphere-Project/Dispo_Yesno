
#include <FastLED.h>
#define LED_PIN 0
#define BRIGHTNESS  50
#define LED_TYPE    WS2811
#define COLOR_ORDER RGB
#define NUM_LEDS 150

CRGB leds[NUM_LEDS];

void setup() {

   	delay(2000);
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
    FastLED.setBrightness(  BRIGHTNESS );

    for (int i = 0; i < 76; i++) {
      leds[i] = CRGB(255,0,0);
    }
    for (int i = 76; i < NUM_LEDS; i++) {
      leds[i] = CRGB(255,255,255);
    }

    leds[0] = CRGB(0,0,255);
    leds[75] = CRGB(0,255,0);

    FastLED.show();

}


void loop() {

}
