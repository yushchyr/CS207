/*
   Roman Yushchyk`
   200368308
   CS207
   LAB_3 Button
   Part 1
*/

// Initialization
int buttonState; // Variable for reading the pushbutton status
int buttonState_2; // Variable for reding second  pushbutton state
const int buttonPin = 2; // Button pin
const int buttonPin_2 = 3; // Second button pin
const int led = 9; // LED pin assignment
const int t = 200; // Standart delay time unit

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // Initiating serial 1
  pinMode(buttonPin, INPUT_PULLUP); // Button 1 Pin assignment
  pinMode(buttonPin_2, INPUT); // Button 2 pin assignment
  pinMode(led, OUTPUT); // Pin assignment LED
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonState = digitalRead(buttonPin); // Reading button 1 state
  buttonState_2 = digitalRead(buttonPin_2); // Reading button 2 state
  Serial.print("Button 1 State: ");
  Serial.println(buttonState);
  Serial.print("Button 2 State: ");
  Serial.println(buttonState_2);

  if (buttonState == LOW) { // If button 1 (Pullup) is pressed
    digitalWrite(led, HIGH); // Turn LED light ON
  }

  if (buttonState_2 == HIGH) { // If button 2 (Pulldown) is pressed
    digitalWrite(led, LOW);    // Turn LED OFF
    delay(t); // Delay time
  }

