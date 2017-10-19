/*
   Roman Yushchyk
   200368308
   UofR CS207

*/
#include <Servo.h>
#include "Morze.h"
#include "pitches.h"
#include "Play.h"
#include "Button.h"
// Assignment
int led = 13;
int led_Analog = A1;
int servo_Pin = 11;
int A_Read = A0;
int LED2 = 10;
int LED = 12;
int LED3 = 9;
int pos;
int time_Unit = 1000; // 1 Second
Servo myservo;

void setup() {
  Serial.begin(9600);
  Serial.println("Type your massege here: ");
  Play();
  myservo.attach(servo_Pin);
  pinMode(led_Analog, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
}


void loop() {
  input();
  for (int Volts = 0; Volts <= 1023; Volts++) {
    analogWrite(led_Analog, Volts);
    delay(time_Unit / 100);
  }
  analogWrite(led_Analog, 0);
  delay(2 * time_Unit);
  // LED Pin #13
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(time_Unit);                       // wait for a second
  button(A_Read);
  digitalWrite(led, LOW);// turn the LED off by making the voltage LOW
  delay(time_Unit);
  button(A_Read);

  // LED Pin #12;
  // 3 Short
  digitalWrite(LED, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(75);                       // wait for a second
  button(A_Read);
  digitalWrite(LED, LOW);// turn the LED off by making the voltage LOW
  delay(75);
  button(A_Read);
  digitalWrite(LED, HIGH);
  delay(75);
  button(A_Read);
  digitalWrite(LED, LOW);
  delay(75);
  button(A_Read);
  digitalWrite(LED, HIGH);
  delay(75);
  button(A_Read);
  digitalWrite(LED, LOW);
  delay(75);
  button(A_Read);
  // 3 Long
  digitalWrite(LED, HIGH);
  delay(183);
  button(A_Read);
  digitalWrite(LED, LOW);
  delay(183);
  button(A_Read);
  digitalWrite(LED, HIGH);
  delay(183);
  button(A_Read);
  digitalWrite(LED, LOW);
  delay(183);
  button(A_Read);
  digitalWrite(LED, HIGH);
  delay(183);
  button(A_Read);
  digitalWrite(LED, LOW);
  delay(183);
  button(A_Read);
  // 3 Short
  digitalWrite(LED, HIGH);
  delay(75);
  button(A_Read);
  digitalWrite(LED, LOW);
  delay(75);
  button(A_Read);
  digitalWrite(LED, HIGH);
  delay(75);
  button(A_Read);
  digitalWrite(LED, LOW);
  delay(75);
  button(A_Read);
  digitalWrite(LED, HIGH);
  delay(75);
  button(A_Read);
  digitalWrite(LED, LOW);
  // Cycle Delay
  button(A_Read);
  delay(2000);
  button(A_Read);
  //Servo
  for (int pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  button(A_Read);
  for (int pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  button(A_Read);  
  digitalWrite(LED2, LOW);
  delay (500);
  button(A_Read);
  digitalWrite(LED2, HIGH);
  delay(500);
  button(A_Read);
  digitalWrite(LED2, LOW);
  delay(500);
  button(A_Read);

  digitalWrite(LED3, LOW);
  delay (500);
  button(A_Read);
  digitalWrite(LED3, HIGH);
  delay(500);
  button(A_Read);
  digitalWrite(LED3, LOW);
  delay(500);
  button(A_Read);
}
