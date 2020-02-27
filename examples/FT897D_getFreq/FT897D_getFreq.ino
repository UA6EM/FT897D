/*
  
  ------------------

  FT897D_getFreq

    Radio CAT port GND -> Arduino GND
    Radio CAT port TX  -> Arduino pin 2
    Radio CAT port RX  -> Arduino pin 3

 
*/

#include <SoftwareSerial.h>
#include "FT897D.h"     // the file FT897D.h has a lot of documentation which I've added to make using the library easier

FT897D radio;           // define "radio" so that we may pass CAT commands
                  
void setup() {

/*---- Working on a way to allow easier user input of I/O pins for software serial emulation
  ---- Right now, it is necessary to edit the FT897D.cpp file and to edit the line which states:
  ---- extern SoftwareSerial rigCat(3,2); // rx,tx
  ---- change the rx & tx pins to values which suit your application and save the FT897D.cpp file
*/

//  SoftwareSerial userSerial(3,2);  
//  rig.setSerial(userSerial);
  Serial.begin(9600);
  radio.begin(4800);    // as with Serial.begin(9600); we wish to start the software serial port
                        // so that we may control a radio via CAT commands
 Serial.println("In WORK");                       
}

void loop() {         
  int dly = 1;            // delay for x milliseconds between commands
/* *
  radio.lock(true);         // lock the radio's controls
  delay(dly);
  radio.lock(false);        // unlock the radio's controls
  delay(dly);
  radio.setMode("pkt");     // set mode to PKT (note these mode names are NOT case sensitive!)
  delay(dly);
  radio.setMode("AM");      // set mode to AM
  delay(dly);
  radio.setMode("USB");     // set mode to USB
  delay(dly);
  radio.setMode("LSB");     // set mode to LSB
  delay(dly);
  radio.setMode("CW");      // set mode to CW
  delay(dly);
  radio.setMode("CWR");     // set mode to CW-R
  delay(dly);
  radio.setMode("DIG");     // set mode to DIG
  delay(dly);
  radio.setMode("FMN");     // set mode to FM-N
  delay(dly);
  radio.setMode("FM");      // set mode to FM
  delay(dly);

  radio.setFreq(1407000);  // set VFO frequency to xx
  delay(dly);
  
  // perform a frequency sweep
  for (long freq=0; freq < 3; freq++){
    radio.setFreq(14400000 + freq * 5000);
  }
  delay(dly);
  for (long freq=0; freq < 3; freq++){
    radio.setFreq(14800000 - freq * 5000);
  }
    
  radio.clar(true);        // enable clarifier 
  delay(dly);
  radio.clar(false);       // disable clarifier 
  delay(dly);
  radio.split(true);       // enable split operation
  delay(dly);
  radio.split(false);      // disable split operation
  delay(dly);
  radio.rptrOffset("+");   // set positive repeater offset
  delay(dly);
  radio.rptrOffset("-");   // set negative repeater offset
  delay(dly);
  radio.rptrOffsetFreq(600);  // set an offset frequency in kHz
  delay(dly);  
  radio.rptrOffset("s");   // enable simplex mode
  delay(dly);
  radio.squelch("TSQ");    // set the radio to CTCSS on RX & TX
  delay(dly);
  radio.squelchFreq(1000,"C");  // set CTCSS tone 100.0Hz (TX + RX) - note the C = CTCSS tone
  delay(dly);
  radio.squelch("DCS");    // set the radio to DCS on RX & TX
  delay(dly);
  radio.squelchFreq(371,"D");  // set DCS code 0371 (TX + RX) - note the D = DCS code
  delay(dly);
  radio.squelch("OFF");    // clear CTCSS & DCS squelch
  delay(dly);
  /* */
    Serial.print("FREQ = "); 
    unsigned long fff = radio.getFreqMode();
 // Serial.println(radio.getFreqMode());
    Serial.println(fff);
     byte mmm = 0;
     mmm = radio.getMode();
    Serial.print("MODE = "); 
    Serial.println(mmm);
    delay(100);
    radio.setMode("LSB");     // set mode to LSB
}
