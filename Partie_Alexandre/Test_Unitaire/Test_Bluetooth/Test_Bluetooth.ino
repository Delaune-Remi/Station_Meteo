#include <Ethernet.h>
#include <SPI.h>
#include <Wire.h>
#include "CLCD.h"
#include "I2C.h"
#include "newChar.h"
#include "Inimeac.h"

CLCD lcd(0x02,16,2);
CLCD lcd1(0x01,16,2);
Inimeac Trame;
char vitesse [5];
char directionVent [5];
char temperature [6];
char hygrometrie [6];
char pression [6];





byte mac[] = {0x90, 0x98, 0x97, 0x00, 0x05, 0xAB};
byte ip[] = {192, 168,  190,  123};
EthernetServer serveur(80);


String inputString = "";         // a String to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup() {
  initI2C(0);
  lcd.init();
  lcd1.init();
  Serial3.begin(9600);
  Serial.begin(9600); 
  inputString.reserve(200);
  if (Ethernet.begin(mac) == 0) {
    //Serial.println("Impossible de se connecter au serveur DHCP");
    Ethernet.begin(mac, ip);
  }
 
}

void loop() {
//  siteWeb();

  if (stringComplete) {
    Serial.println(inputString);
    Trame.decodeTrameINIMEAC(inputString,true,vitesse,directionVent,temperature,hygrometrie,pression);
    // clear the string:
    inputString = "";
    stringComplete = false;
   // afficheur();
  }
  
    
}

void serialEvent3() {
  while (Serial3.available()) {
    // get the new byte:
    char inChar = (char)Serial3.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
  Serial3.flush();
}





/*void siteWeb() {
  
  EthernetClient client = serveur.available(); //on écoute le port
  if (client) { //si client connecté
    //Serial.println("\nClient en ligne\n"); //on le dit...
    if (client.connected()) { // si le client est en connecté
      pageWeb(client); // fonction pour l'entête de la page HTML
      //Serial.println("Fin de communication avec le client\n");
      client.stop(); //on déconnecte le client
    }
  }
}

void pageWeb(EthernetClient cl) {
  
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
    
      //CSS
      
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
 
  //Corps page
  
    cl.println("<body>");
      cl.println("<div id=\"CentrePage\">");
      
          //Baniere
          
      cl.println("<table id=\"entete\">");
        cl.println("<tr>");
          cl.println("<td><h1>STATION MÉTÉO <br/>AÉRO-CLUB SAINT-VALÉRY</h1></td>");
          cl.println("<td><p><a href=\"http://aeroclub.cauchois.free.fr/index.html\" target=\"_blank\"><img src=\"http://aeroclub.cauchois.free.fr/images/ACC_sticker.png\" alt=\"Logo de l'aéroclub\" /></a></p></td>");
        cl.println("</tr>");
      cl.println("</table>");
      
          //Tableau de donnée
      
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
            cl.println(" kts </td>");
          cl.println("</tr>");
          cl.println("<tr>");
              cl.println("<td class=\"donne1\">");
                    if (vitesse [0]=='0'){
                        vitesse [0]=' ';
                        cl.print((((float(vitesse [1])-48)) +  ((float(vitesse [3])-48)/10) +  ((float(vitesse [4])-48)/100) )*1.852);
                    }
                    else{
                    cl.print((((float(vitesse [0])-48)*10) + ((float(vitesse [1])-48)) +  ((float(vitesse [3])-48)/10) +  ((float(vitesse [4])-48)/100) )*1.852); 
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
                    cl.print(((((float(temperature [0])-48)*10) + (float(temperature [1])-48) + ((float(temperature [3])-48)/10) + ((float(temperature [4])-48)/100))*9)/5+32); 
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
      cl.println("<div id=\"piedpage\">");
        cl.println("<p> Bonjour. Vous souhaitez visiter le site internet de l' <a  href=\"http://aeroclub.cauchois.free.fr/index.html\" target=\"_blank\">Aéroclub Cauchois </a> ?<br /></p>");
      cl.println("</div>");
      
      cl.println("</div>");
    cl.println("</body>");
  cl.println("</html>");
}

void afficheur(void){
                            lcd.setCursor(0,0);
                            lcd.print(temperature [0]);
                            lcd.print(temperature [1]);
                            lcd.print(temperature [2]);
                            lcd.print(temperature [3]);
                            lcd.print(char(223));
                            lcd.print("C");

                            lcd.setCursor(1,0);
                            lcd.print(pression [0]);
                            lcd.print(pression [1]);
                            lcd.print(pression [2]);
                            lcd.print(pression [3]);
                            lcd.print(pression [4]);
                            lcd.print("hPa");

                            lcd.setCursor(0,9);
                            lcd.print(hygrometrie [1]);
                            lcd.print(hygrometrie [2]);
                            lcd.print(hygrometrie [3]);
                            lcd.print(hygrometrie [4]);
                            lcd.print("%");
                            lcd.cursor_off();

                            lcd1.setCursor(0,0);
                            lcd1.print(vitesse [0]);
                            lcd1.print(vitesse [1]);
                            lcd1.print(vitesse [2]);
                            lcd1.print(vitesse [3]);
                            lcd1.print(vitesse [4]);
                            lcd1.print("kts");

                            lcd1.setCursor(1,0);
                            lcd1.print(directionVent [0]);
                            lcd1.print(directionVent [1]);
                            lcd1.print(directionVent [2]);
                            lcd1.print(directionVent [3]);
                            lcd1.print(directionVent [4]);
                            lcd1.print(char(223));
                            lcd1.cursor_off();

}
*/
