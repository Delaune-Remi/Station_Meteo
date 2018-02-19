#include "Inimeac.h"

Inimeac trame;

void setup() {
  Serial2.begin(38400); // Vitesse de transmission du module bluetooth
  Serial.begin(38400);
}

void loop() {
  trame.setTrame();
  Serial.write(trame.getTrame());
  Serial.write('\n');
}
