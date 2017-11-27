int data = 4; 
int clock = 8;
int latch = 7;
int t = 500;
int slider = A2;
int slider_Read;
int slider_Read_Map;
long pattern[10] = {0b11111001, 0b10100100, 0b10110000, 0b10011001, 0b10010010, 0b10000010, 0b11111000, 0b10000000, 0b10011000, 0b10011000};

/*
 * setup() - this function runs once when you turn your Arduino on
 * We set the three control pins to outputs
 */
void setup()
{
  pinMode(data, OUTPUT);
  pinMode(clock, OUTPUT);  
  pinMode(latch, OUTPUT);  
  pinMode(slider, INPUT);
}
void loop(){
  slider_Read  = analogRead(slider);
  slider_Read_Map = map(slider_Read, 0 , 1023, 0, 9);

  updateLEDsLong(pattern[slider_Read_Map]);
 
}
void updateLEDsLong(int value){
  digitalWrite(latch, LOW);    //Pulls the chips latch low
  for(int i = 0; i < 8; i++){  //Will repeat 8 times (once for each bit)
    int bit = value & 0b10000000; //We use a "bitmask" to select only the 16 
                                 //bit in our number 
    value = value << 1;          //we move our number up one bit value so next time bit
                                 //7 will be bit 8 and we will do our math on it
    if(bit == 128){digitalWrite(data, HIGH);} //if bit 8 is a 1, set our data pin high
    else{digitalWrite(data, LOW);}            //if bit 8 is a 0, set the data pin low
    digitalWrite(clock, HIGH);                //the next three lines pulse the clock
    delay(1);
    digitalWrite(clock, LOW);
  }
  digitalWrite(latch, HIGH);  //pulls the latch high, to display our data
}
