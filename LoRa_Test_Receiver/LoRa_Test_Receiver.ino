/**
@file LoRa_Test_Receiver
@brief Arduino MKR 1300 WAN LoRa WAN receiving test

The receiver includes a 0.9 inches Oled monochromatic display
to show updates on the connection status and data.

@date April, 2021
@author Enrico Miglino <enrico.miglino@gmail.com>
@version 1.0.1
*/
#include <SPI.h>
#include <LoRa.h>
#include <Streaming.h>
#include <Streaming.h>
//#include "oled.h"

#define SYS_LED 6

//! Dispaly instance
//Adafruit_SSD1306 oled = Adafruit_SSD1306(OLED_WIDTH, OLED_HEIGHT, &Wire, -1);

/**
Initialization function
*/
void setup() {
  // Initialize the monitoring serial
  Serial.begin(38400);
  // Initialize the communication serial
  Serial1.begin(115200);

  // Notify the LoRa activity
  pinMode(SYS_LED, OUTPUT);
  digitalWrite(SYS_LED, LOW);

  Serial << "LoRa Receiver" << endl;

  if (!LoRa.begin(868E6)) {
    Serial <<"Starting LoRa failed! System halted." << endl;
    while (1);
  }

  /*// Initialize the display
  oled.begin(SSD1306_SWITCHCAPVCC, OLED_I2C);
  oled.setRotation(2); // Rotate the display 180 Deg

  // Clear the buffer.
  oled.clearDisplay();
  oled.display();

  // Show title
  initDisplay(&oled); 
  textFont(MONO_BOLD, 9, &oled);
  showText("LoRa", 40, 9, COL_WHITE, &oled); 
  showText("Receiver", 13, 25, COL_WHITE, &oled);
  showText("Ver.1.0", 16, 40, COL_WHITE, &oled);
  showText("NanodroneII", 0, 55, COL_WHITE, &oled);

  delay(5000);

  // Clear the buffer.
  oled.clearDisplay();
  textFont(MONO, 9, &oled);
  showText("Ready", 35, 40, COL_WHITE, &oled);
  delay(3000);

  oled.clearDisplay();
  oled.display();
  */
}

void loop() {
  int packetSize = LoRa.parsePacket();

  /*if(Serial1.available()) {
    Serial << "From PSoC6 " << Serial1.readString() << endl;
  }*/
  
  if (packetSize) {
    digitalWrite(SYS_LED, HIGH);
    Serial << "Receiving LoRa packet of " << packetSize << " bytes" << endl;
    // read packet
    while (LoRa.available()) {
      String inPacket = LoRa.readString();
      Serial << "Sending >>" << inPacket << endl;
      Serial1.println(inPacket); 
    }
    digitalWrite(SYS_LED, LOW);
  }
}