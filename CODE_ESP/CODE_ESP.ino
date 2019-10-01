// TODO
// - REVERSE COLORS YES NO                                                        -- CHECK
// - Preferences: PANEL_ID                                                        -- CHECK
// - PANEL_ID : Selective roads & mapping offset                                  -- CHECK
// - Adjust timings backupPeriod_SD / backupPeriod_EEPROM To fit to museum hours  -- TODO
// - OTA ?                                                                        -- TODO
// - Unlog Serial                                                                 -- TODO

// Specific To 4 Devices:
// - Adjust roadsNo, roadsYes, mappingOffset

#define PANEL_ID 2

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


#define NUM_LEDS    151
#define LED_PIN     0
#define BRIGHTNESS  75
#define LED_TYPE    WS2811
#define COLOR_ORDER RGB
CRGB leds[NUM_LEDS];
#define YESPIN       4
#define NOPIN        16
#define RESETPIN     17
// Btns States
int yesState, noState, resetState = 0;
// Yes & No
unsigned long Taction, Tnow = 0;
unsigned long eventDuration = 13000;
bool listenToYesNo = true;
// Reset
unsigned long Treset = 0;
unsigned long resetPressDuration = 4000;
unsigned long resetDuration = 5000;
bool pressingReset = false;
bool resetting = false;


// ANIMATE
char *justVoted = "none";
bool acting = false;
int actionFrame = 0;
int framePeriod = 150;
int framePeriodTemp;
int TlastFrame = 0;
CRGB voteColor;
CRGB noColor = CRGB(255,0,0);
CRGB yesColor = CRGB(255,255,255);
int roadNumber = 0;
int orderArray[NUM_LEDS];
int proportionArray[150];
int roadsYes[ 4 ][ 3 ];
int roadsNo[ 4 ][ 3 ];
int mappingOffset;
// int roadsYes[ 4 ][ 3 ] = { { 9,18, 38 }, { 18, 40, 44 }, { 21, 37, 45 }, { 34, 47, 73 } };
// int roadsNo[ 4 ][ 3 ] = { { 9, 84, 129 }, { 83, 112, 140 }, { 82, 98, 113 }, { 85, 95, 120 } };
int roadsYes_AllPanels[ 4 ][ 4 ][ 3 ] = {
{ { 9, 18, 38 }, { 18, 40, 44 }, { 21, 37, 45 }, { 34, 47, 73 } },    // YES Panel 1
{ { 10, 11, 12 }, { 10, 11, 12 }, { 10, 11, 12 }, { 10, 11, 12 } },   // YES Panel 2
{ { 10, 11, 12 }, { 10, 11, 12 }, { 10, 11, 12 }, { 10, 11, 12 } },   // YES Panel 3
{ { 10, 11, 12 }, { 10, 11, 12 }, { 10, 11, 12 }, { 10, 11, 12 } } }; // YES Panel 4
int roadsNo_AllPanels[ 4 ][ 4 ][ 3 ] = {
{ { 9, 84, 129 }, { 83, 112, 140 }, { 82, 98, 113 }, { 85, 95, 120 } },// NO Panel 1
{ { 10, 11, 12 }, { 10, 11, 12 }, { 10, 11, 12 },{ 10, 11, 12 } },     // NO Panel 2
{ { 10, 11, 12 }, { 10, 11, 12 }, { 10, 11, 12 },{ 10, 11, 12 } },     // NO Panel 3
{ { 10, 11, 12 }, { 10, 11, 12 }, { 10, 11, 12 },{ 10, 11, 12 } } };   // NO Panel 4
int mappingOffset_AllPanels[ 4 ] = { 74 , 74 , 74 , 74 };

//OSCILLATE
unsigned long TendOfAction = 0;

// MEMORY
Preferences preferences;
unsigned int panelid = 0;
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
const uint8_t zero[] = { 0, 0, 0, SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F, 0, 0 };
const uint8_t line1[] = { SEG_D,SEG_D,SEG_D,SEG_D,SEG_D,SEG_D };
const uint8_t line2[] = { SEG_G,SEG_G,SEG_G,SEG_G,SEG_G,SEG_G };
const uint8_t line3[] = { SEG_A,SEG_A,SEG_A,SEG_A,SEG_A,SEG_A };
const uint8_t NO_seg[] = {0,
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,   // O
  SEG_A | SEG_B | SEG_C | SEG_E | SEG_F,          // N
  0,0,0
};
const uint8_t SD_seg[] = {0,
  SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,   // D
  SEG_A | SEG_C | SEG_D | SEG_F | SEG_G,   // S
  0,0,0
};

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

  // DISPLAYS
  display1.setBrightness(0x03);
  display2.setBrightness(0x03);
  display1.setSegments(blank);
  display2.setSegments(blank);

  // SPI (SD)
  // SPI.begin(18, 19, 23, 5); // SCK / MISO(DO) / MOSI(DI) / CS(SS) DEFAULT
  SPI.begin(21, 19, 18, 5);  // SCK / MISO(DO) / MOSI(DI) / CS(SS)
  getMemory();

  // FILL ARRAYS
  for (int i = 0; i < NUM_LEDS; i++) {
    orderArray[i]=i;
  }

  // PANEL ID
  preferences.begin("my-app", false);
  #ifdef PANEL_ID
    preferences.putUInt("panelid", PANEL_ID);
  #endif
  panelid = preferences.getUInt("panelid", 254);
  preferences.end();
  // ID -> Roads Yes & No, mappingOffset

  for (size_t i = 0; i < 4; i++) {
    for (size_t j = 0; j < 3; j++) {
      roadsNo[i][j]=roadsNo_AllPanels[panelid-1][i][j];
    }
  }
  for (size_t i = 0; i < 4; i++) {
    for (size_t j = 0; j < 3; j++) {
      roadsYes[i][j]=roadsYes_AllPanels[panelid-1][i][j];
    }
  }
  mappingOffset = mappingOffset_AllPanels[panelid-1];

}


void loop() {

  // FastLED.clear();

  Tnow = millis();
  checkBtns();
  checkBackups();
  animate();
  oscillate();

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
    yes_NUM ++;
    justVoted = "yes";
    launchAnim();
  }
  if ((noState == LOW)&&(listenToYesNo==true)) {
    listenToYesNo=false;
    Taction = Tnow;
    no_NUM ++;
    justVoted = "no";
    launchAnim();
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
    display1.setSegments(line2); display2.setSegments(line2);
  }
  if ((resetState == HIGH)&&(pressingReset == true)&&(resetting == false)) {
    pressingReset = false;
    Serial.println("STOPPED PRESSING RESET");
    display1.setSegments(blank); display2.setSegments(blank);
  }
  // LAUNCH RESET
  if ((Tnow-Treset > resetPressDuration)&&(pressingReset == true)&&(resetting == false)){
    resetting = true;
    reset();
    display1.setSegments(zero); display2.setSegments(zero);

  }
  // RESET OVER - LISTEN AGAIN
  if ((Tnow-Treset > resetPressDuration+resetDuration)&&(resetting == true)){
    pressingReset = false;
    resetting = false;
    Serial.println("DONE RESETTING");
    display1.setSegments(blank); display2.setSegments(blank);
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
    display1.setSegments(NO_seg);
    display2.setSegments(SD_seg);
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
