// LEDS
#include <FastLED.h>

#define NUM_LEDS 150
#define LED_PIN 0
#define BRIGHTNESS  60
#define LED_TYPE    WS2811
#define COLOR_ORDER RGB
CRGB leds[NUM_LEDS];

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

  // Constructor
  public:
  Blinker(int position)
  {
	pos = random(NUM_LEDS);
	val = 0;
	Tlast = 0;
  OnTime = random(OnTimeMin,OnTimeMax);
  OffTime = random(OffTimeMin,OffTimeMax);
  }

  void Update()
  {
    unsigned long Tnow = millis();


		// // ON
		// if(Tnow-Tlast>OffTime){
		// 	leds[pos] = CRGB(255,255,255);
		// }
		// // OFF
		// if(Tnow-Tlast>OffTime+OnTime){
		// 	leds[pos] = CRGB(0,0,0);
		// 	// RELOOP
		// 	Tlast = Tnow;
		// 	OnTime = random(OnTimeMin,OnTimeMax);
		// 	OffTime = random(OffTimeMin,OffTimeMax);
		// 	pos = random(NUM_LEDS);
		// }

    // ON
    if((Tnow-Tlast>OffTime)&&(Tnow-Tlast<OffTime+OnTime)){
			val = val + 10;
			if(val>255){val=255;}
			leds[pos] = CRGB(val,val,val);
			Serial.println(val);
    }
    // OFF
    if(Tnow-Tlast>OffTime+OnTime){
			val = val - 10;
			if(val<0){val=255;}
			leds[pos] = CRGB(val,val,val);
			Serial.println(val);
      // RELOOP
			if(val<=5){
				Serial.println("RELOOP");
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


void setup() {
	// LEDS
	FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
	FastLED.setBrightness(  BRIGHTNESS );

	Serial.begin(115200);
}

Blinker blinky0(1);
Blinker blinky1(1);
Blinker blinky2(1);
Blinker blinky3(1);
Blinker blinky4(1);
Blinker blinky5(1);
Blinker blinky6(1);
Blinker blinky7(1);
Blinker blinky8(1);
Blinker blinky9(1);
Blinker blinky10(1);
Blinker blinky11(1);
Blinker blinky12(1);
Blinker blinky13(1);
Blinker blinky14(1);
Blinker blinky15(1);
Blinker blinky16(1);
Blinker blinky17(1);
Blinker blinky18(1);
Blinker blinky19(1);
Blinker blinky20(1);
Blinker blinky21(1);
Blinker blinky22(1);
Blinker blinky23(1);
Blinker blinky24(1);
Blinker blinky25(1);
Blinker blinky26(1);
Blinker blinky27(1);
Blinker blinky28(1);
Blinker blinky29(1);
Blinker blinky30(1);
Blinker blinky31(1);
Blinker blinky32(1);
Blinker blinky33(1);
Blinker blinky34(1);
Blinker blinky35(1);
Blinker blinky36(1);
Blinker blinky37(1);
Blinker blinky38(1);
Blinker blinky39(1);



void loop() {

	FastLED.clear();

	int masterPeriod = 7000;
	float master = (cos(millis()*2*PI/masterPeriod)+1)/2 * BRIGHTNESS;

	// float master = cos(millis()*2*PI/masterPeriod) * BRIGHTNESS;
	// master = master*master/255;
	if(master<0){ master = 0; }

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

  FastLED.show();
  delay(1);
}
