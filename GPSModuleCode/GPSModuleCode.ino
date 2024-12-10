#include <TinyGPS++.h>

// Create an instance of the GPS library
TinyGPSPlus gps;

void setup() {
  Serial.begin(115200);       // Serial monitor
  Serial1.begin(9600);        // GPS module baud rate, using Serial1 on Mega or ESP32
}

void loop() {
  // Check if there’s data available on Serial1
  while (Serial1.available() > 0) {
    gps.encode(Serial1.read());  // Read GPS data and parse it
  
    // If new location data is available, print it  
    if (gps.location.isUpdated()) {
      Serial.print("Latitude: ");
      Serial.println(gps.location.lat(), 6);
      Serial.print("Longitude: ");
      Serial.println(gps.location.lng(), 6);
      Serial.print("Number of Satellites: ");
      Serial.println(gps.satellites.value());
      Serial.print("Speed: ");
      Serial.println(gps.speed.mph());
      Serial.print("Altitude: ");
      Serial.println(gps.altitude.meters());
    }
  }
}
