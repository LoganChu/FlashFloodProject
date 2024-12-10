/*
Stepper Motor Control - one revolution

This program drives a unipolar or bipolar stepper motor.

The motor is attached to digital pins 8 - 11 of the Arduino.


The motor should revolve one 

revolution in one direction, then
one revolution in the other direction.
*/


#include <Stepper.h>

const int stepsPerRevolution = 2048;  // change this to fit the number of steps per revolution
// for your motor

// initialize the stepper library on pins 8 through 11:

Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

void setup() {
  Serial.begin(9600);
  analogReference(INTERNAL);
}

void loop() {
  int sensorValue1 = analogRead(A5);
  Serial.println(sensorValue1);
  delay(200);
  int sensorValue2 = analogRead(A5);
  Serial.println(sensorValue2);
  if(sensorValue1>15 && sensorValue2>15){
    Serial.print("Motor should turn on");
    myStepper.setSpeed(20);
    myStepper.step(-stepsPerRevolution);
    delay(1000);
  }
}



