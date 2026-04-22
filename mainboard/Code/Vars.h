// This file is for all globle varibles and paramiders 

#include <Arduino.h>
#ifndef Vars_h
#define Vars_h

//pins
short thmist = A0;
short button = 2, fanHeater = 8, fan1 = 12, fanPin = 11, ultrasonic = 9, heaterPin = 10, encloser = 3;//other pins

//max heater before estop
int heatMax = 65;//in C
//farenhight or celsies 
bool farenhight = false;
//timer
unsigned long time = 0;
int timer = 0;
//fan control
bool fan = false;
//lid open 
bool open = false;
//how many neo pixels there are
int ledCount = 50;

#endif