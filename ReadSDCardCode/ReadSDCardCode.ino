/*
  SD card read/write

  This example shows how to read and write data to and from an SD card file
  The circuit. Pin numbers reflect the default
  SPI pins for Uno and Nano models:
   SD card attached to SPI bus as follows:
 ** SDO - pin 11
 ** SDI - pin 12
 ** CLK - pin 13
 ** CS - pin 4 (For For Uno, Nano: pin 10. For MKR Zero SD: SDCARD_SS_PIN)

  created   Nov 2010
  by David A. Mellis
  modified  24 July 2020
  by Tom Igoe

  This example code is in the public domain.

*/
#include <SD.h>

const int chipSelect = 10;
File myFile;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  delay(1000);
  // wait for Serial Monitor to connect. Needed for native USB port boards only:
  while (!Serial);

  Serial.println("Initializing SD card...");
  SD.begin(chipSelect);

  Serial.println("initialization done.");
  
  // re-open the file for reading:
  myFile = SD.open("data.txt");
  if (myFile) {
    Serial.println("data.txt:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  }
   else {
    // if the file didn't open, print an error:
    Serial.println("error opening test1.txt");
  }
}

void loop() {
  // nothing happens after setup
}
