#include <Meke_MAX31855.h>

#define CS   10
Meke_MAX31855 thermocouple(CS);

void setup() {
  Serial.begin(9600); 
  delay(500);
}

void loop() {

  double internal = thermocouple.readInternal();
   Serial.print("Internal Temp = ");
   Serial.println(internal);

   double Thermocouple = thermocouple.readThermocouple();
     Serial.print("C = "); 
     Serial.println(Thermocouple); 
   delay(1000);
}