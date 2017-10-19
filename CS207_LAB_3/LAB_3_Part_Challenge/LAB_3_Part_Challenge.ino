/*
   Roman Yushchyk`
   200368308
   CS207
   LAB_3 Button
   Part 1
*/

// Initialization
volatile int buttonState; // Variable for reading the interupt pushbutton status
volatile int buttonState_2; // Variable for reding second  pushbutton state
const int buttonPin = 2; // Button Inerrupt Pin
const int buttonPin_2 = 3; // Second button pin
const int led = 9; // LED pin assignment
const int led_2 = 10; // LED_2 assignment
const int t = 200; // Standart delay time unit

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // Initiating serial 1
  attachInterrupt(digitalPinToInterrupt(buttonPin), blink, CHANGE); // Setting up digital interrupt on pin 2
  pinMode(buttonPin, INPUT_PULLUP); // Button 1 Pin assignment
  pinMode(buttonPin_2, INPUT); // Button 2 pin assignment
  pinMode(led, OUTPUT); // Pin mode led
  pinMode(led_2, OUTPUT); // Pin mode led 2
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonState = digitalRead(buttonPin); // Reading button 1 state
  buttonState_2 = digitalRead(buttonPin_2); // Reading button 2 state
  digitalWrite(led, buttonState); // Turning led 9 On and OFF trough interrrupt service 
  
  if (buttonState_2 == HIGH) { // If button 2 (Pulldown) is pressed
    digitalWrite(led_2, HIGH);    // Turn LED ON
    delay(t); // Delay time
  }
  else
  digitalWrite(led_2, LOW); // And OFF
}
  
  void blink() { // Interrupt ISR servise rutine
  buttonState = !buttonState; // Equality check.
  }
