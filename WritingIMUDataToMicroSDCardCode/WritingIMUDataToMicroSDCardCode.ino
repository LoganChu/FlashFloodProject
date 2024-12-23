#include <SD.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LSM9DS1.h>
#include <Adafruit_Sensor.h>  // not used in this demo but required!

// i2c
Adafruit_LSM9DS1 lsm = Adafruit_LSM9DS1();

// #define LSM9DS1_SCK A5
// #define LSM9DS1_MISO 12
// #define LSM9DS1_MOSI A4
// #define LSM9DS1_XGCS 6
// #define LSM9DS1_MCS 5

float AX = 0;
float AY = 0;
float AZ = 0;
float velocity = 0;
// You can also use software SPI
//Adafruit_LSM9DS1 lsm = Adafruit_LSM9DS1(LSM9DS1_SCK, LSM9DS1_MISO, LSM9DS1_MOSI, LSM9DS1_XGCS, LSM9DS1_MCS);
// Or hardware SPI! In this case, only CS pins are passed in
//Adafruit_LSM9DS1 lsm = Adafruit_LSM9DS1(LSM9DS1_XGCS, LSM9DS1_MCS);
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
  Serial.begin(9600); //parameter is the baud rate (bits per second)
  digitalWrite(8, HIGH);
  while (!Serial) {
  }
  Serial.println("LSM9DS1 data read");
  lsm.begin();
  Serial.println("Found LSM9DS1 9DOF");
  // helper to just set the default scaling we want, see above!
  setupSensor();
  delay(2000);
  SD.begin(chipSelect);
}

void loop() 
{
  myFile = SD.open("test.txt", FILE_WRITE);
  lsm.read();  /* ask it to read in the data */ 
  // if the file opened okay, write to it:
 
  /* Get a new sensor event */ 
  sensors_event_t a, m, g, temp;
  lsm.getEvent(&a, &m, &g, &temp); 
  //Serial.print("Distance:   "); 
  float distance = a.distance;
  int time = a.timestamp;
  float altitude = a.altitude;
  Serial.print(distance);
  Serial.print(",");
  //Serial.print("Time:  ");
  Serial.print(time);
  Serial.print(",");
  //Serial.print("Altitude:  ");
  Serial.print(altitude);
  Serial.print("\n");
  //Serial.print("Orientation:    "); Serial.print(a.orientation.x);Serial.print("     "); Serial.print(a.orientation.y);Serial.print("     ");  Serial.println(a.orientation.z);
  
  AX = a.acceleration.x;
  AY = a.acceleration.y;
  AZ = a.acceleration.z;
 
  Serial.print("Accel X: "); Serial.print(a.acceleration.x); Serial.print(" m/s^2");
  Serial.print("\tY: "); Serial.print(a.acceleration.y);     Serial.print(" m/s^2 ");
  Serial.print("\tZ: "); Serial.print(a.acceleration.z);     Serial.println(" m/s^2 ");

  if (myFile) {
    Serial.print("Writing to data.txt...");
    myFile.print("Distance:   "); myFile.println(distance); //myFile.print(",");
    myFile.print("Time:  "); myFile.println(time); //myFile.print(",");
    myFile.print("Altitude:  "); myFile.println(altitude); //myFile.print(",");
    myFile.print("Orientation:    "); myFile.print(a.orientation.x); myFile.print("     "); myFile.print(a.orientation.y); myFile.print("     ");  myFile.println(a.orientation.z);
 
    myFile.print("Accel X: "); myFile.print(AX); myFile.print(" m/s^2");
    myFile.print("\tY: "); myFile.print(AY);     myFile.print(" m/s^2 ");
    myFile.print("\tZ: "); myFile.print(AZ);     myFile.println(" m/s^2 ");

    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening data.txt");
  }
  delay(1000);

  //Serial.print("Gyro X: "); Serial.print(g.gyro.x);   Serial.print(" rad/s");
  //Serial.print("\tY: "); Serial.print(g.gyro.y);      Serial.print(" rad/s");
  //Serial.print("\tZ: "); Serial.print(g.gyro.z);      Serial.println(" rad/s");
}
