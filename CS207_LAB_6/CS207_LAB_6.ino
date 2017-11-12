// Sweep
// by Roman Yushchyk
// 200368308
// LAB 6

// Assignment
#include <Servo.h>
const int pot_Pin = A1;
volatile int pot_Read; // Potentiomenter read
int top = 50; // Maxiumum pulse delay time
int bot = 5; // Minimum pulse delay time

Servo myservo;  // create servo object to control a servo
// a maximum of eight servo objects can be created

volatile int pos = 0;    // variable to store the servo position
volatile int inc = 1; // Increment 
volatile int del = 15; // Delay time

void setup()
{
  Serial.begin(9600); // Beginning serial comunication
  pinMode(pot_Pin, INPUT_PULLUP); // Pin Mode sselection
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}


void loop()
{
  //  Serial increment to Servo loop Extra code
  //  pot_Read = analogRead(pot_Pin);
  //  Serial.println(pot_Read);
  //  del = map(pot_Read, 21, 1020, bot, top);
  //  Serial.println(del);
  //
  // Serial.print("Eneter your increment here: ");
  //  if (Serial.available() != 0) {
  //    inc = Serial.parseInt();
  //    Serial.println(inc);
  // }

  for (inc = 0; inc <= 90; inc += 10) {
    // Loop 1
         for (pos = pos; pos <= 90 + inc; pos += 1) {// goes from 0 degrees to 180 degrees
      // in steps of 1 degree
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        // Extra code for a potentometer cservo control
        //      pot_Read = analogRead(pot_Pin);
        //      Serial.println(pot_Read);
        //      del = map(pot_Read, 0, 1023, bot, top);
        //      Serial.println(del);
        delay(del); // waits 15ms for the servo to reach the position
         }
 

    // Loop 2
   
      for (pos = 90 + inc; pos >= 90 - inc; pos -= 1)    // goes from 180 degrees to 0 degrees
      {
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        // Extra code for a potentometer cservo control
        //      pot_Read = analogRead(pot_Pin);
        //      Serial.println(pot_Read);
        //      del = map(pot_Read, 0, 1023, bot, top);
        //      Serial.println(del);
        delay(del);                       // waits 15ms for the servo to reach the position
      }

}
}

