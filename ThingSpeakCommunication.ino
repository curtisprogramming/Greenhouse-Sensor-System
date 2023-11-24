#include <WiFiNINA.h>
#include "secrets.h"
#include "ThingSpeak.h"
#include "SensorData.h"

WiFiClient client;

unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

void setupThingSpeakCommunication() {

  Serial.begin(115200);

  wifiConnectionSetup();
  ThingSpeak.begin(client);  //Initialize ThingSpeak

}

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

    int field1_status = ThingSpeak.setField(1, sensor_data.ambientTemperature);
    int field2_status = ThingSpeak.setField(2, sensor_data.ambientHumidity);

    // write to the ThingSpeak channel
    int write_status = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
    if(write_status == 200){
      Serial.println("Channel update successful.");
    }
    else{
      Serial.println("Problem updating channel. HTTP error code " + String(write_status));
    }

  }

}