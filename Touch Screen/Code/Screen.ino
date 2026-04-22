
//incled parting file
#include "Parse.h"

//define touch screen and tft
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
Elegoo_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

int MButton = 67; 
int touchX = 180;
int touchY = 120;
int touchXOld = 180;
int touchYOld = 120;
uint16_t color[5][5];

//Setup code
void setup() {
  //start serial at 115200 baud rate
  Serial.begin(115200);
  Serial1.begin(115200);
  delay(1000);
  //mouse setup;
  pinMode(MButton, INPUT_PULLUP);
  pinMode(A11, INPUT);
  pinMode(A12, INPUT);



  //start tft and set roation
  tft.begin(0x9341);
  tft.setRotation(1);

  //pin setup for touchscreen and buzzer
  pinMode(13, OUTPUT);
  pinMode(SD_CS, OUTPUT);
  pinMode(buzzer+4, OUTPUT);
  digitalWrite(buzzer+4, LOW);
  pinMode(buzzer, OUTPUT);
  digitalWrite(LCD_CS, HIGH);
  pinMode(SD_CS, OUTPUT);
  digitalWrite(SD_CS, HIGH);

  delay(200);
  //inshalise SD card and report if failed
  if (!SD.begin(SD_CS)) {
    //Serial.println(F("SD failed!"));
    parse("Text(SD ERROR,50,100,4,65535)", tft);
    while (1)
      ;
  }


  //remove old files
  SD.remove(update);
  SD.remove(bFile);

  //run the starting file
  sd("begin.txt", tft);
  //mouse
  //mouse
  readColor();
}


//the runing body of the code
void loop() {

  //save screen touch to p
  digitalWrite(13, HIGH);
  TSPoint p = ts.getPoint();
  digitalWrite(13, LOW);
  pinMode(LCD_CS, OUTPUT);
  pinMode(LCD_CD, OUTPUT);

  mouse();
  //p.z = click();
  //check to see if screen was touched
  if (p.z > 15 || click()) {
    int temp = p.x;
    //convert the touch to quredents on screen
    p.x = map(p.y, 930, 40, 0, 320);
    p.y = map(temp, 900, 160, 0, 240);

    //mouse
    if(click()){
      p.x = touchX;
      p.y = touchY;
    }
    


    //extra delay to prevent double press
    delay(100);

    //check to see if a button was pressesd
    for (int i = 0; i < bCount; i++) {
      if (p.x > buttons[i][0] && p.x < buttons[i][2] && p.y > buttons[i][1] && p.y < buttons[i][3]) {

        //beep the buzzer
        for (int i = 0; i < 100000 / (2 * pitch) && Buzz; i++) {
          digitalWrite(buzzer, HIGH);
          delayMicroseconds(pitch);
          digitalWrite(buzzer, LOW);
          delayMicroseconds(pitch);
        }

        //if button was pressed open file and print line
        file = SD.open(bFile);
        //serch through the file until corect line is found
        for (int j = 0; j <= i; j++) {
          for (int k = 0; k < 40; k++) {
            Fileline[k] = file.read();
            if (Fileline[k] == 10) {
              Fileline[k] = 0;
              break;
            }
          }
        }
        //close the file
        file.close();
        delay(5);
        //run the file line
        parse(Fileline, tft);
        if (fileName[0] != 0) {
          sd(fileName, tft);
          fileName[0] = 0;
        }
        if (old == 1) {
          sd(OldFile, tft);
          old = 0;
        }
        parse("Run(text.txt)", tft);
        Time = millis();
        //mouse
        readColor();

        break;
      }
      
    }
  }

  if (Serial1.available()) {
    serial(Serial1.readStringUntil('\n').c_str(), tft);
    if (old == 1) {
      sd(OldFile, tft);
      old = 0;
    }
  }

  if (Time + UPDATE_TIME < millis()) {
    parse("Run(text.txt)", tft);
    x += 10;
    Time = millis();
  }
}

//mouse
int click(){
  if(!digitalRead(MButton)) return 30;
  return 0;
}
void mouse(){
  int Ax = analogRead(A11);
  int Ay = analogRead(A12);
  bool change = false;

  if(Ay < 300 && touchX < 315){
    touchX +=5;
    change = true;
  }
  if(Ay > 700 && touchX > 0){
    touchX -=5;
    change = true;
  }
  if(Ax > 700 && touchY < 235){
    touchY +=5;
    change = true;
  }
  if(Ax < 300 && touchY > 0){
    touchY -=5;
    change = true;
  }

  if(change){
    for(int i = 0; i < 5; i++){
      for(int j = 0; j < 5; j++){
        tft.drawPixel(touchXOld+i, touchYOld+j, color[i][j]);
        color[i][j] = tft.readPixel(touchX+i, touchY+j);
      }
    }
    touchXOld = touchX;
    touchYOld = touchY;
    tft.fillRect(touchX, touchY, 5, 5, 65535);
    tft.fillRect(touchX+1, touchY+1, 3, 3, 0);
    delay(15);
  }

}

void readColor(){
  for(int i = 0; i < 5; i++){
      for(int j = 0; j < 5; j++){
        color[i][j] = tft.readPixel(touchX+i, touchY+j);
      }
    }
    touchXOld = touchX;
    touchYOld = touchY;
    tft.fillRect(touchX, touchY, 5, 5, 65535);
    tft.fillRect(touchX+1, touchY+1, 3, 3, 0);
}


