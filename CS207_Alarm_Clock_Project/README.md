# Stargate Alarm Clock [V3]
===================================

This is an alarm clock project made with a a help of MCUfriend display, RTC clock and a MP3 player. This project is exploring arduino poteantail to the max. It is also futuring mercury tilt switch as a means of controling alarm and a secondary a pause button in at the mp3 player screen.

![alt text][20171126_180822]

[20171126_180822]: https://github.com/yushchyr/CS207/blob/master/CS207_Alarm_Clock_Project/Photos/20171126_180822.jpg "My Home screen"

Repository Contents
============

* **/Garbage**  - Here is where my old files are saved.
* **/Images and Bitmap files** - This is where the BPM amd .C 
* **/Images and Bitmam foles/Backgroud** - Files with a BMP files for the scren backround.
for the alarm clock!
**/Librarys** - Here's where the software for your device goes.
* **/Photos** - here where you can find some photos of the project
* **/LICENSE** - The license file.
* **/README.md** - The file you're reading now! :-D

Requirements and Materials
============

Librarys and devices used.

Dependencies:

* Adafruit-GFX - Adafruit general graphical library
* TFTLCD - Adafruit TFT library. They being used be MCUFRIEND
* Touch-screen - Touchsecreen read library
* MCUFRIEND_kbv - hardware specific library for this TFT
* BY8001 - Mp3 Player
* DS3231 - RTC alarm cloack
* SDfat - Faster library for the native mega pins 50, 52, 51
* SD - using Sofware Serial if uncomente a line in this library with pins 11, 12, 13 on Arduino mega. Which is twice as slow.


Bill of Materials:
* Arduino Mega 2560 
* McuFriend TFT touchscreen 480 x 320
* X 2 - 0.8W Speakers; 
* X SD memory card. 
* RTC 32231 - Real time clock module with a temerature sensor SCL, SDAT pins on arduino mega. Pin 20, 21.
* BY8001 - Is a MP3 player originally choosed by howtomechatronics project. pin 13, 12.
* Tilt Switch pin 11.
* One giant breadboard or a soldering iron.
* Few dozen Jumper cables.

Build Instructions
==================

1) Band pins 11, 12, 13 at 90 degrees to allow TFT slide in place leaving them availeble for a jumper cables to pins 50, 52, 51 on Arduino Mega 2560

2) Install both SD Cards
One should contain Background folder (Use short name 6,5 char Win+R enter dir/X to get a short name for your file) Anatherway arduino will not read it proerly. You may want to change the name of abackround folder to a 5 letter and arduoino code for SD file access accordingly or try copig folder with all attributes, anater solution is to use "" as a root indicator.)

Second SD card is for MP3 payer. Just poot your files into root

I soldered MP3 player Jumper cabeles amd a tilt switch to the bottom of Arduino Mega to safe on space where there is already TFT screen SD card cabeles obscuring pins enetrence.

Firmware Installation
=====================
Instalation of Librarys come down to CTRL+C CTRL+V from repository to your Documents/Arduino/Librarys folder.
It is a good idea to poot your MP3 into a power stend by mode
Check the library.  I did not do that as it is at this moment.
Id id implement random boot sector for the EEPROM selection but it is comented out in two places. For debagging. random() and seed() for the starting point integer in a array address.

To install:
Open arduino and click upload afetr changing Port settings :-).

