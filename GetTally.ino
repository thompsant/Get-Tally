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
*/

// includes the Blackmagic Design SDI Control library.
#include <BMDSDIControl.h>

// declares a class object called 'tally' using the default I²C address
BMD_SDITallyControl_I2C tally(0x6E);

// Tally Data length is 128 bytes, so array of bytes was created
byte data[128];

// ATEM ID of the camera this module is defined here
int atemID = 4;


// standard Arduino setup function
void setup() {

  // begins tally control and does not override incoming tally
  tally.begin();
  tally.setOverride(false);

  // configures pin 8 as an output.
  pinMode(8, OUTPUT);
}

// standard Arduino looping function
void loop() {

  // tally control read function that takes in an array and fills it with the data in the ITDATA register
  tally.read(data);

  // simple logic that compares camera ATEM ID to a corresponding zero-based entry in the data array
  if ( data[atemID - 1] == 1 ) {
    digitalWrite(8, HIGH);
  } else {
    digitalWrite(8, LOW);
  }

  // wait for 33 milliseconds or just shy of 1 frame at 29.97 or 30 fps
  delay(33);
}
