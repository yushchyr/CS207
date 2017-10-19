/*
   Roman Yushchyk`
   200368308
   CS207
   LAB_3 Button
*/
// Variables assignment
int buttonState; // Variable for reading the pushbutton status
int buttonState_2; // Variable for reding second  pushbutton state
const int buttonPin = 2; // Button pin
const int buttonPin_2 = 3; // Second button pin
const int led = 9; // LED pin assignment
const int led_2 = 10; // LED_2 pin assignment
const int t = 200; // Standart time unit for this 
// int ledPower; // Analog power increment value

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // Initiating serial 1
  pinMode(buttonPin, INPUT); // Button 1 Pin assignment
  pinMode(buttonPin_2, INPUT); // Button 2 pin assignment
  pinMode(led, OUTPUT); // Pin assignment LED
  pinMode(led_2, OUTPUT); // Pin assignment LED 2

}

void loop() {
  // put your main code here, to run repeatedly:
  buttonState = digitalRead(buttonPin); // Reading button 1 state
  buttonState_2 = digitalRead(buttonPin_2); // Reading button 2 state
  Serial.print("Button 1 State: "); // Serial monitor Debugging lines
  Serial.println(buttonState);  // Serial monitor Debugging lines
  Serial.print("Button 2 State: "); // Serial monitor Debugging lines
  Serial.println(buttonState_2); // Serial monitor Debugging lines

  if (buttonState == LOW) { // If button one (PULLUP) is pushed it register GRD (0V);
    digitalWrite(led, LOW); // Then it set first led OFF
    digitalWrite(led_2, HIGH); // And the second is ON
  }

  if (buttonState_2 == HIGH) { // If button two (PULLDOWN) is pressed it register 5V
    digitalWrite(led, HIGH); // Then sets led one ON
    digitalWrite(led_2, LOW); // And the second one is OFF
  }
  // Analog Button code
  //  buttonState = digitalRead(buttonPin);// buttonState is assigned the state of buttonPin
  //  if (buttonState == 0) { // If button state is ground or 0V then:
  //    analogWrite(led, ledPower); // Set LED high 5V
  //    ledPower = ledPower + 10;
  //    Serial.print("Power: ");
  //    Serial.println(ledPower);
  //    if (ledPower >= 1023) {
  //      ledPower = 0;
  //    }
  //    Serial.print("Button state is: ");
  //    Serial.println(buttonState);
  //  }
  //  else { // Otherwise keep LED pin off or LOW
  //    digitalWrite(led, LOW); // Set LED OFf
  //    Serial.print("Button state is: ");
  //    Serial.println(buttonState);
  //  }
  delay(t); // Delay time 
}

