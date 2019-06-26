
void readFile(fs::FS &fs, const char * path){
    File file = fs.open(path);
    if(!file){
        Serial.println("Failed to open file for reading");
        return;
    }
    int i = 0;
    // while(file.available()){
    //   readBuffer[i]=file.read();
    //   i++;
    // }
    for(int i = 0; i < sizeof(readBuffer); i++){
      readBuffer[i]=file.read();
    }
    file.close();
}

int readFileInt(fs::FS &fs, const char * path){

    File file = fs.open(path);
    int intRead;

    while(file.available()){
      intRead = file.parseInt();
    }
    file.close();
    return intRead;

}

void writeFile(fs::FS &fs, const char * path, const char * message){

    File file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("Failed to open file for writing");
        return;
    }
    if(file.print(message)){
        // Serial.println("File written");
    } else {
        // Serial.println("Write failed");
    }
    file.close();
}

void appendFile(fs::FS &fs, const char * path, const char * message){
    // Serial.printf("Appending to file: %s\n", path);

    File file = fs.open(path, FILE_APPEND);
    if(!file){
        Serial.println("Failed to open file for appending");
        return;
    }
    if(file.print(message)){
        // Serial.println("Message appended");
    } else {
        // Serial.println("Append failed");
    }
    file.close();
}
