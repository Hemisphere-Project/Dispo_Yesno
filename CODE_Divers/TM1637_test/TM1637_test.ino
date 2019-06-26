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
  display1.setBrightness(0x03);
  display2.setBrightness(0x03);

  Serial.begin(115200);
}

void loop()
{
  // uint8_t blank[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
  // uint8_t all[] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };

  // display2.setBrightness(0x03);
  //
  // display1.setSegments(blank);
  // display2.setSegments(blank);
  // delay(1000);

  display1.showNumberDec(12345, false);


  // ADJUST ORDER
  int num = 123456;
  // if(num > 999999){
  //   SAY ITS TOO MUCH
  // }

  String strA = String(num);
  while (strA.length()<6) { strA = "0"+strA; }
  String strB="000000";
  strB.setCharAt(0,strA.charAt(2));
  strB.setCharAt(1,strA.charAt(1));
  strB.setCharAt(2,strA.charAt(0));
  strB.setCharAt(3,strA.charAt(5));
  strB.setCharAt(4,strA.charAt(4));
  strB.setCharAt(5,strA.charAt(3));
  int newnum = atoi(strB.c_str());


  display2.showNumberDec(newnum, false);

  Serial.print(strA);
  Serial.print(".   .");
  Serial.print(strB);
  Serial.print(".   .");
  Serial.println(newnum);




}
