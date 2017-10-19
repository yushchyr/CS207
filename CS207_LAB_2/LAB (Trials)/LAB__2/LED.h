/*
   Roman Yushchyk
   200368308
   UofR CS207

*/
// Blinker LED Function Prototype
void blinker(int led, int t, int t2) {
  digitalWrite(led, HIGH); // Setting power On +5V.
  delay(t); // Interval ON
  digitalWrite(led, LOW); // Setting power Off 0V.
  delay(t2); // Interval OFF
};

// SOS Signal Function Prototype
void sos(int led, int l, int l2, int s, int s2,  int t2) {
  // Long Beep 1
  digitalWrite(led, HIGH); // Setting power On +5V.
  delay(l); // Interval ON for a Long Beep.
  digitalWrite(led, LOW); // Setting power Off 0V.
  delay(l2); // Interval OFF
  // Long Beep 2
  digitalWrite(led, HIGH); // Setting power On +5V.
  delay(l); // Interval ON for a Long Beep.
  digitalWrite(led, LOW); // Setting power Off 0V.
  delay(l2); // Interval OFF
  // Long Beep 3
  digitalWrite(led, HIGH); // Setting power On +5V.
  delay(l); // Interval ON for a Long Beep.
  digitalWrite(led, LOW); // Setting power Off 0V.
  delay(l2); // Interval OFF
  // Short Beep 1
  digitalWrite(led, HIGH); // Setting power On +5V.
  delay(s); // Interval ON for a Short Beep.
  digitalWrite(led, LOW); // Setting power Off 0V.
  delay(s2); // Interval OFF
  // Short Beep 2
  digitalWrite(led, HIGH); // Setting power On +5V.
  delay(s); // Interval ON for a Short Beep.
  digitalWrite(led, LOW); // Setting power Off 0V.
  delay(s2); // Interval OFF
  // Short Beep 3
  digitalWrite(led, HIGH); // Setting power On +5V.
  delay(s); // Interval ON for a Short Beep.
  digitalWrite(led, LOW); // Setting power Off 0V.
  delay(s2); // Interval OFF
  // Long Beep 1
  digitalWrite(led, HIGH); // Setting power On +5V.
  delay(l); // Interval ON for a Long Beep.
  digitalWrite(led, LOW); // Setting power Off 0V.
  delay(l2); // Interval OFF
  // Long Beep 2
  digitalWrite(led, HIGH); // Setting power On +5V.
  delay(l); // Interval ON for a Long Beep.
  digitalWrite(led, LOW); // Setting power Off 0V.
  delay(l2); // Interval OFF
  // Long Beep 3
  digitalWrite(led, HIGH); // Setting power On +5V.
  delay(l); // Interval ON for a Long Beep.
  digitalWrite(led, LOW); // Setting power Off 0V.
  delay(l2); // Interval OFF
  delay(t2); // Interval in between word SOS is the same as a total word leanfg 2 s.
};

// Text to Morze
// Short Beep
void short_Beep (int led, int s, int s2) {
  digitalWrite(led, HIGH); // Setting power On +5V.
  delay(s); // Interval ON for a Short Beep.
  digitalWrite(led, LOW); // Setting power Off 0V.
  delay(s2); // Interval OFF
}
// Long Beep
void long_Beep(int led, int l, int l2) {
  digitalWrite(led, HIGH); // Setting power On +5V.
  delay(l); // Interval ON for a Long Beep.
  digitalWrite(led, LOW); // Setting power Off 0V.
  delay(l2); // Interval OFF
}
// How many characters in a arrey
String num_Of_Ch(String t_m, int& num_Of_Char){
num_Of_Char = ( t_m.length());
};

void  t_To_m (int led, int l, int l2, int s, int s2,  int t2, String t_m) {

};

