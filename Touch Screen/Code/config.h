//https://rgbcolorpicker.com/565

//this file allows for chars to be used simaler to strings
#include "char.h"
#include "var.h"
#include <Arduino.h>

int num = 50;
int numOut = 0;
int Current = 0;
int time1 = 400;
int time2 = 10;
int time3 = 300;
int timeS1 = 400;
int timeS2 = 10;
int timeS3 = 300;
int Ace = 0;
int Temp = 0;
int old = 0;
unsigned int Acetone = 0;
unsigned int Clean = 500;
int tempicher = 0;



char OldFile[12];

void Var(const char* in, int value, Elegoo_TFTLCD& tft);
void parse(char* in, Elegoo_TFTLCD& tft);
void sd(const char* in, Elegoo_TFTLCD& tft);

void special(char* out, const char* in, Elegoo_TFTLCD& tft) {
  if (equal(in, "EEPROM", 6)) {
    intToChar(out, EEPROM.read(toInt(in, 6, index(in, 0, 0, FILELINE))));
  } else if (equal(in, "X", 1)) {
    out[0] = 0;
    if (Acetone > 999) intToChar(out, (Acetone / 1000));
    else intToChar(out, (Acetone));
  } else if (equal(in, "/X", 2)) {
    out[0] = 0;
    charBuilder(out, "X");
    } else if (equal(in, "/Ace", 4)) {
    intToChar(out, Ace);
  } else if (equal(in, "/Temp", 5)) {
    intToChar(out, Temp);
  } else if (equal(in, "Y", 1)) {
    out[0] = 0;
    if (Acetone > 999) charBuilder(out, "PPM");
    else charBuilder(out, "PPB");
  } else if (equal(in, "NUMOut", 6)) {
    if (numOut < 1000) {
      int value = toInt(in, 6, index(in, 0, 0, FILELINE));
      numOut = numOut * 10;
      numOut += value;
    }
  } else if (equal(in, "NUM2", 4)) {
    intToChar(out, numOut);
  } else if (equal(in, "NUM", 3)) {
    intToChar(out, num);
    numOut = 0;
  } else if (equal(in, "T.", 2)) {
    intToChar(out, tempicher);
  }
  //moves number out to eeprom
  else if (equal(in, "NtoE", 4)) {
    if (numOut > 99 && Current <= 6) numOut = 99;
    if (numOut > 60 && (Current == 7 || Current == 8)) numOut = 60;
    EEPROM.write(Current, numOut);
  }
  //move numbers to stadus
  else if (equal(in, "Stadus", 5)) {
    if (Current == 1) {
      if (numOut > 60) numOut = 60;
      Ace = numOut;
    } else if (Current == 2) {
      if (numOut > 99) numOut = 99;
      time1 = numOut * 60;
      timeS1 = time1;
    } else if (Current == 3) {
      if (numOut > 60) numOut = 60;
      Temp = numOut;
    } else if (Current == 4) {
      if (numOut > 99) numOut = 99;
      time3 = numOut * 60;
      timeS3 = time3;
    } else if (Current == 5) {
      num = Ace;
    } else if (Current == 6) {
      num = (time1 + 59) / 60;
    } else if (Current == 7) {
      num = Temp;
    } else if (Current == 8) {
      num = (time3 + 59) / 60;
    }
  }
  //updates the bars on stadis
  else if (equal(in, "UpDate", 6)) {
    special(NULL, "Clock", tft);
    Var("Bar3", ((1.0 * timeS3 - time3) / timeS3 * 150), tft);
    Var("Bar1", ((1.0 * timeS1 - time1) / timeS1 * 150), tft);
    Var("Bar2", ((1.0 * timeS2 - time2) / timeS2 * 150), tft);
  } else if (equal(in, "Clock", 5)) {

    if (time1 > 0) {
      time1--;
      if (time1 > 1) Serial1.println("Run 2");
      Serial1.print("setAcetone ");
      Serial1.println(Ace);
      Serial1.println("setCircFan 1");
      Serial1.println("setServo 1");
    } else if (Acetone > Clean) {
      
      Serial1.println("setFilter 1");
      Serial1.println("setTemp 0");
      Serial1.println("setServo 1");
      time2--;  //make in to equation to estimate time
    } else if (time3 > 0) {
      time3--;
      Serial1.println("setFilter 0");
      Serial1.print("setTemp ");
      Serial1.println(Temp);
      Serial1.println("setServo 1");
    } else {
      Serial1.println("Run 0");
      Serial1.println("setTemp 0");
      Serial1.println("setFilter 0");
      Serial1.println("setCircFan 0");
      Serial1.println("setServo 0");
    }

  }
  //returns the curent time for each bar
  else if (equal(in, "Bar", 3)) {
    short row = toInt(in, 3, index(in, 0, 0, FILELINE));
    if (row == 1) {
      intToChar(out, (time1 + 59) / 60);
    }
    if (row == 2) {
      intToChar(out, (time2 + 59) / 60);
    }
    if (row == 3) {
      intToChar(out, (time3 + 59) / 60);
    }
  }
  //total remaning time
  else if (equal(in, "Total", 5)) {
    intToChar(out, (time1 + time2 + time3 + 59) / 60);
    if (time1 < 1 && time2 < 1 && time3 == 1) {
      tft.fillRoundRect(8, 178, 102 - 8, 235 - 178, 10, 1984);
      tft.setCursor(19, 195);
      tft.setTextColor(0);
      tft.setTextSize(3);
      tft.println("Done");
    }

  } else if (equal(in, "DispBeep", 8)) {
    if (!Buzz) {
      tft.fillRoundRect(170, 190, 310 - 170, 235 - 190, 10, 46518);
      tft.setCursor(182, 205);
      tft.setTextColor(65535);
      tft.setTextSize(2);
      tft.println("Buzzer OFF");

    } else {
      tft.fillRoundRect(170, 190, 310 - 170, 235 - 190, 10, 1247);
      tft.setCursor(182, 205);
      tft.setTextColor(65535);
      tft.setTextSize(2);
      tft.println("Buzzer ON");
    }
  } else if (equal(in, "CBeep", 5)) {
    if (Buzz) {
      Buzz = 0;
      tft.fillRoundRect(170, 190, 310 - 170, 235 - 190, 10, 46518);
      tft.setCursor(182, 205);
      tft.setTextColor(65535);
      tft.setTextSize(2);
      tft.println("Buzzer OFF");

    } else {
      Buzz = 1;
      tft.fillRoundRect(170, 190, 310 - 170, 235 - 190, 10, 1247);
      tft.setCursor(182, 205);
      tft.setTextColor(65535);
      tft.setTextSize(2);
      tft.println("Buzzer ON");
      //beep the buzzer
      for (int i = 0; i < 100000 / (2 * pitch) && Buzz; i++) {
        digitalWrite(buzzer, HIGH);
        delayMicroseconds(pitch);
        digitalWrite(buzzer, LOW);
        delayMicroseconds(pitch);
      }
    }
    EEPROM.write(9, Buzz);

  } else if (equal(in, "Beep", 4)) {
    for (int i = 0; i < 100000 / (2 * pitch) && Buzz; i++) {
      digitalWrite(buzzer, HIGH);
      delayMicroseconds(pitch);
      digitalWrite(buzzer, LOW);
      delayMicroseconds(pitch);
    }

  } else if (equal(in, "/Return", 7)) {
    old = 1;
  } else {
    int i = 0;
    for (; in[i] != 0; i++)
      out[i] = in[i];
    out[i] = 0;
  }
}

