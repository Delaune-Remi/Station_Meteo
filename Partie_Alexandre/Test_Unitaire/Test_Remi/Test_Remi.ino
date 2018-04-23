
/*********  Librairie pour la gestion du site Web *******/

#include <Ethernet.h>

#include <Wire.h>

/*********  Librairie pour la gestion du temps *******/

#include <avr/io.h>
#include <avr/interrupt.h>

/*********  Librairie pour la gestion des Afficheurs *******/

#include "CLCD.h"
#include "I2C.h"
#include "newChar.h"

/*********  Librairie pour la gestion de la Trame Capteur *******/

#include "Inimeac.h"

/*********  Creation de Classes pour les Afficheurs *******/

CLCD lcd(0x02, 16, 2);
CLCD lcd1(0x01, 16, 2);

/*********  Creation d'une Classe pour la Trame Capteur *******/

Inimeac Trame;

/********* Declaration de Variables pour les Capteurs *********/

char vitesse [5];
char directionVent [5];
char temperature [6];
char hygrometrie [6];
char pression [6];

/********* Declaration de Variables pour la Trame INIMEAC *********/

char caractere = ' ';
String trame = "";
bool trameComplete = false;

/********* Declaration de Variables pour la gestion du temps *********/

volatile unsigned int compteur_IT2 = 0;
volatile unsigned char compteur_IT1 = 0;
bool flag_Afficheur = false;
bool flag = false;

#define DUREE 4 // Duree de 5s pour l'acquisition des donnees

/********* Declaration de Variables pour le site Web *********/

byte mac[] = {0x90, 0x98, 0x97, 0x00, 0x05, 0xAB};
byte ip[] = {192, 168,  190,  123};
EthernetServer serveur(80);

/********* Declaration de Variables pour les Afficheurs *********/

static int etat;

void setup() {

  /********* Configuration du timer 2 *********/

  TCCR2A = 0x01;                          // Mode Normal (pas de PWM) et broche OC2A et OC2B non utilisees
  TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20); // Pre-division a 1024 (horloge/1024)
  TIMSK2 |= (1 << TOIE2);                 // Interruption de débordement du Timer actif
  sei();                                  // Activation globales des Interruption

  /********* Initialisation de la liaison serie i2c  *********/

  initI2C(122);
  lcd.init();
  lcd1.init();

  /********* Initialisation des afficheurs  *********/

  Serial3.begin(9600);
  Serial.begin(9600);
  chargerSymbol_avion(0x02, 0x08);
  chargerSymbol_avion(0x01, 0x08);
  chargerE_accentAigu(0x02, 0x09);
  chargerE_accentAigu(0x01, 0x09);
  chargerSymbol_flocon(0x01, 0x0B);
  chargerSymbol_flocon(0x02, 0x0B);
  chargerSymbol_pluie(0x01, 0x0A);
  chargerSymbol_pluie(0x02, 0x0A);
  lcd.setCursor(0, 0);
  lcd.print("----------------");
  lcd.setCursor(1, 1);
  lcd.print("Initialisation");
  lcd1.setCursor(1, 0);
  lcd1.print("----------------");
  lcd1.setCursor(0, 1);
  for (int i = 0; i < 14; i++) {
    lcd1.print(char(255));
    delay(215);
  }

  /********* Initialisation du site web  *********/

  if (Ethernet.begin(mac) == 0) {
    Serial.println("Impossible de se connecter au serveur DHCP");
    Ethernet.begin(mac, ip);
  }
}

/********* Programme Principale  *********/

void loop() {
  acquisitionDonnees();
  siteWeb();
  afficheur();
}

/*********  Sous Programme permettant la gestion du temps *******/

ISR(TIMER2_OVF_vect) {
  compteur_IT2++;
  compteur_IT1++;

  if (compteur_IT1 == 153) {  // Permet de gerer le temps pour les afficheurs
    flag_Afficheur = true;
    compteur_IT1 = 0;
  }

  if (compteur_IT2 == (61*DUREE) ) {
    /*  Permet de gerer la duree entre chaque acquisition a 5s
        car le nombre interruption du timer par seconde est donnee par :
        Fcpu/(Pre-Division*ValeurMax(255))
    */
    flag = true;
    compteur_IT2 = 0;
  }
}

