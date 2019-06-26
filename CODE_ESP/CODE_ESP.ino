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
#include "TM1637Display.h"


#define NUM_LEDS 50
#define LED_PIN 0
#define BRIGHTNESS  50
#define LED_TYPE    WS2811
#define COLOR_ORDER RGB
CRGB leds[NUM_LEDS];


#define YESPIN        4
#define NOPIN         16
#define RESETPIN      17
// Btns States
int yesState, noState, resetState = 0;
// Yes & No
unsigned long Taction = 0;
unsigned long Tnow = 0;
unsigned long eventDuration = 1000;
bool listenToYesNo = true;
// Reset
unsigned long Treset = 0;
unsigned long resetDelay = 2000;
unsigned long resetDuration = 10000;
bool pressingReset = false;
bool resetting = false;

bool acting = false;
unsigned long actionFrame = 0;
char *justVoted = "none";

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

  // SPI
  // SPI.begin(18, 19, 23, 5); // SCK / MISO(DO) / MOSI(DI) / CS(SS) DEFAULT
  SPI.begin(21, 19, 18, 5);  // SCK / MISO(DO) / MOSI(DI) / CS(SS)
  getMemory();

  // DISPLAYS
  display1.setBrightness(0x03);
  display2.setBrightness(0x03);

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
  Serial.println("Yes "+String(yes_NUM)+" No "+String(no_NUM));
  display1.showNumberDec(yes_NUM, false);
  display2.showNumberDec(no_NUM, false);

}


void votedNo(){

  no_NUM ++;
  justVoted = "no";
  acting = true;
  actionFrame = 0;
  Serial.println("Yes "+String(yes_NUM)+" No "+String(no_NUM));
  display1.showNumberDec(yes_NUM, false);
  display2.showNumberDec(no_NUM, false);

}

void endOfAction(){
  Serial.println("ANIM DONE");
  acting = false;
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0,0,0);
  }
}


void checkActions(){

  if(acting==true){

    if(justVoted=="yes"){
      FastLED.clear();
      for (int i = 0; i < yes_NUM; i++) {
        leds[i] = CRGB(255,255,255);
      }
    }
    if(justVoted=="no"){
      FastLED.clear();
      for (int i = 0; i < no_NUM; i++) {
        leds[i] = CRGB(255,0,0);
      }
    }

  }

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
