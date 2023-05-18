#define gasSensor1 A1
#define gasSensor2 A2
#define gasSensor3 A3

//  This function returns the analog data to calling function
int readSensor(int sensor) {
  unsigned int sensorValue = analogRead(sensor);  // Read the analog value from sensor
  unsigned int outputValue = map(sensorValue, 0, 1023, 0, 255); // map the 10-bit data to 8-bit data
  return outputValue;             // Return analog moisture value
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print("Sensor 1: ");
  Serial.print(readSensor(A1));

  Serial.print("  Sensor 2: ");
  Serial.print(readSensor(A2));

  Serial.print("  Sensor 3: ");
  Serial.println(readSensor(A3));

  delay(1000);
}
