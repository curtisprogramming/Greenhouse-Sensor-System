#include <SPI.h>
#include <WiFiNINA.h>

// Pin definitions for Airlift Wifi Featherwing
#define SPIWIFI       SPI    // The SPI port
#define SPIWIFI_SS    13     // Chip select pin
#define ESP32_RESETN  12     // Reset pin
#define SPIWIFI_ACK   11     // BUSY or READY pin
#define ESP32_GPIO0   -1     // GPIO0 pin (not used)

#include "Secrets.h" 

///////please enter your sensitive data in the Secret tab/Secrets.h
char ssid[] = SECRET_SSID;   // your network SSID (name)
char pass[] = SECRET_PASS;   // your network password (use for WPA, or use as key for WEP)
int status = WL_IDLE_STATUS; // the Wifi radio's status

// Prototype function
void _printMacAddress(byte mac[]);

/**
 * Set up WiFi connection for Airlift Wifi Featherwing.
 */
void wifiConnectionSetup() {
    Serial.begin(115200);

    while (!Serial) {
        ; // wait for serial port to connect. Needed for native USB port only
    }

    Serial.println("Connecting to wifi network");

    // Set up WiFi module pins
    WiFi.setPins(SPIWIFI_SS, SPIWIFI_ACK, ESP32_RESETN, ESP32_GPIO0, &SPIWIFI);

    // Check for the WiFi module:
    while (WiFi.status() == WL_NO_MODULE) {
        Serial.println("Communication with WiFi module failed!");
        // Don't continue until the WiFi module is available
        delay(1000);
    }

    connectToWifi();
    printWifiDeviceInfo();
    printWifiInfo();
}

/**
 * Connect to WiFi network.
 */
void connectToWifi() {
    String fv = WiFi.firmwareVersion();
    if (fv < "1.0.0") {
        Serial.println("Please upgrade the firmware");
    }

    // Attempt to connect to Wifi network:
    while (status != WL_CONNECTED) {
        Serial.print("Attempting to connect to WPA SSID: ");
        Serial.println(ssid);
        // Connect to WPA/WPA2 network:
        status = WiFi.begin(ssid, pass);

        // Wait 10 seconds for connection:
        delay(10000);
    }
}

/**
 * Print Airlift Wifi Featherwing information.
 */
void printWifiDeviceInfo() {
    Serial.println("\nAirlift Wifi Featherwing Information: ");
    printMacAddress();
}

/**
 * Print WiFi information.
 */
void printWifiInfo() {
    Serial.println("\nWifi information:");

    if (status == WL_CONNECTED) {
        // Print the SSID of the network you're attached to:
        Serial.print("  SSID: ");
        Serial.println(WiFi.SSID());

        // Print the MAC address of the router you're attached to:
        byte bssid[6];
        WiFi.BSSID(bssid);
        Serial.print("  BSSID: ");
        _printMacAddress(bssid);

        // Print your board's IP address:
        IPAddress ip = WiFi.localIP();
        Serial.print("  IP Address: ");
        Serial.println(ip);

        // Print the received signal strength:
        long rssi = WiFi.RSSI();
        Serial.print("  Signal strength (RSSI): ");
        Serial.println(rssi);

        // Print the encryption type:
        byte encryption = WiFi.encryptionType();
        Serial.print("  Encryption Type: ");
        Serial.println(encryption, HEX);
        Serial.println();
    } else {
        Serial.println("  No network connection");
    }
}

/**
 * Print the MAC address of Airlift Wifi Featherwing.
 */
void printMacAddress() {
    // Read and print the MAC address
    byte mac[6];
    WiFi.macAddress(mac);
    Serial.print("  MAC: ");
    _printMacAddress(mac);
}

/**
 * Print MAC address in a readable format.
 */
void _printMacAddress(byte mac[]) {
    for (int i = 5; i >= 0; i--) {
        // Add leading zero for single-digit values
        if (mac[i] < 16) {
            Serial.print("0");
        }
        Serial.print(mac[i], HEX);
        if (i > 0) {
            Serial.print(":");
        }
    }
    Serial.println();
}
