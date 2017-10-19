/*
  Roman Yushchyk
  200368308
  LAB 2
*/
// Resistor A) 100 kOhms
// Resistor B) 120 Ohms
// Resistor C) 150 kOhms

//Pin Assignment
const int LED_PIN = 12; // LED Digital output
const int LED2_PIN = A5; // LED Analog output
const int t = 240; // Standart time
const int dots = t; // Short beep signal length
const int dash = 3 * t; // Long beep signal length
const int p_between_d = t; // Interval in between dashes and dots
const int p_between_l = 3 * t; // Interval between letters
const int p_between_w = 7 * t; // Interval between words
const int buz = 9; // Buzzer pin assignment
const int fr = 220; // Frequancy
String str; // String container
void setup() { // Setup run
  Serial.begin(9600); // Starting serial connection 
  pinMode(LED_PIN, OUTPUT); // Pin initiation
  pinMode(LED2_PIN, OUTPUT); // Analog pin
  Serial.println("Enter your messege here: "); // First line of the interface to be displayd
  }
void delay_In_between_Dash_Or_Dot() { // Delay function prototype
  delay(p_between_d); 
}
void delay_In_between_Letters() {  // Delay function prototype
  delay(p_between_l);
}
void delay_In_between_Words() {  // Delay function prototype
  delay(p_between_w);
}

void short_dot() { // Short beep prototype
  digitalWrite(LED_PIN, HIGH); // Turning 5V On
  tone(buz, fr);
  delay(dots); // How long it stays On
  digitalWrite(LED_PIN, LOW); // Turning 5V Off
  noTone(buz);
}
void long_dash() { // Long beep prototype
  digitalWrite(LED_PIN, HIGH); // Turning 5V On
  tone(buz, fr);
  delay(dash); // How long it stays On
  digitalWrite(LED_PIN, LOW); // Turning 5V Off
  noTone(buz);
}

