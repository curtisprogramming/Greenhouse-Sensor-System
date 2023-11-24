#include <Arduino.h>
#include "SensorData.h"

/**
 * Arduino setup function.
 * Initializes serial port, sets up SEN-54 sensor, and configures ThingSpeak communication.
 */
void setup() {
    Serial.begin(115200);
    setup_basic_sen54();
    setupThingSpeakCommunication();
}

/**
 * Arduino loop function.
 * Updates sensor data and introduces a delay of 15 seconds. (8000 a day, the free limit)
 */
void loop() {
    updateSensorData();
    delay(15000);
}


