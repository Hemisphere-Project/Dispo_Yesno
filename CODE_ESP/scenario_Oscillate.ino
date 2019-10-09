
// Timing
unsigned long Tlast;
long OnTime, OffTime;

long OnTimeMin = 800;
long OnTimeMax = 1200;
long OffTimeMin = 500;
long OffTimeMax = 1500;


//////////////////////////////////////////
/////////////   BLINKER    ///////////////
//////////////////////////////////////////

class Blinker
{
	int pos;
	int val;
	long OnTime;
	long OffTime;
	unsigned long Tlast;
	int id;
	int red_white;

  // Constructor
  public:
  Blinker(int myid)
  {
	pos = random(NUM_LEDS);
	val = 0;
	Tlast = 0;
  OnTime = random(OnTimeMin,OnTimeMax);
  OffTime = random(OffTimeMin,OffTimeMax);
	id = myid;
	red_white = random(0,2);
  }

  void Update()
  {
    // ON
    if((Tnow-Tlast>OffTime)&&(Tnow-Tlast<OffTime+OnTime)){
			val = val + 10;
			if(val>255){val=255;}
			if(red_white==0){ leds[pos] = CRGB(val,val,val); }
			if(red_white==1){ leds[pos] = CRGB(val,0,0); }

    }
    // OFF
    if(Tnow-Tlast>OffTime+OnTime){
			val = val - 4;
			if(val<0){val=255;}
			if(red_white==0){ leds[pos] = CRGB(val,val,val); }
			if(red_white==1){ leds[pos] = CRGB(val,0,0); }
      // RELOOP
			if(val<=5){
				Tlast = Tnow;
				OnTime = random(OnTimeMin,OnTimeMax);
				OffTime = random(OffTimeMin,OffTimeMax);
				pos = random(NUM_LEDS);
			}
    }

  }

};

//////////////////////////////////////////
//////////////////////////////////////////
//////////////////////////////////////////


Blinker blinky0(0);
Blinker blinky1(1);
Blinker blinky2(2);
Blinker blinky3(3);
Blinker blinky4(4);
Blinker blinky5(5);
Blinker blinky6(6);
Blinker blinky7(7);
Blinker blinky8(8);
Blinker blinky9(9);
Blinker blinky10(10);
Blinker blinky11(11);
Blinker blinky12(12);
Blinker blinky13(13);
Blinker blinky14(14);
Blinker blinky15(15);
Blinker blinky16(16);
Blinker blinky17(17);
Blinker blinky18(18);
Blinker blinky19(19);
Blinker blinky20(20);
Blinker blinky21(21);
Blinker blinky22(22);
Blinker blinky23(23);
Blinker blinky24(24);
Blinker blinky25(25);
Blinker blinky26(26);
Blinker blinky27(27);
Blinker blinky28(28);
Blinker blinky29(29);
Blinker blinky30(30);
Blinker blinky31(31);
Blinker blinky32(32);
Blinker blinky33(33);
Blinker blinky34(34);
Blinker blinky35(35);
Blinker blinky36(36);
Blinker blinky37(37);
Blinker blinky38(38);
Blinker blinky39(39);



void oscillate() {

	if(acting==false){
		FastLED.clear();

		// MASTER BREATH
		int masterPeriod = 7000;
		float master = (sin( (millis()-TendOfAction)*2*PI/masterPeriod - PI/2) +1 )/2 * BRIGHTNESS;
		// master = master*master/255;
		if(master<0){ master = 0; }

		// Fix (smooth restart)
		if((Tnow-TendOfAction)<400){ master = 0; }

		FastLED.setBrightness(  master );

	  blinky0.Update();
	  blinky1.Update();
	  blinky2.Update();
	  blinky3.Update();
	  blinky4.Update();
	  blinky5.Update();
	  blinky6.Update();
	  blinky7.Update();
		blinky8.Update();
		blinky9.Update();
		blinky10.Update();
		blinky11.Update();
		blinky12.Update();
		blinky13.Update();
		blinky14.Update();
		blinky15.Update();
		blinky16.Update();
		blinky17.Update();
		blinky18.Update();
		blinky19.Update();
		blinky20.Update();
		blinky21.Update();
		blinky22.Update();
		blinky23.Update();
		blinky24.Update();
		blinky25.Update();
		blinky26.Update();
		blinky27.Update();
		blinky28.Update();
		blinky29.Update();
		blinky30.Update();
		blinky31.Update();
		blinky32.Update();
		blinky33.Update();
		blinky34.Update();
		blinky35.Update();
		blinky36.Update();
		blinky37.Update();
		blinky38.Update();
		blinky39.Update();

	}

}
