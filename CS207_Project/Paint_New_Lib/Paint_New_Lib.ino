/*
  Roman Yushchyk
  200368308
  Alarm clock
*/
// Intialisation
#include <Wire.h>
#include <BY8001.h>
#include <DS3231.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;       // hard-wired for UNO shields anyway.
#include <TouchScreen.h>
#if defined(__SAM3X8E__)
#undef __FlashStringHelper::F(string_literal)
#define F(string_literal) string_literal
#endif

// TFT Shield pinout
uint8_t YP = A1;  // must be an analog pin, use "An" notation!
uint8_t XM = A2;  // must be an analog pin, use "An" notation!
uint8_t YM = 7;   // can be a digital pin
uint8_t XP = 6;   // can be a digital pin
uint8_t SwapXY = 0;

// TFT Shield corner touch points values
uint16_t TS_LEFT = 920;
uint16_t TS_RT  = 150;
uint16_t TS_TOP = 940;
uint16_t TS_BOT = 120;
volatile uint16_t xpos = 0, ypos = 0;  //screen coordinates
char *name = "Unknown controller";
// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate

// Touch screen initialisation
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

// Touch point initialisation
TSPoint tp;

// Minimum and maximum pressure input range
#define MINPRESSURE 20
#define MAXPRESSURE 1000

// Swap function prototype
#define SWAP(a, b) {uint16_t tmp = a; a = b; b = tmp;}

// Screen  variables
int16_t BOXSIZE;
int16_t PENRADIUS = 3;
uint16_t identifier, oldcolor, currentcolor;
uint8_t Orientation = 1;    // Landscape orientaion is default
char currentPage, playStatus;
String alarmString = "";
int pos_X; //

// Assign human-readable names to some common 16-bit color values:
#define BLACK           0x0000      /*   0,   0,   0 */
#define Navy            0x000F      /*   0,   0, 128 */
#define DarkGreen       0x03E0      /*   0, 128,   0 */
#define DarkCyan        0x03EF      /*   0, 128, 128 */
#define Maroon          0x7800      /* 128,   0,   0 */
#define Purple          0x780F      /* 128,   0, 128 */
#define Olive           0x7BE0      /* 128, 128,   0 */
#define LightGrey       0xC618      /* 192, 192, 192 */
#define DarkGrey        0x7BEF      /* 128, 128, 128 */
#define BLUE            0x001F      /*   0,   0, 255 */
#define GREEN           0x07E0      /*   0, 255,   0 */
#define CYAN            0x07FF      /*   0, 255, 255 */
#define RED             0xF800      /* 255,   0,   0 */
#define MAGENTA         0xF81F      /* 255,   0, 255 */
#define YELLOW          0xFFE0      /* 255, 255,   0 */
#define WHITE           0xFFFF      /* 255, 255, 255 */
#define Orange          0xFD20      /* 255, 165,   0 */
#define GreenYellow     0xAFE5      /* 173, 255,  47 */
#define Pink            0xF81F

// Real Time Clock instance
DS3231 rtc;
bool Century = false;
int DoW;
String day_Of_The_Week = "Day of the week";


// Show Serial info Screen
void show_Serial(void) {
  Serial.print(F("Found "));
  Serial.print(name);
  Serial.println(F(" LCD driver"));
  Serial.print(F("ID=0x"));
  Serial.println(identifier, HEX);
  Serial.println("Screen is " + String(tft.width()) + "x" + String(tft.height()));
  Serial.println("Calibration is: ");
  Serial.println("LEFT = " + String(TS_LEFT) + " RT  = " + String(TS_RT));
  Serial.println("TOP  = " + String(TS_TOP)  + " BOT = " + String(TS_BOT));
  Serial.print("Wiring is: ");
  Serial.println(SwapXY ? "SWAPXY" : "PORTRAIT");
  Serial.println("YP=" + String(YP)  + " XM=" + String(XM));
  Serial.println("YM=" + String(YM)  + " XP=" + String(XP));
}

