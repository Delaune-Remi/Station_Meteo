// Test d'un écran LCD I2DC "CLCD" de Lextronic
// version 162 (2 lignes et 16 colonnes)

// écriture d'une bibliothèque Arduino pour AstonDB8 (Yves)

#include <Wire.h>
#include "CLCD.h"

CLCD lcd(0x00,16,2);

void setup()
{
  lcd.init();
  
  // 
  lcd.backlight();
  lcd.print("Salut, Yves");
  lcd.setCursor(1,6);
  lcd.print("by Pobot");
  lcd.setCursor(1,0);
  lcd.cursor_on();
  //
}


void loop()
{
   
}
