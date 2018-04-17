#include "Inimeac.h"

Inimeac trame;

void setup() {
  Serial2.begin(38400); // Vitesse de transmission du module bluetooth
  Serial.begin(38400);
}

void loop() {
  trame.setTrame();
  Serial2.write(trame.getTrame());
  Serial2.write('\n');
  Serial.write(trame.getTrame());
  Serial.write('\n');
}
