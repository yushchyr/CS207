/* Lab 8 First Build Sketch 
 * Written Nov 15 2011 by Alex Clarke
 */
// Pin Constants
const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;
const int buttonPin = 12;

// Color Variables
int color = 0;
// Button State Variables
float curButton = HIGH;
float lastButton = HIGH;

// variables for tone
int value;
int toneOn;
int increment = 1;

void setup()
{
  // Set up RGB LED pins
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  //Set up button pin
  pinMode(buttonPin, INPUT);
  // Trick to make this a pull up button
  // Other side of button must be attached to ground
  digitalWrite(buttonPin, HIGH);  
  // Quick way to set pins 0 to 7 to OUTPUT
  DDRD = B11111111;
} 

void loop()
{
  //Store Last Button State
  lastButton = curButton;

  //Read Current Button
  curButton = digitalRead(buttonPin);


  //If button was just pressed cycle color
  if (curButton == LOW && lastButton == HIGH)
  {
    color++;
  }
  //Set RGB LED to a color
  if (color == 0) //RED
  { 
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);
  }
  else if (color == 1) //GREEN
  {
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
    digitalWrite(bluePin, LOW);
  }
  else if (color == 2) //BLUE
  {
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, HIGH);
  }
  else //Invalid color, reset to RED
  {
    color = 0;
  }

  
  if (toneOn == true)
  {
    PORTD = value/2;
  }
  else
  {
    PORTD = 0;
  }
  
  toneOn = !toneOn;
  value+= increment;
  
  if (value == 255 || value == 0) 
  {
    increment = -increment;
  }
  delayMicroseconds(1000000l/440);
}

