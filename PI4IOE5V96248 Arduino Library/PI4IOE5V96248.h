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


#include "Arduino.h"

#ifndef PI4IOE5V96248_H
#define PI4IOE5V96248_H

class PI4IOE5V96248
{
  private:  // These private functions are not available to Arduino sketches.
    byte deviceAddress; // I2C Address of PI4IOE5V96248
    byte value[6]; // tracking pin values for chip, expressed as hex values per port (6 ports total)
    byte read_io[6];

  public:  // These public functions are available to Arduino sketches.
    PI4IOE5V96248();
    byte begin(byte address = 0x23); // Example PI4IOE5V96248 I2C address, depends on setting for AD0, AD1, AD2
    void writePin(byte port, byte pin, byte highLow);
    void writePort(byte port, byte portValue);
    void writeAll(byte highLow[6]);
    byte readPin(byte port, byte pin);
    byte readPort(byte port);
    byte * readAll();
    byte * returnValue();

}; //PI4IOE5V96248 class
#endif  // PI4IOE5V96248_H
