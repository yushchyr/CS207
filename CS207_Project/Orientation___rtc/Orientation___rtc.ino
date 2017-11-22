/*
   Roman Yushchyk
   200368308
   Alarm Clock
*/
// Library list
#include <TouchScreen.h>
#include <Adafruit_GFX.h>
#include <UTFTGLUE.h>
#include <TFT_HX8357GLUE.h>
#include <MCUFRIEND_kbv.h>
#include <DS3231.h>

// Intstantiation of a LCD TFT
MCUFRIEND_kbv tft;
//TFT_HX8357GLUE tft;

// Real time clock Intstantiation
DS3231  rtc(SDA, SCL);

// Pin Assignment for a screen
uint8_t YP = A1;  // must be an analog pin, use "An" notation!
uint8_t XM = A2;  // must be an analog pin, use "An" notation!
uint8_t YM = 7;   // can be a digital pin
uint8_t XP = 6;   // can be a digital pin

// Object declaration
uint8_t SwapXY; // Swap switch state container
uint16_t TS_LEFT; // Touch screen reference value container
uint16_t TS_RT; // Touch screen reference value container
uint16_t TS_TOP; // Touch screen reference value container
uint16_t TS_BOT; // Touch screen reference value container
uint16_t identifier;
uint8_t Orientation = 0;    // 0 - 3, 0 - PORTRAIT(USB Side), 1 - Landscape
uint16_t tmp;
uint16_t xpos, ypos;  //screen coordinates
int16_t BOXSIZE;
int16_t PENRADIUS = 3;
uint16_t oldcolor, currentcolor;
char *name = "Unknown controller"; // Screen controller name container
static word totalTime, elapsedTime, playback, minutes, seconds, lastSeconds, minutesR, secondsR;
String currentClock, currentHours, currentMinutes, currentSeconds, currentDate;
String timeString, hoursString, minutesString, secondsString, hoursS, minutesS, secondsS, dateS;
#define MINPRESSURE 20
#define MAXPRESSURE 1000
#define SWAP(a,b) {uint16_t tmp = a; a = b; b = tmp;}
// Color table
#define Black           0x0000      /*   0,   0,   0 */
#define Navy            0x000F      /*   0,   0, 128 */
#define DarkGreen       0x03E0      /*   0, 128,   0 */
#define DarkCyan        0x03EF      /*   0, 128, 128 */
#define Maroon          0x7800      /* 128,   0,   0 */
#define Purple          0x780F      /* 128,   0, 128 */
#define Olive           0x7BE0      /* 128, 128,   0 */
#define LightGrey       0xC618      /* 192, 192, 192 */
#define DarkGrey        0x7BEF      /* 128, 128, 128 */
#define Blue            0x001F      /*   0,   0, 255 */
#define Green           0x07E0      /*   0, 255,   0 */
#define Cyan            0x07FF      /*   0, 255, 255 */
#define Red             0xF800      /* 255,   0,   0 */
#define Magenta         0xF81F      /* 255,   0, 255 */
#define Yellow          0xFFE0      /* 255, 255,   0 */
#define White           0xFFFF      /* 255, 255, 255 */
#define Orange          0xFD20      /* 255, 165,   0 */
#define GreenYellow     0xAFE5      /* 173, 255,  47 */
#define Pink            0xF81F
// Touch screen input instantiation
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
// Touch point container
TSPoint tp; 

void draw_Note_Screen() { // Draw Note function  
  ts = TouchScreen(XP, YP, XM, YM, 300);
  tft.begin(identifier);
  tft.setRotation(Orientation);
  BOXSIZE = tft.width() / 6;
  tft.fillScreen(Black);
  tft.fillRect(0, 0, BOXSIZE, BOXSIZE, Red);
  tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, Yellow);
  tft.fillRect(BOXSIZE * 2, 0, BOXSIZE, BOXSIZE, Green);
  tft.fillRect(BOXSIZE * 3, 0, BOXSIZE, BOXSIZE, Cyan);
  tft.fillRect(BOXSIZE * 4, 0, BOXSIZE, BOXSIZE, Blue);
  tft.fillRect(BOXSIZE * 5, 0, BOXSIZE, BOXSIZE, Magenta);
  tft.drawRect(0, 0, BOXSIZE, BOXSIZE, White);
  currentcolor = Red;
  delay(1000);
  
}

