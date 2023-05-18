#include <Arduino.h>
#include <stdarg.h>

#include "GasSensor.h"

//  This function returns the analog data to calling function
int readSensor(int sensor) {
  unsigned int sensorValue = analogRead(sensor);  // Read the analog value from sensor
  unsigned int outputValue = map(sensorValue, 0, 1023, 0, 255); // map the 10-bit data to 8-bit data
  return outputValue;             // Return analog moisture value
}

int averagedSensors(int sensors, ...) {
  va_list arguments;
  float sum;

  va_start(arguments, sensors);

  for (int i=0; i<sensors; i++) {
    sum += readSensor(va_arg(arguments, int));
  }
  va_end(arguments);

  return round(sum/sensors);
}