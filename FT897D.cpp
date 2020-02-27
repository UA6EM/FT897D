/*
  FT897D.cpp	Arduino library for controlling a Yaesu FT857D/FT897D
			radio via CAT commands.
 
 Version:  0.1
 Created:  2012.08.16
Released:  2012.08.17
  Author:  James Buck, VE3BUX
     Web:  http://www.ve3bux.com
	 
	 Version:  0.2 (MODYFI in FT897D)
 Created:  2020.02.26
Released:  2020.02.26
  Author:  Victor UA6EM (LN14AE)
     Web:  http://www.ua6em.ru
	 

*/

#include <Arduino.h>
#include <SoftwareSerial.h>
#include "FT897D.h"

// define software serial IO pins here:
extern SoftwareSerial rigCat(2,3); // rx,tx

#define dlyTime 5	// delay (in ms) after serial writes

FT897D::FT897D(){ }	// nothing to do when first instanced

// Setup software serial with user defined input
// from the Arduino sketch (function, though very slow)
void FT897D::setSerial(SoftwareSerial portInfo) {
  rigCat = portInfo;
}

// similar to Serial.begin(baud); command
void FT897D::begin(int baud) {
  rigCat.begin(baud);
}

// lock or unlock the radio
void FT897D::lock(boolean toggle) {
	if (toggle == true) singleCmd(CAT_LOCK_ON);
	if (toggle == false) singleCmd(CAT_LOCK_OFF);
}

// set or release the virtual PTT button
void FT897D::PTT(boolean toggle) {
	if (toggle == true) singleCmd(CAT_PTT_ON);
	if (toggle == false) singleCmd(CAT_PTT_OFF);
}

// set radio frequency directly (as a long integer)
void FT897D::setFreq(long freq) {
	byte rigFreq[5] = {0x00,0x00,0x00,0x00,0x00};
rigFreq[4] = CAT_FREQ_SET; // command byte

	unsigned char tempWord[4];
	converted = to_bcd_be(tempWord, freq, 8);

	for (byte i=0; i<4; i++){
		rigFreq[i] = converted[i];
	}

sendCmd(rigFreq,5);
	getByte();
}

// set radio mode using human friendly terms (ie. USB)
void FT897D::setMode(char * mode) {
	byte rigMode[5] = {0x00,0x00,0x00,0x00,0x00};
rigMode[0] = CAT_MODE_USB; // default to USB mode
rigMode[4] = CAT_MODE_SET; // command byte

if (strcasecmp(mode, "LSB") == 0) rigMode[0] = CAT_MODE_LSB;
if (strcasecmp(mode, "USB") == 0) rigMode[0] = CAT_MODE_USB;
if (strcasecmp(mode, "CW") == 0) rigMode[0] = CAT_MODE_CW;
if (strcasecmp(mode, "CWR") == 0) rigMode[0] = CAT_MODE_CWR;
if (strcasecmp(mode, "AM") == 0) rigMode[0] = CAT_MODE_AM;
if (strcasecmp(mode, "FM") == 0) rigMode[0] = CAT_MODE_FM;
if (strcasecmp(mode, "DIG") == 0) rigMode[0] = CAT_MODE_DIG;
if (strcasecmp(mode, "PKT") == 0) rigMode[0] = CAT_MODE_PKT;
if (strcasecmp(mode, "FMN") == 0) rigMode[0] = CAT_MODE_FMN;

sendCmd(rigMode,5);
	getByte();
}

// turn the clarifier on or off
void FT897D::clar(boolean toggle) {
	if (toggle == true) singleCmd(CAT_CLAR_ON);
	if (toggle == false) singleCmd(CAT_CLAR_OFF);
}

