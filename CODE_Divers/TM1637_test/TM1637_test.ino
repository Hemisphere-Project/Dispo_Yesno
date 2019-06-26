#include <Arduino.h>
#include "TM1637Display.h"

// USING TM1637 LIB - OPTIMIZED FOR 6 DIGITS
// https://github.com/gdampf/TM1637
// Forked from the original TM1637 Lib
// https://github.com/avishorp/TM1637

// Module connection pins (Digital Pins)
#define CLK1 26
#define DIO1 27
#define CLK2 32
#define DIO2 33
#define NUMBEROFDIGITS 6
#define NOKEYPAD


const uint8_t SEG_DONE[] = {
  SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,           // d
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,   // O
  SEG_C | SEG_E | SEG_G,                           // n
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G,           // E
  0,0
};
const uint8_t one_s[] = { SEG_D,0,0,0,0,0 };
const uint8_t two_s[] = { 0,SEG_D,0,0,0,0 };
const uint8_t three_s[] = { 0,0,SEG_D,0,0,0 };
const uint8_t four_s[] = { 0,0,0,SEG_D,0,0 };
const uint8_t five_s[] = { 0,0,0,0,SEG_D,0 };
const uint8_t six_s[] = { 0,0,0,0,0,SEG_D };

TM1637Display display1(CLK1, DIO1, 100, NUMBEROFDIGITS);
TM1637Display display2(CLK2, DIO2, 100, NUMBEROFDIGITS);

void setup()
{
}

void loop()
{
  uint8_t blank[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
  uint8_t all[] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
  display1.setBrightness(0x03);
  display2.setBrightness(0x03);

  display1.setSegments(blank);
  display2.setSegments(blank);
  delay(1000);
  display1.showNumberDec(123456, false);
  display2.showNumberDec(789012, false);
  delay(3000);

  display1.setSegments(one_s);
  display2.setSegments(one_s);
  delay(200);
  display1.setSegments(two_s);
  display2.setSegments(two_s);
  delay(200);
  display1.setSegments(three_s);
  display2.setSegments(three_s);
  delay(200);
  display1.setSegments(four_s);
  display2.setSegments(four_s);
  delay(200);
  display1.setSegments(five_s);
  display2.setSegments(five_s);
  delay(200);
  display1.setSegments(six_s);
  display2.setSegments(six_s);
  delay(200);



}
