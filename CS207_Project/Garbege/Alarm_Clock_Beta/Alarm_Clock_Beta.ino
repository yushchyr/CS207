#include <FreeDefaultFonts.h>
#include <MCUFRIEND_kbv.h>
#include <TFT_HX8357GLUE.h>
#include <UTFTGLUE.h>

/*
  Arduino Touch Screen MP3 Music Player and Alarm Clock

  Crated by Dejan Nedelkovski,
  www.HowToMechatronics.com

  UFTF, URTouch and DS3231 libraries made by Henning Karlsen which can be found and downloaded from his website, www.rinkydinkelectronics.com.
  BY8001 MP3 Player Library made by borland of Arduino forum, Released in public domain. Dowload link: https://github.com/r0ndL/BY8001
*/
//#include <Adafruit_GFX.h>    // Core graphics library
//#include <Adafruit_TFTLCD.h> // Hardware-specific library
//#include <UTFT.h>
//#include <URTouch.h>
#include <SoftwareSerial.h>
#include <BY8001.h>
#include <DS3231.h>
//==== Creating Objects
//UTFT     tft(SSD1289, 38, 39, 40, 41); //Parameters should be adjusted to your Display/Schield model
//MCUFRIEND_kbv tft;
TFT_HX8357GLUE tft;
//Adafruit_TFTLCD tft;

//URTouch  myTouch( 6, 5, 4, 3, 2);
SoftwareSerial mp3Serial(11, 10);  // RX, TX
BY8001 mp3;  // creating an instance of class BY8001 and call it 'mp3'
DS3231  rtc(SDA, SCL);
//==== Defining Fonts
extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];
extern unsigned int MusicPlayerButton[0x1040];
extern unsigned int AlarmButton[0x1040];
extern unsigned int ButtonPlay[0x1AE9];
extern unsigned int ButtonPause[0x1AE9];
extern unsigned int PreviousButton[0x9C4];
extern unsigned int NextButton[0x9C4];
extern unsigned int VolumeDown[0x170];
extern unsigned int VolumeUp[0x3B8];
int x, y; // Variables for the coordinates where the display has been pressed
char currentPage, playStatus;
int iV = 15;
int trackNum = 1;
int b = 16;
int aHours = 0;
int aMinutes = 0;
int mercury_Value; // Mercury tilt swithc state
int mercury_Pin = A5; // Mercury pin
boolean alarmNotSet = true;
String alarmString = "";
float currentTemperature, temperature;
static word totalTime, elapsedTime, playback, minutes, seconds, lastSeconds, minutesR, secondsR;
String currentClock, currentHours, currentMinutes, currentSeconds, currentDate;
String timeString, hoursString, minutesString, secondsString, hoursS, minutesS, secondsS, dateS;