// Show TFT info Screen
void show_tft(void) {
  tft.setCursor(0, 0);
  tft.setTextSize(2);
  tft.print(F("Found "));
  tft.print(name);
  tft.println(F(" LCD"));
  tft.setTextSize(1);
  tft.print(F("ID=0x"));
  tft.println(identifier, HEX);
  tft.println("Screen is " + String(tft.width()) + "x" + String(tft.height()));
  tft.println("Calibration is: ");
  tft.println("LEFT = " + String(TS_LEFT) + " RT  = " + String(TS_RT));
  tft.println("TOP  = " + String(TS_TOP)  + " BOT = " + String(TS_BOT));
  tft.print("\nWiring is: ");
  if (SwapXY) {
    tft.setTextColor(CYAN);
    tft.setTextSize(2);
  }
  tft.println(SwapXY ? "SWAPXY" : "PORTRAIT");
  tft.println("YP=" + String(YP)  + " XM=" + String(XM));
  tft.println("YM=" + String(YM)  + " XP=" + String(XP));
  tft.setTextSize(2);
  tft.setTextColor(RED);
  tft.setCursor((tft.width() - 48) / 2, (tft.height() * 2) / 4);
  tft.print("EXIT");
  tft.setTextColor(YELLOW, BLACK);
  tft.setCursor(0, (tft.height() * 6) / 8);
  tft.print("Touch screen for loc");
  while (1) {
    tp = ts.getPoint();
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    pinMode(XP, OUTPUT);
    pinMode(YM, OUTPUT);
    if (tp.z < MINPRESSURE || tp.z > MAXPRESSURE) continue;
    if (tp.x > 450 && tp.x < 570  && tp.y > 450 && tp.y < 570) break;
    tft.setCursor(0, (tft.height() * 3) / 4);
    tft.print("tp.x=" + String(tp.x) + " tp.y=" + String(tp.y) + "   ");
  }
}

// Touch Screen Read
void touch_Screen_Read() {
  // Pressure point read
  tp = ts.getPoint();   //tp.x, tp.y are ADC values
  // if sharing pins, you'll need to fix the directions of the touchscreen pins
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  pinMode(XP, OUTPUT);
  pinMode(YM, OUTPUT);
  //    digitalWrite(XM, HIGH);
  //    digitalWrite(YP, HIGH);
  // we have some minimum pressure we consider 'valid'
  // pressure of 0 means no pressing!

  if (tp.z > MINPRESSURE && tp.z < MAXPRESSURE) {
    // is controller wired for Landscape ? or are we oriented in Landscape?
    if (SwapXY != (Orientation & 1)) SWAP(tp.x, tp.y);
    // scale from 0->1023 to tft.width  i.e. left = 0, rt = width
    // most mcufriend have touch (with icons) that extends below the TFT
    // screens without icons need to reserve a space for "erase"
    // scale the ADC values from ts.getPoint() to screen values e.g. 0-239
    if (Orientation == 0) {
      xpos = map(tp.x, TS_RT, TS_LEFT, 0, tft.width());
      ypos = map(tp.y, TS_BOT, TS_TOP, 0, tft.height());

    }
    else if (Orientation == 1) {
      xpos = map(tp.x, TS_LEFT, TS_RT, 0, tft.width());
      ypos = map(tp.y, TS_BOT, TS_TOP, 0, tft.height());
    }
    else if (Orientation == 2) {
      xpos = map(tp.x, TS_RT, TS_LEFT, 0, tft.width());
      ypos = map(tp.y, TS_BOT, TS_TOP, 0, tft.height());
    }
    else if (Orientation == 3) {
      xpos = map(tp.x, TS_RT, TS_LEFT, 0, tft.width());
      ypos = map(tp.y, TS_BOT, TS_TOP, 0, tft.height());
    }
  }
}

void paint_Setup() {
  show_tft();
  BOXSIZE = tft.width() / 6;
  tft.fillScreen(BLACK);
  tft.fillRect(0, 0, BOXSIZE, BOXSIZE, RED);
  tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, YELLOW);
  tft.fillRect(BOXSIZE * 2, 0, BOXSIZE, BOXSIZE, GREEN);
  tft.fillRect(BOXSIZE * 3, 0, BOXSIZE, BOXSIZE, CYAN);
  tft.fillRect(BOXSIZE * 4, 0, BOXSIZE, BOXSIZE, BLUE);
  tft.fillRect(BOXSIZE * 5, 0, BOXSIZE, BOXSIZE, MAGENTA);
  tft.drawRect(0, 0, BOXSIZE, BOXSIZE, WHITE);
  currentcolor = RED;
  delay(1000);
}

