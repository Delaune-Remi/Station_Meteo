
void setup() {
  Serial3.begin(4800); // reglage de la vitesse de transmission du bus series numero 3
  Serial.begin(4800);
  /*
   * Pour pouvoir recuperer la trame et l'afficher sur le moniteur serie (Serial)
   * Il faut avoir la meme vitesse de transmission ( 4800 bauds ), valeur fixee par le CV3F (Serial3 "ici")
   */
}

void loop() {
  char trame [255];
  Serial3.readBytesUntil('\0',trame,40); // Lecture de la trame NMEA0183
  
  Serial.write(trame); // Lecture de RX3 et envoie au moniteur serie
}
