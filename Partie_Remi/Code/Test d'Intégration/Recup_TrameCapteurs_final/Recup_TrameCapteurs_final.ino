/********* Inclusion des librairies ********/

#include "SFE_BMP180.h"
#include "CapteurCV3F.h"
#include "Inimeac.h"
#include <Wire.h>

/********* Creation d'objets *********/

Inimeac trame;
SFE_BMP180 bmp180;
CapteurCV3F capteurCV3F;

/********* Creation des definitions *********/

#define ALTITUDE 1655.0

void setup() {

/********* Initialisation des liaisons Series *********/

  Serial.begin(9600);
  Serial2.begin(9600);
  Serial1.begin(9600);
  Serial3.begin(4800);

/********* Initialisation du Capteur BMP180 *********/
  
  bmp180.begin();
  
}

void loop() {
     char status;
     double T,P,H;
     String Te,Pa,He;
     int reading;
     char* pPa=NULL;
      char* pTe=NULL;
     char* pHe=NULL;
     
     status = bmp180.startTemperature();
     delay(status);
     status = bmp180.getTemperature(T);
     if (status != 0){
        status = bmp180.startPressure(3);
        
/********* Lecture de la valeur correspondant a la pression ********/

        delay(status);
        status = bmp180.getPressure(P,T);
        if (status != 0){

/********* Gestion du stockage de la pression *******/

          Pa=String(P,2); 
          pPa = new char [Pa.length()+1];
          strcpy (pPa, Pa.c_str());

/********* Affichage de la pression *******/

          Serial.print("Pression : ");
          Serial.print(pPa);
          Serial.println(" mBar (Hpa) ");
          
        } 
     }
      Serial.print("La vitesse du vent est de : ");
      Serial.print(capteurCV3F.getVitesseVent());
      Serial.println(" Kts");
      Serial.print("La direction du vent est de : ");
      Serial.print(capteurCV3F.getDirectionVent());
      Serial.println(char(176));
      
      Wire.beginTransmission(0x27); //adresse I2C de la serie de capteur HIH8000
      Wire.write(byte(0x00));       // Initialisation des mesures par l'envoie de zero bits 
      Wire.endTransmission();       //arret de la transmission
      
      delay(100);

      Wire.requestFrom(0x27, 4); 
      if (4 <= Wire.available())    // Faire si les 4 bits sont reçue
      { 
        
/********* Lecture de la valeur correspondant a l'hygrometrie *******/
         
        reading = Wire.read();  
        reading = reading << 8;
        reading |= Wire.read(); 

/********* Conversion de la valeur correspondant a l'hygrometrie *******/

        H = reading / 16382.0 * 100.0; 

/********* Gestion du stockage de l'hygrometrie *******/
        
        He=String(H,2);
        pHe = new char [He.length()+1];
        strcpy (pHe, He.c_str());

/********* Affichage de l'hygrometrie *******/

        Serial.print("Humidite : ");
        Serial.print(pHe);
        Serial.println ("%");
        
/********* Lecture de la valeur correspondant a la temperature *******/
   
        reading = Wire.read();
        reading = reading << 6;
        reading |= (Wire.read()>>2);
        
/********* Conversion de la valeur correspondant a la temperature *******/
        
        T = reading / 16382.0 * 165.0 - 40;

/********* Gestion du stockage de la temperature *******/

        Te=String(T,2);
        
        pTe = new char [Te.length()+1];
        
        strcpy (pTe, Te.c_str());
    
/********* Affichage de la temperature *******/
    
        Serial.print("Temperature : ");
        Serial.print(pTe);
        Serial.print ((char(176)));
        Serial.println ("C\n\n");
        
      }
      
/********* Generation de la trame INMEAC pour le site et l'application *******/

      delay(5000);  
      trame.setTrame(capteurCV3F.getVitesseVent(),capteurCV3F.getDirectionVent(),pTe,pHe,pPa,"Y");
      char* trame1=trame.getTrame();          // Trame pour le site
      char* trame2=trame.getTrameApplication(); // Trame pour l'application
     
/********* Envoie de la trame au site web *******/
    
      Serial1.println(trame1);  // Envoie de la trame 
      Serial.print("Trame envoyer au site web     : ");
      Serial.println(trame1);  // Envoie de la trame au moniteur
      Serial.println("");  

/********* Envoie de la trame a L'application *******/

      Serial2.println(trame2);  // Envoie de la trame a la tablette
      Serial.print("Trame envoyer a l'application : ");
      Serial.println(trame2);  // Envoie de la trame au moniteur
      Serial.println("");  

/********* Liberation de la memoire allouee *******/

      delete pPa;
      delete pHe;
      delete pTe; 
      
}