void paint_Loop() {

  // are we in top color box area ?
  if (ypos < BOXSIZE) {               //draw white border on selected color box
    oldcolor = currentcolor;

    if (xpos < BOXSIZE) {
      currentcolor = RED;
      tft.drawRect(0, 0, BOXSIZE, BOXSIZE, WHITE);
    } else if (xpos < BOXSIZE * 2) {
      currentcolor = YELLOW;
      tft.drawRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, WHITE);
    } else if (xpos < BOXSIZE * 3) {
      currentcolor = GREEN;
      tft.drawRect(BOXSIZE * 2, 0, BOXSIZE, BOXSIZE, WHITE);
    } else if (xpos < BOXSIZE * 4) {
      currentcolor = CYAN;
      tft.drawRect(BOXSIZE * 3, 0, BOXSIZE, BOXSIZE, WHITE);
    } else if (xpos < BOXSIZE * 5) {
      currentcolor = BLUE;
      tft.drawRect(BOXSIZE * 4, 0, BOXSIZE, BOXSIZE, WHITE);
    } else if (xpos < BOXSIZE * 6) {
      currentcolor = MAGENTA;
      tft.drawRect(BOXSIZE * 5, 0, BOXSIZE, BOXSIZE, WHITE);
    }

    if (oldcolor != currentcolor) { //rub out the previous white border
      if (oldcolor == RED) tft.fillRect(0, 0, BOXSIZE, BOXSIZE, RED);
      if (oldcolor == YELLOW) tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, YELLOW);
      if (oldcolor == GREEN) tft.fillRect(BOXSIZE * 2, 0, BOXSIZE, BOXSIZE, GREEN);
      if (oldcolor == CYAN) tft.fillRect(BOXSIZE * 3, 0, BOXSIZE, BOXSIZE, CYAN);
      if (oldcolor == BLUE) tft.fillRect(BOXSIZE * 4, 0, BOXSIZE, BOXSIZE, BLUE);
      if (oldcolor == MAGENTA) tft.fillRect(BOXSIZE * 5, 0, BOXSIZE, BOXSIZE, MAGENTA);
    }
  }
  // are we in drawing area ?
  if (((ypos - PENRADIUS) > BOXSIZE) && ((ypos + PENRADIUS) < tft.height())) {
    tft.fillCircle(xpos, ypos, PENRADIUS, currentcolor);
  }
  // are we in erase area ?
  if (ypos > tft.height() - 10) {
    // press the bottom of the screen to erase
    tft.fillRect(0, BOXSIZE, tft.width(), tft.height() - BOXSIZE, BLACK);
  }
}

void TFT_Setup() {

  uint16_t tmp;
  tft.begin(9600);

  tft.reset();
  identifier = tft.readID();
  //    if (identifier == 0) identifier = 0x9341;
  if (0) {
  } else if (identifier == 0x0154) {
    name = "S6D0154";
    TS_LEFT = 914; TS_RT = 181; TS_TOP = 957; TS_BOT = 208;
  } else if (identifier == 0x7783) {
    name = "ST7781";
    TS_LEFT = 865; TS_RT = 155; TS_TOP = 942; TS_BOT = 153;
    SwapXY = 1;
  } else if (identifier == 0x7789) {
    name = "ST7789V";
    YP = A2; XM = A1; YM = 7; XP = 6;
    TS_LEFT = 906; TS_RT = 169; TS_TOP = 161; TS_BOT = 919;
  } else if (identifier == 0x9320) {
    name = "ILI9320";
    YP = A3; XM = A2; YM = 9; XP = 8;
    TS_LEFT = 902; TS_RT = 137; TS_TOP = 941; TS_BOT = 134;
  } else if (identifier == 0x9325) {
    name = "ILI9325";
    TS_LEFT = 900; TS_RT = 103; TS_TOP = 96; TS_BOT = 904;
  } else if (identifier == 0x9325) {
    name = "ILI9325 Green Dog";
    TS_LEFT = 900; TS_RT = 130; TS_TOP = 940; TS_BOT = 130;
  } else if (identifier == 0x9327) {
    name = "ILI9327";
    TS_LEFT = 899; TS_RT = 135; TS_TOP = 935; TS_BOT = 79;
    SwapXY = 1;
  } else if (identifier == 0x9329) {
    name = "ILI9329";
    TS_LEFT = 143; TS_RT = 885; TS_TOP = 941; TS_BOT = 131;
    SwapXY = 1;
  } else if (identifier == 0x9341) {
    name = "ILI9341 BLUE";
    TS_LEFT = 920; TS_RT = 139; TS_TOP = 944; TS_BOT = 150;
    SwapXY = 0;
  } else if (identifier == 0) {
    name = "ILI9341 DealExtreme";
    TS_LEFT = 893; TS_RT = 145; TS_TOP = 930; TS_BOT = 135;
    SwapXY = 1;
  } else if (identifier == 0 || identifier == 0x9341) {
    name = "ILI9341";
    TS_LEFT = 128; TS_RT = 911; TS_TOP = 105; TS_BOT = 908;
    SwapXY = 1;
  } else if (identifier == 0x9486) {
    name = "ILI9486";
    TS_LEFT = 904; TS_RT = 170; TS_TOP = 950; TS_BOT = 158;
  } else if (identifier == 0x9488) {
    name = "ILI9488";
    TS_LEFT = 904; TS_RT = 170; TS_TOP = 950; TS_BOT = 158;
  } else if (identifier == 0xB509) {
    name = "R61509V";
    TS_LEFT = 889; TS_RT = 149; TS_TOP = 106; TS_BOT = 975;
    SwapXY = 1;
  } else if (identifier == 0x5310) {
    name = "HX8357D";
    TS_LEFT = 904; TS_RT = 170; TS_TOP = 950; TS_BOT = 158;
    SwapXY = 1;
  }
  else {
    name = "unknown";
  }
  switch (Orientation) {
    case 0:   break;        // No change,  calibrated for PORTRAIT
    case 1: SWAP(TS_LEFT, TS_BOT);  SWAP(TS_TOP, TS_RT); break; // Landscape
    case 2: SWAP(TS_LEFT, TS_RT); SWAP(TS_BOT, TS_TOP); break;
    case 3: SWAP(TS_RT, TS_BOT); SWAP(TS_RT, TS_LEFT); break;
  }

  ts = TouchScreen(XP, YP, XM, YM, 300);     //call the constructor AGAIN with new values.
  tft.begin(identifier);
  show_Serial();
  tft.setRotation(Orientation);
}

