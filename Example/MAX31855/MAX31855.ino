#include <Meke_MAX31855.h>

#define CS   10
Meke_MAX31855 thermocouple(CS);

void setup() {
  Serial.begin(9600);
  delay(500);
}

void loop() {

  Serial.print("Internal Temp = ");
  printTemperature(thermocouple.readInternal());

  Serial.print("Thermocouple Temp = ");
  printTemperature(thermocouple.readThermocouple());
  Serial.println();

  delay(1000);
}


// Print the temperature, or the type or fault
void printTemperature(double temperature) {
  switch ((int) temperature) {
    case -276:
      Serial.print("FAULT_OPEN");
      break;
    case -277:
      Serial.print("FAULT_SHORT_GND");
      break;
    case -278:
      Serial.print("FAULT_SHORT_VCC");
      break;
    case -275:
      Serial.print("NO_MAX31855");
      break;
    default:
      Serial.print(temperature);
      break;
  }
  Serial.print("   ");
}

