#include <Arduino.h>
#include "network.h"

int ledPin = D9;  // Onboard LED 
int userPin = D4; // Onboard User Push Button

void setup()
{
   Serial.begin(115200); // Set UART baud rate
   pinMode(ledPin, OUTPUT); 

   // NOTE: D4 pin must be set as pullup, https://www.dfrobot.com/forum/topic/315558
   // Very fun to sift through the documentation and user forums to find this one
   pinMode(userPin, INPUT_PULLUP); 
   
   initWiFi();
   Serial.print("RRSI: ");
   Serial.println(WiFi.RSSI());
}

void loop()
{
   // Test line
   Serial.println(WiFi.RSSI());

   // Test for Wifi Connectivity 
   // Reset the ESP32 CPU with user push button
   if (digitalRead(userPin) == LOW)
   {
      digitalWrite(ledPin, HIGH);
      delay(1000);
      esp_restart();
   }
   else
   {
      digitalWrite(ledPin, LOW);
   }

   // refresh rate of 1 second*
   // *might not be accurate to say refresh rate, need to read further in docs
   // to see if inputs are interrupt driven or polled
   delay(1000);
}