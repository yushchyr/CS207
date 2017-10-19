
void input(){
  String SMS;
  SMS = Serial.read();
  if(Serial.available() > 0){
  Serial.println(SMS);
  exit;
  }
}

