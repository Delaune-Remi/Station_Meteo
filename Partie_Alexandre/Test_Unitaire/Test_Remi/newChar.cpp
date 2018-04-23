#include <Wire.h>
#include "CLCD.h"
#include "newChar.h"


void chargerNouveauChar(int addr_lcd, int addr_memoire, char ligne1, char ligne2, char ligne3, char ligne4, char ligne5, char ligne6, char ligne7, char ligne8){
  if (addr_memoire<=15 && addr_memoire>=8){
    Wire.beginTransmission(addr_lcd);
    Wire.write(0x1B);
    Wire.write(0x44);
    Wire.write(addr_memoire);
    Wire.write(ligne1);
    Wire.write(ligne2);
    Wire.write(ligne3);
    Wire.write(ligne4);
    Wire.write(ligne5);
    Wire.write(ligne6);
    Wire.write(ligne7);
    Wire.write(ligne8);
    Wire.endTransmission();
  }
}

void chargerE_accentAigu(int addr_lcd, int addr_memoire){
  if (addr_memoire<=15 && addr_memoire>=8){
    Wire.beginTransmission(addr_lcd);
    Wire.write(0x1B);
    Wire.write(0x44);
    Wire.write(addr_memoire);
    Wire.write(0x02);
    Wire.write(0x04);
    Wire.write(0x0E);
    Wire.write(0x11);
    Wire.write(0x1F);
    Wire.write(0x10);
    Wire.write(0x0E);
    Wire.write(0x00);
    Wire.endTransmission();
  }
}


void chargerSymbol_bateau(int addr_lcd, int addr_memoire){
  if (addr_memoire<=15 && addr_memoire>=8){
    Wire.beginTransmission(addr_lcd);
    Wire.write(0x1B);
    Wire.write(0x44);
    Wire.write(addr_memoire);
    Wire.write(0x08);
    Wire.write(0x0C);
    Wire.write(0x0E);
    Wire.write(0x0F);
    Wire.write(0x0F);
    Wire.write(0x08);
    Wire.write(0x1F);
    Wire.write(0x1E);
    Wire.endTransmission();
  }
}
void chargerSymbol_avion(int addr_lcd, int addr_memoire){
  if (addr_memoire<=15 && addr_memoire>=8){
    Wire.beginTransmission(addr_lcd);
    Wire.write(0x1B);
    Wire.write(0x44);
    Wire.write(addr_memoire);
    Wire.write(0x04);
    Wire.write(0x04);
    Wire.write(0x0E);
    Wire.write(0x1F);
    Wire.write(0x15);
    Wire.write(0x04);
    Wire.write(0x0E);
    Wire.write(0x11);    
    Wire.endTransmission();
  }
}

void chargerSymbol_flecheHaut(int addr_lcd, int addr_memoire){
  if (addr_memoire<=15 && addr_memoire>=8){
    Wire.beginTransmission(addr_lcd);
    Wire.write(0x1B);
    Wire.write(0x44);
    Wire.write(addr_memoire);
    Wire.write(0x00);
    Wire.write(0x04);
    Wire.write(0x0E);
    Wire.write(0x15);
    Wire.write(0x04);
    Wire.write(0x04);
    Wire.write(0x00);
    Wire.write(0x00);    
    Wire.endTransmission();
  }
}

void chargerSymbol_flecheBas(int addr_lcd, int addr_memoire){
  if (addr_memoire<=15 && addr_memoire>=8){
    Wire.beginTransmission(addr_lcd);
    Wire.write(0x1B);
    Wire.write(0x44);
    Wire.write(addr_memoire);
    Wire.write(0x00);
    Wire.write(0x04);
    Wire.write(0x04);
    Wire.write(0x15);
    Wire.write(0x0E);
    Wire.write(0x04);
    Wire.write(0x00);
    Wire.write(0x00);    
    Wire.endTransmission();
  }
}

void chargerSymbol_flecheGaucheinverse(int addr_lcd, int addr_memoire){
  if (addr_memoire<=15 && addr_memoire>=8){
    Wire.beginTransmission(addr_lcd);
    Wire.write(0x1B);
    Wire.write(0x44);
    Wire.write(addr_memoire);
    Wire.write(0x1F);
    Wire.write(0x1B);
    Wire.write(0x17);
    Wire.write(0x00);
    Wire.write(0x17);
    Wire.write(0x1B);
    Wire.write(0x1F);
    Wire.write(0x1F);    
    Wire.endTransmission();
  }
}

void chargerSymbol_flecheDroiteinverse(int addr_lcd, int addr_memoire){
  if (addr_memoire<=15 && addr_memoire>=8){
    Wire.beginTransmission(addr_lcd);
    Wire.write(0x1B);
    Wire.write(0x44);
    Wire.write(addr_memoire);
    Wire.write(0x1F);
    Wire.write(0x1B);
    Wire.write(0x1D);
    Wire.write(0x00);
    Wire.write(0x1D);
    Wire.write(0x1B);
    Wire.write(0x1F);
    Wire.write(0x1F);    
    Wire.endTransmission();
  }
}

void chargerSymbol_brouillard(int addr_lcd, int addr_memoire){
  if (addr_memoire<=15 && addr_memoire>=8){
    Wire.beginTransmission(addr_lcd);
    Wire.write(0x1B);
    Wire.write(0x44);
    Wire.write(addr_memoire);
    Wire.write(0x00);
    Wire.write(0x08);
    Wire.write(0x15);
    Wire.write(0x02);
    Wire.write(0x08);
    Wire.write(0x15);
    Wire.write(0x02);
    Wire.write(0x00);    
    Wire.endTransmission();
  }
}

void chargerSymbol_flocon(int addr_lcd, int addr_memoire){
  if (addr_memoire<=15 && addr_memoire>=8){
    Wire.beginTransmission(addr_lcd);
    Wire.write(0x1B);
    Wire.write(0x44);
    Wire.write(addr_memoire);
    Wire.write(0x04);
    Wire.write(0x15);
    Wire.write(0x0A);
    Wire.write(0x15);
    Wire.write(0x0A);
    Wire.write(0x15);
    Wire.write(0x04);
    Wire.write(0x00);    
    Wire.endTransmission();
  }
}

void chargerSymbol_soleil(int addr_lcd, int addr_memoire){
  if (addr_memoire<=15 && addr_memoire>=8){
    Wire.beginTransmission(addr_lcd);
    Wire.write(0x1B);
    Wire.write(0x44);
    Wire.write(addr_memoire);
    Wire.write(0x04);
    Wire.write(0x15);
    Wire.write(0x0D);
    Wire.write(0x1B);
    Wire.write(0x0D);
    Wire.write(0x15);
    Wire.write(0x04);
    Wire.write(0x00);    
    Wire.endTransmission();
  }
}

void chargerSymbol_pluie(int addr_lcd, int addr_memoire){
  if (addr_memoire<=15 && addr_memoire>=8){
    Wire.beginTransmission(addr_lcd);
    Wire.write(0x1B);
    Wire.write(0x44);
    Wire.write(addr_memoire);
    Wire.write(0x0E);
    Wire.write(0x11);
    Wire.write(0x11);
    Wire.write(0x0E);
    Wire.write(0x00);
    Wire.write(0x0A);
    Wire.write(0x00);
    Wire.write(0x14);    
    Wire.endTransmission();
  }
}