/*********  Sous Programme permettant l'acquisition des donnees *******/

void acquisitionDonnees() {
  
  if (flag == true) {
    Serial.println(flag);
    for (int i=0;i<124;i++){
    caractere = Serial3.read();
    trame += caractere;
    Serial.print(caractere);
    if (caractere == '\n') {
      trameComplete = true;

    } else {
      trameComplete = false;
    }
    if (trameComplete == true)
    {
      Trame.decodeTrameINIMEAC(trame, trameComplete, vitesse, directionVent, temperature, hygrometrie, pression);
      trame = "";
    }
    }
    flag=false;
  }
}

/*********  Sous Programmes permettant la gestion du site Web *******/

void siteWeb() {

  EthernetClient client = serveur.available(); //on écoute le port
  if (client) { //si client connecté
    Serial.println("\nClient en ligne\n"); //on le dit...
    if (client.connected()) { // si le client est en connecté
      entete(client); // fonction pour l'entête de la page HTML
      corps(client); // fonction pour le corps
      piedpage(client); // fonction pour le pied de page
      Serial.println("Fin de communication avec le client\n");
      client.stop(); //on déconnecte le client
    }
  }
}

void entete(EthernetClient cl) {

  //infos pour le navigateur
  cl.println("HTTP/1.1 200 OK"); // type du HTML
  cl.println("Content-Type: text/html; charset=UTF-8 "); //type de fichier et encodage des caractères
  cl.println("Connection: close");  // fermeture de la connexion quand toute la réponse sera envoyée
  cl.println("Refresh: 5");  // rafraîchissement automatique de la page toutes les 5 secondes
  cl.println();
  //balises d'entête
  cl.println("<!DOCTYPE HTML>");
  cl.println("<html>");
  cl.println("<head>");
  cl.println("<title>Station météo</title>");
  cl.println("<link rel=\"icon\" type=\"image/ico\" href=\"http://www.icone-png.com/ico/26/25788.ico\"/>");
  cl.println("<style type=text/css>");
  cl.println("body{margin-left:auto;");
  cl.println("margin-right:auto;");
  cl.println("cursor: url(https://icon-icons.com/icons2/308/PNG/32/plane-icon_34103.png), default;");
  cl.println("font-family:\"Century Gothic\",serif;");
  cl.println("text-align:center;");
  cl.println("background-color : #ca0000;");
  cl.println("max-width:800px;}");
  cl.println("#entete{text-align:center;");
  cl.println("margin-left:auto;");
  cl.println("margin-right:auto;");
  cl.println("min-width:600px;");
  cl.println("padding-bottom:20px;}");
  cl.println("#donnee {padding-top:40px;");
  cl.println("margin-left:auto;");
  cl.println("padding-bottom:343px;");
  cl.println("font-size:24px;");
  cl.println("margin-right:auto;}");
  cl.println(".donne1 {border:thin solid black;");
  cl.println("vertical-align:middle;");
  cl.println("text-align:center;");
  cl.println("min-width:200px;}");
  cl.println("#Introduction,#piedpage {border:thin black solid;}");
  cl.println("#CentrePage{background-color : white;}");
  cl.println("a:hover{cursor: url(https://icon-icons.com/icons2/907/PNG/32/commercial-aeroplane-bottom-view_icon-icons.com_70518.png), pointer;");
  cl.println("color: #ca0000;}");
  cl.println("</style>");
  cl.println("</head>");

}
void corps(EthernetClient cl) {
  cl.println("<body>");
  cl.println("<div id=\"CentrePage\">");
  cl.println("<table id=\"entete\">");
  cl.println("<tr>");
  cl.println("<td><h1>STATION MÉTÉO <br/>AÉRO-CLUB SAINT-VALÉRY</h1></td>");
  cl.println("<td><p><a href=\"http://aeroclub.cauchois.free.fr/index.html\" target=\"_blank\"><img src=\"http://aeroclub.cauchois.free.fr/images/ACC_sticker.png\" alt=\"Logo de l'aéroclub\" /></a></p></td>");
  cl.println("</tr>");
  cl.println("</table>");
  cl.println("<div id=\"Introduction\">");
  cl.println("<p>Voici les données météorologiques de la station météo </p>");
  cl.println("</div>");
  cl.println("<div id=\"corps\">");
  cl.println("<table id=\"donnee\">");
  cl.println("<tr>");
  cl.println("<td class=\"donne1\" colspan=\"2\"><h2> Relevés météorologiques <br /></h2></td>");
  cl.println("<td class=\"donne1\" rowspan=\"8\"><img src=\"http://www.qu-est-ce.com/wp-content/uploads/2013/01/dessin-de-rose-des-vents.jpg\" alt=\"logo\"/></td>");
  cl.println("</tr>");
  cl.println("<tr>");
  cl.println("<td class=\"donne1\" rowspan=\"2\"> Vitesse du vent </td>");
  cl.println("<td class=\"donne1\">");
  cl.print(vitesse [0]);
  cl.print(vitesse [1]);
  cl.print(vitesse [2]);
  cl.print(vitesse [3]);
  cl.print(vitesse [4]);
  cl.print(vitesse [5]);
  cl.println(" kts </td>");
  cl.println("</tr>");
  cl.println("<tr>");
  cl.println("<td class=\"donne1\">");
  if (trameComplete == false) {
    cl.print(" ");
  }
  else {
    cl.print((((float(vitesse [0]) - 48) * 100) + ((float(vitesse [1]) - 48) * 10) + ((float(vitesse [2]) - 48)) +  ((float(vitesse [4]) - 48) / 10) +  ((float(vitesse [5]) - 48) / 100) ) * 1.852);
  }
  cl.println(" km/h </td>");
  cl.println("</tr>");
  cl.println("<tr>");
  cl.println("<td class=\"donne1\"> Direction du Vent </td>");
  cl.println("<td class=\"donne1\">");
  cl.print(directionVent [0]);
  cl.print(directionVent [1]);
  cl.print(directionVent [2]);
  cl.print(directionVent [3]);
  cl.print(directionVent [4]);
  cl.println(" ° </td>");
  cl.println("</tr>");
  cl.println("<tr>");
  cl.println("<td class=\"donne1\" rowspan=\"2\"> Température </td>");
  cl.println("<td class=\"donne1\">");
  cl.print(temperature [0]);
  cl.print(temperature [1]);
  cl.print(temperature [2]);
  cl.print(temperature [3]);
  cl.print(temperature [4]);
  cl.println(" °C</td>");
  cl.println("</tr>");
  cl.println("<tr>");
  cl.println("<td class=\"donne1\">");
  if (trameComplete == false) {
    cl.print(" ");
  }
  else {
    cl.print(((((float(temperature [0]) - 48) * 10) + (float(temperature [1]) - 48) + ((float(temperature [3]) - 48) / 10) + ((float(temperature [4]) - 48) / 100)) * 9) / 5 + 32);
  }
  cl.println(" °F </td>");
  cl.println("</tr>");
  cl.println("<tr>");
  cl.println("<td class=\"donne1\"> Pression </td>");
  cl.println("<td class=\"donne1\">");
  cl.print(pression [0]);
  cl.print(pression [1]);
  cl.print(pression [2]);
  cl.print(pression [3]);
  cl.print(pression [4]);
  cl.print(pression [5]);
  cl.print(pression [6]);
  cl.println(" hPa </td>");
  cl.println("</tr>");
  cl.println("<tr>");
  cl.println("<td class=\"donne1\"> Humidité </td>");
  cl.println("<td class=\"donne1\">");
  cl.print(hygrometrie [1]);
  cl.print(hygrometrie [2]);
  cl.print(hygrometrie [3]);
  cl.print(hygrometrie [4]);
  cl.print(hygrometrie [5]);
  cl.println(" % </td>");
  cl.println("</tr>");
  cl.println("</table>");
  cl.println("</div>");
}


