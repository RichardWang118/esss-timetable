#include <Arduino.h>
#include "network.h"
#include <GxEPD2_BW.h>
#include <Fonts/FreeMonoBold12pt7b.h>

int ledPin = D9;  // Onboard LED
int userPin = D4; // Onboard User Push Button

#define PIN_EPD_BUSY 14
#define PIN_EPD_CS 13
#define PIN_EPD_RST 21
#define PIN_EPD_DC 22
#define PIN_EPD_SCK 18
#define PIN_EPD_MISO 19
#define PIN_EPD_MOSI 23

// e-paper display driver and size
#define MAX_HEIGHT 480
#define MAX_WIDTH 800
GxEPD2_BW<GxEPD2_750_T7, GxEPD2_750_T7::HEIGHT> display(
    GxEPD2_750_T7(PIN_EPD_CS, PIN_EPD_DC, PIN_EPD_RST, PIN_EPD_BUSY));

void initDisplay()
{
   Serial.println("init display");
   display.init(115200, true, 10, false);
   // remap spi
   SPI.end();
   SPI.begin(PIN_EPD_SCK,
             PIN_EPD_MISO,
             PIN_EPD_MOSI,
             PIN_EPD_CS);

   return;
}

void setup()
{
   delay(5000);
   Serial.begin(115200); // Set UART baud rate
   pinMode(ledPin, OUTPUT);

   // NOTE: D4 pin must be set as pullup, https://www.dfrobot.com/forum/topic/315558
   // Very fun to sift through the documentation and user forums to find this one
   pinMode(userPin, INPUT_PULLUP);

   // initWiFi();
   // Serial.print("RRSI: ");
   // Serial.println(WiFi.RSSI());

   initDisplay();

   Serial.println("init display2");
   display.setRotation(0); // landscape orientation
   display.setTextColor(GxEPD_BLACK);

   // Test display
   display.firstPage();
   do
   {
      display.fillScreen(GxEPD_WHITE); // Clear screen to white
      display.setCursor(0, 10);
      display.setFont(&FreeMonoBold12pt7b); // set font
      display.println("Rat");
   } while (display.nextPage());
}

void loop()
{
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

   static unsigned long lastUpdate = 0;
   if (millis() - lastUpdate > 10000) // Update every 10 seconds
   {
      lastUpdate = millis();

      display.firstPage();
      do
      {
         display.fillScreen(GxEPD_WHITE); // Clear screen to white
         display.setCursor(0, 10);
         display.setFont(&FreeMonoBold12pt7b);
         display.println("Rat2");
      } while (display.nextPage());
   }

   // refresh rate of 1 second*
   // *might not be accurate to say refresh rate, need to read further in docs
   // to see if inputs are interrupt driven or polled
   delay(1000);
}