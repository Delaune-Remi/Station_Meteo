#include <Ethernet.h>
#include <SPI.h>

byte mac[] = {0x90, 0x98, 0x97, 0x00, 0x05, 0xAB};
byte ip[] = {192, 168,  190,  123};
EthernetServer serveur(80);

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
      String affichage = GET(client); //appel de la fonction de décodage
      while (client.available()) { // tant qu'il a des infos à transmettre
        char c=client.read(); // on lit le caractère  
        Serial.write(c);// on l'écrit sur le moniteur série
        delay(1); //délai de lecture
      }
      //réponse au client
      /*client.println("HTTP/1.1 200 OK"); // type du HTML
      client.println("Content-Type: text/html; charset=UTF-8 "); //type de fichier et encodage des caractères
      client.println("Connection: close");  // fermeture de la connexion quand toute la réponse sera envoyée
      client.println("Refresh: 5");*/  // rafraîchissement automatique de la page toutes les 5 secondes
      client.println(); //saut de ligne obligatoire avant la suite
      client.println("<!DOCTYPE HTML>"); // informe le navigateur du type de document à afficher
      client.println("<html>"); //début code html
      client.println("<head>"); //entête
      client.println("<title>Essai</title>");
      client.println("</head>");
      client.println("<body>");
      client.println("<h1>Essai</h1>");
      client.println("<hr>");
      /*for (int p=0;p<6;p++){
        client.print("pin A");
        client.print(p);
        client.print(":");
        client.print(analogRead(p));
        client.print("<br>");
      }*/
      client.println("<a href=?valeur=100&autreValeur=10&anniv=oui target=_self>Envoi</a><br>");
      client.println("<a href=? target=_self>Refresh</a><br>");
      client.println("<br><hr></body></html>"); //ligne horizontale et fermeture des balises
      client.stop(); //on déconnecte le client
      Serial.println("Fin de communication avec le client\n");
    }
  }
}
//fonctin décodage GET
String GET(EthernetClient cl) {
  int lecture = 0; // variable pour les étapes de décodage
  String resultat = "<br>"; //initialisation de la chaine de réponse
  String donnee = ""; //chaine pour stocker la lecture des données
  while (cl.available()) { // tant qu'il a des infos à transmettre
    char c = cl.read(); // on lit le caractère
    if (lecture == 0 && c == '?') { //début de lecture des données donc d'un nom
      lecture = 1;
      donnee = "";
    }
    else if (lecture == 1 && c == '=') { //début de lecture d'une valeur
      lecture = 2;
      resultat += donnee + " : "; //on construit la chaîne de réponse
      donnee = "";
    }
    else if (lecture == 2 && c == '&') { //nouveau nom
      lecture = 1;
      resultat += donnee + "<br>"; //on construit la chaîne de réponse
      donnee = "";
    }
    else if ((lecture == 2 || lecture == 1) && c == ' ') { //fin de lecture
      lecture = 3;
      resultat += donnee + "<br><br>"; // on finit la chaîne réponse.
    }
    else if (lecture == 1 || lecture == 2) {//récupération des données de nom ou de valeur
      donnee += c;
    }
    delay(1); //delai de lecture
  }
  return resultat; // retour le la chaîne de réponse
}


