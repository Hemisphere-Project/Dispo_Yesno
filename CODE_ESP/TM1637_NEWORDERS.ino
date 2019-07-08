
void showNumber_NEWORDER1(int num, TM1637Display display){

  if(num >= 999999){ return; }

  display.setSegments(blank);

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

  display.setSegments(blank);

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
