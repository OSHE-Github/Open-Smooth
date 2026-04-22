// Refrence: https://www.instructables.com/Temperature-Sensor-Using-Thermistor-With-Arduino-U/
// Author: Austin Deegan
// Date: 11/3/25
// Discription: Outputs the tempacher with and analog input
#include "Thermister.h"
#include <Arduino.h>

//vars
static  int timeDelay = 1000; // how long between each mesherment
static double out = 0;
static double out2 = 0;
static unsigned long time = -timeDelay;
static int pin2;

//Inishalise. Input <Analog Pin>
NTC_100k::NTC_100k(int pin){
  pinMode(pin,INPUT); 
  pin2 = pin;
}

//Returns the curent temp.
//Input <True if want in Farenhight> 
double NTC_100k::readNow(bool Faren){
  
  double temp; // alot of fun math
  temp = analogRead(A0) * (5.0 / 1023.0);
  temp = (100000 * temp) / (5.0 - temp);  // Assuming 100k series resistor
  temp = (1.0 / ( (1.0 / 298.15) + (1.0 / 3950.0) * log(temp / 100000))) - 273.15;
  if(Faren) out = ((temp* 9.0/5)+32); // converted to farenhight
  else out = temp;
  return out;
}

//Returns the curent temp in dlayed segments. 
//Input <True if want in Farenhight>  
double NTC_100k::read(bool Faren){ // input alalog read and true for farenhight

  if(time + timeDelay < millis()){ // a delay in how fast meshrments are taken.
    out2 = readNow(Faren);
    time = millis();
  }

  return out2;
}


