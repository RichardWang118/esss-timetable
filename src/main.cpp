#include <Arduino.h>

// // put function declarations here:
// int myFunction(int, int);

// void setup() {
//   // put your setup code here, to run once:
//   int result = myFunction(2, 3);
// }

// void loop() {
//   // put your main code here, to run repeatedly:
// }

// // put function definitions here:
// int myFunction(int x, int y) {
//   return x + y;
// }

int ledPin = D9;    //Define LED pin 
void setup(){
   pinMode(ledPin, OUTPUT);// Set ledPin as output mode 
}

void loop(){
   digitalWrite(ledPin, HIGH);   // Outputting high, the LED turns on 
  //  delay(1000);     //Delay 1 second 
  //  digitalWrite(ledPin, LOW);  // Outputting low, the LED turns off
  //  delay(1000);           
}