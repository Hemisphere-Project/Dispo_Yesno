//////////////////////////////////////////////
/////////////////   ACTIONS   ////////////////
//////////////////////////////////////////////

void launchAnim(){

  acting = true;
  actionFrame = 0;
  framePeriodTemp = framePeriod;
  shuffleArray(orderArray,NUM_LEDS);
  calcProportions();
  roadNumber = random(0,4);
  if(justVoted=="yes"){voteColor = yesColor;}
  if(justVoted=="no"){voteColor = noColor;}
  FastLED.setBrightness(BRIGHTNESS);
  // Serial.println("Yes "+String(yes_NUM)+" No "+String(no_NUM));
}

void endOfAction(){
  Serial.println("ANIM DONE");
  acting = false;
  TendOfAction = Tnow;
  display1.setSegments(blank);
  display2.setSegments(blank);
}




void animate(){

  if ((Tnow-TlastFrame > framePeriodTemp)&&(acting==true)){

    // CHEMIN FIXE
    if(actionFrame<=7) {
      FastLED.clear();
      leds[actionFrame] = voteColor; // 1 2 3 4 5 6 7
    }
    // CHEMIN GAUCHE DROITE
    if((actionFrame>7)&&(actionFrame<=10)) {
      FastLED.clear();
      if(justVoted=="yes"){ int pos = roadsYes[roadNumber][actionFrame-8]; leds[pos] = voteColor; }
      if(justVoted=="no"){ int pos = roadsNo[roadNumber][actionFrame-8]; leds[pos] = voteColor; }
    }
    // FILL
    int fillFrame = actionFrame - 17; // Start offset: frame 20
    if((fillFrame>0)&&(fillFrame<=150)) {
      int pos = orderArray[fillFrame-1];
      if(proportionArray[pos]==0){ leds[pos] = noColor; }
      if(proportionArray[pos]==1){ leds[pos] = yesColor; }
      //EASE IN-OUT
      if((fillFrame>0)&&(fillFrame<=2)){ framePeriodTemp = 100; }
      if((fillFrame>2)&&(fillFrame<=7)){ framePeriodTemp = 80; }
      if((fillFrame>5)&&(fillFrame<=130)){ framePeriodTemp = framePeriodTemp - fillFrame*3; }
      if((fillFrame>130)&&(fillFrame<=150)){ framePeriodTemp = 50; }
      if(framePeriodTemp<10){ framePeriodTemp = 10; }
    }

    if(fillFrame==150){
      framePeriodTemp = framePeriod;
    }

    // DISPLAYS
    if ((actionFrame % 3 == 0)&&(actionFrame < 10)) { display1.setSegments(line2); display2.setSegments(line2); }
    if ((actionFrame % 3 == 1)&&(actionFrame < 10)) { display1.setSegments(line3); display2.setSegments(line3); }
    if ((actionFrame % 3 == 2)&&(actionFrame < 10)) { display1.setSegments(line1); display2.setSegments(line1); }
    if(actionFrame==10){
      showNumber_NEWORDER1(no_NUM, display1);
      showNumber_NEWORDER1(yes_NUM, display2);
    }

    // EMPTY
    int emptyFrame = actionFrame - 180;  // Start offset: frame 200
    if ((emptyFrame>0)&&(emptyFrame<=150)) {
      int pos = orderArray[emptyFrame-1];
      leds[pos] = CRGB(0,0,0) ;
      framePeriodTemp = framePeriodTemp - emptyFrame*2;
      if(framePeriodTemp<10){ framePeriodTemp = 10; }
    }

    // NEXT
    actionFrame ++;
    TlastFrame = Tnow;

  }

}

void calcProportions(){


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

}


void shuffleArray(int * array, int size)
{
  int last = 0;
  int temp = array[last];
  for (int i=0; i<size; i++)
  {
    int index = random(size);
    array[last] = array[index];
    last = index;
  }
  array[last] = temp;
}
