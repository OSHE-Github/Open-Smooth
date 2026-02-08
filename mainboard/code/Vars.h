// This file is for all globle varibles and paramiders 

#include <Arduino.h>
#ifndef Vars_h
#define Vars_h

//needs to be rewrten and formated
short thmist = A0;
short button = 2, fanHeater = 8, fan1 = 12, fanPin = 11, ultrasonic = 9, heaterPin = 10, encloser = 13;//other pins
int heatMax = 100;//in C
bool farenhight = false;
unsigned long time = 0;
bool fan = false;
int timer = 0;

#endif