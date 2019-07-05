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

BMD_SDITallyControl_I2C tally(0x6E);  // declares Tally Control object using the default I²C address
byte tallyData[128];
int tallyLength = 0;                    // Tally Data length is 128 bytes
int atemID = 7;                         // ATEM ID of the camera

void SOS() {                            // outputs SOS pattern on LED
  digitalWrite(8, LOW)
  digitalWrite(8, HIGH); delay(250); digitalWrite(8, LOW); delay(100);
  digitalWrite(8, HIGH); delay(250); digitalWrite(8, LOW); delay(100);
  digitalWrite(8, HIGH); delay(250); digitalWrite(8, LOW); delay(100);
  digitalWrite(8, HIGH); delay(1000); digitalWrite(8, LOW); delay(100);
  digitalWrite(8, HIGH); delay(1000); digitalWrite(8, LOW); delay(100);
  digitalWrite(8, HIGH); delay(1000); digitalWrite(8, LOW); delay(100);
  digitalWrite(8, HIGH); delay(250); digitalWrite(8, LOW); delay(100);
  digitalWrite(8, HIGH); delay(250); digitalWrite(8, LOW); delay(100);
  digitalWrite(8, HIGH); delay(250); digitalWrite(8, LOW);
  delay(2000);
}

void RunTally() {                       // simple logic that compares camera ATEM ID to entry in the data array
  if ( tallyData[atemID - 1] == 1 ) {
    digitalWrite(8, HIGH); }
  else {
    digitalWrite(8, LOW); }
}

void setup() {
  tally.begin();                        // begins tally control
  tally.setOverride(false);             // does not override incoming tally
  pinMode(8, OUTPUT);                   // configures pin 8 as an output
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  tallyLength = tally.read(tallyData);  // takes in an array and fills it with the data
                                        // in the ITDATA register and returns data length
  if ( tallyLength == sizeof(tallyData) && tallyLength == 128 ) {
    RunTally();
  } else {
    SOS()
  }
  
  delay(33);                            // wait for 33 milliseconds or just shy of 1 frame at 29.97 or 30 fps
}