// GPL RX3QFN
// set the clarifier frequency
void FT897D::clarFreq(long freq) {
	// will come back to this later
	byte clarOfst[5] = {0x00,0x00,0x00,0x00,0x00};
    if (freq >= 0 ) clarOfst[0] = 0x00;//offset > 0
	if (freq < 0 ) clarOfst[0] = 0x01; // offset < 0
	clarOfst[1] = 0x00;//default
	clarOfst[4] = CAT_CLAR_SET;//command byte

unsigned char tempWord[2];
converted = to_bcd_be(tempWord, abs(freq), 4);

for (byte i=0; i<2; i++){
clarOfst[i+2] = converted[i];
}

sendCmd(clarOfst,5);
getByte();
}

// switch between VFO A and VFO B
void FT897D::switchVFO() {
	singleCmd(CAT_VFO_AB);
}

// turn split operation on or off
void FT897D::split(boolean toggle) {
	if (toggle == true) singleCmd(CAT_SPLIT_ON);
	if (toggle == false) singleCmd(CAT_SPLIT_OFF);
}

// control repeater offset direction
void FT897D::rptrOffset(char * ofst) {
	byte rigOfst[5] = {0x00,0x00,0x00,0x00,0x00};
	rigOfst[0] = CAT_RPTR_OFFSET_S; // default to simplex
	rigOfst[4] = CAT_RPTR_OFFSET_CMD; // command byte

if (strcmp(ofst, "-") == 0) rigOfst[0] = CAT_RPTR_OFFSET_N;
if (strcmp(ofst, "+") == 0) rigOfst[0] = CAT_RPTR_OFFSET_P;
if (strcmp(ofst, "s") == 0) rigOfst[0] = CAT_RPTR_OFFSET_S;

sendCmd(rigOfst,5);
	getByte();
}

void FT897D::rptrOffsetFreq(long freq) {
	byte offsetFreq[5] = {0x00,0x00,0x00,0x00,0x00};
	offsetFreq[4] = CAT_RPTR_FREQ_SET; // command byte

freq = (freq * 100); // convert the incoming value to kHz

	unsigned char tempWord[4];
	converted = to_bcd_be(tempWord, freq, 8);

	for (byte i=0; i<4; i++){
		offsetFreq[i] = converted[i];
	}

	sendCmd(offsetFreq,5);
	getByte();
}

// enable or disable various CTCSS and DCS squelch options
void FT897D::squelch(char * mode) {
	byte rigSql[5] = {0x00,0x00,0x00,0x00,0x00};
	rigSql[0] = CAT_MODE_USB; // default to USB mode
	rigSql[4] = CAT_SQL_CMD; // command byte

if (strcasecmp(mode,"DCS")==0) rigSql[0]= CAT_SQL_DCS;
if (strcasecmp(mode,"DDC")==0) rigSql[0]= CAT_SQL_DCS_DECD;
if (strcasecmp(mode,"DEN")==0) rigSql[0]= CAT_SQL_DCS_ENCD;
if (strcasecmp(mode,"TSQ")==0) rigSql[0]= CAT_SQL_CTCSS;
if (strcasecmp(mode,"TDC")==0) rigSql[0]=CAT_SQL_CTCSS_DECD;
if (strcasecmp(mode,"TEN")==0) rigSql[0]=CAT_SQL_CTCSS_ENCD;
if (strcasecmp(mode,"OFF")==0) rigSql[0]= CAT_SQL_OFF;

	sendCmd(rigSql,5);
	getByte();
}

void FT897D::squelchFreq(unsigned int freq, char * sqlType) {
	byte rigSqlFreq[5] = {0x00,0x00,0x00,0x00,0x00};
if (strcasecmp(sqlType,"C")==0) rigSqlFreq[4] = CAT_SQL_CTCSS_SET;
if (strcasecmp(sqlType,"D")==0) rigSqlFreq[4] = CAT_SQL_DCS_SET;
	
	byte freq_bcd[2];
	to_bcd_be(freq_bcd, (long)  freq, 4);

	for (byte i=0; i<4; i++){
		rigSqlFreq[i] = freq_bcd[i];
	}
	sendCmd(rigSqlFreq,5);
	getByte();
}

