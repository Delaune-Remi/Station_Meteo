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
  lcd.setCursor(0,1);
  lcd1.setCursor(0,1);
  lcd.print("Initialisation");
  lcd1.print("Initialisation"); 
  lcd.setCursor(1,0);
  lcd1.setCursor(1,0);
  for(int i=0;i<16;i++){
  lcd.print(char(255));
  lcd1.print(char(255));
  delay(215);
  }
}

void loop()
{
  lcd.clear();
  lcd1.clear();
  lcd.backlight();
  lcd1.backlight();
  lcd.setCursor(0,1);
  lcd1.setCursor(0,1);
  lcd.print("Station Meteo");
  lcd1.print("Station Meteo");
  lcd.cursor_off();
  lcd1.cursor_off();
  lcd.setCursor(1,0);
  lcd1.setCursor(1,0);
  lcd.print("AeroClubSaintVal");
  lcd1.print("AeroClubSaintVal");
  lcd.cursor_off();
  lcd1.cursor_off();
  delay(5000);
  lcd.clear();
  lcd1.clear();
  lcd.print("Temp");
  lcd1.print("VitVent:");
  lcd.setCursor(0,8);
  lcd1.setCursor(0,9);
  lcd.print(":");
  lcd.setCursor(0,10);
  lcd.print(char(255));
  lcd.print(char(255));
  lcd.print(",");
  lcd.print(char(255));
  lcd.print(char(223));
  lcd.print("C");
  lcd1.print(char(255));
  lcd1.print(char(255));
  lcd1.print(",");
  lcd1.print(char(255));
  lcd1.print("kts");
  lcd.setCursor(1,0);
  lcd1.setCursor(1,0);
  lcd.print("Pression:");
  lcd1.print("DirecVent: ");
  lcd.setCursor(1,9);
  lcd1.setCursor(1,10);
  lcd.cursor_off();
  lcd1.cursor_off();
  lcd.print(char(255));
  lcd.print(char(255));
  lcd.print(char(255));
  lcd.print(char(255));
  lcd1.print(char(255));
  lcd1.print(char(255));
  lcd1.print(char(255));
  lcd1.print(",");
  lcd1.print(char(255));
  lcd.print("hPa");
  lcd1.print(char(223));
  delay(5000);
  lcd.clear();
  lcd1.clear();
  lcd.setCursor(0,0);
  lcd1.setCursor(0,0);
  lcd.print("Humidite");
  lcd1.print("Humidite");
  lcd.setCursor(0,9);
  lcd.print(":");
  lcd1.setCursor(0,9);
  lcd1.print(":");
  lcd.setCursor(0,12);
  lcd1.setCursor(0,12);
  lcd.print(char(255));
  lcd.print(char(255));
  lcd.print(char(255));
  lcd.print("%");
  lcd1.print(char(255));
  lcd1.print(char(255));
  lcd1.print(char(255));
  lcd1.print("%");
  lcd.setCursor(1,0);
  lcd1.setCursor(1,0);
  lcd.print("bts-sn-yvetot.fr");
  lcd1.print("bts-sn-yvetot.fr");
  lcd.cursor_off();
  lcd1.cursor_off();
  delay(5000);
  lcd.cursor_off();
  lcd1.cursor_off();
  lcd.clear();
  lcd1.clear();
  }


