#include "Inimeac.h"

Inimeac trame;

void setup() {
  Serial3.begin(38400); // Vitesse de transmission du module bluetooth
  Serial.begin(38400);
}

void loop() {
  trame.setTrame();
  if (Serial3.available())
    Serial3.write(Serial.read());
  if(Serial.available())
    Serial.write(Serial3.read());
 }
