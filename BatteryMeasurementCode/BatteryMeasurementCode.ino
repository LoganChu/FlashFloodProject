void setup() {
  Serial.begin(9600);
  float measuredvbat = analogRead(A9);
  measuredvbat *= 2;    // we divided by 2, so multiply back
  measuredvbat *= 3.3;  // Multiply by 3.3V, our reference voltage
  measuredvbat /= 1024; // convert to voltage
  Serial.print("VBat: " ); Serial.println(measuredvbat);

}

void loop() {
  // put your main code here, to run repeatedly:

}
