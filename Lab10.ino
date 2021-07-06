SYSTEM_MODE(MANUAL);
SYSTEM_THREAD(ENABLED);
#include <Wire.h>
#include "oled-wing-adafruit.h"
#include <blynk.h>

OledWingAdafruit display;

void printToDisplay(String output)
{
  //reset display
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);

      //output to display
  display.println(output);
  display.display();
}
void setup() {
  //set up wire, display, and serial
  Serial.begin(9600);
  Wire.begin();
  display.setup();
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Test");
  display.display();

  //while (!Serial.isConnected());
  Serial.print("CONNECT PLS");
}

void loop() {

  while (!Serial.isConnected()); //DONT start until Serial is connected
  printToDisplay("SERIAL CONNECTED!");
  char x = Serial.read();
  //char x = '?';
  printToDisplay((String) x);

  
  //transmit value of light to slave bus
  if (x == '0' || x == '1')
  {
    Wire.beginTransmission(0x2A); // transmit to slave device 
    Wire.write((char) x);             // sends one byte
    Wire.endTransmission();    // stop transmitting
  }
  //receive transmission
  else if (x == '?')
  {
    //read request and print to serial
    Wire.requestFrom(0x2a, 1);
    char state = Wire.read();
    Serial.print(state);
  }
  delay(500);
}