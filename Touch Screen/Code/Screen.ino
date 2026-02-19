

#include "Parse.h"


TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
Elegoo_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);


void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  //sdcard

  

  tft.begin(0x9341);

  tft.setRotation(1);

  pinMode(13, OUTPUT);

  if (!SD.begin(SD_CS)) {
    Serial.println(F("SD failed!"));
    parse("text(SD ERROR,50,100,4,0)",tft);
    return;
  }
  SD.remove(update);
  sd("begin.txt");
}

void sd(String in){
  File file = SD.open(in);
  read(file, tft);
  file.close();
}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(13, HIGH);
  TSPoint p = ts.getPoint();
  digitalWrite(13, LOW);
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);

  delay(1000);
  parse("run(update.txt)", tft);
  x+=10;
}
