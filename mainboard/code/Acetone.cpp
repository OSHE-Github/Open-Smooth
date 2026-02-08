// Author: Austin Deegan
// Date: 1/7/26
// Discription: Outputs the tempacher with and analog input
#include "Acetone.h"
#include <Arduino.h>


//vars
Adafruit_SGP30 sgp;

static int fan2, ultrsonic2, aceA2, aceD2; 
static int target = 0;
bool fango = false;

//inishalises bomb
//input <ultrisonic pin> <alalog sencer pin> <digital sencer pin> <filtration fan>
bomb::bomb(int ultrsonic, int fan){
  pinMode(ultrsonic, OUTPUT);
  pinMode(fan, OUTPUT);
  fan2 = fan;
  ultrsonic2 = ultrsonic; 
}

//sets the target acetone
//input <target acetone[0-99]>
void bomb::setAcetone(int set){
  target = set;
  if(target > 100) target = 100;
}

void bomb::Setup(){
  //sgp.begin();
  Serial.println("\nSGP30 test");

  if (! sgp.begin()){
    Serial.println("Sensor not found :(");
    while (1);
  }
}

//filter controll
//input <true to run>
void bomb::runFilter(bool runF){
  fango = runF;
  if(fango) digitalWrite(fan2, HIGH);
  else digitalWrite(fan2, LOW);
}

//returns acetone reading[0-99] 
long bomb::getAcetone(){
  sgp.IAQmeasure();
  //Serial.println(sgp.eCO2);
  return sgp.TVOC;//ppb //might need to change to diftent setting
}

//returns the target acetone [0-99]
int bomb::getPresent(){
  return target;
}

//returns fillter oporation
bool bomb::getFilter(){
  return fango;
}

//stops ultrisonic, turns on fan, zeros target
void bomb::kill(){
  digitalWrite(fan2, HIGH);
  digitalWrite(ultrsonic2, LOW);
  target = 0;
  fango = true;

}

//runs the ultrisonic sencer. must contiuly call to update
//input <true if want ultrisonic to be active>
void bomb::run(bool ace){
  if(fango) digitalWrite(fan2, HIGH);
  else digitalWrite(fan2, LOW);

  if(getAcetone()<target && target>0 && ace) digitalWrite(ultrsonic2,HIGH);
  else digitalWrite(ultrsonic2,LOW);

}

//turns of ultrisonic. will resome if run is cald
void bomb::pause(){
  digitalWrite(ultrsonic2, LOW);  
}



