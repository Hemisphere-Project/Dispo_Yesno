#include "FS.h"
#include "SD.h"
#include "SPI.h"

#include <Preferences.h>

Preferences preferences;

char readBuffer[100];
int yes_SD, no_SD;


void setup(){
    Serial.begin(115200);


    // SPI.begin(18, 19, 23, 5); // SCK / MISO (DO)/ MOSI (DI) / CS(SS) DEFAULT
    SPI.begin(21, 19, 18, 5);  // SCK / MISO (DO)/ MOSI (DI) / CS(SS)

    if(!SD.begin()){
      Serial.println("Card Mount Failed");
      return;
    }
    uint8_t cardType = SD.cardType();
    if(cardType == CARD_NONE){
      Serial.println("No SD card attached");
      return;
    }

    // SD
    ////////////////////

    readFile(SD, "/archive.txt");
    Serial.println("ARCHIVE IS ");
    for(int i = 0; i < sizeof(readBuffer); i++){
      Serial.print(readBuffer[i]);
      if(i==sizeof(readBuffer)-1){ Serial.println('etc......'); }
    }

    // GET
    yes_SD = readFileInt(SD, "/oui.txt");
    no_SD = readFileInt(SD, "/non.txt");
    Serial.println("Yes SD "+String(yes_SD)+" No SD "+String(no_SD));
    // SET MEMORY
    yes_SD = yes_SD + 100;
    no_SD = no_SD + 100;
    writeFile(SD, "/oui.txt", String(yes_SD).c_str());
    writeFile(SD, "/non.txt", String(no_SD).c_str());
    // RESET: SET ARCHIVE & SET MEMORY A 0
    String text = "Au dernier reset : OUI "+String(yes_SD)+" NON "+String(no_SD)+'\n';
    appendFile(SD, "/archive.txt", text.c_str());
    writeFile(SD, "/oui.txt", "0");
    writeFile(SD, "/non.txt", "0");



    // EEPROM
    ////////////////////
    preferences.begin("my-app", false);
    // GET
    unsigned int yes_EEPROM = preferences.getUInt("yes", 0);
    unsigned int no_EEPROM = preferences.getUInt("no", 0);
    Serial.println("Yes EEPROM "+String(yes_EEPROM) );
    Serial.println("No EEPROM "+String(no_EEPROM) );
    // SET MEMORY
    yes_EEPROM = yes_SD;
    no_EEPROM = no_SD;
    preferences.putUInt("yes", yes_EEPROM);
    preferences.putUInt("no", no_EEPROM);
    // RESET EEPROM
    preferences.putUInt("yes", 0);
    preferences.putUInt("no", 0);
    preferences.end();

}



void loop(){


}
