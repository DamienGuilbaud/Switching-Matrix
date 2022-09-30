
#include <Wire.h>
#include <PI4IOE5V96248.h>

PI4IOE5V96248 io_exp_1; // Object for communicating with the io expander
PI4IOE5V96248 io_exp_2;
PI4IOE5V96248 io_exp_3;
PI4IOE5V96248 io_exp_4;
PI4IOE5V96248 io_exp_5;
PI4IOE5V96248 io_exp_6;
PI4IOE5V96248 io_exp_7;
PI4IOE5V96248 io_exp_8;
PI4IOE5V96248 io_exp_9;
PI4IOE5V96248 io_exp_10;
PI4IOE5V96248 io_exp_11;
PI4IOE5V96248 io_exp_12;
PI4IOE5V96248 io_exp_13;
PI4IOE5V96248 io_exp_14;
PI4IOE5V96248 io_exp_15;
PI4IOE5V96248 io_exp_16;


PI4IOE5V96248 exp_list[16] = {};

byte addies[16] = {0x10, 0x14, 0x12, 0x16, 0x11, 0x15, 0x13, 0x17, 0x50, 0x54, 0x52, 0x56, 0x51, 0x55, 0x53, 0x57};

const int ledPin =  LED_BUILTIN;

int x;
int y;
int s;
int c;

void change_switch(int x, int y, int s, int c) {


    int exp_ind = 0;
    int port_num = 0;
    int port_pin = 0;
    int mult_8 = 0;
    
      exp_ind = (3*x) + s; //exp_ind 1-48
      if (exp_ind<9) {
        port_num = 0;
      }
      if ((8<exp_ind) && (exp_ind <17)) {
        port_num = 1;
      }
      if ((16<exp_ind) && (exp_ind<25)) {
        port_num = 2;
      }
      if ((24<exp_ind) && (exp_ind<33)) {
        port_num = 3;
      }
      if ((32<exp_ind) && (exp_ind<41)) {
        port_num = 4;
      }
      if ((40<exp_ind) && (exp_ind<49)) {
        port_num = 5;
      }
      mult_8 = exp_ind/8;
      if ( (exp_ind - (8*mult_8))==0) {
        port_pin = 7;
      }
      else {
        port_pin = exp_ind - (8*mult_8) - 1;//subtract highest multiple of 8 from exp_ind 
      }
       
      if (y==17) {
        Reset_board();
      }
      else {
      exp_list[y].writePin(port_num, port_pin,c);
      }
      
}

