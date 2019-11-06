# Get Tally
Get Tally is a simple Arduino Sketch written for an Arduino using the Blackmagic Design 3G-SDI Shield for Arduino.

This Sketch reads the tally brightness information on the SDI input of the BMD shield and lights up an external LED if that brightness data is anything other than OFF.

This script doesn't override the incoming tally, so that tally information is passed on to a viewfinder if one is connected to the shield's SDI output.

This script was designed for a pretty specific purpose. We designed the script for use with an Arduino and BMD shield in an enclosure with an LED. This is to provide our BMD URSA Minis with a functional "on board" tally that we can use to provide input to our prompter hood optosensors. This could easily be adapted to various different applications.
