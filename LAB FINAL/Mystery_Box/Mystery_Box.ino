// CS207 Lab Test Template 1
// Name: Roman Yushchyk
// Student Number: 200368308
// Part 2 Mistery Box

// Library
#include <EEPROM.h>
#include "pitches.h"

// Initiation
const int data = 4;
const int latch = 7;
const int clock = 8;
const int button1 = 10;
volatile int button1_Read = -1;
const int button2 = 11;
volatile int button2_Read = -1;
const int button3 = 12;
volatile int button3_Read = -1;
const int slider1 = A2;
volatile int slider1_Read = -1;
volatile int slider1_Read_Map = -1;
const int slider2 = A1;
volatile int slider2_Read = -1;
volatile int slider2_Read_Map = -1;
const int slider3 = A0;
volatile int slider3_Read = -1;
volatile int slider3_Read_Map = -1;
const int buzzer = 3;

// Intiation of variables for the light sensor
const int LDR = A3;
volatile int LDR_Read = -1;

// EEPROM Sequirity Code
const int memoryAddress = 0;
int codeDigOne = -1;
int codeDigTwo = -1;
int codeDigThree = -1;
int counter;

// Mode selector
volatile int mode = -1;

// Time
int t = 200;

void lightSensor() {
  LDR_Read = analogRead(LDR);
}

void read_Push_buttons() {
  // Rading values of all three buttons
  button1_Read = digitalRead(button1);
  Serial.print("Button One State: ");
  Serial.println(button1_Read);
  button2_Read = digitalRead(button2);
  Serial.print("Button Two State: ");
  Serial.println(button2_Read);
  button3_Read = digitalRead(button3);
  Serial.print("Button Three State: ");
  Serial.println(button3_Read);
}

void read_Slider(int n) {
  if (n == 1) {
    slider1_Read = analogRead(slider1);
    slider1_Read_Map = map(slider1_Read, 0, 1023, 0, 9);
  }
  else if (n == 2) {
    slider2_Read = analogRead(slider2);
    slider2_Read_Map = map(slider2_Read, 0, 1023, 0, 9);
  }
  else if (n == 3) {
    slider3_Read = analogRead(slider3);
    slider3_Read_Map = map(slider3_Read, 0, 1023, 0, 9);
  }

}

void display_Digit(int value) {
  digitalWrite(latch, LOW);    //Pulls the chips latch low
  for (int i = 0; i < 8; i++) { //Will repeat 8 times (once for each bit)
    int bit = value & 0b10000000; //We use a "bitmask" to select only the 16
    //bit in our number
    value = value << 1;          //we move our number up one bit value so next time bit
    //7 will be bit 8 and we will do our math on it
    if (bit == 128) {
      digitalWrite(data, HIGH); //if bit 8 is a 1, set our data pin high
    }
    else {
      digitalWrite(data, LOW); //if bit 8 is a 0, set the data pin low
    }
    digitalWrite(clock, HIGH);                //the next three lines pulse the clock
    delay(1);
    digitalWrite(clock, LOW);
  }
  digitalWrite(latch, HIGH);  //pulls the latch high, to display our data
}

int numberGlyphs[] =
{
  B11000000, //0
  B11111001, //1
  B10100100, //2
  B10110000, //3
  B10011001, //4
  B10010010, //5
  B10000010, //6
  B11111000, //7
  B10000000, //8
  B10011000, //9
  B11111111, //10 - CLEAR
};

int melody[18] = { 494,   0, 494,   0, 494,   0, 494,   0, 392,   0, 440,   0, 494,   0, 440,   0, 494,   0  };
int noteDurations[18] = { 100, 100, 100, 100, 100, 100, 500, 100, 500, 100, 500, 100, 100, 300, 100, 100, 1700, 100  };


void play_Melody_One() {
  for (int thisNote = 0; thisNote < 18; thisNote++) {
    if (melody[thisNote] != 0) {
      tone(buzzer, melody[thisNote], noteDurations[thisNote]);
      delay(noteDurations[thisNote]);
    }
    else {
      delay(noteDurations[thisNote]);
      // stop the tone playing:
      noTone(buzzer);
    }
  }
}

void setup()
{
  // Serial begin
  Serial.begin(9200);

  // Retriving security code from EEPROM
  Serial.println("Reading code from EEPROM.");
  EEPROM.get(memoryAddress, codeDigOne);
  EEPROM.get(memoryAddress + 10, codeDigTwo);
  EEPROM.get(memoryAddress + 20, codeDigThree);
  delay(1000);

  // Confirmation
  Serial.println("Code from EEPROM: ");
  Serial.print("Number One: ");
  Serial.println(codeDigOne);
  Serial.print("Number Two: ");
  Serial.println(codeDigTwo);
  Serial.print("Number Three: ");
  Serial.println(codeDigThree);

  // Setup light sensor
  pinMode(LDR, INPUT);
  lightSensor(); // Reading default value


  // Set up output pins
  pinMode(data, OUTPUT);
  pinMode(latch, OUTPUT);
  pinMode(clock, OUTPUT);

  // Set up button inputs
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);

  // Start Mistery box in a mode 1 (Stand by for the light sensor read a change in luminescence)
  mode = 1;

  // Claers display
  display_Digit(numberGlyphs[10]);
}


void loop()
{
  if (mode == 1) {
    lightSensor();
    Serial.print("Light Senor read: ");
    Serial.println(LDR_Read);
    if (LDR_Read < 700) {
      // Run didgits
      for (int i = 0; i <= 10; i++) {
        display_Digit(numberGlyphs[i]);
        delay(t);
      }
      // Setting current mode to 2 (Stend by for pressed buttons)
      mode = 2;
    }
  }
  if (mode == 2) {
    read_Push_buttons();

    // If button 1 is pushed
    if (button1_Read == 0) {
      read_Slider(1);
      display_Digit(numberGlyphs[slider1_Read_Map]);
      delay(t);

      // Claers display
      display_Digit(numberGlyphs[10]);
    }

    // If button 1 is pushed
    if (button2_Read == 0) {
      read_Slider(2);
      display_Digit(numberGlyphs[slider2_Read_Map]);
      delay(t);

      // Claers display
      display_Digit(numberGlyphs[10]);
    }

    // If button 1 is pushed
    if (button3_Read == 0) {
      read_Slider(3);
      display_Digit(numberGlyphs[slider3_Read_Map]);
      delay(t);
      // Claers display
      display_Digit(numberGlyphs[10]);
    }
    if ((slider1_Read_Map == codeDigOne) && (slider2_Read_Map == codeDigTwo) && (slider3_Read_Map == codeDigThree)) {
      if((button1_Read == 1) &&  (button2_Read == 1) && (button3_Read == 1)) mode = 3;
    }

  }

  if (mode == 3) {
    play_Melody_One();
    delay(t);
    slider1_Read_Map = -1;
    slider2_Read_Map = -1;
    slider3_Read_Map = -1;
    mode = 1;
  }

}
