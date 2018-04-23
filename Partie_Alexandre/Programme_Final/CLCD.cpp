#include <LiquidCrystal.h>

// [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
// []
// []	LCD API for Lextronic CCLCD I2C models
// []
// []  
// []   Library by julien@pobot.org (2011-10)
// []
// [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]

#include <Wire.h>

#include <string.h>			//needed for strlen()

#include <inttypes.h>

#include "Arduino.h"		//all things wiring / arduino

#include "CLCD.h"

#define _LCDEXPANDED				// If defined turn on advanced functions

// Global Vars 

uint8_t g_num_lines = 4;
uint8_t g_num_col = 20;

int g_cmdDelay = 50;
int g_charDelay = 0;

// [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
// []
// []	Class Constructor 
// []
// []	num_lines = 1-4
// []   num_col = 1-80
// []  
// []   
// []
// [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]

CLCD::CLCD (uint8_t address,uint8_t num_col,uint8_t num_lines)
{

  _Addr = address;
  g_num_lines = num_lines;
  g_num_col = num_col;

}

// [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
// []
// []	initiatize lcd after a short pause
// []
// []	
// []   Put the display in some kind of known mode
// []   Put the cursor at 0,0
// []
// [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]


void CLCD::init () {

  Wire.begin();
  off();
  clear();
  blink_off();
  cursor_off(); 
  home();

}

// [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
// []
// []	Over ride the default delays used to write commands to the display
// []
// []	The default values are set by the library
// []   this allows the programer to take into account code delays
// []   and speed things up.
// []   
// []
// [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]


void CLCD::setDelay (int cmdDelay,int charDelay) {

  g_cmdDelay = cmdDelay;
  g_charDelay = charDelay;

}




// [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
// []
// []   write a command to the display. 
// []
// [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]


void CLCD::command(uint8_t value) {

  delay(g_cmdDelay);
}


// [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
// []
// []   write a command to the display. 
// []
// []	This is also used by the print, and println
// []	
// []
// [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]



size_t CLCD::write(uint8_t value) {

  Wire.beginTransmission(_Addr);
  Wire.write(value);
  Wire.endTransmission();
  delay(g_charDelay);

  return sizeof value;
}



// [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
// []
// []	Clear the display, and put cursor at 0,0 
// []
// []
// [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]


void CLCD::clear(){

  Wire.beginTransmission(_Addr);
  Wire.write(0x1B);
  Wire.write(0x43);
  delay(g_cmdDelay);
  Wire.endTransmission();

}

// [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
// []
// []	Home to custor to 0,0
// []
// []	Do not disturb data on the displayClear the display
// []
// []
// [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]


void CLCD::home(){

  setCursor(0,0);					// The command to home the cursor does not work on the version 1.3 of the display
}


// [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
// []
// []	Turn on the display
// []
// []	Depending on the display, might just turn backlighting on
// []
// []
// [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]

void CLCD::backlight(){
  on(); 
}

void CLCD::on(){

  Wire.beginTransmission(_Addr);
  Wire.write(0x1B);
  Wire.write(0x42);
  Wire.endTransmission();
  delay(g_cmdDelay);
}


// [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
// []
// []	Turn off the display
// []
// []	Depending on the display, might just turn backlighting off
// []
// []
// [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]

void CLCD::off(){

  Wire.beginTransmission(_Addr);
  Wire.write(0x1B);
  Wire.write(0x62);
  Wire.endTransmission();
  delay(g_cmdDelay);

}


// [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
// []
// []	Turn on the underline cursor
// []
// []
// [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]

void CLCD::cursor_on(){

  Wire.beginTransmission(_Addr);
  Wire.write(0x1B);
  Wire.write(0x53);
  Wire.endTransmission();
  delay(g_cmdDelay);

}


// [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
// []
// []	Turn off the underline cursor
// []
// []
// [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]

void CLCD::cursor_off(){

  Wire.beginTransmission(_Addr);
  Wire.write(0x1B);
  Wire.write(0x73);
  Wire.endTransmission();

}


// [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
// []
// []	Turn on the blinking block cursor
// []
// []
// [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]


void CLCD::blink_on(){


}


// [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
// []
// []	Turn off the blinking block cursor
// []
// []
// [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]

void CLCD::blink_off(){

}


// [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
// []
// []	Position the cursor to position line,column
// []
// []	line is 0 - Max Display lines
// []	column 0 - Max Display Width
// []
// [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]


void CLCD::setCursor(uint8_t line_num, uint8_t x){

  Wire.beginTransmission(_Addr);
  Wire.write(0x1B);
  Wire.write(0x4C);
  Wire.write(min(x,g_num_col));
  Wire.write(min(line_num,g_num_lines));
  Wire.endTransmission();
  delay(g_cmdDelay);

}


// [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
// []
// []	Return the status of the display
// []
// []	Does nothing on this display
// []
// [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]	

uint8_t CLCD::status(){

  return 0;
}


// [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
// []
// []	Read data from keypad
// []
// []	
// []	
// []
// [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]


uint8_t CLCD::keypad (){


}



// [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
// []
// []	Load data for a custom character
// []
// []	Char = custom character number 0-7
// []	Row is array of chars containing bytes 0-7
// []
// []
// [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]


void CLCD::load_custom_character(uint8_t char_num, uint8_t *rows)
{


}



void CLCD::setBacklight(uint8_t new_val)
{
  if (new_val) {
    on(); 
  } 
  else {
    off();
  }
}


void CLCD::setContrast(uint8_t new_val)
{

}







