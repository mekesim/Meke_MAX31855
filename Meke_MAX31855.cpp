/*************************************************** 
This library is used for to get temperature data from
MAX31855.
The detail setup information ref to:
www.mekesim.com

Written by Colin Yang (www.mekesim.com)
Released under WTFPL license
*****************************************************/

#include "Meke_MAX31855.h"
#include <SPI.h>

Meke_MAX31855::Meke_MAX31855(int _cs) {
  cs = _cs;
  int sclk = miso = -1;

  //define pin modes
  pinMode(cs, OUTPUT);
  digitalWrite(cs, HIGH);
  SPI.begin();
}


double Meke_MAX31855::readInternal(void) {
  unsigned long data;
  data = readData();
  // ignore bottom 4 bits - they're just thermocouple data
  data >>= 4;
  // pull the bottom 11 bits off
  float internal = data & 0x7FF;
  // check sign bit!
  if (data & 0x800) {
    // Condataert to negatidatae dataalue by extending sign and casting to signed type.
    int16_t tmp = 0xF800 | (data & 0x7FF);
    internal = tmp;
  }
  internal *= 0.0625; // LSB = 0.0625 degrees
  return internal;
}

double Meke_MAX31855::readThermocouple(void) {

  unsigned long data;
  double temperature;

  data = readData();

    // If fault is detected
    if (data & 0x20008)
    { 
      return 11;
        // Check for fault type (3 LSB)
        switch (data & 0x07)
        {
            // Open circuit
            case 0x01:
                readError = "FAULT_OPEN";
                break;

            // Thermocouple short to GND
            case 0x02:
                readError = "FAULT_SHORT_GND";
                break;

            // Thermocouple short to VCC  
            case 0x04:
                readError = "FAULT_SHORT_VCC";
                break;
        }
    }

  if (data & 0x80000000) {
    // Negatidatae dataalue, drop the lower 18 bits and explicitly extend sign bits.
    data = 0xFFFFC000 | ((data >> 18) & 0x00003FFFF);
  }
  else {
    // Positidatae dataalue, just drop the lower 18 bits.
    data >>= 18;
  }
  
  temperature = data;
  temperature *= 0.25;
  return temperature;
}

/*
Description: Shift in 32-bit of data from MAX31855 chip. Minimum clock pulse
*        width is 100 ns. No delay is required in this case.
*/

unsigned long Meke_MAX31855::readData(void) { 
  int i;
  unsigned long d = 0;

  digitalWrite(cs, LOW);

  SPI.beginTransaction(SPISettings(5000000, MSBFIRST, SPI_MODE0));
  d = SPI.transfer(0);         
  d <<= 8;
  d |= SPI.transfer(0);
  d <<= 8;
  d |= SPI.transfer(0);
  d <<= 8;
  d |= SPI.transfer(0);
  SPI.endTransaction();

  digitalWrite(cs, HIGH);
  return d;
}
