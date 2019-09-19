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
   modified 21 August 2019
   by Anthony Thompson
*/

// includes the Blackmagic Design SDI Control library.
#include <BMDSDIControl.h>

const int shieldAddress = 0x6E;
BMD_SDITallyControl_I2C tally(shieldAddress);    // declares Tally Control object using the default I²C address
BMD_SDICameraControl_I2C ccu(shieldAddress);
byte tallyData[128];                    // Tally Data length is 128 bytes
int tallyLength = 0;                    // length of data read from register
int atemID = 6;                         // ATEM ID of the camera

void setup() {
//  Serial.begin(9600);                   // open serial port at 9600 bps
  tally.begin();                        // begins tally control
  ccu.begin();
  tally.setOverride(false);             // does not override incoming tally
  ccu.setOverride(false);
  pinMode(8, OUTPUT);                   // configures pin 8 as an output
}

void loop() {
  tallyLength = tally.read(tallyData);  // reads tally data from ITDATA register

  if ( tallyData[atemID - 1] == 1 ) {
    digitalWrite(8, HIGH); }
  else {
    digitalWrite(8, LOW); }

/*  for (int i = 0; i < sizeof(tallyData); i++) {
   Serial.print(tallyData[i]); 
  }
  Serial.print("\n");*/

  delay(33);                            // wait for a little less than one frame at 30 fps
}
