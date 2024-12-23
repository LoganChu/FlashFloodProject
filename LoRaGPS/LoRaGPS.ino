// Feather9x_TX
// -*- mode: C++ -*-
// Example sketch showing how to create a simple messaging client (transmitter)
// with the RH_RF95 class. RH_RF95 class does not provide for addressing or
// reliability, so you should only use RH_RF95 if you do not need the higher
// level messaging abilities.
// It is designed to work with the other example Feather9x_RX

#include <SPI.h>
#include <RH_RF95.h>
#include <TinyGPS++.h>
#include <cstdio>
#include <iostream>

// Create an instance of the GPS library
TinyGPSPlus gps;

#define RFM95_CS    8
#define RFM95_INT   3
#define RFM95_RST   4

// Change to 434.0 or other frequency, must match RX's freq!
#define RF95_FREQ 915.0

// Singleton instance of the radio driver
RH_RF95 rf95(RFM95_CS, RFM95_INT);

void setup() {

  pinMode(RFM95_RST, OUTPUT); //set output
  digitalWrite(RFM95_RST, HIGH); //turn on

  //Serial.begin(115200);
  Serial1.begin(9600);        // GPS module baud rate, using Serial1 on Mega or ESP32
  while (!Serial) delay(1);
  delay(100);

  //Serial.println("Feather LoRa TX Test!");

  // manual reset
  digitalWrite(RFM95_RST, LOW);
  delay(10);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);
  rf95.init();
  /*
  while (!rf95.init()) {
    Serial.println("LoRa radio init failed");
    Serial.println("Uncomment '#define SERIAL_DEBUG' in RH_RF95.cpp for detailed debug info");
    while (1);
  }
  */
  Serial.println("LoRa radio init OK!");
  // Defaults after init are 434.0MHz, modulation GFSK_Rb250Fd250, +13dbM
  
  rf95.setFrequency(RF95_FREQ);
  /*
  if (!rf95.setFrequency(RF95_FREQ)) {
    Serial.println("setFrequency failed");
    while (1);
  }
  */
  Serial.print("Set Freq to: "); Serial.println(RF95_FREQ);
  

  // Defaults after init are 434.0MHz, 13dBm, Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on

  // The default transmitter power is 13dBm, using PA_BOOST.
  // If you are using RFM95/96/97/98 modules which uses the PA_BOOST transmitter pin, then
  // you can set transmitter powers from 5 to 23 dBm:
  rf95.setTxPower(23, false);
}

int16_t packetnum = 0;  // packet counter, we increment per xmission

void loop() {

  while (Serial1.available() > 0) {
    gps.encode(Serial1.read());  // Read GPS data and parse it

    // If new location data is available, print it  
    if (gps.location.isUpdated()) {

      //char radiopacket[50] = "GPS Module Test";
      //std::string message = "Latitude: " + std::to_string(gps.location.lat())[0:10] + "Longtitude: "+ std::to_string(gps.location.lng());
      char radiopacket1[50];
      //snprintf(radiopacket, sizeof(radiopacket), "%s", message);
      snprintf(radiopacket1, sizeof(radiopacket1), "%.6f", gps.location.lat()); // Format to 6 decimal places
      snprintf(radiopacket1+10, sizeof(radiopacket1)-10, "%.6f", gps.location.lng()); // Format to 6 decimal places
      itoa(packetnum++, radiopacket1+50, 10);
      Serial.print("Sending "); Serial.println(radiopacket1);
      radiopacket1[50] = 0;

      Serial.println("Sending...");
      delay(10);
      rf95.send((uint8_t *)radiopacket1, 20);

      Serial.println("Waiting for packet to complete...");
      delay(10);
      rf95.waitPacketSent();
      // Now wait for a reply
      uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
      uint8_t len = sizeof(buf);

      Serial.println("Waiting for reply...");
      
      if (rf95.waitAvailableTimeout(1000)) {
        // Should be a reply message for us now
        if (rf95.recv(buf, &len)) {
          Serial.print("Got reply: ");
          Serial.println((char*)buf);
          Serial.print("RSSI: ");
          Serial.println(rf95.lastRssi(), DEC);
        } else {
          Serial.println("Receive failed");
        }
      } else {
        Serial.println("No reply, is there a listener around?");
      }
      
    }
  }  
}
