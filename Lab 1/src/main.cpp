/**
 * Blink
 *
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */
#include "Arduino.h"

// Set LED_BUILTIN if it is not defined by Arduino framework
// #define LED_BUILTIN 13

void setup()
{
  // testing for breakpoint
  //  initialize LED digital pin as an output.
  //  pinMode(LED_BUILTIN, OUTPUT);
  //  initialize LED pin blank to blank as an output
  //  pinMode(LED_BUILTIN, OUTPUT);

  // Set up for knight rider
  for (int i = 36; i < 44; i++)
  {
    pinMode(i, OUTPUT);
  }
}

void loop()
{
  // // Test Blink of integrated LED on pin 13
  // { // turn the LED on (HIGH is the voltage level)
  //   digitalWrite(LED_BUILTIN, HIGH);

  //   // wait for a second
  //   delay(1000);

  //   // turn the LED off by making the voltage LOW
  //   digitalWrite(LED_BUILTIN, LOW);

  //   // wait for a second
  //   delay(1000);
  // }

  // Test Blink of External LED
  // {// turn the LED on (HIGH is the voltage level)
  // digitalWrite(LED_BUILTIN, HIGH);

  // // wait for a second
  // delay(1000);

  // // turn the LED off by making the voltage LOW
  // digitalWrite(LED_BUILTIN, LOW);

  //  // wait for a second
  // delay(1000);
  // }

  // Creating Night Rider program
   bool increase=true;
   int indent=35;
   while (true)
   {
     if (increase)
     {
       digitalWrite(indent,LOW);
      delay(150);
      digitalWrite(indent,HIGH);
       indent+=1;
       indent==44 ? increase=false:increase;

    }else
    {
      digitalWrite(indent,LOW);
      delay(150);
      digitalWrite(indent,HIGH);
      indent-=1;
      indent==35 ? increase=true:increase;
    }
  }
}