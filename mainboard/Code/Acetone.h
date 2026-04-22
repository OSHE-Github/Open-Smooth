// Author: Austin Deegan
// Date: 10/10/25
// Discription: controls a sprayer and alcahall sencer.

// coments in Acetone.cpp

#ifndef Acetone_h
#define Acetone_h
#include <Wire.h>
#include "Adafruit_SGP30.h"

class bomb{

public:

  bomb(int ultrsonic, int fan);

  void setAcetone(int set);

  void runFilter(bool run);

  void Setup();
  
  long getAcetone();

  int getPresent();

  bool getFilter();

  void kill();

  void run(bool ace);

  void pause();
};



#endif