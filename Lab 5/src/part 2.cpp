
#include <Arduino.h>

#include <Adafruit_LiquidCrystal.h>

Adafruit_LiquidCrystal lcd_1(0);
String direction = "none";
double speed = 0;
int PWM_pin = 3;
double duty_cycle = 0;

void setup() {
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(PWM_pin, OUTPUT);
  Serial.begin(9600);
  lcd_1.begin(16, 2);
  lcd_1.print("Motor Standby");
  delay(2000);
}

void loop() {
  bool initialLoop;
  lcd_1.setCursor(0, 0);
  lcd_1.setBacklight(1);
  analogWrite(PWM_pin, speed);
  lcd_1.clear();
  lcd_1.print("Direction: " + direction);
  lcd_1.setCursor(0, 1);
  lcd_1.print(String(speed) + "%");

  Serial.println("Enter On/Off: ");
  while (Serial.available() == 0) {} //wait for data available
  String teststr = Serial.readString(); //read until timeout
  teststr.trim();
  digitalWrite(PWM_pin, HIGH);
  if (teststr == "On" | teststr == "on" | teststr == "ON") {
    if (initialLoop != true) {
      lcd_1.clear();
      lcd_1.print("Direction: CW");
      lcd_1.setCursor(0, 1);
      lcd_1.print(String(100) + "%");
      direction = "CW";
      duty_cycle = 255;
    }
    initialLoop = true;
    digitalWrite(7, LOW);
    digitalWrite(6, HIGH);
    while (teststr != "End") {
      Serial.println("Menu: \n > SC, Sc or sc for speed change \n > CW, Cw or cw for clockwise direction \n > CC, Cc or cc for counterclockwise direction");
      Serial.println(" > LoopOn or LO to loop motor from 0 to 100 with 10% increments \n End to exit this menu: ");
      while (Serial.available() == 0) {} //wait for data available
      teststr = Serial.readString(); //read until timeout
      teststr.trim();

      if (teststr == "SC" | teststr == "sc" | teststr == "Sc") {
        double percentage;
        Serial.println("Enter speed percentage from 0 to 100: ");
        while (Serial.available() == 0) {} //wait for data available
        percentage = Serial.parseInt(); //read until timeout
        if (percentage <= 100 && percentage >= 0) {
          duty_cycle = percentage * 255 / 100;
          speed = percentage;
          analogWrite(PWM_pin, duty_cycle);
          Serial.println("Percentage inputted: " + String(percentage) + "%");
          lcd_1.clear();
          lcd_1.print("Direction: " + direction);
          lcd_1.setCursor(0, 1);
          lcd_1.print(String(percentage) + "%");

        } else {
          Serial.println("Invalid range percentage!");
        }

      } else if (teststr == "CW" | teststr == "Cw" | teststr == "cw") {
        Serial.println("Clockwise Activated");
        digitalWrite(7, LOW);
        digitalWrite(6, HIGH);
        direction = "CW";

        lcd_1.clear();
        lcd_1.print("Direction: " + direction);
        lcd_1.setCursor(0, 1);
        lcd_1.print(String(speed) + "%");
      } else if (teststr == "CC" | teststr == "Cc" | teststr == "cc") {
        Serial.println("Counter Clockwise Activated");
        digitalWrite(6, LOW);
        digitalWrite(7, HIGH);
        direction = "CC";

        lcd_1.clear();
        lcd_1.print("Direction: " + direction);
        lcd_1.setCursor(0, 1);
        lcd_1.print(String(speed) + "%");
      } else if (teststr == "LoopOn" | teststr == "LO") {
        double percentageLoop = 0;
        double duty_cycleLoop = 0;
        Serial.println("Loop Speed On");
        for (percentageLoop = 0; percentageLoop <= 100; percentageLoop += 10) {
          duty_cycleLoop = percentageLoop * 255 / 100;
          analogWrite(PWM_pin, duty_cycleLoop);
          Serial.println("Percentage inputted: " + String(percentageLoop) + "%");
          lcd_1.clear();
          lcd_1.print("Direction: " + direction);
          lcd_1.setCursor(0, 1);
          lcd_1.print(String(percentageLoop) + "%");
          delay(1000);
        }
        duty_cycle = speed * 255 / 100;
        analogWrite(PWM_pin, duty_cycle);
        lcd_1.clear();
        lcd_1.print("Direction: " + direction);
        lcd_1.setCursor(0, 1);
        lcd_1.print(String(speed) + "%");

      }

    }
  }
  if (teststr == "Off" | teststr == "off" | teststr == "OFF") {
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    speed = 0;
    direction = "none";
    initialLoop = false;
    lcd_1.clear();
    lcd_1.print("Direction: " + direction);
    lcd_1.setCursor(0, 1);
    lcd_1.print(String(speed) + "%");
  }

}