void Reset_board(){

byte test_h[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
byte test_l[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

  io_exp_1.writeAll(test_h);
  io_exp_2.writeAll(test_h);
  io_exp_3.writeAll(test_h);
  io_exp_4.writeAll(test_h);
  
  io_exp_5.writeAll(test_h);
  io_exp_6.writeAll(test_h);
  io_exp_7.writeAll(test_h);
  io_exp_8.writeAll(test_h);

  io_exp_9.writeAll(test_h);
  io_exp_10.writeAll(test_h);
  io_exp_11.writeAll(test_h);
  io_exp_12.writeAll(test_h);

  io_exp_13.writeAll(test_h);
  io_exp_14.writeAll(test_h);
  io_exp_15.writeAll(test_h);
  io_exp_16.writeAll(test_h);
}

int counter = 100;
int list_xy[100][4] = {};

void setup() {
  Serial.begin(115200);//,SERIAL_8E2);
  Serial.setTimeout(1000);
  Wire.begin(); //Join I2C bus, set SDA and SCL pins respectively (tested on ESP32, remove pins if using another chip)
  Wire.setClock(100000); //Set speed to 400Khz, chip supports up to 1Mhz

  pinMode(LED_BUILTIN, OUTPUT);

  delay(1000); //give system chance to stabilize, likely not needed.
 

      if (!io_exp_1.begin(addies[0]))
      {
        Serial.println("Failed to init PI4IOE5V96248 :(");
        while (1); //loop forever
      }
     // Serial.println("PI4IOE5V96248 found! :)");
      
      if (!io_exp_2.begin(addies[1]))
      {
        Serial.println("Failed to init PI4IOE5V96248 :(");
        while (1); //loop forever
      }
      //Serial.println("PI4IOE5V96248 found! :)");
      
      if (!io_exp_3.begin(addies[2]))
      {
        Serial.println("Failed to init PI4IOE5V96248 :(");
        while (1); //loop forever
      }
      //Serial.println("PI4IOE5V96248 found! :)");
      
      if (!io_exp_4.begin(addies[3]))
      {
        Serial.println("Failed to init PI4IOE5V96248 :(");
        while (1); //loop forever
      }
      //Serial.println("PI4IOE5V96248 found! :)");

      if (!io_exp_5.begin(addies[4]))
      {
        Serial.println("Failed to init PI4IOE5V96248 :(");
        while (1); //loop forever
      }
      //Serial.println("PI4IOE5V96248 found! :)");
      
      if (!io_exp_6.begin(addies[5]))
      {
        Serial.println("Failed to init PI4IOE5V96248 :(");
        while (1); //loop forever
      }
      //Serial.println("PI4IOE5V96248 found! :)");

      if (!io_exp_7.begin(addies[6]))
      {
        Serial.println("Failed to init PI4IOE5V96248 :(");
        while (1); //loop forever
      }
      //Serial.println("PI4IOE5V96248 found! :)");
      
      if (!io_exp_8.begin(addies[7]))
      {
        Serial.println("Failed to init PI4IOE5V96248 :(");
        while (1); //loop forever
      }
      //Serial.println("PI4IOE5V96248 found! :)");

      if (!io_exp_9.begin(addies[8]))
      {
        Serial.println("Failed to init PI4IOE5V96248 :(");
        while (1); //loop forever
      }
      //Serial.println("PI4IOE5V96248 found! :)");
      
      if (!io_exp_10.begin(addies[9]))
      {
        Serial.println("Failed to init PI4IOE5V96248 :(");
        while (1); //loop forever
      }
      //Serial.println("PI4IOE5V96248 found! :)");

      if (!io_exp_11.begin(addies[10]))
      {
        Serial.println("Failed to init PI4IOE5V96248 :(");
        while (1); //loop forever
      }
     // Serial.println("PI4IOE5V96248 found! :)");
      
      if (!io_exp_12.begin(addies[11]))
      {
        Serial.println("Failed to init PI4IOE5V96248 :(");
        while (1); //loop forever
      }
      //Serial.println("PI4IOE5V96248 found! :)");

      if (!io_exp_13.begin(addies[12]))
      {
        Serial.println("Failed to init PI4IOE5V96248 :(");
        while (1); //loop forever
      }
      //Serial.println("PI4IOE5V96248 found! :)");
      
      if (!io_exp_14.begin(addies[13]))
      {
        Serial.println("Failed to init PI4IOE5V96248 :(");
        while (1); //loop forever
      }
      //Serial.println("PI4IOE5V96248 found! :)");

      if (!io_exp_15.begin(addies[14]))
      {
        Serial.println("Failed to init PI4IOE5V96248 :(");
        while (1); //loop forever
      }
      //Serial.println("PI4IOE5V96248 found! :)");
      
      if (!io_exp_16.begin(addies[15]))
      {
        Serial.println("Failed to init PI4IOE5V96248 :(");
        while (1); //loop forever
      }
      //Serial.println("PI4IOE5V96248 found! :)");

      pinMode(ledPin, OUTPUT);

exp_list[0]=io_exp_1;
exp_list[1]=io_exp_2;
exp_list[2]=io_exp_3;
exp_list[3]=io_exp_4;
exp_list[4]=io_exp_5;
exp_list[5]=io_exp_6;
exp_list[6]=io_exp_7;
exp_list[7]=io_exp_8;
exp_list[8]=io_exp_9;
exp_list[9]=io_exp_10;
exp_list[10]=io_exp_11;
exp_list[11]=io_exp_12;
exp_list[12]=io_exp_13;
exp_list[13]=io_exp_14;
exp_list[14]=io_exp_15;
exp_list[15]=io_exp_16;


}


void loop() {

  while (Serial.available()==0) {}
  counter=Serial.parseInt();
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(LED_BUILTIN, HIGH);
 if (Serial.read() == '\n') {
   for (int i = 0; i < counter; i++) { 
    while (Serial.available()==0) {}
    x=Serial.parseInt();
    y=Serial.parseInt();
    s=Serial.parseInt();
    c=Serial.parseInt();
    if (Serial.read() == '\n') {
    // while (Serial.read() != '\n') {}
    list_xy[i][0] = x;
    list_xy[i][1] = y;
    list_xy[i][2] = s;
    list_xy[i][3] = c;
    }
   }
 }

for (int i = 0; i < counter; i++) {
    x = list_xy[i][0];
    y = list_xy[i][1];
    s = list_xy[i][2];
    c = list_xy[i][3];
    change_switch(x, y, s, c);
    delay(10); //milliseconds //delay = 2 --> 500Hz
    //delayMicroseconds(333);
}


}

// citation for PI4IOE5V96248.h
//By: Ilia Baranov
// BSD 3-Clause License

// Copyright (c) 2021, Blueprint Foundry
// All rights reserved.

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:

// 1. Redistributions of source code must retain the above copyright notice, this
//    list of conditions and the following disclaimer.

// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.

// 3. Neither the name of the copyright holder nor the names of its
//    contributors may be used to endorse or promote products derived from
//    this software without specific prior written permission.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