```


Usage
=====
Set time for RTC from the setup.
Thats first. Time and date as well as two alarms and the day of the week. Thats to be done only once.
If all the connection done right you should see a main screen

Vido Link (Copy included in a repositary/Photos) 
* **Link to my youtube video**
https://www.youtube.com/watch?v=vo4xf93aJQE&t=23s
I did some minor debugging after shotting this video. 
So it is looking a little better now.

Team
=====
The build team consists of: 
Roman Yushchyk

Credits
=======
References: 
I found this project that inspire me to try my own modification. I took from here some hardware listenning and a basic idea of screen controll layeout. There rest is history and a lot of spend time. Because my product is nothing but different in its core. I diviated ealy from the layout of the original project and it became more like an art effort to fit image properly to the screen. 

 * **Link** http://howtomechatronics.com/projects/arduino-touch-screen-music-player-alarm-clock-project/
=======
# Repository Title [version number]
===================================

This is an alarm clock project made witha a help of MCUfriend display, RTC clock and a MP3 player. This project is exploring arduino poteantail to the max. It is also futuring mercury tilt switch as a means of controling alarm and a psecondary a pause button in at the mp3 player screen.
![alt text][20171126_180822]

[20171126_180822]: https://github.com/yushchyr/CS207/blob/master/CS207_Alarm_Clock_Project/Photos/20171126_180822.jpg "My Home screen"

Repository Contents
============

* **/Garbage**  - Here is where my old files are saved.
* **/Images and Bitmap files** - This is where the BPM amd .C 
* **/Images and Bitmam foles/Backgroud** - Files with a BMP files for the scren backround.
for the alarm clock!
**/Librarys** - Here's where the software for your device goes.
* **/Photos** - here where you can find some photos of the project
* **/LICENSE** - The license file.
* **/README.md** - The file you're reading now! :-D

Requirements and Materials
============

Librarys and devices used.

Dependencies:

* Adafruit-GFX - Adafruit general graphical library
* TFTLCD - Adafruit TFT library. They being used be MCUFRIEND
* Touch-screen - Touchsecreen read library
* MCUFRIEND_kbv - hardware specific library for this TFT
* BY8001 - Mp3 Player
* DS3231 - RTC alarm cloack
* SDfat - Faster library for the native mega pins 50, 52, 51
* SD - using Sofware Serial if uncomente a line in this library with pins 11, 12, 13 on Arduino mega. Which is twice as slow.


Bill of Materials:
* Arduino Mega 2560 
* McuFriend TFT touchscreen 480 x 320
* X 2 - 0.8W Speakers; 
* X SD memory card. 
* RTC 32231 - Real time clock module with a temerature sensor SCL, SDAT pins on arduino mega. Pin 20, 21.
* BY8001 - Is a MP3 player originally choosed by howtomechatronics project. pin 13, 12.
* Tilt Switch pin 11.
* One giant breadboard or a soldering iron.
* Few dozen Jumper cables.

Build Instructions
==================

1) Band pins 11, 12, 13 at 90 degrees to allow TFT slide in place leaving them availeble for a jumper cables to pins 50, 52, 51 on Arduino Mega 2560

2) Install both SD Cards
One should contain Background folder (Use short name 6,5 char Win+R enter dir/X to get a short name for your file) Anatherway arduino will not read it proerly. You may want to change the name of abackround folder to a 5 letter and arduoino code for SD file access accordingly or try copig folder with all attributes, anater solution is to use "" as a root indicator.)

Second SD card is for MP3 payer. Just poot your files into root

I soldered MP3 player Jumper cabeles amd a tilt switch to the bottom of Arduino Mega to safe on space where there is already TFT screen SD card cabeles obscuring pins enetrence.

Firmware Installation
=====================
Instalation of Librarys come down to CTRL+C CTRL+V from repository to your Documents/Arduino/Librarys folder.
It is a good idea to poot your MP3 into a power stend by mode
Check the library.  I did not do that as it is at this moment.
Id id implement random boot sector for the EEPROM selection but it is comented out in two places. For debagging. random() and seed() for the starting point integer in a array address.

To install:
Open arduino and click upload afetr changing Port settings :-).

```


Usage
=====
Set time for RTC from the setup.
Thats first. Time and date as well as two alarms and the day of the week. Thats to be done only once.
If all the connection done right you should see a main screen

Vido Link (Copy included in a repositary/Photos) 
* **Link to my youtube video**
https://www.youtube.com/watch?v=vo4xf93aJQE&t=23s
I did some minor debugging after shotting this video. 
So it is looking a little better now.

Team
=====
The build team consists of: 
Roman Yushchyk

Credits
=======
References: 
I found this project that inspire me to try my own modification. I took from here some hardware listenning and a basic idea of screen controll layeout. There rest is history and a lot of spend time. Because my product is nothing but different in its core. I diviated ealy from the layout of the original project and it became more like an art effort to fit image properly to the screen. 

 * **Link** http://howtomechatronics.com/projects/arduino-touch-screen-music-player-alarm-clock-project/
>>>>>>> 553f17018df2402dc00ffc75c88c9876a5562c55
