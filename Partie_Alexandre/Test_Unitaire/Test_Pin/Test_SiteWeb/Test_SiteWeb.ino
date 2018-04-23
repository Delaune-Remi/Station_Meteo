#include <Ethernet.h>
#include <SPI.h>

byte mac[] = {0x90, 0x98, 0x97, 0x00, 0x05, 0xAB};
byte ip[] = {192, 168,  190,  123};
EthernetServer serveur(80);
char data = 0;
void setup() {
  
  Serial.begin(9600);
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Impossible de se connecter au serveur DHCP");
    Ethernet.begin(mac, ip);
  }
  Serial.print("Le serveur est sur l'adresse : ");
  Serial.println(Ethernet.localIP());
  serveur.begin();
}

void loop() {
  EthernetClient client = serveur.available(); //on écoute le port
  if (client) { //si client connecté
    Serial.println("Client en ligne\n"); //on le dit...
    if (client.connected()) { // si le client est en connecté
      while (client.available()) { // tant qu'il a des infos à transmettre
        char c=client.read(); // on lit le caractère  
        Serial.write(c);// on l'écrit sur le moniteur série
        delay(1); //delai de lecture
      }
      //réponse au client    
      client.println("HTTP/1.1 200 OK"); // type du HTML
      client.println("Content-Type: text/html; charset=UTF-8 "); //type de fichier et encodage des caractères
      client.println("Connection: close");  // fermeture de la connexion quand toute la réponse sera envoyée
      client.println("Refresh: 5");  // rafraîchissement automatique de la page toutes les 5 secondes
      client.println();
      client.println("<!DOCTYPE HTML>"); // informe le navigateur du type de document à afficher
      data = Serial.read();        //Read the incoming data & store into data  
      client.println("<html>"); //début du code html
      client.println("<head>"); //entête
      client.println("<title>Station météo</title>"); //titre de la fenêtre
      client.println("</head>");//fin d'entête
      client.println("<body>"); //corps
      client.println("<h1 align=center>Relevés Météorologiques</h1>"); //titre en grosse lettres
      client.println("<hr>"); //ligne horizontale
      //if(Serial.available() > 0)      // Envoie les données seuelement si on les reçois
  // {
      client.print("Temperature : "); // affichage
      if(data == 'T')     {         // Compare la donnée avec la lettre T
        client.print(data); //numéro de pin
      }
       client.print("°C");
      client.print("<br>"); //saut de ligne
      client.print("Humidité : "); // affichage
      if(data == 'H')     {         
        client.print(data); //numéro de pin
      }
      client.print("%");
      client.print("<br>"); //saut de ligne
      client.print("Pression : "); // affichage
      if(data == 'P')     {        
        client.print(data); //numéro de pin

      }
       client.print("hPa");
        client.print("<br>"); //saut de ligne
      client.print("Direction du vent : "); // affichage
      if(data == 'D')     {         
        client.print(data); //numéro de pin
        
      }
      client.print("°");
      client.print("<br>"); //saut de ligne
      client.print("Vitesse du vent : "); // affichage
      if(data == 'V')     {         
        client.print(data); //numéro de pin
        
      }
      client.print("kts");
      client.println("<hr>"); //ligne horizontale
      client.println("</body>"); //fin du corps
      client.println("</html>"); //fin du code html
      client.stop(); //on déconnecte le client
      Serial.println("Fin de communication avec le client");
     
   //}    
   }
  }
}

