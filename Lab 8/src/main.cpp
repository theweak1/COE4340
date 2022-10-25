#include <Arduino.h>

int val = 0;
float y = 0;
float x = 0;

float formula(int x){
y = -3E-11*pow(x,4) + 9E-08*pow(x,3) - 0.0001*pow(x,2) + 0.0298*pow(x,1) + 11.892;
  return y; 
}

void setup() {
  // put your setup code here, to run once: 
  Serial.begin(9600);
  Serial.print("\n");
}

void loop() {
  delay(2000);
  Serial.print("Total Measurement: ");
  val = analogRead(A0);
  y = formula(val);
  delay(2000);
  Serial.print(y);
  Serial.print("cm");
  Serial.println("");
  delay(2000);
}