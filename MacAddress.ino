// /*
//   This program outputs the MAC address of the 
//   Airlift Wifi Featherwing Processor.

//   If the MAC address is needed, run this program.
// */

// #include <SPI.h>
// #include <WiFiNINA.h>

// // Pin definitions for Airlift Wifi Featherwing
// #define SPIWIFI       SPI    // The SPI port
// #define SPIWIFI_SS    13     // Chip select pin
// #define ESP32_RESETN  12     // Reset pin
// #define SPIWIFI_ACK   11     // BUSY or READY pin
// #define ESP32_GPIO0   -1     // GPIO0 pin (not used)

// // Function prototype
// void _printMacAddress(byte mac[]);

// // Function to print the MAC address of Airlift Wifi Featherwing
// void print_mac_address() {
//   Serial.begin(115200);

//   while (!Serial) {
//     ; // wait for serial port to connect. Needed for native USB port only
//   }

//   Serial.println("Running Airlift Wifi Featherwing Mac Address Output Program");

//   // Set up WiFi module pins
//   WiFi.setPins(SPIWIFI_SS, SPIWIFI_ACK, ESP32_RESETN, ESP32_GPIO0, &SPIWIFI);

//   // Check for the WiFi module:
//   while (WiFi.status() == WL_NO_MODULE) {
//     Serial.println("Communication with WiFi module failed!");
//     // Don't continue until the WiFi module is available
//     delay(1000);
//   }

//   // Read and print the MAC address
//   byte mac[6];
//   WiFi.macAddress(mac);
//   Serial.print("MAC: ");
//   _printMacAddress(mac);
// }

// // Function to print MAC address in a readable format
// void _printMacAddress(byte mac[]) {
//   for (int i = 5; i >= 0; i--) {
//     // Add leading zero for single-digit values
//     if (mac[i] < 16) {
//       Serial.print("0");
//     }
//     Serial.print(mac[i], HEX);
//     if (i > 0) {
//       Serial.print(":");
//     }
//   }
//   Serial.println();
// }

