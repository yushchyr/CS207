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
// Common start points for a Graphic block of elements
int pos_X;
int pos_Y;
bool exitButton = false;

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
#define ORANGE          0xFD20      /* 255, 165,   0 */
#define GreenYellow     0xAFE5      /* 173, 255,  47 */
#define PINK            0xF81F

// Real Time Clock instance
DS3231 rtc;
bool Century = false;
byte DoW = -1;
byte oldDoW;
String day_Of_The_Week = "";
bool h12;
bool PM;
byte currentDate = -1;
byte currentHours = -1;
byte currentMinutes = -1;
byte currentSeconds = -1;
float temperature;


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
  //show_tft();
  BOXSIZE = tft.width() / 8;
  tft.fillScreen(BLACK);
  tft.fillRect(0, 0, BOXSIZE, BOXSIZE, RED);
  tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, YELLOW);
  tft.fillRect(BOXSIZE * 2, 0, BOXSIZE, BOXSIZE, GREEN);
  tft.fillRect(BOXSIZE * 3, 0, BOXSIZE, BOXSIZE, CYAN);
  tft.fillRect(BOXSIZE * 4, 0, BOXSIZE, BOXSIZE, BLUE);
  tft.fillRect(BOXSIZE * 5, 0, BOXSIZE, BOXSIZE, MAGENTA);
  tft.fillRect(BOXSIZE * 6, 0, BOXSIZE, BOXSIZE, ORANGE);
  tft.fillRect(BOXSIZE * 7, 0, BOXSIZE, BOXSIZE, WHITE);
  tft.drawRect(0, 0, BOXSIZE, BOXSIZE, WHITE);
  currentcolor = RED;
  delay(1000);
}

