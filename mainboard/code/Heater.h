// Author: Austin Deegan
// Date: 10/20/25
// Discription: controls a heater with bang bang controls

#include "Thermister.h"

// coments in Heater.cpp

#ifndef Heater_h
#define Heater_h

class RelayHeater{

public:

  RelayHeater(int pin, int fan, NTC_100k thermister); 

  double setTemp(double Temp, bool Faren);

  void kill();

  void pause();

  bool curentFan();

  void runFan(bool on);

  double read(bool Faren);

  double curentSet(bool Faren);

  void run();

};

#endif