void loop() {

  if (Serial.available() > 0) { // If data detected over Seril port 1
    str =  Serial.readString(); // Storing it into a string 
    str.toUpperCase(); // Converts lover case to upper case (Morze has no difference between upper and lover cases)
    Serial.println("You entered: "); // Confirmation message
    Serial.println(str); // Data to be processed

    for (int pos = 0; pos < str.length(); pos++) { // For loop to process all of the characters

      switch (str[pos]) { // Switch for characters and numbers

        case '0': // In case of 0
          long_dash(); // Function call
          delay_In_between_Dash_Or_Dot(); // Function call
          long_dash(); // Function call
          delay_In_between_Dash_Or_Dot(); // Function call
          long_dash(); // Function call
          delay_In_between_Dash_Or_Dot(); // Function call
          long_dash(); // Function call
          delay_In_between_Dash_Or_Dot(); // Function call
          long_dash(); // Function call
          if (pos + 1 == " ") // If next character in the string is a white space then delay for the end of the word is used.
            delay_In_between_Words(); // Function call
          else // In any other case delay between letters is used
            delay_In_between_Letters(); // // Function call
          break;


        case '1':
          short_dot();
          delay_In_between_Dash_Or_Dot();
          long_dash();
          delay_In_between_Dash_Or_Dot();
          long_dash();
          delay_In_between_Dash_Or_Dot();
          long_dash();
          delay_In_between_Dash_Or_Dot();
          long_dash();
          if (pos + 1 == " ")
            delay_In_between_Words();
          else 
            delay_In_between_Letters();
          break;

        case '2':
          short_dot();
          delay_In_between_Dash_Or_Dot();
          short_dot();
          delay_In_between_Dash_Or_Dot();
          long_dash();
          delay_In_between_Dash_Or_Dot();
          long_dash();
          delay_In_between_Dash_Or_Dot();
          long_dash();
          if (pos + 1 == " ")
            delay_In_between_Words();
          else
            delay_In_between_Letters();
          break;

        case '3':
          short_dot();
          delay_In_between_Dash_Or_Dot();
          short_dot();
          delay_In_between_Dash_Or_Dot();
          short_dot();
          delay_In_between_Dash_Or_Dot();
          long_dash();
          delay_In_between_Dash_Or_Dot();
          long_dash();
          if (pos + 1 == " ")
            delay_In_between_Words();
          else 
            delay_In_between_Letters();
          break;


        case '4':
          short_dot();
          delay_In_between_Dash_Or_Dot();
          short_dot();
          delay_In_between_Dash_Or_Dot();
          short_dot();
          delay_In_between_Dash_Or_Dot();
          short_dot();
          delay_In_between_Dash_Or_Dot();
          long_dash();
          if (pos + 1 == " ")
            delay_In_between_Words();
          else 
            delay_In_between_Letters();
          break;
        case '5':
          short_dot();
          delay_In_between_Dash_Or_Dot();
          short_dot();
          delay_In_between_Dash_Or_Dot();
          short_dot();
          delay_In_between_Dash_Or_Dot();
          short_dot();
          delay_In_between_Dash_Or_Dot();
          short_dot();
          if (pos + 1 == " ")
            delay_In_between_Words();
          else 
            delay_In_between_Letters();
          break;

        case '6':
          long_dash();
          delay_In_between_Dash_Or_Dot();
          short_dot();
          delay_In_between_Dash_Or_Dot();
          short_dot();
          delay_In_between_Dash_Or_Dot();
          short_dot();
          delay_In_between_Dash_Or_Dot();
          short_dot();
          if (pos + 1 == " ")
            delay_In_between_Words();
          else 
            delay_In_between_Letters();
          break;

        case '7':
          long_dash();
          delay_In_between_Dash_Or_Dot();
          long_dash();
          delay_In_between_Dash_Or_Dot();
          short_dot();
          delay_In_between_Dash_Or_Dot();
          short_dot();
          delay_In_between_Dash_Or_Dot();
          short_dot();
          if (pos + 1 == " ")
            delay_In_between_Words();
          else delay_In_between_Letters();
          break;

        case '8':
          long_dash();
          delay_In_between_Dash_Or_Dot();
          long_dash();
          delay_In_between_Dash_Or_Dot();
          long_dash();
          delay_In_between_Dash_Or_Dot();
          short_dot();
          delay_In_between_Dash_Or_Dot();
          short_dot();
          if (pos + 1 == " ")
            delay_In_between_Words();
          else 
            delay_In_between_Letters();
          break;

        case '9':
          long_dash();
          delay_In_between_Dash_Or_Dot();
          long_dash();
          delay_In_between_Dash_Or_Dot();
          long_dash();
          delay_In_between_Dash_Or_Dot();
          long_dash();
          delay_In_between_Dash_Or_Dot();
          short_dot();
          if (pos + 1 == " ")
            delay_In_between_Words();
          else 
            delay_In_between_Letters();
          break;

        case 'A':
          short_dot();
          delay_In_between_Dash_Or_Dot();
          long_dash();
          if (pos + 1 == " ")
            delay_In_between_Words();
          else 
            delay_In_between_Letters();
          break;

        case 'B':
          long_dash();
          delay_In_between_Dash_Or_Dot();
          short_dot();
          delay_In_between_Dash_Or_Dot();
          short_dot();
          delay_In_between_Dash_Or_Dot();
          short_dot();
          if (pos + 1 == " ")
            delay_In_between_Words();
          else 
            delay_In_between_Letters();
          break;

        case 'C':
          long_dash();
          delay_In_between_Dash_Or_Dot();
          short_dot();
          delay_In_between_Dash_Or_Dot();
          long_dash();
          delay_In_between_Dash_Or_Dot();
          short_dot();
          if (pos + 1 == " ")
            delay_In_between_Words();
          else 
            delay_In_between_Letters();
          break;

        case 'D':
          long_dash();
          delay_In_between_Dash_Or_Dot();
          short_dot();
          delay_In_between_Dash_Or_Dot();
          short_dot();
          if (pos + 1 == " ")
            delay_In_between_Words();
          else 
            delay_In_between_Letters();
          break;

        case 'E':
          short_dot();
          if (pos + 1 == " ")
            delay_In_between_Words();
          else delay_In_between_Letters();
          break;

        case 'F':
          short_dot();
          delay_In_between_Dash_Or_Dot();
          short_dot();
          delay_In_between_Dash_Or_Dot();
          long_dash();
          delay_In_between_Dash_Or_Dot();
          short_dot();
          if (pos + 1 == " ")
            delay_In_between_Words();
          else 
            delay_In_between_Letters();
          break;

        case 'G':
          long_dash();
          delay_In_between_Dash_Or_Dot();
          long_dash();
          delay_In_between_Dash_Or_Dot();
          short_dot();
          if (pos + 1 == " ")
            delay_In_between_Words();
          else 
            delay_In_between_Letters();
          break;

        case 'H':
          short_dot();
          delay_In_between_Dash_Or_Dot();
          short_dot();
          delay_In_between_Dash_Or_Dot();
          short_dot();
          delay_In_between_Dash_Or_Dot();
          short_dot();
          if (pos + 1 == " ")
            delay_In_between_Words();
          else 
            delay_In_between_Letters();
          break;

        case 'I':
          short_dot();
          delay_In_between_Dash_Or_Dot();
          short_dot();
          if (pos + 1 == " ")
            delay_In_between_Words();
          else 
            delay_In_between_Letters();
          break;

        case 'J':
          short_dot();
          delay_In_between_Dash_Or_Dot();
          long_dash();
          delay_In_between_Dash_Or_Dot();
          long_dash();
          delay_In_between_Dash_Or_Dot();
          long_dash();
          if (pos + 1 == " ")
            delay_In_between_Words();
          else 
            delay_In_between_Letters();
          break;

        case 'K':
          long_dash();
          delay_In_between_Dash_Or_Dot();
          short_dot();
          delay_In_between_Dash_Or_Dot();
          long_dash();
          if (pos + 1 == " ")
            delay_In_between_Words();
          else
            delay_In_between_Letters();
          break;

        case 'L':
          short_dot();
          delay_In_between_Dash_Or_Dot();
          long_dash();
          delay_In_between_Dash_Or_Dot();
          short_dot();
          delay_In_between_Dash_Or_Dot();
          short_dot();
          if (pos + 1 == " ")
            delay_In_between_Words();
          else
            delay_In_between_Letters();
          break;

        case 'M':
          long_dash();
          delay_In_between_Dash_Or_Dot();
          long_dash();
          if (pos + 1 == " ")
            delay_In_between_Words();
          else 
            delay_In_between_Letters();
          break;

        case 'N':
          long_dash();
          delay_In_between_Dash_Or_Dot();
          short_dot();
          if (pos + 1 == " ")
            delay_In_between_Words();
          else
            delay_In_between_Letters();
          break;

        case 'O':
          long_dash();
          delay_In_between_Dash_Or_Dot();
          long_dash();
          delay_In_between_Dash_Or_Dot();
          long_dash();
          if (pos + 1 == " ")
            delay_In_between_Words();
          else
            delay_In_between_Letters();
          break;

        case 'P':
          short_dot();
          delay_In_between_Dash_Or_Dot();
          long_dash();
          delay_In_between_Dash_Or_Dot();
          long_dash();
          delay_In_between_Dash_Or_Dot();
          short_dot();
          if (pos + 1 == " ")
            delay_In_between_Words();
          else 
            delay_In_between_Letters();
          break;

        case 'Q':
          long_dash();
          delay_In_between_Dash_Or_Dot();
          long_dash();
          delay_In_between_Dash_Or_Dot();
          short_dot();
          delay_In_between_Dash_Or_Dot();
          long_dash();
          if (pos + 1 == " ")
            delay_In_between_Words();
          else
            delay_In_between_Letters();
          break;

        case 'R':
          short_dot();
          delay_In_between_Dash_Or_Dot();
          long_dash();
          delay_In_between_Dash_Or_Dot();
          short_dot();
          if (pos + 1 == " ")
            delay_In_between_Words();
          else
            delay_In_between_Letters();
          break;

        case 'S':
          short_dot();
          delay_In_between_Dash_Or_Dot();
          short_dot();
          delay_In_between_Dash_Or_Dot();
          short_dot();
          if (pos + 1 == " ")
            delay_In_between_Words();
          else
            delay_In_between_Letters();
          break;

        case 'U':
          short_dot();
          delay_In_between_Dash_Or_Dot();
          short_dot();
          delay_In_between_Dash_Or_Dot();
          long_dash();
          if (pos + 1 == " ")
            delay_In_between_Words();
          else 
            delay_In_between_Letters();
          break;

        case 'V':
          short_dot();
          delay_In_between_Dash_Or_Dot();
          short_dot();
          delay_In_between_Dash_Or_Dot();
          short_dot();
          delay_In_between_Dash_Or_Dot();
          long_dash();
          delay_In_between_Dash_Or_Dot();
          if (pos + 1 == " ")
            delay_In_between_Words();
          else
            delay_In_between_Letters();
          break;

        case 'W':
          short_dot();
          delay_In_between_Dash_Or_Dot();
          long_dash();
          delay_In_between_Dash_Or_Dot();
          long_dash();
          if (pos + 1 == " ")
            delay_In_between_Words();
          else
            delay_In_between_Letters();
          break;

        case 'X':
          long_dash();
          delay_In_between_Dash_Or_Dot();
          short_dot();
          delay_In_between_Dash_Or_Dot();
          short_dot();
          delay_In_between_Dash_Or_Dot();
          long_dash();
          delay_In_between_Dash_Or_Dot();
          if (pos + 1 == " ")
            delay_In_between_Words();
          else
            delay_In_between_Letters();
          break;

        case 'Y':
          long_dash();
          delay_In_between_Dash_Or_Dot();
          short_dot();
          delay_In_between_Dash_Or_Dot();
          long_dash();
          delay_In_between_Dash_Or_Dot();
          long_dash();
          if (pos + 1 == " ")
            delay_In_between_Words();
          else 
            delay_In_between_Letters();
          break;

        case 'Z':
          long_dash();
          delay_In_between_Dash_Or_Dot();
          long_dash();
          delay_In_between_Dash_Or_Dot();
          short_dot();
          delay_In_between_Dash_Or_Dot();
          short_dot();
          if (pos + 1 == " ")
            delay_In_between_Words();
          else
            delay_In_between_Letters();
          break;

      };
    }
    //      In class part
    //
    //      // S
    //      digitalWrite(LED_PIN, HIGH); // Turning 5V On
    //      tone(buz, fr);
    //      delay(dots); // How long it stays On
    //      digitalWrite(LED_PIN, LOW); // Turning 5V Off
    //      noTone(buz);
    //      delay(p_between_d ); // How long it stays OFf
    //
    //      digitalWrite(LED_PIN, HIGH); // Turning 5V On
    //      tone(buz, fr);
    //      delay(dots); // How long it stays On
    //      digitalWrite(LED_PIN, LOW); // Turning 5V Off
    //      noTone(buz);
    //      delay(p_between_d ); // How long it stays OFf
    //
    //      digitalWrite(LED_PIN, HIGH); // Turning 5V On
    //      tone(buz, fr);
    //      delay(dots); // How long it stays On
    //      digitalWrite(LED_PIN, LOW); // Turning 5V Off
    //      noTone(buz);
    //      delay(p_between_l ); // How long it stays OFf
    //
    //      // O
    //      digitalWrite(LED_PIN, HIGH); // Turning 5V On
    //      tone(buz, fr);
    //      delay(dash); // How long it stays On
    //      digitalWrite(LED_PIN, LOW); // Turning 5V Off
    //      noTone(buz);
    //      delay(p_between_d ); // How long it stays OFf
    //
    //      digitalWrite(LED_PIN, HIGH); // Turning 5V On
    //      tone(buz, fr);
    //      delay(dash); // How long it stays On
    //      digitalWrite(LED_PIN, LOW); // Turning 5V Off
    //      noTone(buz);
    //      delay(p_between_d ); // How long it stays OFf
    //
    //      digitalWrite(LED_PIN, HIGH); // Turning 5V On
    //      tone(buz, fr);
    //      delay(dash); // How long it stays On
    //      digitalWrite(LED_PIN, LOW); // Turning 5V Off
    //      noTone(buz);
    //      delay(p_between_l ); // How long it stays OFf
    //
    //
    //      // S
    //      digitalWrite(LED_PIN, HIGH); // Turning 5V On
    //      tone(buz, fr);
    //      delay(dots); // How long it stays On
    //      digitalWrite(LED_PIN, LOW); // Turning 5V Off
    //      noTone(buz);
    //      delay(p_between_d ); // How long it stays OFf
    //
    //      digitalWrite(LED_PIN, HIGH); // Turning 5V On
    //      tone(buz, fr);
    //      delay(dots); // How long it stays On
    //      digitalWrite(LED_PIN, LOW); // Turning 5V Off
    //      noTone(buz);
    //      delay(p_between_d ); // How long it stays OFf
    //
    //      digitalWrite(LED_PIN, HIGH); // Turning 5V On
    //      tone(buz, fr);
    //      delay(dots); // How long it stays On
    //      digitalWrite(LED_PIN, LOW); // Turning 5V Off
    //      noTone(buz);
    //      delay(p_between_w ); // How long it stays OFf
    //
    //      // My Initials
    //
    //      // Y
    //      digitalWrite(LED_PIN, HIGH); // Turning 5V On
    //      delay(dash); // How long it stays On
    //      digitalWrite(LED_PIN, LOW); // Turning 5V Off
    //      delay(p_between_d ); // How long it stays OFf
    //
    //      digitalWrite(LED_PIN, HIGH); // Turning 5V On
    //      delay(dots); // How long it stays On
    //      digitalWrite(LED_PIN, LOW); // Turning 5V Off
    //      delay(p_between_d ); // How long it stays OFf
    //
    //      digitalWrite(LED_PIN, HIGH); // Turning 5V On
    //      delay(dash); // How long it stays On
    //      digitalWrite(LED_PIN, LOW); // Turning 5V Off
    //      delay(p_between_d ); // How long it stays OFf
    //
    //      digitalWrite(LED_PIN, HIGH); // Turning 5V On
    //      delay(dash); // How long it stays On
    //      digitalWrite(LED_PIN, LOW); // Turning 5V Off
    //      delay(p_between_l ); // How long it stays OFf
    //
    //      // R
    //      digitalWrite(LED_PIN, HIGH); // Turning 5V On
    //      delay(dots); // How long it stays On
    //      digitalWrite(LED_PIN, LOW); // Turning 5V Off
    //      delay(p_between_d ); // How long it stays OFf
    //
    //      digitalWrite(LED_PIN, HIGH); // Turning 5V On
    //      delay(dash); // How long it stays On
    //      digitalWrite(LED_PIN, LOW); // Turning 5V Off
    //      delay(p_between_d ); // How long it stays OFf
    //
    //      digitalWrite(LED_PIN, HIGH); // Turning 5V On
    //      delay(dots); // How long it stays On
    //      digitalWrite(LED_PIN, LOW); // Turning 5V Off
    //      delay(p_between_d ); // How long it stays OFf
    //
    //      // Analog
    //
    //      // S
    //      analogWrite(LED2_PIN, 255); // Turning 5V On
    //      delay(dots); // How long it stays On
    //      analogWrite(LED_PIN, 0); // Turning 5V Off
    //      delay(p_between_d ); // How long it stays OFf
    //
    //      analogWrite(LED2_PIN, 255); // Turning 5V On
    //      delay(dots); // How long it stays On
    //      analogWrite(LED_PIN, 0); // Turning 5V Off
    //      delay(p_between_d ); // How long it stays OFf
    //
    //      analogWrite(LED2_PIN, 255); // Turning 5V On
    //      delay(dots); // How long it stays On
    //      analogWrite(LED2_PIN, 0); // Turning 5V Off
    //      delay(p_between_l ); // How long it stays OFf
    //
    //      // O
    //      analogWrite(LED2_PIN, 255); // Turning 5V On
    //      delay(dash); // How long it stays On
    //      analogWrite(LED2_PIN, 0); // Turning 5V Off
    //      delay(p_between_d ); // How long it stays OFf
    //
    //      analogWrite(LED2_PIN, 255); // Turning 5V On
    //      delay(dash); // How long it stays On
    //      analogWrite(LED2_PIN, 0); // Turning 5V Off
    //      delay(p_between_d ); // How long it stays OFf
    //
    //      analogWrite(LED2_PIN, 255); // Turning 5V On
    //      delay(dash); // How long it stays On
    //      analogWrite(LED2_PIN, 0); // Turning 5V Off
    //      delay(p_between_l ); // How long it stays OFf
    //
    //
    //      // S
    //      analogWrite(LED2_PIN, 255); // Turning 5V On
    //      delay(dots); // How long it stays On
    //      analogWrite(LED2_PIN, 0); // Turning 5V Off
    //      delay(p_between_d ); // How long it stays OFf
    //
    //      analogWrite(LED2_PIN, 255); // Turning 5V On
    //      delay(dots); // How long it stays On
    //      analogWrite(LED2_PIN, 0); // Turning 5V Off
    //      delay(p_between_d ); // How long it stays OFf
    //
    //      analogWrite(LED2_PIN, 255); // Turning 5V On
    //      delay(dots); // How long it stays On
    //      analogWrite(LED2_PIN, 0); // Turning 5V Off
    //      delay(p_between_w ); // How long it stays OFf
    //

  }
}
