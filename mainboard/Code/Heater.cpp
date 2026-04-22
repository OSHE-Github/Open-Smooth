// Author: Austin Deegan
// Date: 10/20/25
// Discription: controls a heater with bang bang controls

#include "Heater.h"
#include "Thermister.h"
#include <Arduino.h>

//vars
static double target = 0;
static int pin2, fan0;
static NTC_100k heat(0);
static bool fanP = false;
static unsigned long time = 0;
static int milliSec = 3000;
static bool fire = false;
//inishalise. Input <heater pin> <fan pin> <NTC_100k object>
RelayHeater::RelayHeater(int pin, int fan, NTC_100k thermister){ 
  pinMode(pin, OUTPUT);
  pinMode(fan, OUTPUT);
  pin2 = pin;
  fan0 = fan;
  heat = thermister;
}

// Sets the target tempacher. 0 to disable. 
//Must constently call run or will over heat.
//Input <temp in F or C> <True if Farenhight> 
double RelayHeater::setTemp(double Temp, bool Faren){
  double old = Temp;
  target = Temp;
  if(Faren) target = (target - 32) * 5/9;
  return old;
}

// Shuts off the heater. No longer need to call run 
void RelayHeater::kill(){
  target = 0;
  digitalWrite(pin2,LOW);
  digitalWrite(fan0,HIGH);
}

//disables heater until next run comand
void RelayHeater::pause(){
  digitalWrite(pin2,LOW);
}

//Returns the tempacher of the heater.
//Input <True if want in Farenhight> 
double RelayHeater::read(bool Faren){
  return heat.read(Faren);
}

//Returns if fan is on (true) or off (false)
bool RelayHeater::curentFan(){
  return fanP;
}

//Manulay control a fan
//Input <set true to run fan> 
void RelayHeater::runFan(bool on){
  if(on) digitalWrite(fan0,HIGH);
  else digitalWrite(fan0,LOW);
  fanP = on;
}

//Returns the curent target of the heater
//Input <True if want in Farenhight> 
double RelayHeater::curentSet(bool Faren){
  if(Faren && target!=0) return ((target * 9.0/5)+32); // converted to farenhight
  return target;
}

// MUST constntly call to run the heater
//curently bad and untested implemented
void RelayHeater::run(){
  if(target > 10){
     digitalWrite(fan0,HIGH);
     fanP = true;
  }
  // else{
  //   digitalWrite(fan0,LOW);
  //    fanP = false;
  // }
  if(heat.read(false)/10<target && target>0 && time + milliSec < millis() ){
    digitalWrite(pin2,HIGH);
    fire = true;
  }
  else{
    digitalWrite(pin2,LOW);
    if(fire){
      fire = false;
      time = millis();
    }
  } 
}



