#include <Arduino.h>
#include "SensorData.h"

void setup() {

  //open serial port
  Serial.begin(115200);
  setup_basic_sen54();
  setupThingSpeakCommunication();

}

void loop() {

  updateSensorData();

  delay(15000);

}

