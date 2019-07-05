/*
   Get Tally

   Turns on an LED if Program tally for the chosen camera is detected.

   This is written and inteded to be used for the Blackmagic Design 3G-SDI Shield for Arduino.
   This script will read the incoming tally information via the SDI Input on the SDI Shield and
   compare the Tally data array to the set ATEM ID in the script. If the Tally data shows Program
   tally enabled for that ATEM ID, it will turn an LED on that is connected to Digital Pin 8.

   This was created for a dedicated LED box at each camera to provide the URSA Mini 4Ks in our studios
   an "onboard" tally light for use with Autoscript prompter optosensors. Tally Override is not enabled
   so tally will be passed through the shield to the BMD camera.

   created 03 July 2019
   by Anthony Thompson
   modified 04 July 2019
   by Anthony Thompson
   modified 05 July 2019
   by Anthony Thompson
*/

// includes the Blackmagic Design SDI Control library.
#include <BMDSDIControl.h>

BMD_SDITallyControl_I2C tally(0x6E);    // declares Tally Control object using the default I²C address
byte tallyData[128];                    // Tally Data length is 128 bytes
int tallyLength = 0;                    // length of data read from register
int atemID = 4;                         // ATEM ID of the camera


void SOS() {                            // outputs SOS pattern to LED
  digitalWrite(8, LOW);
  digitalWrite(8, HIGH); delay(250); digitalWrite(8, LOW); delay(100);
  digitalWrite(8, HIGH); delay(250); digitalWrite(8, LOW); delay(100);
  digitalWrite(8, HIGH); delay(250); digitalWrite(8, LOW); delay(100);
  digitalWrite(8, HIGH); delay(500); digitalWrite(8, LOW); delay(100);
  digitalWrite(8, HIGH); delay(500); digitalWrite(8, LOW); delay(100);
  digitalWrite(8, HIGH); delay(500); digitalWrite(8, LOW); delay(100);
  digitalWrite(8, HIGH); delay(250); digitalWrite(8, LOW); delay(100);
  digitalWrite(8, HIGH); delay(250); digitalWrite(8, LOW); delay(100);
  digitalWrite(8, HIGH); delay(250); digitalWrite(8, LOW);
  delay(1000);
}

void RunTally() {                       // simple logic that compares camera ATEM ID to entry in the data array
  if ( tallyData[atemID - 1] == 1 ) {
    digitalWrite(8, HIGH); }
  else {
    digitalWrite(8, LOW); }
}

void Booting() {                        // rapidly blink LED if tallyLength is between 0 - 128
    digitalWrite(8, HIGH);
    delay(30);
    digitalWrite(8, LOW);
  }

void setup() {
  tally.begin();                        // begins tally control
  tally.setOverride(false);             // does not override incoming tally
  pinMode(8, OUTPUT);                   // configures pin 8 as an output
}

void loop() {
  tallyLength = tally.read(tallyData);  // reads tally data from ITDATA register
  

  if ( tallyLength >= 0 && tallyLength < sizeof(tallyData) ) {
    Booting();                          // looks to see if tally data is valid
  } else if ( tallyLength == sizeof(tallyData) ) {
    RunTally();                         // run if normal tally data is received
  } else {
    SOS();                              // something else is wrong, send help
  }
  
  delay(30);                            // wait for a little less than one frame at 30 fps
}
