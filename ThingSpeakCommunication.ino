#include <WiFiNINA.h>
#include "secrets.h"
#include "ThingSpeak.h"
#include "SensorData.h"

WiFiClient client;

unsigned long myChannelNumber = SECRET_CH_ID;
const char *myWriteAPIKey = SECRET_WRITE_APIKEY;

/**
 * Set up ThingSpeak communication.
 */
void setupThingSpeakCommunication() {
    Serial.begin(115200);
    wifiConnectionSetup();
    ThingSpeak.begin(client);  // Initialize ThingSpeak
}

/**
 * Update sensor data on ThingSpeak.
 */
void updateSensorData() {
    connectToWifi();

    // Get sensor data
    SensorData sensor_data = get_sen54_data();

    if (sensor_data.valid_data) {
        Serial.println("\nSensor Data:");
        Serial.print("  Ambient Temperature: ");
        Serial.println(sensor_data.ambientTemperature);
        Serial.print("  Ambient Humidity: ");
        Serial.println(sensor_data.ambientHumidity);

        float temp_f = sensor_data.ambientTemperature * (9.0/5.0) + 32.0;

        int field1_status = ThingSpeak.setField(1, temp_f);
        int field2_status = ThingSpeak.setField(2, sensor_data.ambientHumidity);

        // Write to the ThingSpeak channel
        int write_status = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
        if (write_status == 200) {
            Serial.println("Channel update successful.");
        } else {
            Serial.println("Problem updating channel. HTTP error code " + String(write_status));
        }
    }
}
