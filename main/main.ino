#include "src/GasSensor.h"
#include "src/ParticleSensor.h"
#include <SoftwareSerial.h>

#define gasSensor1 A1
#define gasSensor2 A2
#define gasSensor3 A3

SoftwareSerial pmsSerial(62, 63); //A8 and A9
struct pms5003data data;


void gasSensorTest() {
  Serial.print("Sensor 1: ");
  Serial.print(readSensor(gasSensor1));
  Serial.print("  Sensor 2: ");
  Serial.print(readSensor(gasSensor2));
  Serial.print("  Sensor 3: ");
  Serial.print(readSensor(gasSensor3));
  Serial.print("  Averaged: ");
  Serial.println(averagedSensors(3, gasSensor1, gasSensor2, gasSensor3));
}

void ParticleSensorSetup() {
  pmsSerial.begin(9600);
}

void particleSensorTest() {
  bool notRead = 1;
  int timeout = 0;
  while (notRead) {
    if (readPMSdata(&pmsSerial, &data)) {
      notRead = 0;
      // reading data was successful!
      Serial.println();
      Serial.println("---------------------------------------");
      Serial.println("Concentration Units (standard)");
      Serial.print("PM 1.0: "); Serial.print(data.pm10_standard);
      Serial.print("\t\tPM 2.5: "); Serial.print(data.pm25_standard);
      Serial.print("\t\tPM 10: "); Serial.println(data.pm100_standard);
      Serial.println("---------------------------------------");
      Serial.println("Concentration Units (environmental)");
      Serial.print("PM 1.0: "); Serial.print(data.pm10_env);
      Serial.print("\t\tPM 2.5: "); Serial.print(data.pm25_env);
      Serial.print("\t\tPM 10: "); Serial.println(data.pm100_env);
      Serial.println("---------------------------------------");
      Serial.print("Particles > 0.3um / 0.1L air:"); Serial.println(data.particles_03um);
      Serial.print("Particles > 0.5um / 0.1L air:"); Serial.println(data.particles_05um);
      Serial.print("Particles > 1.0um / 0.1L air:"); Serial.println(data.particles_10um);
      Serial.print("Particles > 2.5um / 0.1L air:"); Serial.println(data.particles_25um);
      Serial.print("Particles > 5.0um / 0.1L air:"); Serial.println(data.particles_50um);
      Serial.print("Particles > 10.0 um / 0.1L air:"); Serial.println(data.particles_100um);
      Serial.println("---------------------------------------");
    }
    if (timeout++ > 20) {
      break;
    }
  }
}

void setup() {
  Serial.begin(115200);
  ParticleSensorSetup();
}

void loop() {
  delay(1000);
  gasSensorTest();  
  particleSensorTest();
}
