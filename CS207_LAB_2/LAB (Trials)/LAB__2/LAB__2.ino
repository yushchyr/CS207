/*
   Roman Yushchyk
   200368308
   UofR CS207

*/
#include "LED.h" // Blinker function prototype file
// Variable collection.
int t = 1000; // t = 1 second (1000mLs).Interval for ON time.
int t2 = 2000; // t2 = 2 seconds (2000mLs). Interval for OFF time.
int led = 13; // Led pin assignment
int l = 122;
int l2 = 22;
int s = 22;
int s2 = 122;
String* num_Of_Char;
String t_m = "Test";

void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT); // Activation of a Pin mode
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  // blinker(led, t, t2); // Blinker function call to Blinker.h file.
  // sos(led, l , l2, s, s2, t2); // SOS Blinker manual
  String num_Of_Ch(String t_m, String& num_Of_Char);
  delay(1000);
  Serial.println(* num_Of_Char);
//void  t_To_m (int led, int l, int l2, int s, int s2,  int t2, String t_m);
}
