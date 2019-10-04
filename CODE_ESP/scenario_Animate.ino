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
  // LOG("Yes "+String(yes_NUM)+" No "+String(no_NUM));
}

void endOfAction(){

  acting = false;
  TendOfAction = Tnow;
  display1.setSegments(blank);
  display2.setSegments(blank);
  // LOG("ANIM DONE");
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
    int fillFrame = actionFrame - 23; // Start offset: à frame i
    if((fillFrame>0)&&(fillFrame<=NUM_LEDS)) {
      int pos = orderArray[fillFrame-1];
      if(proportionArray[pos]==0){ leds[pos] = yesColor; }
      if(proportionArray[pos]==1){ leds[pos] = noColor; }
      //EASE IN-OUT
      if((fillFrame>0)&&(fillFrame<=2)){ framePeriodTemp = 100; }
      if((fillFrame>2)&&(fillFrame<=7)){ framePeriodTemp = 80; }
      if((fillFrame>5)&&(fillFrame<=130)){ framePeriodTemp = framePeriodTemp - fillFrame*3; }
      if((fillFrame>130)&&(fillFrame<=NUM_LEDS)){ framePeriodTemp = 50; }
      if(framePeriodTemp<10){ framePeriodTemp = 10; }
    }

    if(fillFrame==NUM_LEDS){
      framePeriodTemp = 100;
    }

    // DISPLAYS
    if ((actionFrame % 3 == 0)&&(actionFrame < 11)) { display1.setSegments(line2); display2.setSegments(line2); }
    if ((actionFrame % 3 == 1)&&(actionFrame < 11)) { display1.setSegments(line3); display2.setSegments(line3); }
    if ((actionFrame % 3 == 2)&&(actionFrame < 11)) { display1.setSegments(line1); display2.setSegments(line1); }
    if(actionFrame==11){
      showNumber_NEWORDER1(yes_NUM, display1);
      showNumber_NEWORDER1(no_NUM, display2);
    }

    // EMPTY
    int emptyFrame = actionFrame - 200;  // Start offset à frame i
    if ((emptyFrame>0)&&(emptyFrame<=NUM_LEDS)) {
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


  float yes_NUM_f, yes_PROP_f, no_NUM_f, no_PROP_f;
  yes_NUM_f = yes_NUM;
  no_NUM_f = no_NUM;
  int yes_PROP, no_PROP;

  yes_PROP_f = (yes_NUM_f/(yes_NUM_f+no_NUM_f))*NUM_LEDS;
  yes_PROP = int(yes_PROP_f);
  no_PROP = NUM_LEDS - yes_PROP;

  for (int i = mappingOffset; i >= 0 ; i--) {
    if(yes_PROP>0){ proportionArray[i] = 0; yes_PROP --; }
    if(yes_PROP==0){ proportionArray[i] = 1; }
  }

  for (int i = mappingOffset+1; i < NUM_LEDS ; i++) {
    if(yes_PROP>0){ proportionArray[i] = 0; yes_PROP --; }
    if(yes_PROP==0){ proportionArray[i] = 1; }
  }

}

// void calcProportionsOLD(){
//
//
//   float no_NUM_f, no_PROP_f, yes_NUM_f, yes_PROP_f;
//   no_NUM_f = no_NUM;
//   yes_NUM_f = yes_NUM;
//   int no_PROP, yes_PROP;
//
//   no_PROP_f = (no_NUM_f/(no_NUM_f+yes_NUM_f))*NUM_LEDS;
//   no_PROP = int(no_PROP_f);
//   yes_PROP = NUM_LEDS - no_PROP;
//
//   for (int i = mappingOffset; i >= 0 ; i--) {
//     if(no_PROP>0){ proportionArray[i] = 0; no_PROP --; }
//     if(no_PROP==0){ proportionArray[i] = 1; }
//   }
//
//   for (int i = mappingOffset+1; i < NUM_LEDS ; i++) {
//     if(no_PROP>0){ proportionArray[i] = 0; no_PROP --; }
//     if(no_PROP==0){ proportionArray[i] = 1; }
//   }
//
// }


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
