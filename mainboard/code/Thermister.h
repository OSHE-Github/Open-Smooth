// Refrence: https://www.instructables.com/Temperature-Sensor-Using-Thermistor-With-Arduino-U/
// Author: Austin Deegan
// Date: 9/18/25
// Discription: Outputs the tempacher with and analog input

#ifndef Thermister_h
#define Thermister_h

class NTC_100k{

public:

  NTC_100k(int pin); // inishalize with analog pin

  double read(bool Faren); // input alalog read and true for farenhight

  double readNow(bool Faren); // input alalog read and true for farenhight
};


#endif