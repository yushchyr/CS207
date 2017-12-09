// CS207 Lab Test Template 1
// Name: Roman Yushchyk
// Student Number: 200368308
// part 1 EEProm

// Library
#include <EEPROM.h>

// Initiation
const int memoryAddress = 0;
int codeDigOne = 3;
int codeDigTwo = 3;
int codeDigThree = 3;



void setup() {
  // put your setup code here, to run once:

  // Serial begin
  Serial.begin(9200);

  // Store code to th EEPROM
  Serial.println("Writingrite code to the EEPROM.");
  EEPROM.put(memoryAddress, codeDigOne);
  EEPROM.put(memoryAddress + 10, codeDigTwo);
  EEPROM.put(memoryAddress + 20, codeDigThree);

  // Confirmation
  Serial.println("Reading code from EEPROM.");
  EEPROM.get(memoryAddress, codeDigOne);
  EEPROM.get(memoryAddress + 10, codeDigTwo);
  EEPROM.get(memoryAddress + 20, codeDigThree);
  Serial.print("Number One: ");
  Serial.println(codeDigOne);
  Serial.print("Number Two: ");
  Serial.println(codeDigTwo);
  Serial.print("Number Three: ");
  Serial.println(codeDigThree);

}

void loop() {
  // put your main code here, to run repeatedly:

}
