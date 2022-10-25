#include <arduino.h>
#define IN1  24
#define IN2  26
#define IN3  28
#define IN4  30
int Steps = 0;
unsigned long last_time;
unsigned long currentMillis;
int steps_left=4095;
long time;


void setup() {
  Serial.begin(9600);
  pinMode(IN1, OUTPUT); 
  pinMode(IN2, OUTPUT); 
  pinMode(IN3, OUTPUT); 
  pinMode(IN4, OUTPUT); 
}

void loop() {
  bool reverse =false;
  digitalWrite(IN1, LOW); 
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  Serial.println("\n Enter CW for clockwise rotation, CCW for Counterclockwise rotation or");
  Serial.println("STP, to rotate specific amount of steps");
 while (Serial.available() == 0) {}     //wait for data available
  String str = Serial.readString();  //read until timeout
  str.trim();

  if(str =="CW" | str =="Cw" | str =="cw"){
    Serial.println("Rotaing Clockwise \n");
    Serial.println("To exit Write Esc");
          
    while (true){
        while(steps_left>0)
        {
          currentMillis = micros();
      
          if(currentMillis-last_time>=1000)
          {
            stepper(Steps, reverse); 
            time=time+micros()-last_time;
            last_time=micros();
            steps_left--;
          }
        }
      steps_left=4095;
      str = Serial.readString();  //read until timeout
      str.trim();
      if(str=="Esc" | str=="ESC" | str=="esc") break;
    }
        digitalWrite(IN1, LOW); 
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW); 
  }
  else if (str=="CCW" | str=="Ccw" | str=="ccw")
  {
    reverse = true;
Serial.println("Rotaing Counterclockwise \n");
    Serial.println("To exit Write Esc");
          
    while (true){
        while(steps_left>0)
        {
          currentMillis = micros();
      
          if(currentMillis-last_time>=1000)
          {
            stepper(Steps, reverse); 
            time=time+micros()-last_time;
            last_time=micros();
            steps_left--;
          }
        }
      steps_left=4095;
      str = Serial.readString();  //read until timeout
      str.trim();
      if(str=="Esc" | str=="ESC" | str=="esc") break;
    }
        digitalWrite(IN1, LOW); 
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW);
  }
  else if(str=="STP" | str=="Stp" | str=="stp")
  {
  Serial.println("How many Steps do you want to rotate?\n");
  while (Serial.available() == 0) {}     //wait for data available
  int steps = Serial.parseInt();
  Serial.println("Steps to rotate: " + String(steps));
  if(!reverse){
    Serial.println("Rotating Clockwise");
  }
  else {
    Serial.println("Rotating CounterClockwise");
  }
  while (true){
        while(steps>0)
        {
          currentMillis = micros();
      
          if(currentMillis-last_time>=1000)
          {
            stepper(Steps, reverse); 
            time=time+micros()-last_time;
            last_time=micros();
            steps--;
          }
        }
        break;
    }
        digitalWrite(IN1, LOW); 
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW);
  }
}

void stepper(int xw, bool rev)
  {
    if(!rev){
      
   switch(xw)
    {
     case 0:
       digitalWrite(IN1, LOW); 
       digitalWrite(IN2, LOW);
       digitalWrite(IN3, LOW);
       digitalWrite(IN4, HIGH);
     break; 
     case 1:
       digitalWrite(IN1, LOW); 
       digitalWrite(IN2, LOW);
       digitalWrite(IN3, HIGH);
       digitalWrite(IN4, HIGH);
     break; 
     case 2:
       digitalWrite(IN1, LOW); 
       digitalWrite(IN2, LOW);
       digitalWrite(IN3, HIGH);
       digitalWrite(IN4, LOW);
     break; 
     case 3:
       digitalWrite(IN1, LOW); 
       digitalWrite(IN2, HIGH);
       digitalWrite(IN3, HIGH);
       digitalWrite(IN4, LOW);
     break; 
     case 4:
       digitalWrite(IN1, LOW); 
       digitalWrite(IN2, HIGH);
       digitalWrite(IN3, LOW);
       digitalWrite(IN4, LOW);
     break; 
     case 5:
       digitalWrite(IN1, HIGH); 
       digitalWrite(IN2, HIGH);
       digitalWrite(IN3, LOW);
       digitalWrite(IN4, LOW);
     break; 
       case 6:
       digitalWrite(IN1, HIGH); 
       digitalWrite(IN2, LOW);
       digitalWrite(IN3, LOW);
       digitalWrite(IN4, LOW);
     break; 
     case 7:
       digitalWrite(IN1, HIGH); 
       digitalWrite(IN2, LOW);
       digitalWrite(IN3, LOW);
       digitalWrite(IN4, HIGH);
     break; 
     default:
       digitalWrite(IN1, LOW); 
       digitalWrite(IN2, LOW);
       digitalWrite(IN3, LOW);
       digitalWrite(IN4, LOW);
     break; 
    }
    }
    else
    {
     switch(xw)
    {
     case 7:
       digitalWrite(IN1, LOW); 
       digitalWrite(IN2, LOW);
       digitalWrite(IN3, LOW);
       digitalWrite(IN4, HIGH);
     break; 
     case 6:
       digitalWrite(IN1, LOW); 
       digitalWrite(IN2, LOW);
       digitalWrite(IN3, HIGH);
       digitalWrite(IN4, HIGH);
     break; 
     case 5:
       digitalWrite(IN1, LOW); 
       digitalWrite(IN2, LOW);
       digitalWrite(IN3, HIGH);
       digitalWrite(IN4, LOW);
     break; 
     case 4:
       digitalWrite(IN1, LOW); 
       digitalWrite(IN2, HIGH);
       digitalWrite(IN3, HIGH);
       digitalWrite(IN4, LOW);
     break; 
     case 3:
       digitalWrite(IN1, LOW); 
       digitalWrite(IN2, HIGH);
       digitalWrite(IN3, LOW);
       digitalWrite(IN4, LOW);
     break; 
     case 2:
       digitalWrite(IN1, HIGH); 
       digitalWrite(IN2, HIGH);
       digitalWrite(IN3, LOW);
       digitalWrite(IN4, LOW);
     break; 
       case 1:
       digitalWrite(IN1, HIGH); 
       digitalWrite(IN2, LOW);
       digitalWrite(IN3, LOW);
       digitalWrite(IN4, LOW);
     break; 
     case 0:
       digitalWrite(IN1, HIGH); 
       digitalWrite(IN2, LOW);
       digitalWrite(IN3, LOW);
       digitalWrite(IN4, HIGH);
     break; 
     default:
       digitalWrite(IN1, LOW); 
       digitalWrite(IN2, LOW);
       digitalWrite(IN3, LOW);
       digitalWrite(IN4, LOW);
     break; 
    } 
    }
    Steps--;
      if(Steps<0)
        Steps=7;
}