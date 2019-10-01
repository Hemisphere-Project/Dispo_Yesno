
#include <FastLED.h>
#define LED_PIN 0
#define BRIGHTNESS  50
#define LED_TYPE    WS2811
#define COLOR_ORDER RGB
#define NUM_LEDS 151

CRGB leds[NUM_LEDS];

void setup() {

   	delay(2000);
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
    FastLED.setBrightness(  BRIGHTNESS );

    for (int i = 0; i < 75; i++) {
      leds[i] = CRGB(255,255,255);
    }
    for (int i = 75; i < 150; i++) {
      leds[i] = CRGB(255,0,0);
    }

    leds[150] = CRGB(0,255,0);

    FastLED.show();

}


void loop() {

  FastLED.show();
  delay(200);

}
