/*
  Roman Yushchyk
  200368308
  CS 207
  ASS 4
*/

// Working Code
// Assignment 4
// Constant initiation
const int b_Down = 2; // Down botton connection
const int b_Left = 3; // Left botton connection
const int b_Up = 4;   // Up botton connection
const int b_Right = 5;// Right botton connection
const int b_A = 6;    // A botton connection
const int b_B = 7;    // B botton connection
const int b_AA = 8;   // AA botton connection
const int b_BB = 9;   // BB button connection

// Void Setep
void setup() {
  Serial.begin(9600); // Activation of a serial port 1
  pinMode(b_Down, INPUT_PULLUP); // Pin down mode assignment
  pinMode(b_Left, INPUT_PULLUP); // Pin left mode assignment
  pinMode(b_Up, INPUT_PULLUP);   // Pin up mode assignment
  pinMode(b_Right, INPUT_PULLUP);// Pin right mode assignment
  pinMode(b_AA, INPUT_PULLUP);   // Pin A mode assignment
  pinMode(b_BB, INPUT_PULLUP);   // Pin B mode assignment
  pinMode(b_A, INPUT_PULLUP);    // Pin AA mode assignment
  pinMode(b_B, INPUT_PULLUP);    // Pin BB mode assignment
}

// Void Loop
void loop() {

  if (digitalRead(b_Down) == 0) { // If button is pressed send a Serial string
    Serial.println("1");

  }

  if (digitalRead(b_Left) == 0) { // If button is pressed send a Serial string
    Serial.println("2");

  }

  if (digitalRead(b_Up) == 0) { // If button is pressed send a Serial string
    Serial.println("3");

  }

  if (digitalRead(b_Right) == 0) { // If button is pressed send a Serial string
    Serial.println("4");

  }

  if (digitalRead(b_A) == 0) { // If button is pressed send a Serial string
    Serial.println("5");

  }

  if (digitalRead(b_B) == 0) { // If button is pressed send a Serial string
    Serial.println("6");

  }

  if (digitalRead(b_AA) == 0) { // If button is pressed send a Serial string
    Serial.println("7");

  }

  if (digitalRead(b_BB) == 0) { // If button is pressed send a Serial string
    Serial.println("8");

  }
}


/*
  Code that didnt want to work properly with a current game.

  Roman Yushchyk
  200368308
  CS 207
  LAB 4


  // Assignment
  const int b_Down = 2;
  const int b_Left = 3;
  const int b_Up = 4;
  const int b_Right = 5;
  const int b_A = 6;
  const int b_B = 7;
  const int b_AA = 8;
  const int b_BB = 9;
  int down_Button_State = 1;
  int left_Button_State = 1;
  int up_Button_State = 1;
  int right_Button_State = 1;
  int a_Button_State = 1;
  int b_Button_State = 1;
  int aA_Button_State = 1;
  int bB_Button_State = 1;
  int new_Button_State = 1;

  // Void Setep
  void setup() {
  Serial.begin(9600);
  pinMode(b_Down, INPUT_PULLUP);
  pinMode(b_Left, INPUT_PULLUP);
  pinMode(b_Up, INPUT_PULLUP);
  pinMode(b_Right, INPUT_PULLUP);
  pinMode(b_AA, INPUT_PULLUP);
  pinMode(b_BB, INPUT_PULLUP);
  pinMode(b_A, INPUT_PULLUP);
  pinMode(b_B, INPUT_PULLUP);
  }

  // Void Loop
  void loop() {

  new_Button_State = digitalRead(b_Down);
  if (new_Button_State != down_Button_State) {
    Serial.println("1");
    down_Button_State = new_Button_State;
    // Serial.println("You pressed Down button");
  }


  new_Button_State = digitalRead(b_Left);
  if (new_Button_State != left_Button_State) {
    Serial.println("2");
     left_Button_State = new_Button_State;
    // Serial.println("You pressed Left buttoon");
  }

  new_Button_State = digitalRead(b_Up);
  if (new_Button_State != up_Button_State) {
    Serial.println("3");
     up_Button_State = new_Button_State;
    // Serial.println("You pressed Up button");
  }

  new_Button_State = digitalRead(b_Right);
  if (new_Button_State != right_Button_State) {
    Serial.println("4");
     right_Button_State = new_Button_State;
    // Serial.println("You pressed Right button");
  }

  new_Button_State = digitalRead(b_A);
  if (new_Button_State != a_Button_State) {
    Serial.println("5");
     a_Button_State = new_Button_State;
    // Serial.println("You pressed Fire Button");
  }

  new_Button_State = digitalRead(b_B);
  if (new_Button_State != b_Button_State) {
    Serial.println("6");
     b_Button_State = new_Button_State;
    //  Serial.println("You pressed Run button");
  }

  new_Button_State = digitalRead(b_AA);
  if (new_Button_State != aA_Button_State) {
    Serial.println("7");
     aA_Button_State = new_Button_State;
    // Serial.println("You pressed Rapid Fire button");
  }

  new_Button_State = digitalRead(b_BB);
  if (new_Button_State != bB_Button_State) {
    Serial.println("8");
     bB_Button_State = new_Button_State;
    // Serial.println("You pressed Constant Run button");
  }
  }
*/
