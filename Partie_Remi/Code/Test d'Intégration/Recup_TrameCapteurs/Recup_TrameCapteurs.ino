/*Inclusion des librairies */

#include "SFE_BMP180.h"
#include "CapteurCV3F.h"
#include <Wire.h>

/* Creation d'objets */

SFE_BMP180 bmp180;
CapteurCV3F capteurCV3F;

/*Creation des definitions*/

#define ALTITUDE 1655.0

void setup() {
  Serial.begin(4800);
  bmp180.begin();
}

void loop() {
     char status;
     double T,P,p0;
     char* Te;
     
     status = bmp180.startTemperature();
     delay(status);
     status = bmp180.getTemperature(T);
     if (status != 0){
        Serial.print("\nTemperature : ");
        Serial.print(T);
        Serial.println(" C ");
        
        sprintf(Te,"%f",T);
        
        Serial.print("\nTemperature : ");
        Serial.print(Te);
        Serial.println(" C ");
        status = bmp180.startPressure(3);
        delay(status);
        status = bmp180.getPressure(P,T);
        if (status != 0){
          Serial.print("Pression : ");
          Serial.print(P);
          Serial.println(" mBar (Hpa) ");
        } 
     }   
}
