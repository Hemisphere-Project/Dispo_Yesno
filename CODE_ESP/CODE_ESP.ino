// LEDS
#include <FastLED.h>
// SD
#include "FS.h"
#include "SD.h"
#include "SPI.h"
// EEPROM
#include <Preferences.h>
// TM1637 DISPLAY
#include <Arduino.h>
#include "src/TM1637/TM1637Display.h"


#define NUM_LEDS 150
#define LED_PIN 0
#define BRIGHTNESS  50
#define LED_TYPE    WS2811
#define COLOR_ORDER RGB
CRGB leds[NUM_LEDS];


// #define YESPIN        4
// #define NOPIN         16
#define NOPIN         4
#define YESPIN        16
#define RESETPIN      17
// Btns States
int yesState, noState, resetState = 0;
// Yes & No
unsigned long Taction, Tnow = 0;
unsigned long eventDuration = 5000;
bool listenToYesNo = true;
// Reset
unsigned long Treset = 0;
unsigned long resetDelay = 2000;
unsigned long resetDuration = 10000;
bool pressingReset = false;
bool resetting = false;


// ANIMATE
char *justVoted = "none";
bool acting = false;
unsigned long actionFrame = 0;
unsigned long framePeriod = 200;
unsigned long TlastFrame = 0;
CRGB voteColor;
CRGB noColor = CRGB(255,0,0);
CRGB yesColor = CRGB(255,255,255);
int roadNumber = 0;
int roadsNo[ 4 ][ 3 ] = { { 9,18, 38 }, { 18, 40, 44 }, { 21, 37, 45 }, { 34, 47, 73 } };
int roadsYes[ 4 ][ 3 ] = { { 9, 84, 129 }, { 83, 112, 140 }, { 82, 98, 113 }, { 85, 95, 120 } };
int proportionArray[150];
int mappingOffset = 74; // MAPPING: NUM PIXELS BEFORE DATA GAP

// MEMORY
Preferences preferences;
char readBuffer[100];
int yes_NUM, no_NUM;
// Backups timings
unsigned long TlastBackup_SD, TlastBackup_EEPROM = 0;
// unsigned long backupPeriod_SD = 20000;
// unsigned long backupPeriod_EEPROM = 60000;
unsigned long backupPeriod_SD = 900000; // 15 min
unsigned long backupPeriod_EEPROM = 14400000; // 4 hours

// DISPLAYS
#define CLK1 26
#define DIO1 27
#define CLK2 32
#define DIO2 33
#define NUMBEROFDIGITS 6
#define NOKEYPAD

TM1637Display display1(CLK1, DIO1, 100, NUMBEROFDIGITS);
TM1637Display display2(CLK2, DIO2, 100, NUMBEROFDIGITS);
const uint8_t blank[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
const uint8_t line1[] = { SEG_D,SEG_D,SEG_D,SEG_D,SEG_D,SEG_D };
const uint8_t line2[] = { SEG_G,SEG_G,SEG_G,SEG_G,SEG_G,SEG_G };
const uint8_t line3[] = { SEG_A,SEG_A,SEG_A,SEG_A,SEG_A,SEG_A };

void setup() {

  delay(2000);
  // SERIAL
  Serial.begin(115200);

  // LEDS
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(  BRIGHTNESS );

  // BTNS
  pinMode(YESPIN, INPUT_PULLUP);
  pinMode(NOPIN, INPUT_PULLUP);
  pinMode(RESETPIN, INPUT_PULLUP);

  // SPI (SD)
  // SPI.begin(18, 19, 23, 5); // SCK / MISO(DO) / MOSI(DI) / CS(SS) DEFAULT
  SPI.begin(21, 19, 18, 5);  // SCK / MISO(DO) / MOSI(DI) / CS(SS)
  getMemory();

  // DISPLAYS
  display1.setBrightness(0x03);
  display2.setBrightness(0x03);
  display1.setSegments(blank);
  display2.setSegments(blank);

}


void loop() {

  // FastLED.clear();

  Tnow = millis();
  checkBtns();
  checkBackups();
  checkActions();
  FastLED.show();
  delay(1);

}

//////////////////////////////////////////////
/////////////////   BUTTONS   ////////////////
//////////////////////////////////////////////

void checkBtns(){

  // VALUES
  yesState = digitalRead(YESPIN);
  noState = digitalRead(NOPIN);
  resetState = digitalRead(RESETPIN);

  // YES NO
  if ((yesState == LOW)&&(listenToYesNo==true)) {
    listenToYesNo=false;
    Taction = Tnow;
    votedYes();
  }
  if ((noState == LOW)&&(listenToYesNo==true)) {
    listenToYesNo=false;
    Taction = Tnow;
    votedNo();
  }
  // ACTION OVER - LISTEN AGAIN
  if ((Tnow-Taction > eventDuration)&&(listenToYesNo==false)){
    listenToYesNo = true;
    endOfAction();
  }


  // RESET
  if ((resetState == LOW)&&(pressingReset == false)&&(resetting == false)) {
    pressingReset = true;
    Treset = Tnow;
    Serial.println("STARTED PRESSING RESET");
  }
  if ((resetState == HIGH)&&(pressingReset == true)&&(resetting == false)) {
    pressingReset = false;
    Serial.println("STOPPED PRESSING RESET");
  }
  // LAUNCH RESET
  if ((Tnow-Treset > resetDelay)&&(pressingReset == true)&&(resetting == false)){
    resetting = true;
    reset();
  }
  // RESET OVER - LISTEN AGAIN
  if ((Tnow-Treset > resetDelay+resetDuration)&&(resetting == true)){
    pressingReset = false;
    resetting = false;
    Serial.println("DONE RESETTING");
  }

}

//////////////////////////////////////////////
/////////////////   ACTIONS   ////////////////
//////////////////////////////////////////////

void votedYes(){

  yes_NUM ++;
  justVoted = "yes";
  acting = true;
  actionFrame = 0;
  roadNumber = random(0,4); //Min included, Max excluded
  Serial.println(roadNumber);
  voteColor = yesColor;
  Serial.println("Yes "+String(yes_NUM)+" No "+String(no_NUM));
  showNumber_NEWORDER1(no_NUM, display1);
  showNumber_NEWORDER1(yes_NUM, display2);


}


void votedNo(){

  no_NUM ++;
  justVoted = "no";
  acting = true;
  actionFrame = 0;
  roadNumber = random(0,4);
  Serial.println(roadNumber);
  voteColor = noColor;
  Serial.println("Yes "+String(yes_NUM)+" No "+String(no_NUM));
  showNumber_NEWORDER1(no_NUM, display1);
  showNumber_NEWORDER1(yes_NUM, display2);


}

void endOfAction(){
  Serial.println("ANIM DONE");
  acting = false;
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0,0,0);
  }
}




