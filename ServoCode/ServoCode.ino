#include <Servo.h>

Servo servo1;
Servo servo2;


void setup() {
  servo1.attach(8);
  servo2.attach(7);

}

void loop() {
  servo1.write(180);
  servo2.write(180);
  delay(1000);
  servo1.write(360);
  servo2.write(360);
  delay(1000);
  

}
