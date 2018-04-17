/*Inclusion des librairies */

#include "SFE_BMP180.h"
#include <Wire.h>

/* Creation d'objets */

SFE_BMP180 bmp180;

/*Creation des definitions*/

#define ALTITUDE 1655.0

void setup() {
  Serial.begin(4800);
  bmp180.begin();
}

void loop() {
     char status;
     double T,P,p0;
     String Te,Pa;
     
/* Permet l'initialisation de la recuperation de la temperature pour le capteur*/

     status = bmp180.startTemperature(); 
     delay(status);
     
/* Permet l'obtention de la temperature*/

     status = bmp180.getTemperature(T);
     if (status != 0){
        Te= String(T,2);
        Serial.print("\nTemperature : ");
        Serial.print(Te);
        Serial.print(char(176));
        Serial.println("C ");
        status = bmp180.startPressure(3);
        delay(status);
        status = bmp180.getPressure(P,T);
        if (status != 0){
          Serial.print("Pression : ");
          Serial.print(String(P,2));
          Serial.println(" mBar (Hpa) ");
        } 
     }   
}
