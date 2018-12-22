#include "RTClib.h"
#include "LedControlMS.h"
RTC_DS1307 rtc;
LedControl lc = LedControl(12, 11, 10, 1);
int binary[4];
pinMode(8, OUTPUT); 
digitalWrite(8, HIGH);
void setupRtc() {
  Serial.begin(9600);
  if (! rtc.begin())
  {
    Serial.print("Couldn't find RTC");
    while (1);
  }
 
  if (! rtc.isrunning())
  {
    Serial.print("RTC is NOT running!");
  }
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));//auto update from computer time
  //rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));// to set the time manualy
 
}
void setupLcd() {
  lc.shutdown(0, false);
  lc.setIntensity(0, 4);
  lc.clearDisplay(0);
}
void setup ()
{
  setupRtc();
  setupLcd();
}
void loop() {
  DateTime now = rtc.now();
  int  nowSecond = now.second();
  int   nowMinute = now.minute();
  int  nowHour = now.hour();
  int  nowDayOfTheWeek = now.dayOfTheWeek();
  int  nowDay = now.day();
  int nowMonth = now.month();
  int nowYear = now.year();
  setToLed(0, 0, toBinary(nowSecond % 10));
  setToLed(0, 1, toBinary(nowSecond / 10));
  setToLed(0, 2, toBinary(nowMinute % 10));
  setToLed(0, 3, toBinary(nowMinute / 10));
  setToLed(0, 4, toBinary(nowHour % 10));
  setToLed(0, 5, toBinary(nowHour / 10));
  setToLed(0, 7, toBinary(nowDayOfTheWeek));
  setToLed(4, 4, toBinary(nowDay % 10));
  setToLed(4, 5, toBinary(nowDay / 10));
  setToLed(4, 2, toBinary(nowMonth % 10));
  setToLed(4, 3, toBinary(nowMonth / 10));
  setToLed(4, 0, toBinary(nowYear % 10));
  setToLed(4, 1, toBinary((nowYear / 10) % 10));
}
 
 
int* toBinary(int n) {
  int i = 3 ;
  for (int b = 0 ; b < 4 ; b++) {
    binary[b] = 0;
  }
  while (n) {
    binary[i--] = n % 2 ;
    n = n / 2;
  }
  return binary ;
 
}
void setToLed(int row, int col, int n[]) {
  for (int i = 3 ; i >= 0 ; i--) {
    if (n[i] == 1)
      lc.setLed(0, row++, col, true);
    else
      lc.setLed(0, row++, col, false);
  }
}