void setup() {
  // Initiate display
  tft.begin(0x9488);
  //tft.InitLCD();
  //tft.clrScr();
  //myTouch.InitTouch();
  //myTouch.setPrecision(PREC_MEDIUM);
  // Initialize the rtc object
  rtc.begin();
  // Music
  Serial.begin(9600);  // set serial monitor baud rate to Arduino IDE
  mp3Serial.begin(9600);  // BY8001 set to 9600 baud (required)
  mp3.setup(mp3Serial); // tell BY8001 library which serial port to use.
  delay(800);  // allow time for BY8001 cold boot; may adjust depending on flash storage size

  drawHomeScreen();  // Draws the Home Screen
  currentPage = '0'; // Indicates that we are at Home Screen
  playStatus = '0';
  mp3.setVolume(15);
  delay(100);
  currentTemperature = rtc.getTemp();
  currentDate = rtc.getDateStr();
  currentClock = rtc.getTimeStr();
  timeString = rtc.getTimeStr();
  currentHours = timeString.substring(0, 2);
  currentMinutes = timeString.substring(3, 5);
  currentSeconds = timeString.substring(6, 8);
}
void loop() {
  // Homes Screen
  if (currentPage == '0') {
    // Checks for change of the clock
    if ( currentClock != rtc.getTimeStr()) {
      timeString = rtc.getTimeStr();
      hoursS = timeString.substring(0, 2);
      minutesS = timeString.substring(3, 5);
      secondsS = timeString.substring(6, 8);
      tft.setFont(SevenSegNumFont);
      tft.setColor(0, 255, 0);
      tft.print(secondsS, 224, 50);

      if ( currentMinutes != minutesS ) {
        tft.print(minutesS, 128, 50);
        currentMinutes = minutesS;
      }
      if ( currentHours != hoursS ) {
        tft.print(hoursS, 32, 50);
        currentHours = hoursS;
      }
      // Checks for change of the date
      dateS = rtc.getDateStr();
      delay(10);
      if ( currentDate != dateS) {
        tft.setColor(255, 255, 255); // Sets color to white
        tft.setFont(BigFont); // Sets font to big
        tft.print(rtc.getDateStr(), 153, 7);
      }
      // Checks for change of the temperature
      temperature = rtc.getTemp();
      delay(10);
      if ( currentTemperature != temperature ) {
        tft.setColor(255, 255, 255); // Sets color to white
        tft.setFont(BigFont); // Sets font to big
        tft.printNumI(temperature, 39, 7);
        currentTemperature = temperature;
      }
      delay(10);
      currentClock = rtc.getTimeStr();
    }
    // Checks whether the screen has been touched
    if (myTouch.dataAvailable()) {
      myTouch.read();
      x = myTouch.getX(); // X coordinate where the screen has been pressed
      y = myTouch.getY(); // Y coordinates where the screen has been pressed

      // If we press the Music Player Button
      if ((x >= 55) && (x <= 120) && (y >= 125) && (y <= 190)) { // Touch scrreen range for a button read
        drawFrame(87, 157, 33);
        currentPage = '1';
        tft.clrScr();
        delay(100);
        drawMusicPlayerScreen();
        delay(100);
      }

      // If we press the Alarm Button
      if ((x >= 195) && (x <= 260) && (y >= 125) && (y <= 190)) { // Touch scrreen range for a button read
        drawFrame(227, 160, 29);
        currentPage = '2';
        tft.clrScr();
      }
    }
  }

  // Music Player Screen
  if (currentPage == '1') {
    if (myTouch.dataAvailable()) {
      myTouch.read();
      x = myTouch.getX(); // X coordinate where the screen has been pressed
      y = myTouch.getY(); // Y coordinates where the screen has been pressed

      // If we press the Play Button
      if ((x >= 116) && (x <= 204) && (y >= 77) && (y <= 165)) { // Touch scrreen range for a Play button read
        if (playStatus == '0') {
          drawFrame(159, 121, 42);
          drawPauseButton();
          mp3.playTrackFromFolder(00, 001);
          delay(100);
          playStatus = '2';
          return;
        }
        if (playStatus == '1') {
          drawFrame(159, 121, 42);
          drawPauseButton();
          mp3.play();
          delay(100);
          playStatus = '2';
          return;
        }
        if (playStatus == '2') {
          drawFrame(159, 121, 42);
          drawPlayButton();
          mp3.pause();
          delay(100);
          playStatus = '1';
          return;
        }
      }

      // If we press the Previous Button
      if ((x >= 45) && (x <= 95) && (y >= 97) && (y <= 147)) { // Touch scrreen range for a button read
        drawFrame(70, 121, 26);
        mp3.previousTrack();
        delay(100);
        drawTrackBar();
      }

      // If we press the Next Button
      if ((x >= 227) && (x <= 277) && (y >= 97) && (y <= 147)) { // Touch scrreen range for a button read
        drawFrame(252, 122, 26);
        mp3.nextTrack();
        delay(100);
        drawTrackBar();
      }

      // If we press the VolumeDown Button
      if ((x >= 35) && (x <= 75) && (y >= 165) && (y <= 209)) { // Touch scrreen range for a button read
        drawUnderline(45, 205, 65, 205);
        if (iV >= 0 & iV <= 30) {
          iV--;
          drawVolume(iV);
        }
        mp3.decreaseVolume();
        delay(100);
      }

      // If we press the VolumeUp Button
      if ((x >= 230) && (x <= 280) && (y >= 165) && (y <= 209)) { // Touch scrreen range for a button read
        drawUnderline(235, 205, 275, 205);
        if (iV >= 0 & iV <= 30) {
          iV++;
          drawVolume(iV);
        }
        mp3.increaseVolume();
        delay(100);
      }

      // If we press the MENU Button
      if ((x >= 0) && (x <= 75) && (y >= 0) && (y <= 30)) { // Touch scrreen range for a button read
        tft.clrScr(); // Clearing a screen before drawing a new frame
        drawHomeScreen();  // Draws the Home Screen
        currentPage = '0';
        return;
      }
    }

    // Updates the track bar
    if (playStatus == '1' || playStatus == '2') {
      trackPlayTime();
    }

    // Printing the clock in the upper right corner
    tft.setFont(BigFont);
    tft.setColor(255, 255, 255);
    printClock(187, 5);
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Alarm Clock Screen
  if (currentPage == '2') {
    tft.setFont(BigFont);
    tft.setColor(255, 255, 255);
    tft.print("MENU", 5, 5);
    tft.print("Set Alarm", CENTER, 20);

    // Draws a colon between the hours and the minutes
    tft.setColor(0, 255, 0);
    tft.fillCircle (112, 65, 4);
    tft.setColor(0, 255, 0);
    tft.fillCircle (112, 85, 4);
    tft.setFont(SevenSegNumFont);
    tft.setColor(0, 255, 0);
    tft.printNumI(aHours, 32, 50, 2, '0');
    tft.printNumI(aMinutes, 128, 50, 2, '0');
    tft.setColor(255, 255, 255);
    tft.drawRoundRect (42, 115, 82, 145);
    tft.drawRoundRect (138, 115, 178, 145);
    tft.setFont(BigFont);
    tft.print("H", 54, 122);
    tft.print("M", 150, 122);

    tft.drawRoundRect (215, 60, 303, 90);
    tft.print("SET", 236, 67);
    tft.drawRoundRect (215, 115, 303, 145);
    tft.print("CLEAR", 220, 122);

    alarmNotSet = true;

    while (alarmNotSet) {
      if (myTouch.dataAvailable()) {
        myTouch.read();
        x = myTouch.getX(); // X coordinate where the screen has been pressed
        y = myTouch.getY(); // Y coordinates where the screen has been pressed
        //Set hours button
        if ((x >= 42) && (x <= 82) && (y >= 115) && (y <= 145)) {
          drawRectFrame(42, 115, 82, 145);
          aHours++;
          if (aHours >= 24) {
            aHours = 0;
          }
          tft.setFont(SevenSegNumFont);
          tft.setColor(0, 255, 0);
          tft.printNumI(aHours, 32, 50, 2, '0');
        }

        // Set minutes buttons
        if ((x >= 138) && (x <= 178) && (y >= 115) && (y <= 145)) {
          drawRectFrame(138, 115, 178, 145);
          aMinutes++;
          if (aMinutes >= 60) {
            aMinutes = 0;
          }
          tft.setFont(SevenSegNumFont);
          tft.setColor(0, 255, 0);
          tft.printNumI(aMinutes, 128, 50, 2, '0');
        }

        // Set alarm button
        if ((x >= 215) && (x <= 303) && (y >= 60) && (y <= 80)) {
          drawRectFrame(215, 60, 303, 90);
          if (aHours < 10 && aMinutes < 10) {
            alarmString = "0" + (String)aHours + ":" + "0" + (String)aMinutes + ":" + "00";
          }
          else if (aHours < 10 && aMinutes > 9) {
            alarmString = "0" + (String)aHours + ":" + (String)aMinutes + ":" + "00";
          }
          else if (aHours > 9 && aMinutes < 10) {
            alarmString = (String)aHours + ":" + "0" + (String)aMinutes + ":" + "00";
          }
          else {
            alarmString = (String)aHours + ":" + (String)aMinutes + ":" + "00";
          }
          tft.setFont(BigFont);
          tft.print("Alarm set for:", CENTER, 165);
          tft.print(alarmString, CENTER, 191);

        }

        // Clear alarm button
        if ((x >= 215) && (x <= 303) && (y >= 115) && (y <= 145)) {
          drawRectFrame(215, 115, 303, 145);
          alarmString = "";
          tft.setColor(0, 0, 0);
          tft.fillRect(45, 165, 275, 210);
        }

        // If we press the MENU Button
        if ((x >= 0) && (x <= 75) && (y >= 0) && (y <= 30)) {
          alarmNotSet = false;
          currentPage = '0';
          tft.clrScr();
          drawHomeScreen();  // Draws the Home Screen
        }
      }
    }

  }
  
  // Alarm activation
  if (alarmNotSet == false) {
    if (alarmString == rtc.getTimeStr()) {
      tft.clrScr();
      mp3.setVolume(25);
      mp3.playTrackByIndexNumber(1);
      delay(100);
      tft.setFont(BigFont);
      tft.setColor(255, 255, 255);
      tft.print("ALARM", CENTER, 90);
      tft.drawBitmap (127, 10, 65, 64, AlarmButton);
      tft.print(alarmString, CENTER, 114);
      tft.drawRoundRect (94, 146, 226, 170);
      tft.print("DISMISS", CENTER, 150); // Alarm control
      boolean alarmOn = true;
      while (alarmOn) {
        if (myTouch.dataAvailable()) {
          myTouch.read();
          x = myTouch.getX(); // X coordinate where the screen has been pressed
          y = myTouch.getY(); // Y coordinates where the screen has been pressed
          
          // Add Read value from a mercury tilt switch 
          mercury_Value = analogRead(mercury_Pin);
          
          // Add condition for a snoze
          if(mercury_Value != 0){
            alarmOn = false;
            alarmString = "";
            tft.clrScr();
            mp3.stopPlayback();
            delay(100);
            currentPage = '0';
            playStatus = '0';
            mp3.setVolume(15);
            drawHomeScreen();
          }
          // Stop alarm button
          if ((x >= 94) && (x <= 226) && (y >= 146) && (y <= 170)) { 
            drawRectFrame(94, 146, 226, 170);
            alarmOn = false;
            alarmString = "";
            tft.clrScr();
            mp3.stopPlayback();
            delay(100);
            currentPage = '0';
            playStatus = '0';
            mp3.setVolume(15);
            drawHomeScreen();
          }

        }
      }
    }
  }
}

void drawHomeScreen() {
  tft.setBackColor(0, 0, 0); // Sets the background color of the area where the text will be printed to black
  tft.setColor(255, 255, 255); // Sets color to white
  tft.setFont(BigFont); // Sets font to big
  tft.print(rtc.getDateStr(), 153, 7);
  tft.print("T:", 7, 7);
  tft.printNumI(rtc.getTemp(), 39, 7);
  tft.print("C", 82, 7);
  tft.setFont(SmallFont);
  tft.print("o", 74, 5);
  if (alarmString == "" ) {
    tft.setColor(255, 255, 255);
    tft.print("by www.HowToMechatronics.com", CENTER, 215);
  }
  else {
    tft.setColor(255, 255, 255);
    tft.print("Alarm set for: ", 68, 215);
    tft.print(alarmString, 188, 215);
  }
  drawMusicPlayerButton();
  drawAlarmButton();
  drawHomeClock();
}

void drawMediaScren() {
  tft.setBackColor(0, 0, 0); // Sets the background color of the area where the text will be printed to black
  tft.setColor(255, 255, 255); // Sets color to white
  tft.setFont(BigFont); // Sets font to big
  tft.print("MP3 Player", 50, CENTER ); // Prints the string on the screen
  tft.print("Bluetooth", 100, CENTER ); // Prints the string on the screen
  tft.print("FM Radio", 150, CENTER ); // Prints the stringg on the screen
  
}

void drawMusicPlayerScreen() {
  // Title
  tft.setBackColor(0, 0, 0); // Sets the background color of the area where the text will be printed to black
  tft.setColor(255, 255, 255); // Sets color to white
  tft.setFont(BigFont); // Sets font to big
  tft.print("MENU", 5, 5); // Prints the string on the screen
  tft.setColor(255, 0, 0); // Sets color to red
  tft.drawLine(0, 26, 319, 26); // Draws the red line
  tft.setColor(255, 255, 255); // Sets color to white
  tft.setFont(SmallFont); // Sets font to big
  tft.print("by www.HowToMechatronics.com", CENTER, 215); // Prints the string on the screen
  // Volume Bar
  tft.setColor(255, 255, 255);
  tft.fillRect (78, 184, 78 + 150, 184 + 8);
  tft.setColor(240, 196, 30);
  tft.fillRect (78, 184, 78 + 75, 184 + 8);
  // Track Bar
  tft.setColor(255, 255, 255);
  tft.fillRect (48, 50, 48 + 224, 50 + 8);
  tft.setFont(SmallFont);
  tft.setColor(255, 255, 255);
  tft.print("0:00", 8, 48);
  tft.print("-0:00", 276, 48);
  drawPlayButton();

  if (playStatus == '2') {
    drawPauseButton();
  }
  drawPreviousButton();
  drawNextButton();
  drawVolumeDown();
  drawVolumeUp();
}

void drawMusicPlayerButton() {
  tft.drawBitmap (55, 125, 65, 64, MusicPlayerButton);
}

void drawAlarmButton() {
  tft.drawBitmap (195, 125, 65, 64, AlarmButton);
}

void drawPlayButton() {
  tft.drawBitmap (118, 79, 83, 83, ButtonPlay);
}

void drawPauseButton() {
  tft.drawBitmap (118, 79, 83, 83, ButtonPause);
}

void drawNextButton() {
  tft.drawBitmap (227, 97, 50, 50, NextButton);
}

void drawPreviousButton() {
  tft.drawBitmap (45, 97, 50, 50, PreviousButton);
}

void drawVolumeDown() {
  tft.drawBitmap (50, 177, 16, 23, VolumeDown);
}

void drawVolumeUp() {
  tft.drawBitmap (241, 175, 34, 28, VolumeUp);
}

// check for if Mp3 Player is stopped
bool checkFor_mp3IsStopped() {
  if (mp3Serial.available() > 0) {
    if (mp3.getPlaybackStatus() == 0) {
      return true;
    }
  }
  else return false;
}

// Highlights the button when pressed
void drawFrame(int x, int y, int r) {
  tft.setColor(255, 0, 0);
  tft.drawCircle (x, y, r);
  while (myTouch.dataAvailable())
    myTouch.read();
  tft.setColor(0, 0, 0);
  tft.drawCircle (x, y, r);
}

void drawRectFrame(int x1, int y1, int x2, int y2) {
  tft.setColor(255, 0, 0);
  tft.drawRoundRect (x1, y1, x2, y2);
  while (myTouch.dataAvailable())
    myTouch.read();
  tft.setColor(255, 255, 255);
  tft.drawRoundRect (x1, y1, x2, y2);
}

void drawUnderline(int x1, int y1, int x2, int y2) {
  tft.setColor(255, 0, 0);
  tft.drawLine (x1, y1, x2, y2);
  while (myTouch.dataAvailable())
    myTouch.read();
  tft.setColor(0, 0, 0);
  tft.drawLine (x1, y1, x2, y2);
}

// Sound bar
void drawVolume(int x) {
  tft.setColor(255, 255, 255);
  tft.fillRect (78 + 5 * x, 184, 78 + 150, 184 + 8);
  tft.setColor(240, 196, 30);
  tft.fillRect (78, 184, 78 + 5 * x, 184 + 8);
}

// Clears the track bar
void drawTrackBar() {
  tft.setColor(255, 255, 255);
  tft.fillRect (48, 50, 48 + 224, 50 + 8);
}

// Updates the track bar
void trackPlayTime() {
  totalTime = mp3.getTotalTrackPlaybackTime();
  delay(10);
  elapsedTime = mp3.getElapsedTrackPlaybackTime();
  delay(10);
  minutes = (int)elapsedTime / 60;
  seconds = (((float)elapsedTime / 60) - minutes) * 60;
  playback = totalTime - elapsedTime;
  minutesR = (int)playback / 60;
  secondsR = (((float)playback / 60) - minutesR) * 60;
  tft.setFont(SmallFont);
  tft.setColor(255, 255, 255);
  tft.printNumI(minutes, 8, 48);
  tft.print(":", 16, 48);
  tft.printNumI((int)seconds, 24, 48, 2, '0');
  tft.print("-", 276, 48);
  tft.printNumI(minutesR, 284, 48);
  tft.print(":", 292, 48);
  tft.printNumI((int)secondsR, 300, 48, 2, '0');
  int trackBarX = map(elapsedTime, 0, totalTime, 0, 224);
  tft.setColor(255, 0, 0);
  tft.fillRect (48, 50, 48 + trackBarX, 50 + 8);
  if (totalTime == elapsedTime) {
    mp3.nextTrack();
    delay(30);
    tft.setColor(255, 255, 255);
    tft.fillRect (48, 50, 48 + 224, 50 + 8);
  }
}

void printClock(int x, int y) {
  if ( currentClock != rtc.getTimeStr()) {
    tft.print(rtc.getTimeStr(), x, y);
    currentClock = rtc.getTimeStr();
  }
}

void drawColon() {
  tft.setColor(0, 255, 0);
  tft.fillCircle (112, 65, 4);
  tft.setColor(0, 255, 0);
  tft.fillCircle (112, 85, 4);
  tft.setColor(0, 255, 0);
  tft.fillCircle (208, 65, 4);
  tft.setColor(0, 255, 0);
  tft.fillCircle (208, 85, 4);
}

void drawHomeClock() {
  timeString = rtc.getTimeStr();
  currentHours = timeString.substring(0, 2);
  currentMinutes = timeString.substring(3, 5);
  currentSeconds = timeString.substring(6, 8);
  tft.setFont(SevenSegNumFont);
  tft.setColor(0, 255, 0);
  tft.print(currentSeconds, 224, 50);
  tft.print(currentMinutes, 128, 50);
  tft.print(currentHours, 32, 50);
  drawColon();
}
