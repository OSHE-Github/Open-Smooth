#include "var.h"

#include <SD.h>
#include <SPI.h>

#include <Elegoo_GFX.h>    // Core graphics library
#include <Elegoo_TFTLCD.h> // Hardware-specific library
#include <TouchScreen.h>

void parse(String in, Elegoo_TFTLCD tft);
String special(String in);

int input[7];
char Fileline [40];

void read(File file, Elegoo_TFTLCD tft){
  while(file.available()){
    for(int i = 0; i < 40; i++){
      Fileline[i] = file.read();
      if (Fileline[i]==10){
        Fileline[i] = 0;
        break;
      } 
    }
    parse(String(Fileline), tft);
  }
}

void parse( String in, Elegoo_TFTLCD tft){
  int next = in.indexOf('(')+1;
  int end;
  String comand = in.substring(0, next-1);
  //Serial.println(comand);

  for(int i = 0; i<7; i++){
    end = in.indexOf(',',next);
    if (end == -1) {
      end = in.indexOf(')',next);
      input[i] = in.substring(next, end).toInt();
      break;
    }
    input[i] = in.substring(next, end).toInt();
    next = end + 1;

  }

  if(comand.equalsIgnoreCase("button")){
    buttons [bCount][0] = input[0];
    buttons [bCount][1] = input[1];
    buttons [bCount][2] = input[2];
    buttons [bCount][3] = input[3];
    bCount++;
    //save output comand on press
  }
  else if(comand.equalsIgnoreCase("Rectangle")){
    tft.fillRect(input[0],input[1],input[2]-input[0],input[3]-input[1],input[4]);
  }
  else if(comand.equalsIgnoreCase("Circle")){
    tft.fillCircle(input[0],input[1],input[2],input[3]);
  }
  else if(comand.equalsIgnoreCase("RoundRect")){
    tft.fillRoundRect(input[0],input[1],input[2]-input[0],input[3]-input[1],input[4],input[5]);
  }
  else if(comand.equalsIgnoreCase("Line")){
    tft.drawLine(input[0],input[1],input[2],input[3],input[4]);
  }
  else if(comand.equalsIgnoreCase("Clear")){
    tft.fillScreen(input[0]);
    bCount = 0;
    SD.remove(update);
  }
  else if(comand.equalsIgnoreCase("Text")){
    tft.setCursor(input[1],input[2]);
    tft.setTextColor(input[4]);
    tft.setTextSize(input[3]);
    tft.println(special(in.substring(5,in.indexOf(','))));
  }
  else if(comand.equalsIgnoreCase("Textupdate")){
    File text = SD.open(update, FILE_WRITE);
    text.print("Rectangle(");
    String coma = ",";
    String end = ")";
    String out =  input[1] + coma + input[2] + coma + (input[1]+input[3]*6*input[4])  + coma + (input[2]+input[3]*8) + coma + input[5] + end;
    text.println(out);

    text.print("text(");
    text.print(in.substring(11,in.indexOf(',')));
    out = coma + input[1] + coma + input[2] + coma + input[3] + coma + input[6] + end;
    text.println(out);
    text.close();
  }
  else if(comand.equalsIgnoreCase("Rotation")){
    tft.setRotation(input[0]);
  }
  else if(comand.equalsIgnoreCase("Run")){
    File file = SD.open(in.substring(4,in.indexOf(')')));
    read(file, tft);
    file.close();
  }
}

String special(String in){

  if(in.equalsIgnoreCase("EPROM1")){
    return (String)0;
  }
  else if(in.equalsIgnoreCase("X")){
    if(x>999) return (String) (x/1000);
    else return (String)x;
  }
  else if(in.equalsIgnoreCase("Y")){
    if(x>999) return "PPM";
    else return "PPB";

  }

  return in;
}

