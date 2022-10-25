
#include <Arduino.h>

void setup() {
  pinMode(9, OUTPUT);
  pinMode(6, OUTPUT);
}

void loop() {
  analogWrite(9, 55);
  digitalWrite(6, LOW);
  delay(5000);
  digitalWrite(6, HIGH);
  delay(5000);
  digitalWrite(6, LOW);
  delay(5000);
  digitalWrite(6, HIGH);
  delay(5000);
}

