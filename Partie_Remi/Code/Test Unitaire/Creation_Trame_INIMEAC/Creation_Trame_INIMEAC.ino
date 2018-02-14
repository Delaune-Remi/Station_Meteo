#include "Inimeac.h" 

Inimeac trame;

void setup() {
  Serial.begin(9600);
  Serial2.begin(38400); // Vitesse de transmission du module bluetooth
}

void loop() {
  char vad;
  vad = trame.setTrame();
  Serial.println(trame.getTrame());
  Serial2.println(trame.getTrame());
}
