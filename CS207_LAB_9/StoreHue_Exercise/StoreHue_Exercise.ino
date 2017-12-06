 /* Hue EEPROM Storage Exercise
 * Written Nov 15 2011 by Alex Clarke
 *
 *Completed program will use a button to cycle through color hues.
 *When the button is released the current hue will be stored to EEPROM
 *
 *Pins 9 10 and 11 should be connected to the Red, Green and Blue pins of an
 *RGB LED.
 *The remaining pin on the LED should be connected to ground.
 *
 *Pin 12 should be connected to one side of a button.
 *The other side of the button should be connected to ground.
 */
#include <EEPROM.h>
 
// Pin Constants
const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;
const int buttonPin = 12;

// Color Variables
float hue = 0, s = 1, v = 1;
float r,g,b;

// Button State Variables
float curButton = HIGH;
float lastButton = HIGH;

void setup()
{
  
  // Set up RGB LED pins
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  EEPROM.get(10,hue);
  //Set up button pin
  pinMode(buttonPin, INPUT);
   // Trick to make this a pull up button
   // Other side of button must be attached to ground
   // This trick doesn't work on pin 13.
  digitalWrite(buttonPin, HIGH);
 
}

void loop()
{
  
  //Store Last Button State
  lastButton = curButton;
  
  //Read Current Button
  curButton = digitalRead(buttonPin);
  
  //Cycle color if button pressed
  if(curButton == LOW)
  {
    hue++;
    //make hue wrap around the color wheel
    if (hue < 0 || hue > 359)
    {
      hue = 0;
      
    } 
    EEPROM.put(10,hue);
  }
  
  //If button was just released, store hue
  if (curButton == HIGH && lastButton == LOW)
  {
   EEPROM.put(10,hue);
  }
    
 
  //get the red green and blue values for the selected hue at full intensity
  hsv2rgb(hue,s,v,r,g,b);
  
  //write the color to the RGB LED
  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);
  
  delay(10);
}


/* function: hsv2rb
 *   This function converts a color in hsv form to rgb form
 *   Based on the description provided on Wikipedia:
 *     http://en.wikipedia.org/w/index.php?title=HSL_and_HSV&oldid=456731840#From_HSV
 * Inputs:
 *    - h: hue. Must be between 0 and 359 inclusive. 
 *              If it is outside this range the color returned will be black.
 *    - s: saturation. Must be between 0 and 1 inclusive.
 *              s is clamped if it is out of range.
 *    - v: value. Must be between 0 and 1 inclusive.
 *              v is clamped if it is out of range.
 *
 * Outputs:
 *    - r: red. Value will be between 0 and 255 inclusive.
 *    - g: green. Value will be between 0 and 255 inclusive.
 *    - b: blue. Value will be between 0 255 inclusive.
 */
void hsv2rgb(float h, float s, float v, float &r, float &g, float &b)
{
  v = constrain(v, 0, 1);
  s = constrain(s, 0, 1);
  float c = v*s;
  float hprime = h/60.0f;
  float x = c * ( 1 - abs(hprime - ((int)hprime/2)*2 - 1));
  
  if (h < 0 || h > 360)
  {
    r = g = b = 0;
  }
  else if ( 0 <= hprime && hprime < 1)
  {
    r = c;
    g = x;
    b = 0;
  }
    else if ( 1 <= hprime && hprime < 2)
  {
    r = x;
    g = c;
    b = 0;
  }
    else if ( 2 <= hprime && hprime < 3)
  {
    r = 0;
    g = c;
    b = x;
  }
    else if ( 3 <= hprime && hprime < 4)
  {
    r = 0;
    g = x;
    b = c;
  }
    else if ( 4 <= hprime && hprime < 5)
  {
    r = x;
    g = 0;
    b = c;
  }
    else if ( 5 <= hprime && hprime < 6)
  {
    r = c;
    g = 0;
    b = x;
  }
  
  float m = v - c;
  r += m;
  g += m;
  b += m;
  r *= 255;
  g *= 255;
  b *= 255;
  
}
