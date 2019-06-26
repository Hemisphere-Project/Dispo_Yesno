
#include <FastLED.h>
#define LED_PIN 0
#define BRIGHTNESS  20
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS 10

CRGB leds[NUM_LEDS];

void setup() {

   	delay(2000);
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
    FastLED.setBrightness(  BRIGHTNESS );

    for (int i = 0; i < 5; i++) {
      leds[i] = CRGB(255,255,255);
    }
    for (int i = 5; i < NUM_LEDS; i++) {
      leds[i] = CRGB(255,0,0);
    }

    FastLED.show();

}


void loop() {

}