void Var(const char* in, int value, Elegoo_TFTLCD& tft) {

  if (equal(in, "EEPROM", 6)) {
    EEPROM.write(toInt(in, 6, index(in, 0, 0, FILELINE)), value);
  } else if (equal(in, "EtoN", 4)) {
    num = EEPROM.read(value);
  } else if (equal(in, "NtoE", 4)) {
    if (numOut > 99 && Current <= 6) numOut = 99;
    if (numOut > 60 && (Current == 7 || Current == 8)) numOut = 60;
    EEPROM.write(value, numOut);
  } else if (equal(in, "Current", 7)) {
    Current = value;
  } else if (equal(in, "Bar", 3)) {
    short row = toInt(in, 3, index(in, 0, 0, FILELINE));
    if (value > 150) value = 150;
    if (row == 1) {
      tft.fillRect(95, 57, value, 78 - 57, 1984);
    }
    if (row == 2) {
      tft.fillRect(95, 97, value, 118 - 97, 1984);
    }
    if (row == 3) {
      tft.fillRect(95, 137, value, 158 - 137, 1984);
    }
  } else if (equal(in, "Select", 6)) {
    Ace = EEPROM.read(7);
    Temp = EEPROM.read(8);
    short row = toInt(in, 6, index(in, 0, 0, FILELINE));
    if (row == 1) {
      timeS1 = EEPROM.read(value) * 60;
      time1 = timeS1;
    }
    if (row == 3) {
      timeS3 = EEPROM.read(value) * 60;
      time3 = timeS3;
    }
  }
}

bool stop = false;

void serial(const char* in, Elegoo_TFTLCD& tft) {
  Serial.println(in);

  if (equal(in, "KILL", 1) && !stop) {
    stop = true;
    parse("Run(estop.txt)", tft);
  } else if (equal(in, "OPEN", 4)) {
    parse("Run(lid.txt)", tft);
  } else if (equal(in, "CLOSE", 5)) {
    old = 1;
  } else if (equal(in, "FILTER", 6)) {
    parse("Run(filter.txt)", tft);
  }  
  else if (equal(in, "ACETONE", 7)) {
    Acetone = toInt(in, 8, index(in, 0, 0, FILELINE) - 1);
  } else if (equal(in, "TEMP", 4)) {
    tempicher = toInt(in, 5, index(in, 0, 0, FILELINE) - 1);
  }
}
