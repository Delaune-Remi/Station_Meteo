#include <Wire.h>
#include "CLCD.h"
#include "I2C.h"
#include <Print.h>
CLCD lcd(0x02,16,2);
CLCD lcd1(0x01,16,2);
void setup()
{
  initI2C(122);
  lcd.init();
  lcd1.init();
  lcd.print("Bonjour");
}

void loop()
{
}