void checkActions(){

  if ((Tnow-TlastFrame > framePeriod)&&(acting==true)){

    // FastLED.clear();




    if(actionFrame<=7) {
      leds[actionFrame] = voteColor; // 1 2 3 4 5 6 7
    }
    if((actionFrame>7)&&(actionFrame<=10)) {
      if(justVoted=="yes"){ int position = roadsYes[roadNumber][actionFrame-8]; leds[position] = voteColor; }
      if(justVoted=="no"){ int position = roadsNo[roadNumber][actionFrame-8]; leds[position] = voteColor; }

    }
    if((actionFrame>10)&&(actionFrame<=150)) {
      getProportions();
    }

    actionFrame ++;
    TlastFrame = Tnow;


  }


}

void getProportions(){



  float no_NUM_f, no_PROP_f, yes_NUM_f, yes_PROP_f;
  no_NUM_f = no_NUM;
  yes_NUM_f = yes_NUM;
  int no_PROP, yes_PROP;

  no_PROP_f = (no_NUM_f/(no_NUM_f+yes_NUM_f))*150;
  no_PROP = int(no_PROP_f);
  yes_PROP = 150 - no_PROP;


  for (int i = mappingOffset; i >= 0 ; i--) {
    if(no_PROP>0){ proportionArray[i] = 0; no_PROP --; }
    if(no_PROP==0){ proportionArray[i] = 1; }
  }

  for (int i = mappingOffset+1; i < 150 ; i++) {
    if(no_PROP>0){ proportionArray[i] = 0; no_PROP --; }
    if(no_PROP==0){ proportionArray[i] = 1; }
  }


  //SHOW

  for (int i = 0; i < 150; i++) {

    if(proportionArray[i]==0){
      leds[i] = noColor;
    }
    if(proportionArray[i]==1){
      leds[i] = yesColor;
    }

  }

  // + SHUFFLE ALGO




}


//////////////////////////////////////////////
//////////////////  MEMORY   /////////////////
//////////////////////////////////////////////

void getMemory(){

  // SD OK - READ SD
  if(SD.begin()){
    yes_NUM = readFileInt(SD, "/oui.txt");
    no_NUM = readFileInt(SD, "/non.txt");
    Serial.println("Yes SD "+String(yes_NUM)+" No SD "+String(no_NUM));
  }
  // IF SD PROBLEM - READ EEPROM
  if(!SD.begin()){
    Serial.println("Card Mount Failed");
    preferences.begin("my-app", false);
    yes_NUM = preferences.getUInt("yes", 0);
    no_NUM = preferences.getUInt("no", 0);
    Serial.println("Yes EEPROM "+String(yes_NUM)+ " No EEPROM "+String(yes_NUM) );
    preferences.end();
    // TODO SIGNALER PROBLEME SD VIA AFFICHEURS
  }

}

void checkBackups(){

  if ((Tnow-TlastBackup_SD > backupPeriod_SD)&&(true)){
    TlastBackup_SD = Tnow;
    writeFile(SD, "/oui.txt", String(yes_NUM).c_str());
    writeFile(SD, "/non.txt", String(no_NUM).c_str());
  }

  if ((Tnow-TlastBackup_EEPROM > backupPeriod_EEPROM)&&(true)){
    TlastBackup_EEPROM = Tnow;
    preferences.begin("my-app", false);
    preferences.putUInt("yes", yes_NUM);
    preferences.putUInt("no", no_NUM);
    preferences.end();
  }

}

void reset(){

  Serial.println("RESET");
  String text = "Au dernier reset : OUI "+String(yes_NUM)+" NON "+String(no_NUM)+'\n';
  appendFile(SD, "/archive.txt", text.c_str());

  yes_NUM = 0;
  no_NUM = 0;
  writeFile(SD, "/oui.txt", String(yes_NUM).c_str());
  writeFile(SD, "/non.txt", String(no_NUM).c_str());
  preferences.begin("my-app", false);
  preferences.putUInt("yes", yes_NUM);
  preferences.putUInt("no", no_NUM);
  preferences.end();
  TlastBackup_SD = Tnow;
  TlastBackup_EEPROM = Tnow;

}
