
//include varible file and a config file
#include "config.h"

//include librarys
#include <SD.h>
#include <SPI.h>


//create a file object
File file;
//File fileRun;
//function prototypes
void sd(const char* in, Elegoo_TFTLCD &tft);
void parse(char* in, Elegoo_TFTLCD &tft);
int index(const char* in, char c, int start, int size);
void subchar(char* out, const char* in, int start, int end);
unsigned int toInt(const char* in, int start, int end);
bool equal(const char* in, const char* test, int size);

//reads out a file and sends it to be parsed
void read(File &file, Elegoo_TFTLCD &tft){
  while(file.available()){
    
    for(int i = 0; i < FILELINE; i++){
      Fileline[i] = file.read();
      if (Fileline[i]==10){
        Fileline[i] = 0;
        for(int j = i; j < FILELINE; j++){
          Fileline[j] = 0;
        }
        break;
      } 
    }
    parse(Fileline, tft);
  }
}

//parses and runs input char arrays
void parse( char* in, Elegoo_TFTLCD &tft){

  //looks for ( and saves it 
  int next = index(in,'(',0,FILELINE)+1;
  int end;

  //seporat out the comand inculding the first (
  subchar(comand, in, 0, next);

  //seporats out the numbers from the comand
  for(int i = 0; i<7; i++){
    end = index(in,',',next+1,FILELINE);
    //if no , look for the end
    if (end == -1) {
      end = index(in,')',next,FILELINE);
      input[i] = toInt(in,next,end);
      break;
    }
    input[i] = toInt(in,next,end);
    next = end + 1;
  }

  //start of pasrsing 
  //Serial.println(comand);
  //new button(comand,x,y,x2,y2)
  if(equal(comand,"Button",6)){
    
    //the curent file is closes to save memory
    filePosition = file.position();
    strcpy(fileName,file.name());
    file.close();
    delay(5);
    //saves button to file and array
    file = SD.open(bFile, FILE_WRITE);
    buttons [bCount][0] = input[1];
    buttons [bCount][1] = input[2];
    buttons [bCount][2] = input[3];
    buttons [bCount][3] = input[4];
    bCount++;
    char f[FILELINE];
    subchar( f, in, 7, index( in, ',', 0, 40));
    file.println(f);
    //close the buuton file 
    file.close();
    delay(5);

    //reopen and return to position of curent file
    file = SD.open(fileName);
    fileName[0]=0;
    file.seek(filePosition);
  }
  //drawas a Rectangle(x,y,x2,y2,color)
  else if(equal(comand,"Rectangle", 9)){
    tft.fillRect(input[0],input[1],input[2]-input[0],input[3]-input[1],input[4]);
  }
  //drawas a Circle(x,y,r,color)
  else if(equal(comand,"Circle", 6)){
    tft.fillCircle(input[0],input[1],input[2],input[3]);
  }
  //drawas a Round corner Rectangle (x,y,x2,y2,r,color)
  else if(equal(comand,"RoundRect", 9)){
    tft.fillRoundRect(input[0],input[1],input[2]-input[0],input[3]-input[1],input[4],input[5]);
  }
  //draws a line(x,y,x2,y2,color)
  else if(equal(comand,"Line", 4)){
    tft.drawLine(input[0],input[1],input[2],input[3],input[4]);
  }
  //draws a triangle(x,y,x2,y2,x3,y3,color)
  else if(equal(comand,"Triangle",8)){
    tft.fillTriangle(input[0],input[1],input[2]-input[0],input[3]-input[1],input[4],input[5],input[6]);
  }
  //clears screen(color), buttons, and update text 
  else if(equal(comand,"Clear", 5)){
    tft.fillScreen(input[0]);
    bCount = 0;
    SD.remove(update);
    SD.remove(bFile);
  }
  else if(equal(comand,"Delay", 5)){
    delay(input[0]);
  }
  //prints text(text,x,y,thichness,color)
  else if(equal(comand,"Text(", 5)){    
    subchar(in, in, 5, index( in, ',', 0, FILELINE));
    special(in,in,tft);
    tft.setCursor(input[1],input[2]);
    tft.setTextColor(input[4]);
    tft.setTextSize(input[3]);
    tft.println(in);
  }
  //adds text that will update as set intervals UpdateText(text,x,y,size,espaeted chars, cover color, text color)
  else if(equal(comand,"UpdateText", 10)){
    filePosition = file.position();
    strcpy(fileName,file.name());
    file.close();
    delay(5);
    file = SD.open(update, FILE_WRITE);

    file.print("Rectangle(");
    char coma[] = {',',0};
    char end[] = {')',0};
    
    char out[40];
    char temp[10];
    out[0] = 0;
    intToChar(temp,input[1]);
    charBuilder(out,temp);
    charBuilder(out,coma);

    intToChar(temp,input[2]);
    charBuilder(out,temp);
    charBuilder(out,coma);

    intToChar(temp,(input[1]+input[3]*6*input[4]));
    charBuilder(out,temp);
    charBuilder(out,coma);

    intToChar(temp,(input[2]+input[3]*8));
    charBuilder(out,temp);
    charBuilder(out,coma);

    intToChar(temp,input[5]);
    charBuilder(out,temp);
    charBuilder(out,end);

    file.println(out);
 
    file.print("Text(");

    subchar( out, in, 11, index( in, ',', 0, 40));
    file.print(out);

    out[0] = 0;

    charBuilder(out,coma);
    intToChar(temp,input[1]);
    charBuilder(out,temp);
    charBuilder(out,coma);

    intToChar(temp,input[2]);
    charBuilder(out,temp);
    charBuilder(out,coma);

    intToChar(temp,input[3]);
    charBuilder(out,temp);
    charBuilder(out,coma);

    intToChar(temp,input[6]);
    charBuilder(out,temp);
    charBuilder(out,end);

    file.println(out);

    file.close();
    delay(5);
     
    file = SD.open(fileName);
    fileName[0]=0;
    file.seek(filePosition);
  }
  //sets the screen ratation(0-3)
  else if(equal(comand,"Rotation", 8)){
    tft.setRotation(input[0]);
  }
  //runs a file. old file will be closed and not reopended
  else if(equal(comand,"Run", 3)){
    subchar( fileName, in, 4, index( in, ')', 4, 40));
    sd( fileName, tft);
  }
  //prints out to serial
  else if(equal(comand,"Serial", 6)){
    char temp[40];
    subchar(temp, in, 7, index( in, ')', 0, FILELINE));
    Serial1.println(temp);
    Serial.println(temp);
  }
  //runs a text comand in config
  else if(equal(comand,"Word", 4)){
    char temp[40];
    subchar(temp, in, 5, index( in, ')', 0, FILELINE));
    special(temp, temp, tft);
  }
  //runs a text comand in config that exseps a int in
  else if(equal(comand,"Var", 3)){
    char temp[40];
    subchar(temp, in, 4, index( in, ',', 0, FILELINE));
    Var(temp, input[1], tft);
  }
  else if(equal(comand,"Save", 4)){
    subchar(OldFile, in, 5, index( in, ')', 0, FILELINE));
  }
}

//opens a file then sends it to be read
void sd( const char* in, Elegoo_TFTLCD &tft) {//fix
  if(file) {
    file.close();
    delay(50);
  }
  file = SD.open(in);
  
  if(!file) return;
  else fileName[0]=0;
  read(file, tft);
  file.close();
}


