#include <CapSense.h>
/*
  Playing with pots.
  Written 23 Aug 2011 by Alex Clarke
  Roman Yushchyk
  200368308
*/

//constants for this sketch
const int ledPin = 5; // Led 1 pin assigment
const int ledPin_2 = A1; // Led 2 pin assigment
const int piezoPin = 6; // Pieso speaker pin assignment
const int potPin = A0; // Potentiometer pin assigment
const int light_Sensor = A3; // Photoresistor pin assignment
const int t = 200; // Time unit assigment


// variables for this sketch
volatile int pot_value; // Variable for storing
volatile int light_Level; // Variable for a light sensor
volatile int cap_Value; // Variable for pressure capacitive plate
volatile int result; // Mapping input value
CapSense   cs_9_2 = CapSense(9, 2); // Capacitive sensor pin assignment
volatile int total; // Capacitive sensor readvalue
volatile int freq; // Freaquency after mapping
void setup()
{
  Serial.begin(9600); // Beginning of Serial
  pinMode(ledPin, OUTPUT); // led Pin mode selection
  pinMode(ledPin_2, OUTPUT); // led_2 mode selection
  pinMode(piezoPin, OUTPUT); // Piezo speaker selection
  pinMode(light_Sensor, INPUT); // Light Sensor pin mode selection
  pinMode(potPin, INPUT); // Potentiometer pin mode selection
  cs_9_2.set_CS_AutocaL_Millis(0xFFFFFFFF); // Turn off autocalibration i
}

void loop()
{
  light_Level = analogRead(light_Sensor); // Liht level reading
  total =  cs_9_2.capSense(30); // Reading capacitance sensor value
  pot_value = analogRead(potPin); // Reading potentiometter sensor value
  result = map(pot_value, 0, 1023, 0, 255); // Remapping input from a potentiometer to volts
  freq = map(pot_value, 0, 1023, 440, 880); // Remapping input from a potentiometer to 
  tone(piezoPin, freq); // Playing a tone
  Serial.print("Your light level is: "); // Serial print text
  Serial.println(light_Level); // Light level print
  Serial.print("Potentiometer after mapping: ");
  Serial.println(result);
  Serial.print("Total capcitive sensor is: "); // Serial print text
  Serial.println(total); // Cap sensor value print

  if (light_Level < 800 || total > 10) // If Light levels are uner 800
  {
    digitalWrite(ledPin, HIGH); // Turn led ON

  }
  else // In any other scenario
    digitalWrite(ledPin, LOW); { // Turn led OFF
  }
  // Speaker, LED,  cofiguration
  analogWrite(ledPin_2, result);  // Set the LED to brightness pot_value
  tone(piezoPin, freq); // Play the sound represented by frequency pot_value
  delay(t); // Delay time
}