void paint_Loop() {
  touch_Screen_Read();
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
      } else if (xpos < BOXSIZE * 7) {
        currentcolor = ORANGE;
        tft.drawRect(BOXSIZE * 6, 0, BOXSIZE, BOXSIZE, WHITE);
      } else if (xpos < BOXSIZE * 8) {
        currentcolor = WHITE;
        tft.drawRect(BOXSIZE * 7, 0, BOXSIZE, BOXSIZE, WHITE);
      }

      if (oldcolor != currentcolor) { //rub out the previous white border
        if (oldcolor == RED) tft.fillRect(0, 0, BOXSIZE, BOXSIZE, RED);
        if (oldcolor == YELLOW) tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, YELLOW);
        if (oldcolor == GREEN) tft.fillRect(BOXSIZE * 2, 0, BOXSIZE, BOXSIZE, GREEN);
        if (oldcolor == CYAN) tft.fillRect(BOXSIZE * 3, 0, BOXSIZE, BOXSIZE, CYAN);
        if (oldcolor == BLUE) tft.fillRect(BOXSIZE * 4, 0, BOXSIZE, BOXSIZE, BLUE);
        if (oldcolor == MAGENTA) tft.fillRect(BOXSIZE * 5, 0, BOXSIZE, BOXSIZE, MAGENTA);
        if (oldcolor == ORANGE) tft.fillRect(BOXSIZE * 6, 0, BOXSIZE, BOXSIZE, ORANGE);
        if (oldcolor == WHITE) tft.fillRect(BOXSIZE * 7, 0, BOXSIZE, BOXSIZE, WHITE);
      }
    }
    
    // are we in drawing area ?
    if (((ypos - PENRADIUS) > BOXSIZE) && ((ypos + PENRADIUS) < tft.height() - 10)) { // -10 To stop a pan leaving mark at eraze
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

void set_Clock(byte h, byte m, byte s, bool f, bool p) {

  byte newHour = h;
  byte newMinutes = m;
  byte newSeconds = s;
  bool h12 = f;
  bool PM = p;
  if ((newHour != "") && (newMinutes != "") && (newSeconds != "")) {
    rtc.setHour(newHour);
    rtc.setMinute(newMinutes);
    rtc.setSecond(newSeconds);
  }
}

void set_Date(int mm, int dd, int yr, int doW) {
  if ((mm != "") && (dd != "") && (yr != "") && (doW != "")) {
    rtc.setMonth(mm);
    rtc.setDate(dd);
    rtc.setYear(yr);
    rtc.setDoW(doW);
  }

}

void draw_Column(int x, int y1, int y2, int c) {
  // Draw a top dot divider
  tft.drawPixel(x + 2, y1, c);
  tft.drawPixel(x + 1, y1 + 1, c);
  tft.drawPixel(x + 2, y1 + 1, c);
  tft.drawPixel(x + 3, y1 + 1, c);
  tft.drawPixel(x, y1 + 2, c);
  tft.drawPixel(x + 1, y1 + 2, c);
  tft.drawPixel(x + 2, y1 + 2, c);
  tft.drawPixel(x + 3, y1 + 2, c);
  tft.drawPixel(x + 4, y1 + 2, c);
  tft.drawPixel(x, y1 + 3, c);
  tft.drawPixel(x + 1, y1 + 3, c);
  tft.drawPixel(x + 2, y1 + 3, c);
  tft.drawPixel(x + 3, y1 + 3, c);
  tft.drawPixel(x + 4, y1 + 3, c);
  tft.drawPixel(x + 1, pos_Y + 21, c);
  tft.drawPixel(x + 2, pos_Y + 21, c);
  tft.drawPixel(x + 3, pos_Y + 21, c);
  tft.drawPixel(x + 2, pos_Y + 22, c);

  // Draw a bottom dot divider
  tft.drawPixel(x + 2, y2, c);
  tft.drawPixel(x + 1, y2 + 1, c);
  tft.drawPixel(x + 2, y2 + 1, c);
  tft.drawPixel(x + 3, y2 + 1, c);
  tft.drawPixel(x, y2 + 2, c);
  tft.drawPixel(x + 1, y2 + 2, c);
  tft.drawPixel(x + 2, y2 + 2, c);
  tft.drawPixel(x + 3, y2 + 2, c);
  tft.drawPixel(x + 4, y2 + 2, c);
  tft.drawPixel(x, y2 + 3, c);
  tft.drawPixel(x + 1, y2 + 3, c);
  tft.drawPixel(x + 2, y2 + 3, c);
  tft.drawPixel(x + 3, y2 + 3, c);
  tft.drawPixel(x + 4, y2 + 3, c);
  tft.drawPixel(x + 1, y2 + 4, c);
  tft.drawPixel(x + 2, y2 + 4, c);
  tft.drawPixel(x + 3, y2 + 4, c);
  tft.drawPixel(x + 2, y2 + 5, c);
}

void drawHomeClock() {

  // Setting clock to 24 HR mode if h12 is false
  rtc.setClockMode(h12);

  // Clock size and color
  tft.setTextSize(10); // Letter size = 65
  tft.setTextColor(GREEN); // Color is green



  pos_X = 35; // Object group beginniing
  pos_Y = 60; // Object group beginniing

  tft.setCursor(pos_X, pos_Y); // Set cursor

  if (currentHours != rtc.getHour(h12)) { // If Hours update

    if (h12 == false) { // If clock in 24 hours format

      if ((rtc.getHour(h12) >= 10)) { // If Hours is a double digit in 24 hours mode
        tft.setCursor(pos_X + 10, pos_Y);
        tft.fillRect(pos_X + 20, pos_Y, pos_X + 65, pos_Y + 20, BLACK);
        currentHours = rtc.getHour(h12); // Get new current time
        tft.print(currentHours); // Print curent hours
        tft.setCursor(pos_X - 30, pos_Y - 6);
        tft.setTextSize(2);
        tft.setTextColor(RED);
        tft.fillRect(pos_X - 30, pos_Y, pos_X, pos_Y - 29, BLACK);
        tft.print("24H");
      }
      else if (rtc.getHour(h12) == 0) {
        tft.fillRect(pos_X + 10, pos_Y, pos_X + 75, pos_Y + 20, BLACK);
        currentHours = rtc.getHour(h12); // Get new current time
        tft.setCursor(pos_X + 70, pos_Y - 6);
        tft.print(currentHours); // Print curent hours
        tft.setCursor(pos_X - 30, pos_Y);
        tft.setTextSize(2);
        tft.setTextColor(RED);
        tft.fillRect(pos_X - 30, pos_Y, pos_X, pos_Y - 29, BLACK);
        tft.print("24H");
      }
      else if ((rtc.getHour(h12) > 0) && (rtc.getHour(h12) < 10)) { // If Hours is a single digit in 24 hours mode
        tft.setCursor(pos_X + 65, pos_Y);
        tft.fillRect(pos_X + 65, pos_Y, pos_X + 15, pos_Y + 20, BLACK);
        currentHours = rtc.getHour(h12);
        tft.print(currentHours); // Print curent hours
        tft.setCursor(pos_X - 30, pos_Y);
        tft.setTextSize(2);
        tft.setTextColor(RED);
        tft.fillRect(pos_X - 30, pos_Y, pos_X, pos_Y - 29, BLACK);
        tft.print("24H");
      }

    }

    else if (h12 = true) { // If clock in 12 hours format

      if ((rtc.getHour(h12) >= 10) && (rtc.getHour(h12) <= 11)) { // If Hours is a double digit in 24 hours mode
        tft.setCursor(pos_X + 10, pos_Y);
        tft.fillRect(pos_X + 20, pos_Y, pos_X + 65, pos_Y + 20, BLACK);
        currentHours = rtc.getHour(h12); // Get new current time
        tft.print(currentHours); // Print curent hours
        tft.setCursor(pos_X - 30, pos_Y);
        tft.setTextSize(3);
        tft.setTextColor(RED);
        if (PM) {
          tft.fillRect(pos_X - 30, pos_Y, pos_X - 20, pos_Y - 29, BLACK);
          tft.print("PM");
        }
        else {
          tft.fillRect(pos_X - 30, pos_Y, pos_X - 20, pos_Y - 29, BLACK);
          tft.print("AM");
        }
      }
      else if (rtc.getHour(h12) == 12) {
        PM = !PM;
        tft.setCursor(pos_X + 10, pos_Y);
        tft.fillRect(pos_X + 20, pos_Y, pos_X + 65, pos_Y + 20, BLACK);
        currentHours = rtc.getHour(h12); // Get new current time
        tft.print(currentHours); // Print curent hours
        tft.setCursor(pos_X - 30, pos_Y);
        tft.setTextSize(3);
        tft.setTextColor(RED);
        if (PM) {
          tft.fillRect(pos_X - 30, pos_Y, pos_X - 20, pos_Y - 29, BLACK);
          tft.print("PM");
        }
        else {
          tft.fillRect(pos_X - 30, pos_Y, pos_X - 20, pos_Y - 29, BLACK);
          tft.print("AM");
        }
      }
      else if ((rtc.getHour(h12) >= 0) && (rtc.getHour(h12) < 10)) { // If Hours is a single digit in 24 hours mode
        tft.setCursor(pos_X + 65, pos_Y);
        tft.fillRect(pos_X + 65, pos_Y, pos_X + 15, pos_Y + 20, BLACK);
        currentHours = rtc.getHour(h12);
        tft.print(currentHours); // Print curent hours
        tft.setCursor(pos_X - 30, pos_Y);
        tft.setTextSize(3);
        tft.setTextColor(RED);
        if (PM) {
          tft.fillRect(pos_X - 30, pos_Y, pos_X - 20, pos_Y - 29, BLACK);
          tft.print("PM");
        }
        else {
          tft.fillRect(pos_X - 30, pos_Y, pos_X - 20, pos_Y - 29, BLACK);
          tft.print("AM");
        }
      }
    }


  }

  // Draw column
  draw_Column(pos_X + 130, pos_Y + 17, pos_Y + 47, GREEN);

  //   Minutes update
  if (currentMinutes != rtc.getMinute()) {
    if ((rtc.getMinute() < 10) && (rtc.getMinute() >= 0)) {
      currentMinutes = rtc.getMinute(); // Getting new minutes
      tft.setTextSize(10);
      tft.setTextColor(GREEN);
      tft.fillRect(pos_X + 145, pos_Y, pos_X + 75, pos_Y + 20, BLACK);
      tft.setCursor(pos_X + 145, pos_Y); // Set cursor
      tft.print('0');
      tft.setCursor(pos_X + 205, pos_Y); // Set cursor
      tft.print(currentMinutes); // Print minutes
    }
    else if (rtc.getMinute() >= 10) {
      currentMinutes = rtc.getMinute(); // Getting new minutes
      tft.setTextSize(10);
      tft.setTextColor(GREEN);
      tft.setCursor(pos_X + 145, pos_Y); // Set cursor
      tft.fillRect(pos_X + 145, pos_Y, pos_X + 75, pos_Y + 20, BLACK);
      tft.print(currentMinutes); // Print minutes
    }
  }
  // Draw column
  draw_Column(pos_X + 265, pos_Y + 17, pos_Y + 47, GREEN);

  // Draw seconds
  if (currentSeconds != rtc.getSecond()) {
    if ((rtc.getSecond() >= 0) && (rtc.getSecond() < 10)) {
      currentSeconds = rtc.getSecond(); // Getting new Seconds
      tft.fillRect(pos_X + 285, pos_Y, pos_X + 75, pos_Y + 20, BLACK);
      tft.setCursor(pos_X + 285, pos_Y);
      tft.print('0');
      tft.setCursor(pos_X + 285 + 60, pos_Y); // Set cursor
      tft.print(currentSeconds); // Print Seconds
    }
    else {
      currentSeconds = rtc.getSecond(); // Getting new Seconds
      tft.setCursor(pos_X + 285, pos_Y); // Set cursor
      tft.fillRect(pos_X + 285, pos_Y, pos_X + 75, pos_Y + 20, BLACK);
      tft.print(currentSeconds); // Print Seconds
    }
  }
}

void drawAlarmButton() {
  extern const uint8_t AlarmButton[0x1040];
  pos_X = 365;
  pos_Y = 170;
  tft.setAddrWindow(pos_X, pos_Y, pos_X + 64, pos_Y + 65);
  tft.pushColors(AlarmButton, 4160, 1);
}

void drawMusicPlayerButton() {
  extern const uint8_t MusicPlayerButton[0x1040];
  pos_X = 50;
  pos_Y = 170;
  tft.setAddrWindow(pos_X, pos_Y, pos_X + 64, pos_Y + 65);
  tft.pushColors(MusicPlayerButton, 4160, 1);
}

void drawPaintButton() {
  extern const uint8_t PaintButton[4225];
  pos_X = 207;
  pos_Y = 170;
  tft.setAddrWindow(pos_X, pos_Y, pos_X + 64, pos_Y + 65);
  tft.pushColors(PaintButton, 4224, 1);
}

void drawTemp() {
  // Print temperature in a left top corner
  if (temperature != rtc.getTemperature()) {
    pos_X = 7;
    pos_Y = 6;
    temperature = rtc.getTemperature();
    tft.fillRect(pos_X + 25, pos_Y, 58, 15, BLACK);
    tft.setTextColor(WHITE); // Sets color to white
    tft.setTextSize(2); // Sets font to big
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
  }
}

void drawDate() {
  // Print date
  if (currentDate != rtc.getDate()) {
    tft.setTextColor(WHITE); // Sets color to white
    tft.setTextSize(2); // Sets font to big
    currentDate = rtc.getDate();
    tft.fillRect(pos_X + 368, pos_Y, 100 , 15 , BLACK);
    pos_X = tft.width() - 107;
    tft.setCursor(pos_X, 7);
    tft.print(rtc.getMonth(Century), DEC);
    tft.setCursor(pos_X + 18 , 7);
    tft.print(".");
    if (rtc.getDate() < 10) {
      tft.setCursor(pos_X + 28, 7);
      tft.print(0);
      tft.setCursor(pos_X + 40, 7);
      tft.print(rtc.getDate(), DEC);
    }
    else if (rtc.getDate() >= 10) {
      tft.setCursor(pos_X + 28, 7);
      tft.print(rtc.getDate(), DEC);
    }
    tft.setCursor(pos_X + 48 , 7);
    tft.print('.');
    tft.setCursor(pos_X + 58, 7);
    tft.print("2");
    tft.setCursor(pos_X + 70, 7);
    if (Century == false) {
      tft.print('0');
    } else tft.print('1');
    tft.setCursor(pos_X + 80, 7);
    tft.print(rtc.getYear());
  }
}

void drawDayOfTheWeek() {

  // Print day of the week
  if (oldDoW != DoW) {
    oldDoW = DoW;
    tft.fillRect(369, 23, 106, 17, BLACK);
    tft.setTextSize(2); // Sets font to big
    pos_X = tft.width() - 107;
    if (DoW == 1) {
      tft.setTextColor(GREEN);
      tft.setCursor(pos_X + 32, 24);
      tft.print(day_Of_The_Week);
    }
    if (DoW == 2) {
      tft.setTextColor(YELLOW);
      tft.setCursor(pos_X + 32, 24);
      tft.print(day_Of_The_Week);
    }
    if (DoW == 3) {
      tft.setTextColor(YELLOW);
      tft.setCursor(pos_X + 20, 24);
      tft.print(day_Of_The_Week);
    }
    if (DoW == 4) {
      tft.setTextColor(YELLOW);
      tft.setCursor(pos_X - 4, 24);
      tft.print(day_Of_The_Week);
    }
    if (DoW == 5) {
      tft.setTextColor(YELLOW);
      tft.setCursor(pos_X + 8, 24);
      tft.print(day_Of_The_Week);
    }
    if (DoW == 6) {
      tft.setTextColor(YELLOW);
      tft.setCursor(pos_X + 32, 24);
      tft.print(day_Of_The_Week);
    }
    if (DoW == 7) {
      tft.setTextColor(GREEN);
      tft.setCursor(pos_X + 8, 24);
      tft.print(day_Of_The_Week);
    }

  }
}

void drawAlarmStatus() {
  // Check if alarm is ON or OFF
  if (alarmString == "") {
    tft.setTextSize(2);
    tft.setTextColor(GREEN);
    tft.setCursor ((tft.width() / 2) - 90, 299);
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
}

void drawHomeScreen() {
  tft.fillScreen(BLACK); // Sets the background color of the area where the text will be printed to black
  drawAlarmStatus();
  drawDayOfTheWeek();
  drawTemp();
  drawDate();
  drawHomeClock();
  drawAlarmButton();
  drawMusicPlayerButton();
  drawPaintButton();
}

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
    case 1:
      day_Of_The_Week = "Sunday";
      break;
    case 2:
      day_Of_The_Week = "Monday";
      break;
    case 3:
      day_Of_The_Week = "Tuesday";
      break;
    case 4:
      day_Of_The_Week = "Wednesday";
      break;
    case 5:
      day_Of_The_Week = "Thursday";
      break;
    case 6:
      day_Of_The_Week = "Friday";
      break;
    case 7:
      day_Of_The_Week = "Saturday";
      break;
  }

  // Boot in a Home Screen mode
  currentPage = 0;


  // Initiation of RTC objects;
  h12 = false; // True for 12 hr
  PM = false; // It is evening if PM iis true
  //    set_Clock(2, 21, 54, h12, PM); // Upload time is 24s
  //    set_Date(11, 26, 17, 1); // Last one is the day of the week 1 = Sunday
  // rtc.setHour(2);

  drawHomeScreen();

  //paint_Setup();
}

void loop() {
  //paint_Loop();
  if (currentPage == 0)
  {
    drawAlarmStatus();
    drawDayOfTheWeek();
    drawTemp();
    drawDate();
    drawHomeClock();

    touch_Screen_Read();

    // Coordinates of a paint button
    pos_X = 50;
    pos_Y = 170;
    if ((ypos >= pos_Y) && (ypos <= pos_Y + 65) && (xpos >= 207) && (xpos <= 207 + 65)) {
      currentPage = 1;
      paint_Setup();
    }
  }
  if (currentPage == 1) {
    if (exitButton == false) {
      paint_Loop();
    }
  }
}

