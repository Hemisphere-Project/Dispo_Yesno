#include <Arduino.h>
// #include "TM1637Display.h"
#include "src/TM1637/TM1637Display.h" // To use the lib files located inside the sketch folder, not in the arduino default folder

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

const uint8_t line1[] = { SEG_D,SEG_D,SEG_D,SEG_D,SEG_D,SEG_D };
const uint8_t line2[] = { SEG_G,SEG_G,SEG_G,SEG_G,SEG_G,SEG_G };
const uint8_t line3[] = { SEG_A,SEG_A,SEG_A,SEG_A,SEG_A,SEG_A };


TM1637Display display1(CLK1, DIO1, 100, NUMBEROFDIGITS);
TM1637Display display2(CLK2, DIO2, 100, NUMBEROFDIGITS);
int numToDisplay = 1;

void setup()
{
  display1.setBrightness(0x03);
  display2.setBrightness(0x03);
  Serial.begin(115200);
}

void loop()
{
  uint8_t blank[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
  display1.setSegments(blank);
  display2.setSegments(blank);

  showNumber_NEWORDER1(numToDisplay, display1);
  showNumber_NEWORDER2(numToDisplay, display2);


  // ANIM UP
  // **********************************************************************
  delay(1000);
  display1.setSegments(line1);
  display2.setSegments(line1);
  delay(50);
  display1.setSegments(line2);
  display2.setSegments(line2);
  delay(50);
  display1.setSegments(line3);
  display2.setSegments(line3);

  numToDisplay *= 10;
  if (numToDisplay>=999999) {
    numToDisplay = numToDisplay/1000000 + 1;
  }

}

void showNumber_NEWORDER1(int num, TM1637Display display){

  if(num >= 999999){ return; }

  int digit;
  uint8_t data[6];

  digit = num % 10;
  if(num!=0){
    data[0] = display1.encodeDigit(digit);
    display.setSegments(data, 1, 3);
  }
  num /= 10;
  digit = num % 10;
  if(num!=0){
    data[0] = display1.encodeDigit(digit);
    display.setSegments(data, 1, 4);
  }
  num /= 10;
  digit = num % 10;
  if(num!=0){
    data[0] = display1.encodeDigit(digit);
    display.setSegments(data, 1, 5);
  }
  num /= 10;
  digit = num % 10;
  if(num!=0){
    data[0] = display1.encodeDigit(digit);
    display.setSegments(data, 1, 0);
  }
  num /= 10;
  digit = num % 10;
  if(num!=0){
    data[0] = display1.encodeDigit(digit);
    display.setSegments(data, 1, 1);
  }
  num /= 10;
  digit = num % 10;
  if(num!=0){
    data[0] = display1.encodeDigit(digit);
    display.setSegments(data, 1, 2);
  }

}


void showNumber_NEWORDER2(int num, TM1637Display display){

  if(num >= 999999){ return; }

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

  Serial.print(strB);
  Serial.print("  ");
  Serial.println(newnum);

  display.showNumberDec(newnum, true);

}
