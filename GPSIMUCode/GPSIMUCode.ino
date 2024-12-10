#include <SD.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LSM9DS1.h>
#include <Adafruit_Sensor.h> 
#include <TinyGPS++.h>

// Create an instance of the GPS library
TinyGPSPlus gps;

// i2c
Adafruit_LSM9DS1 lsm = Adafruit_LSM9DS1();

float AX = 0;
float AY = 0;
float AZ = 0;
float velocity = 0;
const int chipSelect = 10;
File myFile;

void setupSensor()
{
  // 1.) Set the accelerometer range (The range of measurements the sensor can track)
  lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_2G, lsm.LSM9DS1_ACCELDATARATE_10HZ);
  //lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_4G, lsm.LSM9DS1_ACCELDATARATE_119HZ);
  //lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_8G, lsm.LSM9DS1_ACCELDATARATE_476HZ);
  //lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_16G, lsm.LSM9DS1_ACCELDATARATE_952HZ);
  
  // 2.) Set the magnetometer sensitivity
  lsm.setupMag(lsm.LSM9DS1_MAGGAIN_4GAUSS);
  //lsm.setupMag(lsm.LSM9DS1_MAGGAIN_8GAUSS);
  //lsm.setupMag(lsm.LSM9DS1_MAGGAIN_12GAUSS);
  //lsm.setupMag(lsm.LSM9DS1_MAGGAIN_16GAUSS);

  // 3.) Setup the gyroscope
  lsm.setupGyro(lsm.LSM9DS1_GYROSCALE_245DPS);
  //lsm.setupGyro(lsm.LSM9DS1_GYROSCALE_500DPS);
  //lsm.setupGyro(lsm.LSM9DS1_GYROSCALE_2000DPS);
}

void setup() 
{
  //Serial.begin(115200); //parameter is the baud rate (bits per second)
  digitalWrite(8, HIGH);
  Serial1.begin(9600);  
  lsm.begin();
  setupSensor(); // helper to just set the default scaling we want, see above!
  delay(200);
  SD.begin(chipSelect);
  delay(200);
}

void loop() 
{ 
  myFile = SD.open("EGR1.txt",FILE_WRITE);
  //Serial.println("Final Test pls Work");
  
  while(Serial1.available() > 0) {
    gps.encode(Serial1.read());  // Read GPS data and parse it
    // If new location data is available, print it  
    if (gps.location.isUpdated()) {
      /*
      Serial.print("Latitude: "); Serial.println(gps.location.lat(), 6);
      Serial.print("Longitude: "); Serial.println(gps.location.lng(), 6);
      Serial.print("Number of Satellites: "); Serial.println(gps.satellites.value());
      Serial.print("Speed: "); Serial.println(gps.speed.mph());
      Serial.print("Altitude: "); Serial.println(gps.altitude.meters());
      */

      myFile.print("Latitude: "); myFile.println(gps.location.lat(), 6);
      myFile.print("Longitude: "); myFile.println(gps.location.lng(), 6);
      myFile.print("Number of Satellites: "); myFile.println(gps.satellites.value());
      myFile.print("Speed: "); myFile.println(gps.speed.mph());
      myFile.print("Altitude: "); myFile.println(gps.altitude.meters());
    }
  }
  
  lsm.read(); 

  sensors_event_t a, m, g, temp; lsm.getEvent(&a, &m, &g, &temp); 
 
  float distance = a.distance; int time = a.timestamp; float altitude = a.altitude;
  /*
  Serial.print("Distance:   "); Serial.print(distance); Serial.print(",");
  Serial.print("Time:  "); Serial.print(time); Serial.print(",");
  Serial.print("Altitude:  "); Serial.print(altitude); Serial.print("\n");
  //Serial.print("Orientation:    "); Serial.print(a.orientation.x);Serial.print("     "); Serial.print(a.orientation.y);Serial.print("     ");  Serial.println(a.orientation.z);
  */

  AX = a.acceleration.x; AY = a.acceleration.y; AZ = a.acceleration.z;
  
  /*
  Serial.print("Accel X: "); Serial.print(a.acceleration.x); Serial.print(" m/s^2");
  Serial.print("\tY: "); Serial.print(a.acceleration.y);     Serial.print(" m/s^2 ");
  Serial.print("\tZ: "); Serial.print(a.acceleration.z);     Serial.println(" m/s^2 ");
  */

  if (myFile) {
    //Serial.print("Writing to data.txt...");
    myFile.print("Distance:   "); myFile.println(distance); //myFile.print(",");
    myFile.print("Time:  "); myFile.println(time); //myFile.print(",");
    myFile.print("Altitude:  "); myFile.println(altitude); //myFile.print(",");
    //myFile.print("Orientation:    "); myFile.print(a.orientation.x); myFile.print("     "); myFile.print(a.orientation.y); myFile.print("     ");  myFile.println(a.orientation.z);
 
    myFile.print("Accel X: "); myFile.print(AX); myFile.print(" m/s^2");
    myFile.print("\tY: "); myFile.print(AY);     myFile.print(" m/s^2 ");
    myFile.print("\tZ: "); myFile.print(AZ);     myFile.println(" m/s^2 ");
  } 
  myFile.close();
  delay(500);
  //Serial.print("Gyro X: "); Serial.print(g.gyro.x);   Serial.print(" rad/s");
  //Serial.print("\tY: "); Serial.print(g.gyro.y);      Serial.print(" rad/s");
  //Serial.print("\tZ: "); Serial.print(g.gyro.z);      Serial.println(" rad/s");  } 
}
