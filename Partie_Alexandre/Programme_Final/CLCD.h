// [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
// []
// []	LCD API for Lextronic CLCDxxx I2C models
// []
// []  
// []   Library by julien@pobot.org (2011-10)
// []
// [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]

#ifndef CLCD_h
#define CLCD_h


#define _LCDEXPANDED				// If defined turn on advanced functions

#include <inttypes.h>

#include "Print.h"


class CLCD : public Print {
	
public: 
  
        // MANDATORY

        CLCD(uint8_t address, uint8_t num_col, uint8_t num_lines);
	
	void init();

        void setDelay(int,int);
        
        // print & println through Print.h

	virtual size_t write(uint8_t);
	
	void command(uint8_t value);
	
	void clear();
	
	void home();
	
	void setCursor(uint8_t Line, uint8_t Col );
	
	void cursor_on();
	
	void cursor_off();
	
	void blink_on();
	
	void blink_off();

        // OPTIONAL
	 
	void setBacklight(uint8_t new_val);
	
	void setContrast(uint8_t new_val);
	
        void backlight();

        void on();
	
	void off();	
	
	uint8_t status();
		
	// [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
	// []
	// []	Extended Functions
	// []
	// [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
	
	
#ifdef _LCDEXPANDED		

	
	void load_custom_character(uint8_t char_num, uint8_t *rows);
	
	uint8_t keypad();
	
	void printstr(const char[]);
   
		
#endif
	
private:

  uint8_t _Addr;
	
	
};

#endif