void piedpage(EthernetClient cl) {
  cl.println("<div id=\"piedpage\">");
  cl.println("<p> Bonjour. Vous souhaitez visiter le site internet de l' <a  href=\"http://aeroclub.cauchois.free.fr/index.html\" target=\"_blank\">Aéroclub Cauchois </a> ?<br /></p>");
  cl.println("</div>");
  cl.println("</div>");
  cl.println("</body>");
  cl.println("</html>");

}

/*********  Sous Programmes permettant la gestion des Afficheurs *******/

void afficheur(void) {
  etat = 1;
  if (etat == 1) {
    lcd.clear();
    lcd1.clear();
    flag_Afficheur = 0;
    while ( flag_Afficheur == 0 ) {
      lcd.setCursor(0, 0);
      lcd.print("----------------");
      lcd.setCursor(1, 0);
      lcd.print(char(0x08));
      lcd.print(" StationM");
      lcd.print(char(0x09));
      lcd.print("t");
      lcd.print(char(0x09));
      lcd.print("o ");
      lcd.print(char(0x08));
      lcd.cursor_off();
      lcd1.cursor_off();
      lcd1.setCursor(0, 0);
      lcd1.print("A");
      lcd1.print(char(0x09));
      lcd1.print("roClubSaintVal");
      lcd1.setCursor(1, 0);
      lcd1.print("----------------");
      lcd.cursor_off();
      lcd1.cursor_off();
    }
    etat = 0;
  }

  etat = 1;
  if (etat == 1) {
    lcd.clear();
    lcd1.clear();
    flag_Afficheur = 0;
    while ( flag_Afficheur == 0 ) {

      lcd.print("Temp");
      lcd.setCursor(0, 8);
      lcd.print("Pression");
      lcd.setCursor(1, 0);

      lcd.print(temperature [0]);
      lcd.print(temperature [1]);
      lcd.print(temperature [2]);
      lcd.print(temperature [3]);
      lcd.print(temperature [4]);
      lcd.print(char(223));
      lcd.print("C");
      lcd.setCursor(1, 9);

      lcd.print(pression [0]);
      lcd.print(pression [1]);
      lcd.print(pression [2]);
      lcd.print(pression [3]);
      lcd.print(pression [4]);
      lcd.print(pression [5]);
      lcd.print(pression [6]);
      lcd1.setCursor(0, 6);
      lcd1.print("VENT");
      lcd1.setCursor(1, 0);

      lcd1.print(vitesse [0]);
      lcd1.print(vitesse [1]);
      lcd1.print(vitesse [2]);
      lcd1.print(vitesse [3]);
      lcd1.print(vitesse [4]);
      lcd1.print(vitesse [5]);
      lcd1.print("kts");
      lcd1.setCursor(1, 10);

      lcd1.print(directionVent [0]);
      lcd1.print(directionVent [1]);
      lcd1.print(directionVent [2]);
      lcd1.print(directionVent [3]);
      lcd1.print(directionVent [4]);
      lcd1.print(char(223));
      lcd.cursor_off();
      lcd1.cursor_off();
    }
    etat = 0;
  }
  etat = 1;
  if (etat == 1) {
    lcd.clear();
    lcd1.clear();
    flag_Afficheur = 0;
    while (flag_Afficheur == 0) {
      lcd.setCursor(0, 0);
      lcd1.setCursor(0, 0);
      lcd.print("Humidit");
      lcd.print(char(0x09));
      lcd.print(":");

      lcd.setCursor(0, 10);
      lcd.print(hygrometrie [1]);
      lcd.print(hygrometrie [2]);
      lcd.print(hygrometrie [3]);
      lcd.print(hygrometrie [4]);
      lcd.print(hygrometrie [5]);
      lcd.setCursor(0, 15);
      lcd.print("%");
      lcd.setCursor(1, 0);
      lcd.print("bts-sn-yvetot.fr");
      lcd1.setCursor(0, 0);
      lcd1.print("Projet BTS SN EC");
      lcd1.setCursor(1, 0);
      lcd1.print("#");
      lcd1.print("R");
      lcd1.print(char(0x09));
      lcd1.print("mi,");
      lcd1.print("Erwan,");
      lcd1.print("Alex");
      lcd.cursor_off();
      lcd1.cursor_off();
    }
    etat = 0;
  }
}

