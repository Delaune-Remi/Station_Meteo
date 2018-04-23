#ifndef NEWCHAR_H
#define NEWCHAR_H


void chargerNouveauChar(int addr_lcd, int addr_memoire, char ligne1, char ligne2, char ligne3, char ligne4, char ligne5, char ligne6, char ligne7, char ligne8);
void chargerE_accentAigu(int addr_lcd, int addr_memoire);
void chargerE_accentGrave(int addr_lcd, int addr_memoire);
void chargerSymbol_bateau(int addr_lcd, int addr_memoire);
void chargerSymbol_avion(int addr_lcd, int addr_memoire);
void chargerSymbol_flecheHaut(int addr_lcd, int addr_memoire);
void chargerSymbol_flecheBas(int addr_lcd, int addr_memoire);
void chargerSymbol_flecheGaucheinverse(int addr_lcd, int addr_memoire);
void chargerSymbol_flecheDroiteinverse(int addr_lcd, int addr_memoire);
void chargerSymbol_brouillard(int addr_lcd, int addr_memoire);
void chargerSymbol_flocon(int addr_lcd, int addr_memoire);
void chargerSymbol_soleil(int addr_lcd, int addr_memoire);
void chargerSymbol_pluie(int addr_lcd, int addr_memoire);
#endif

