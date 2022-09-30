/*
  PI4IOE5V96248.cpp
  PI4IOE5V96248 I2C IO expander Source File
  By: Ilia Baranov
  BLueprint Foundry
  Date: March 5th, 2021
  License: BSD 3 Clause
  
  Copyright (c) 2021, Blueprint Foundry
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

  1. Redistributions of source code must retain the above copyright notice, this
     list of conditions and the following disclaimer.

  2. Redistributions in binary form must reproduce the above copyright notice,
     this list of conditions and the following disclaimer in the documentation
     and/or other materials provided with the distribution.

  3. Neither the name of the copyright holder nor the names of its
     contributors may be used to endorse or promote products derived from
     this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/


#include <Wire.h>
#include "Arduino.h"
#include "PI4IOE5V96248.h"

//init function, fills port value array with 0xFF
PI4IOE5V96248::PI4IOE5V96248()
{
  value[0] = 0xFF; //fill state array with HIGH on init, as this is state of chip on power on
  memcpy( ((char*)value) + sizeof(value[0]), value, sizeof(value) - sizeof(value[0]));
}

//communication check, simply checks if chip responds with Ack
byte PI4IOE5V96248::begin(byte address)
{
  // Store the received parameter into member variables
  deviceAddress =  address;

  Wire.beginTransmission(address);
  if (!Wire.endTransmission()) { // default value to verify communication, a 0 means we got an ack
    return 1; //it worked
  }
  return 0;
}

//sets a single pin on the chip, requires port and pin number, and value to set
void PI4IOE5V96248::writePin(byte port, byte pin, byte highLow)
{
  //Set sign value in array and send the port hex value
  if (highLow == HIGH) value[port] |= 1UL << pin ; //set pin (set to 1 or HIGH)
  else value[port] &= ~(1UL << pin) ; //clear pin (set to 0 or LOW)
  writePort(port, value[port]);
}

//Sets an entire port at once, usually the fastest way to set values for this chip
//Note: Port outputs are changed as soon as write is done for each port.
void PI4IOE5V96248::writePort(byte port, byte portValue)
{
  //Set hex value in array and send the array
  value[port] = portValue;
  Wire.beginTransmission(deviceAddress);
  for (int i = 0; i <= port; i++) { //only write up to port number, no benefit writing more
    Wire.write(value[i]);
  }
  Wire.endTransmission();
}

//sets all pins/ports on the chip
void PI4IOE5V96248::writeAll(byte highLow[6])
{
  Wire.beginTransmission(deviceAddress);
  for (int i = 0; i < 6; i++) {
    value[i] = highLow[i]; //copy to private variable for tracking
    Wire.write(value[i]); //write to chip
  }
  Wire.endTransmission();
}

// reads pin value, and returns pin read value
byte PI4IOE5V96248::readPin(byte port, byte pin) {
  return bitRead(readPort(port), pin);
}

//Sets a specific port, reads values
byte PI4IOE5V96248::readPort(byte port) {
  byte * retVal = readAll();
  return retVal[port];
}

// read all values
byte * PI4IOE5V96248::readAll() {
  byte count = 0;
  Wire.requestFrom(deviceAddress, 6);
  while (Wire.available())
  {
    read_io[count] = Wire.read();
    count++;
  }
  Wire.endTransmission();
  return read_io;
}

//returns private value variable, which tracks what the chip is set to.
//Does not actually read from the chip, faster than doing a readAll
byte * PI4IOE5V96248::returnValue() {
  return value;
}
