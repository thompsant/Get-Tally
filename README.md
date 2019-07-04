# Get Tally
Get Tally is a simple Arduino Sketch written for an Arduino using the Blackmagic Design 3G-SDI Shield for Arduino.

This Sketch reads the embedded tally information on the SDI input of the BMD shield and performs a simple comparison based on the value set as the ATEM ID for that camera.

This script doesn't override the incoming tally, so that tally information is passed on to the camera if one is connected to the shield's SDI output.

This script was designed for a pretty specific purpose. We designed the script for use with an Arduino and BMD shield in an enclosure with an LED. This is to provide our BMD URSA Minis with a functional "on board" tally that we can use to provide input to our prompter hood optosensors. This could easily be adapted to various different applications.

### Basic Functionality
This Sketch uses Blackmagic Design's Tally Control class. Specifically, Tally Control's read function. This function is documented, but (IMHO) not very well documented.

The basics of this function is you feed it an array of bytes, it pulls the data from the tally data register that is refreshed every video frame, and updates the input array with that data. You can then iterate over the array to get the tally information. The index (0) position of the array corresponds with Camera 1 and goes up from there.

As written, this Sketch requires you to change the variable ```atemID``` to match the ATEM ID of the camera to which that Arduino is connected. This could be easily modified to handle multiple tally inputs on a single unit as all tally information for all cameras is sent down the SDI signal.
