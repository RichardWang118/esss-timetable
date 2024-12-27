#include "network.h"
#include <Arduino.h>

// sets the esp32 to be an access point and a station connected to another access point
// WiFi.mode(WIFI_AP_STA)

// WIFI SSID and Password (DO NOT COMMIT TO PUBLIC REPO)
const char* ssid = "ssid";
const char* password = "password";

// initialize Wifi network connection
void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}