void note_Touch_Input_loop() { // Draw_Note_Loop_Function;
  
    // are we in top color box area ?
    if (ypos < BOXSIZE) {               //draw white border on selected color box
      oldcolor = currentcolor;

      if (xpos < BOXSIZE) {
        currentcolor = Red;
        tft.drawRect(0, 0, BOXSIZE, BOXSIZE, White);
      } else if (xpos < BOXSIZE * 2) {
        currentcolor = Yellow;
        tft.drawRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, White);
      } else if (xpos < BOXSIZE * 3) {
        currentcolor = Green;
        tft.drawRect(BOXSIZE * 2, 0, BOXSIZE, BOXSIZE, White);
      } else if (xpos < BOXSIZE * 4) {
        currentcolor = Cyan;
        tft.drawRect(BOXSIZE * 3, 0, BOXSIZE, BOXSIZE, White);
      } else if (xpos < BOXSIZE * 5) {
        currentcolor = Blue;
        tft.drawRect(BOXSIZE * 4, 0, BOXSIZE, BOXSIZE, White);
      } else if (xpos < BOXSIZE * 6) {
        currentcolor = Magenta;
        tft.drawRect(BOXSIZE * 5, 0, BOXSIZE, BOXSIZE, White);
      }

      if (oldcolor != currentcolor) { // rub out the previous white border
        if (oldcolor == Red) tft.fillRect(0, 0, BOXSIZE, BOXSIZE, Red);
        if (oldcolor == Yellow) tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, Yellow);
        if (oldcolor == Green) tft.fillRect(BOXSIZE * 2, 0, BOXSIZE, BOXSIZE, Green);
        if (oldcolor == Cyan) tft.fillRect(BOXSIZE * 3, 0, BOXSIZE, BOXSIZE, Cyan);
        if (oldcolor == Blue) tft.fillRect(BOXSIZE * 4, 0, BOXSIZE, BOXSIZE, Blue);
        if (oldcolor == Magenta) tft.fillRect(BOXSIZE * 5, 0, BOXSIZE, BOXSIZE, Magenta);
      }
    }
    // are we in drawing area ?
    if (((ypos - PENRADIUS) > BOXSIZE) && ((ypos + PENRADIUS) < tft.height())) {
      tft.fillCircle(xpos, ypos, PENRADIUS, currentcolor);
    }
    // are we in erase area ?
    if (ypos > tft.height() - 10) {
      // press the bottom of the screen to erase
      tft.fillRect(0, BOXSIZE, tft.width(), tft.height() - BOXSIZE, Black);
    }
}


void drawHomeClock() {
  ts = TouchScreen(XP, YP, XM, YM, 300);
  tft.begin(identifier);
  tft.setRotation(Orientation);
  tft.fillScreen(Black);
  timeString = rtc.getTimeStr();
  currentHours = timeString.substring(0, 2);
  currentMinutes = timeString.substring(3, 5);
  currentSeconds = timeString.substring(6, 8);

  tft.setTextSize(2);
  tft.setTextColor(Green);
  tft.setCursor(224, 50);
  tft.print(currentSeconds);
  tft.setCursor(128, 50);
  tft.print(currentMinutes);
  tft.setCursor(32, 50);
  tft.print(currentHours);
  drawColon();
}

void drawColon() {
  tft.fillCircle (112, 65, 4, Green);
  tft.fillCircle (112, 85, 4, Green);
  tft.fillCircle (208, 65, 4, Green);
  tft.fillCircle (208, 85, 4, Green );
}

void setup() {
// put your setup code here, to run once:
  tft.begin(9600);
  tft.reset();
  identifier = tft.readID();
  if (identifier == 0x8357) {
    name = "HX8357D";
    TS_LEFT = 904; TS_RT = 170; TS_TOP = 950; TS_BOT = 158;
    SwapXY = 1;
  }
  else {
    name = "unknown";
  }
  
  // Orientation TFT screen
  switch (Orientation) {
    case 0:   break;        // No change,  calibrated for PORTRAIT
    case 1: SWAP(TS_LEFT, TS_BOT);  SWAP(TS_TOP, TS_RT); break; // Landscape
    case 2: SWAP(TS_LEFT, TS_RT); SWAP(TS_BOT, TS_TOP); break;
    case 3: SWAP(TS_RT, TS_BOT); SWAP(TS_RT, TS_LEFT); break;
  }
  
  // Draw Notes page
  //draw_Note_Screen();

}



void loop() {
  // put your main code here, to run repeatedly:

  tp = ts.getPoint();   //tp.x, tp.y are ADC values
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  pinMode(XP, OUTPUT);
  pinMode(YM, OUTPUT);

  if (tp.z > MINPRESSURE && tp.z < MAXPRESSURE) {
    if (SwapXY != (Orientation & 1)) SWAP(tp.x, tp.y);
    // scale from 0->1023 to tft.width  i.e. left = 0, rt = width
    // most mcufriend have touch (with icons) that extends below the TFT
    // screens without icons need to reserve a space for "erase"
    // scale the ADC values from ts.getPoint() to screen values e.g. 0-239

    // Touch Screen input orientation
    if (Orientation == 0) {
      xpos = map(tp.x, TS_LEFT, TS_RT, 0, tft.width());
      ypos = map(tp.y, TS_BOT, TS_TOP, 0, tft.height());

    }
    else if (Orientation == 1) {
      xpos = map(tp.x, TS_LEFT, TS_RT, 0, tft.width());
      ypos = map(tp.y, TS_TOP, TS_BOT, 0, tft.height());
    }
    else if (Orientation == 2) {
      xpos = map(tp.x, TS_LEFT, TS_RT, 0, tft.width());
      ypos = map(tp.y, TS_BOT, TS_TOP, 0, tft.height());
    }
    else if (Orientation == 3) {
      xpos = map(tp.x, TS_RT, TS_LEFT, 0, tft.width());
      ypos = map(tp.y, TS_TOP, TS_BOT, 0, tft.height());
    }
   // note_Touch_Input_loop();


  }
drawHomeClock();

}
