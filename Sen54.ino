// Include necessary libraries
#include <Arduino.h>
#include <SensirionI2CSen5x.h>
#include <Wire.h>
#include "SensorData.h"

// Define a maximum buffer requirement for I2C
#define MAXBUF_REQUIREMENT 48

// Check if I2C buffer length is sufficient for the requirement
#if (defined(I2C_BUFFER_LENGTH) &&                \
    (I2C_BUFFER_LENGTH >= MAXBUF_REQUIREMENT)) || \
    (defined(BUFFER_LENGTH) && BUFFER_LENGTH >= MAXBUF_REQUIREMENT)
#define USE_PRODUCT_INFO
#endif

// Create an instance of SensirionI2CSen5x
SensirionI2CSen5x sen5x;

/**
 * Set up basic configurations for Sensirion SEN54.
 */
void setup_basic_sen54() {
    // Begin serial communication
    Serial.begin(115200);

    // Wait for the serial port to be ready
    // while (!Serial) {
    //     delay(100);
    // }

    // Initialize the Wire library for I2C communication
    Wire.begin();

    // Initialize the Sensirion sensor
    sen5x.begin(Wire);

    // Reset the sensor device
    uint16_t error;
    char errorMessage[256];
    error = sen5x.deviceReset();
    if (error) {
        Serial.print("Error trying to execute deviceReset(): ");
        errorToString(error, errorMessage, 256);
        Serial.println(errorMessage);
    }

    // Set temperature offset (if applicable)
    float tempOffset = 0.0;
    if (!error) {
        error = sen5x.setTemperatureOffsetSimple(tempOffset);
        if (error) {
            Serial.print("Error trying to execute setTemperatureOffsetSimple(): ");
            errorToString(error, errorMessage, 256);
            Serial.println(errorMessage);
        } else {
            Serial.print("Temperature Offset set to ");
            Serial.print(tempOffset);
            Serial.println(" deg. Celsius (SEN54/SEN55 only)");
        }
    }

    // Start sensor measurement
    error = sen5x.startMeasurement();
    if (error) {
        Serial.print("Error trying to execute startMeasurement(): ");
        errorToString(error, errorMessage, 256);
        Serial.println(errorMessage);
    }
}

/**
 * Read and return sensor data from Sensirion SEN54.
 *
 * Returns:
 *     SensorData: The sensor data.
 */
SensorData get_sen54_data() {
    // Delay for sensor stabilization
    delay(1000);

    // Read sensor measurements
    float massConcentrationPm1p0;
    float massConcentrationPm2p5;
    float massConcentrationPm4p0;
    float massConcentrationPm10p0;
    float ambientHumidity;
    float ambientTemperature;
    float vocIndex;
    float noxIndex;

    uint16_t error = sen5x.readMeasuredValues(
        massConcentrationPm1p0, massConcentrationPm2p5, massConcentrationPm4p0,
        massConcentrationPm10p0, ambientHumidity, ambientTemperature, vocIndex,
        noxIndex);

    if (error) {
        // Handle error during measurement
        Serial.print("Error trying to execute readMeasuredValues(): ");
        char errorMessage[256];
        errorToString(error, errorMessage, 256);
        Serial.println(errorMessage);

        // Return invalid sensor data
        return SensorData{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, false};
    } else {
        // Return valid sensor data
        return SensorData{massConcentrationPm1p0, massConcentrationPm2p5, massConcentrationPm4p0,
                          massConcentrationPm10p0, ambientHumidity, ambientTemperature, vocIndex,
                          noxIndex, true};
    }
}