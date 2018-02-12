#include "CapteurCV3F.h"
int i=0;

void setup() {
  Serial.begin(4800); 
 
}

void loop() {
  CapteurCV3F capteur;
     Serial.print ("\n\nTrameNMEA_MWV : ");
     Serial.println (capteur.getTrameNMEA_MWV());
     Serial.print ("TrameNMEA_XDR : ");
     Serial.println (capteur.getTrameNMEA_XDR());
     Serial.print ("\nTrameNMEA_MWV : ");
     Serial.println (capteur.getTrameNMEA_MWV());
     Serial.print ("TrameNMEA_XDR : ");
     Serial.println (capteur.getTrameNMEA_XDR());
     Serial.print ("\nTrameNMEA_MWV : ");
     Serial.println (capteur.getTrameNMEA_MWV());
     Serial.print ("TrameNMEA_XDR : ");
     Serial.println (capteur.getTrameNMEA_XDR());
}
