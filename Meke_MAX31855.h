/*************************************************** 
This library is used for to get temperature data from
MAX31855.
The detail setup information ref to:
www.mekesim.com

Written by Colin Yang (www.mekesim.com)
Released under WTFPL license
*****************************************************/

#ifndef Meke_MAX31855_H
#define Meke_MAX31855_H

#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

class Meke_MAX31855 {
 public:
  Meke_MAX31855(int);

  double readInternal(void);
  double readThermocouple(void);  

 private:
  int cs, sclk, miso;
  unsigned long readData(void);
  char readError;
};

#endif