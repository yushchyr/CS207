int value_Read;

void button(int A_Read) {
 
int value_Read = analogRead(A_Read);
  if (value_Read <= 20) {
    Serial.println("Coll You press the button!");
    Play();
  }
}