void drawHomeScreen() {
  // Print temperature in a left top corner
  tft.fillScreen(BLACK); // Sets the background color of the area where the text will be printed to black
  tft.setTextColor(WHITE); // Sets color to white
  tft.setTextSize(2); // Sets font to big
  pos_X = 7;
  tft.setCursor(pos_X, 7);
  tft.print("T:");
  tft.setCursor(pos_X + 25, 7);
  tft.print(rtc.getTemperature());
  tft.setTextSize(1);
  tft.setCursor(pos_X + 85, 3);
  tft.print('o');
  tft.setTextSize(2);
  tft.setCursor(pos_X + 94, 7);
  tft.print("C");
  pos_X = tft.width() - 107;
  tft.setCursor(pos_X, 7);
  tft.print(rtc.getMonth(Century), DEC);
  tft.setCursor(pos_X + 18 , 7);
  tft.print(".");
  tft.setCursor(pos_X + 28, 7);
  tft.print(rtc.getDate(), DEC);
  tft.setCursor(pos_X + 48 , 7);
  tft.print('.');
  tft.setCursor(pos_X + 58, 7);
  tft.print("2");
  tft.setCursor(pos_X + 68, 7);
  if (Century == false) {
    tft.print('0');
  } else tft.print('1');
  tft.setCursor(pos_X + 78, 7);
  tft.print(rtc.getYear());

  if (alarmString == "" ) {
    tft.setTextSize(2);
    tft.setTextColor(GREEN);
    tft.setCursor ((tft.width() / 2) - 85, 299);
    tft.print("by Roman Yushchyk");
  }
  else {
    tft.setTextColor(GREEN);
    tft.setTextSize(2);
    tft.setCursor((tft.width() / 2) - 75, 280);
    tft.print("Alarm set for: ");
    tft.setCursor((tft.width() / 2) - 75 , 299);
    tft.print(alarmString);
  }
  //  drawMusicPlayerButton();
  //   drawAlarmButton();
  //    drawHomeClock();
}

void drawMusicPlayerButton() {

}

void drawAlarmButton() {

}
//
//void drawHomeClock() {
//  currentHours = rtc.getHour();
//  currentMinutes = rtc.getMinute();
//  currentSeconds = rtc.getSecond();
//  tft.setTextSize(2);
//  tft.setTextColor(GREEN);
//  tft.setCursor(224, 50);
//  tft.print(currentSeconds);
//  tft.setCursor(128, 50);
//  tft.print(currentMinutes);
//  tft.setCursor( 32, 50);
//  tft.print(currentHours);
//  drawColon();
//}
//
//
//void drawColon() {
//  myGLCD.setColor(0, 255, 0);
//  myGLCD.fillCircle (112, 65, 4);
//  myGLCD.setColor(0, 255, 0);
//  myGLCD.fillCircle (112, 85, 4);
//  myGLCD.setColor(0, 255, 0);
//  myGLCD.fillCircle (208, 65, 4);
//  myGLCD.setColor(0, 255, 0);
//  myGLCD.fillCircle (208, 85, 4);
//}

void setup() {

  // Begin serial
  Serial.begin(9600);

  // Begin wire library instamnce for Real Time Clock
  Wire.begin();

  // Setup TFT screen
  TFT_Setup();

  // Get current day of the week froom RTC
  DoW = rtc.getDoW();
  
  // Day of the week switch function
  switch (DoW) {
    case 0:
      day_Of_The_Week = "Sunday";
      break;
    case 1:
      day_Of_The_Week = "Monday";
      break;
    case 2:
      day_Of_The_Week = "Tuesday";
      break;
    case 3:
      day_Of_The_Week = "Wednesday";
      break;
    case 4:
      day_Of_The_Week = "Thursday";
      break;
    case 5:
      day_Of_The_Week = "Friday";
      break;
    case 6:
      day_Of_The_Week = "Saturday";
      break;
  }

  currentPage = 0; // Boot in a Home Screen mode
  if (currentPage == 0) {
    drawHomeScreen();
  }

  //paint_Setup();
}

void loop() {
  //paint_Loop();
  touch_Screen_Read();
}