byte FT897D::getMode() {
	unsigned long l = getFreqMode();
	return mode;
}

// get the frequency and the current mode
// if called as getFreqMode() return only the frequency
unsigned long FT897D::getFreqMode() {
	byte rigGetFreq[5] = {0x00,0x00,0x00,0x00,0x00};
	rigGetFreq[4] = CAT_RX_FREQ_CMD; // command byte
	byte chars[4];
	long timeout = millis();
	long elapsed = 0;

	rigCat.flush();	// clear the RX buffer which helps prevent
				// any crap data from making it through

	sendCmd(rigGetFreq, 5);
	
	while (rigCat.available() < 5 && elapsed < 2000) {
		elapsed = millis() - timeout;
     	;}
	
	for (int j = 0; j < 4; j++) {
		chars[j] = rigCat.read();  
   	}
	mode = rigCat.read(); 
	freq = from_bcd_be(chars, 8);
	return freq;
}


// determine if the radio is in TX state
// unless the radio is actively TX, the result is always
// 0x255 so any value other than 0x255 means TX !
boolean FT897D::chkTX() {
	byte rigTXState[5] = {0x00,0x00,0x00,0x00,0x00};
	rigTXState[4] = CAT_TX_DATA_CMD;
	
	sendCmd(rigTXState, 5);

	byte reply = getByte();
	
	if (reply == 0) {
		return false;
	}
	else {
		return true;
	}
}

// spit out any DEBUG data via this function
void FT897D::comError(char * string) {
 Serial.println("Communication Error!");
 Serial.println(string);
}

// gets a byte of input data from the radio
byte FT897D::getByte() {
	unsigned long startTime = millis();
	while (rigCat.available() < 1 && millis() < startTime + 2000) {
		;
	}
	byte radioReply = rigCat.read();
	return radioReply ;
}

// this is the function which actually does the 
// serial transaction to the radio
void FT897D::sendCmd(byte cmd[], byte len) {
	for (byte i=0; i<len; i++) {
		rigCat.write(cmd[i]);
	}
//	return getByte();	// should make this work more quickly
					// in a future update
}

// this function reduces total code-space by allowing for
// single byte commands to be issued (ie. all the toggles)
byte FT897D::singleCmd(int cmd) {
	byte outByte[5] = {0x00,0x00,0x00,0x00,0x00};
	outByte[4] = cmd;
	sendCmd(outByte, 5);
	return getByte();
}

// send a single byte of data (will be removed later)
void FT897D::sendByte(byte cmd) {
	rigCat.write(cmd);
}

void FT897D::flushRX() {
	rigCat.flush();
}

// GPL
// taken from hamlib work
unsigned long FT897D::from_bcd_be(const  byte bcd_data[], unsigned bcd_len)
{
	int i;
	long f = 0;

	for (i=0; i < bcd_len/2; i++) {
		f *= 10;
		f += bcd_data[i]>>4;
		f *= 10;
		f += bcd_data[i] & 0x0f;
	}
	if (bcd_len&1) {
		f *= 10;
		f += bcd_data[bcd_len/2]>>4;
	}
	return f;
}

// GPL
// taken from hamlib work
unsigned char * FT897D::to_bcd_be( unsigned char bcd_data[], unsigned long  freq, unsigned bcd_len)
{
	int i;
	unsigned char a;

	if (bcd_len&1) {
		bcd_data[bcd_len/2] &= 0x0f;
		bcd_data[bcd_len/2] |= (freq%10)<<4;
/* NB: low nibble is left uncleared */
		freq /= 10;
	}
	for (i=(bcd_len/2)-1; i >= 0; i--) {
		a = freq%10;
		freq /= 10;
		a |= (freq%10)<<4;
		freq /= 10;
		bcd_data[i] = a;
	}
	return bcd_data;
}
