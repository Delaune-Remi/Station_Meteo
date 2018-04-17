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
      String trame="";
      String trame1= "";
      int taille=0;
      for (int i=0;i<=40;i++){
          trame.concat((char)Serial3.read()); // recup Trame NMEA
     }
    // Serial.println(trame);
    // Serial.println();
     for (int i=0;i<=30;i++){
      trame.concat((char)Serial3.read()); // recup Trame NMEA
     }
     Serial.println(trame);
     Serial.println();
     Serial.println();
     if (trame [0]=='$' && trame[1] == 'I' || trame[1] == 'W'){
      trame1.concat(trame);
      Serial.print("Trame Correcte : ");
      Serial.println(trame1);
     }
     Serial.println();
     
      
} 
