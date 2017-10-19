/*
 *Roman Yushchyk
 *200368308
 *CS 207 
 *LAB 5
 */
 
 // Assignment 
int fanPin = 9; // Fan pin assignment
int tempPin = A1; // Temperature pin assignment
const int t = 1000; // Time constant 1s
volatile float temp; // Place to store rough temp reading
volatile float volts; // Place to store  volt reading
volatile float celsium; // Place to store celsium reading
volatile float far; // Place to store Fahrenheit reading

// Void Setup 
void setup()
{
  Serial.begin(9600); // Initating serial protocal 
  pinMode(fanPin, OUTPUT); // Fan motor pin initiation
  pinMode(tempPin, INPUT); // Temperature sensor pin initiation
}

// Void loop list 
void loop()
{
  temp = analogRead(tempPin); // Storing collected data into a temporary temp float
  volts = analogToVolts(temp); // Converting it to Volts function call
  celsium = voltsToCelsium(volts); // Converting it to Celsium function call
  far = celsiumToFar(celsium);  // Converting it to Fahrenheit function call
  runMotor(celsium); // Turn on fan motor if Celsium is higher or equal to 27 degees of celsium
  //motorOnThenOff(); // Motor on and off function call
  //motorTwoSpeed(); // Motor two speed function call

  // Serial interface data print out
  Serial.print("Rough read from the semsor: ");
  Serial.println(temp);
  Serial.print("Conversion to Volts output: ");
  Serial.println(volts);
  Serial.print("Conversion to Celsium: ");
  Serial.println(celsium);
  Serial.print("Conversion to Fahrenheit: "); 
  Serial.println(far);
  delay(t);
  // End of the void loop
}

// Custom function list
float analogToVolts(float temp) // Analog to Volts function
{
  float volts;
  volts = temp / 1023.0 * 5.0; //Perform conversion
  return volts; // Return result
}

float voltsToCelsium(float volts) // Volts to Celsium function
{
  float celsium = volts * 100 - 50; // Perform conversion
  return celsium; // Return result
}

float celsiumToFar(float celsium) // Celsium to Farhenheits function
{
  float far = celsium * 9 / 5 + 32; // Perform conversion
  return far; // Return result
}

void runMotor(float celsium) // Auto On/Off Fan function
{
  if (celsium >= 27) // If temperature rize above 27 degrees of Culsium
    digitalWrite(fanPin, HIGH); // Enable motor transistor On
  else // Otherwise keep fan motor Off 
    digitalWrite(fanPin, LOW); // Turn motor off
}

void motorOnThenOff()
{
  const int onTime = 2500; //the number of milliseconds for the motor to turn on for
  const int offTime = 1000; //the number of milliseconds for the motor to turn off for

  digitalWrite(fanPin, HIGH); // turns the motor On
  delay(onTime); // waits for onTime milliseconds
  digitalWrite(fanPin, LOW); // turns the motor Off
  delay(offTime); // waits for offTime milliseconds
}

void motorTwoSpeed()
{
  const int onSpeed = 200; // a number between 0 (stopped) and 255 (full speed)
  const int onTime = 1000; //the number of milliseconds for the motor to turn on for

  const int offSpeed = 27; // a number between 0 (stopped) and 255 (full speed)
  const int offTime = 2500; //the number of milliseconds for the motor to turn off for

  analogWrite(fanPin, onSpeed); // turns the motor
  delay(onTime); // waits for onTime milliseconds
  analogWrite(fanPin, offSpeed); // turns the motor Off
  delay(offTime); // waits for offTime milliseconds
}

