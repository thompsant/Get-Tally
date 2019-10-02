/*
   Get Tally

   This is written and inteded to be used for the Blackmagic Design 3G-SDI Shield for Arduino.
   This script will read the incoming tally brightness information from the Front SDI output on
   a Blackmagic Design URSA camera. We are using this sketch with our URSA Mini 4K cameras in our
   studios. We connect the studio viewfinder to the output SDI of the shield.

   created 28 September 2019
   by Anthony Thompson
   modified 02 October 2019
   by Anthony Thompson
*/

// includes the Blackmagic Design SDI Control library.
#include <BMDSDIControl.h>

const int shieldAddress = 0x6E;
BMD_SDICameraControl_I2C ccu(shieldAddress);  // initializes the camera control library to class instance 'ccu'

const byte OFF = 0x00000001;
byte data = 0x0;
int ccuLength = 0;
byte ccuData[256];

void setup() {
//  Serial.begin(9600);                   // open serial port at 9600 bps
  ccu.begin();
  ccu.setOverride(false);
  
  pinMode(8, OUTPUT);                   // configures pin 8 as an output
}

void loop() {

  if ( ccu.available() ) {
    ccuLength = ccu.read(ccuData);
    data = ccuData[32];
  
    if ( data != OFF ) {
      digitalWrite(8, HIGH); }
    else {
     digitalWrite(8, LOW); }

    ccu.flushRead();
  }
//  Serial.println(ccuData[32]);
//  delay(100);
}
