
void setup() {
  Serial3.begin(4800); // reglage de la vitesse de transmission du bus series numero 3
  Serial.begin(4800);
  /*
   * Pour pouvoir recuperer la trame et l'afficher sur le moniteur serie (Serial)
   * Il faut avoir la meme vitesse de transmission ( 4800 bauds ), valeur fixee par le CV3F (Serial3 "ici")
   */
}

void loop() {
  /*
   * Lecture des trames NMEA0183
   */ 
      char trame [30];
      Serial3.readBytesUntil('\n',trame,30); // Lecture des trame NMEA0183
      if ( trame [0] == '$' && (trame [1]=='I' || trame [2] == 'I') ){
         Serial.write(trame[0]);
         Serial.write(trame[1]);
         Serial.write(trame[2]);
         Serial.write(trame[3]);
         Serial.write(trame[4]);
         Serial.write(trame[5]);
         Serial.write(trame[6]);
         Serial.write(trame[7]);
         Serial.write(trame[8]);
         Serial.write(trame[9]);
         Serial.write(trame[10]);
         Serial.write(trame[11]);
         Serial.write(trame[12]);
         Serial.write(trame[13]);
         Serial.write(trame[14]);
         Serial.write(trame[15]);
         Serial.write(trame[16]);
         Serial.write(trame[17]);
         Serial.write(trame[18]);
         Serial.write(trame[19]);
         Serial.write(trame[20]);
         Serial.write(trame[21]);
         Serial.write(trame[22]);
         Serial.write(trame[23]);
         Serial.write(trame[24]);
         Serial.write(trame[25]);
         Serial.write(trame[26]);
         Serial.write(trame[27]);
         Serial.write('\n');
      }    
} 
