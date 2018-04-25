/********  Librairie pour la gestion du site Web *******/ 
                       
  #include <Ethernet.h>                
  #include <SPI.h>   
  #include <SD.h>

/********  Librairie pour la gestion des afficheurs *******/                    

  #include <Wire.h>
  #include "CLCD.h"
  #include "I2C.h"
  #include "newChar.h"

/********  Librairie pour la gestion de la trame *******/ 
  
  #include "Inimeac.h"

// [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
// []
// []        PROGRAMME PRINCIPAL CREE PAR ALEXANDRE LEBRUN
// []
// []  
// []                PROJET STATION METEO (2018-06)
// []
// [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]

/********  Creation des variables afficheurs *******/   

  CLCD lcd(0x02,16,2); /* Creation du premiere afficheur avec parametre (adresse du module CLCD, nombre de caractere par ligne, nombre de ligne) */ 
  CLCD lcd1(0x01,16,2); /* Creation du deuxieme afficheur avec parametre (adresse du module CLCD, nombre de caractere par ligne, nombre de ligne) */

/********  Creation de la trame *******/  
  
  Inimeac Trame;  /* Creation de la trame de type Inimeac cette trame hérite de la bibliotheque de Inimeac.h cree par Remi */
  
  char vitesse [5]; /* Creation d'un tableau de caractere pour stocker la donnee vitesse */
  char directionVent [5]; /* Creation d'un tableau de caractere pour stocker la donnee directionVent */
  char temperature [6]; /* Creation d'un tableau de caractere pour stocker la donnee temperature */
  char hygrometrie [7]; /* Creation d'un tableau de caractere pour stocker la donnee hygrometrie */
  char pression [7]; /* Creation d'un tableau de caractere pour stocker la donnee pression */

/********  Creation du serveur web *******/  
  
  byte mac[] = {0x90, 0x98, 0x97, 0x00, 0x05, 0xAB}; /* Creation de l'adresse MAC defini par moi-meme */
  byte ip[] = {192, 168,  190,  123}; /* Creation de l'adresse IP static défini par moi-meme */
  EthernetServer serveur(80); /* Creation d'un server qui ecoute sur le port 80 ( HTTP ) */ 

/********  Creation de la chaine contenant cette trame *******/  
  
  String trameINIMEAC = ""; /* Creation d'une chaine pour contenir les données entrantes */
  boolean trameComplete = false; /* Si la chaîne est complete */

/********  Fonction setup pour les initialisations *******/  
  
  void setup() {
    initI2C(0); /* Initialisation de la vitesse du bus I2C à 0 */
    lcd.init(); /* Initialisation du premiere afficheur I2C */
    lcd1.init(); /* Initialisation du deuxieme afficheur I2C */
    Serial3.begin(9600); /* Initialisation du port série 3 a 9600 bauds */
    Serial.begin(9600); /* Initialisation du port série a 9600 bauds */
    //if (Ethernet.begin(mac) == 0){ /* Condition qui verifie si le serveur DHCP n'est pas present */
        Ethernet.begin(mac, ip); /* Si ce n'est pas le cas le serveur passe en IP¨ defini ci-dessus */
   // }
    Serial.println("adresse ip serveur :");
    Serial.println(Ethernet.localIP()); //on affiche l'adresse IP de la connexion
    serveur.begin();
    trameINIMEAC.reserve(104); /* Reservation de 200 caractere maximum pour la trame */
  }

/********  Fonction loop pour le programme principal *******/  
  
  void loop() {

    siteWeb(); /* Fonction qui integre le siteWeb dans le programme */ 
    
    if (trameComplete) { /* Si la trame est complete */
        Serial.println(trameINIMEAC); /* On affiche cette trame sur le moniteur serie de l'arduino */
        Trame.decodeTrameINIMEAC(trameINIMEAC,true,vitesse,directionVent,temperature,hygrometrie,pression); /* Permet de decoder la trame avec les les differents parametres */
        trameINIMEAC = ""; /* Remet la chaine à zero */
        trameComplete = false; /* Donc trame complete est fausse */
        afficheur(); /* Fonction qui integre les afficheurs dans le programme */
    }   
  }

/********  Fonction serialEvent3 permettant de recuperer la trame *******/
  
  void serialEvent3() {
    while (Serial3.available()) { /* Tant que le port serie 3 est disponible */
      char caractere = (char)Serial3.read(); /* On prend les nouveaux octets */
      trameINIMEAC += caractere; /* On ajoute les nouveaux octets dans la variable trameINIMEAC */
      if (caractere == '\n') {  /* Si le prochain caractere est un caractere de nouvelle ligne */
        trameComplete = true;  /* on met la trameComplete a vrai */
      }
    }
    Serial3.flush(); /* On vide le buffer du port serie 3 */
  }

/********  Fonction siteWeb regroupant la pageWeb et le serveur *******/  

  void siteWeb() {
    
    EthernetClient client = serveur.available(); /* on écoute le port */
    if (client) { /* si client connecté */
      if (client.connected()) { /* si le client est en connecté */
        pageWeb(client); /* fonction pour l'entête de la page HTML */
        client.stop(); /* on déconnecte le client */
      }
    }
  }

/********  Fonction pageWeb qui regroupe l'HTML et le CSS *******/   
  
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
              if ((vitesse [0]=='0' || vitesse [0]==' ') && ( vitesse [1]=='0' || vitesse [1]==' ')){
                vitesse [0]=' ';
                vitesse [1]=' ';
                cl.print(vitesse [0]);
                cl.print(vitesse [1]);
                cl.print(vitesse [2]);
                cl.print(vitesse [3]);
                cl.print(vitesse [4]);
                cl.print(vitesse [5]);
              }else if (vitesse [0]=='0' || vitesse [0]==' '){
                vitesse [0]=' ';
                cl.print(vitesse [0]);
                cl.print(vitesse [1]);
                cl.print(vitesse [2]);
                cl.print(vitesse [3]);
                cl.print(vitesse [4]);
                cl.print(vitesse [5]);
              }
              cl.println(" kts </td>");
            cl.println("</tr>");
            cl.println("<tr>");
                cl.println("<td class=\"donne1\">");
                      if (vitesse [1]==' '){
                          cl.print((((float(vitesse [2])-48)) +  ((float(vitesse [4])-48)/10) +  ((float(vitesse [5])-48)/100) )*1.852);
                      }
                      else{
                      cl.print((((float(vitesse [1]-48)*10)) + ((float(vitesse [2])-48)) +  ((float(vitesse [4])-48)/10) +  ((float(vitesse [5])-48)/100) )*1.852); 
                      }
                cl.println(" km/h </td>");
            cl.println("</tr>");
            cl.println("<tr>");
              cl.println("<td class=\"donne1\"> Direction du Vent </td>");
              cl.println("<td class=\"donne1\">");
              if (directionVent [0]=='0' || directionVent [0]==' '){
                directionVent [0]= ' ';
                cl.print(directionVent [0]);
                cl.print(directionVent [1]);
                cl.print(directionVent [2]);
              }else{
                cl.print(directionVent [0]);
                cl.print(directionVent [1]);
                cl.print(directionVent [2]);
              }
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
              if (pression [0]!='1'){
                if (pression [0]==':'){
                  if (pression [1]=='1'){
                    cl.print(pression [1]);
                    cl.print(pression [2]);
                    cl.print(pression [3]);
                    cl.print(pression [4]);
                    cl.print(pression [5]);
                    cl.print(pression [6]);
                    cl.print(pression [7]);
                  }else{
                    cl.print(pression [1]);
                    cl.print(pression [2]);
                    cl.print(pression [3]);
                    cl.print(pression [4]);
                    cl.print(pression [5]);
                    cl.print(pression [6]);
                }
                }else{
                cl.print(pression [0]);
                cl.print(pression [1]);
                cl.print(pression [2]);
                cl.print(pression [3]);
                cl.print(pression [4]);
                cl.print(pression [5]);
                }
              }else{
                cl.print(pression [0]);
                cl.print(pression [1]);
                cl.print(pression [2]);
                cl.print(pression [3]);
                cl.print(pression [4]);
                cl.print(pression [5]);
                cl.print(pression [6]);
              }
              cl.println(" hPa </td>");
            cl.println("</tr>");
            cl.println("<tr>");
              cl.println("<td class=\"donne1\"> Humidité </td>");
              cl.println("<td class=\"donne1\">");
              if (hygrometrie [1]!='1'){
                cl.print(hygrometrie [1]);
                cl.print(hygrometrie [2]);
                cl.print(hygrometrie [3]);
                cl.print(hygrometrie [4]);
                cl.print(hygrometrie [5]);
              }else{
                cl.print(hygrometrie [1]);
                cl.print(hygrometrie [2]);
                cl.print(hygrometrie [3]);
                cl.print(hygrometrie [4]);
                cl.print(hygrometrie [5]);
                cl.print(hygrometrie [6]);
              }
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

/********  Fonction afficheur pour l'affichage des deux ecrans I2C *******/ 
  
  void afficheur(void){
                              
    lcd.setCursor(0,0);
    lcd.print(temperature [0]);
    lcd.print(temperature [1]);
    lcd.print(temperature [2]);
    lcd.print(temperature [3]);
    lcd.print(char(223));
    lcd.print("C");


    if (pression [0]!='1'){
      if (pression [0]==':'){
        if (pression [1]=='1'){
          lcd.setCursor(1,0);
    lcd.print(pression [1]);
    lcd.print(pression [2]);
    lcd.print(pression [3]);
    lcd.print(pression [4]);
    lcd.print(pression [5]);
    lcd.print(pression [6]);
    lcd.print("hPa");
    
        }else{
    lcd.setCursor(1,0);
    lcd.print(pression [1]);
    lcd.print(pression [2]);
    lcd.print(pression [3]);
    lcd.print(pression [4]);
    lcd.print(pression [5]);
    lcd.print("hPa");
        }
    }else{
        lcd.setCursor(1,0);
        lcd.print(pression [0]);
        lcd.print(pression [1]);
        lcd.print(pression [2]);
        lcd.print(pression [3]);
        lcd.print(pression [4]);
        lcd.print("hPa");
      }
    }else{
       lcd.setCursor(1,0);
        lcd.print(pression [0]);
        lcd.print(pression [1]);
        lcd.print(pression [2]);
        lcd.print(pression [3]);
        lcd.print(pression [4]);
        lcd.print(pression [5]);
        lcd.print("hPa");
       }
    
    
    if (hygrometrie [1]!='1'){
    lcd.setCursor(0,11);
    lcd.print(hygrometrie [1]);
    lcd.print(hygrometrie [2]);
    lcd.print(hygrometrie [3]);
    lcd.print(hygrometrie [4]);
    lcd.print("%");
    lcd.cursor_off();
    }else{
      lcd.setCursor(0,10);
      lcd.print(hygrometrie [1]);
      lcd.print(hygrometrie [2]);
      lcd.print(hygrometrie [3]);
      lcd.print(hygrometrie [4]);
      lcd.print(hygrometrie [5]);
      lcd.print("%");
      lcd.cursor_off();
    }

    if ((vitesse [0]=='0' || vitesse [0]==' ') && ( vitesse [1]=='0' || vitesse [1]==' ')){
      vitesse [0]=' ';
      vitesse [1]=' ';
      lcd1.setCursor(0,0);
      lcd1.print(vitesse [2]);
      lcd1.print(vitesse [3]);
      lcd1.print(vitesse [4]);
      lcd1.print("kts");
      }else if (vitesse [0]=='0' || vitesse [0]==' '){
        vitesse [0]=' ';
        lcd1.setCursor(0,0);
        lcd1.print(vitesse [1]);
        lcd1.print(vitesse [2]);
        lcd1.print(vitesse [3]);
        lcd1.print(vitesse [4]);
        lcd1.print(vitesse [5]);
        lcd1.print("kts");
      }
    
      if (directionVent [0]=='0' || directionVent [0]==' '){
        directionVent [0]= ' ';
        lcd1.setCursor(1,0);
        lcd1.print(directionVent [1]);
        lcd1.print(directionVent [2]);
        lcd1.print(char(223));
        lcd1.print(" ");
        lcd1.cursor_off();
        }else{
          lcd1.setCursor(1,0);
          lcd1.print(directionVent [0]);
          lcd1.print(directionVent [1]);
          lcd1.print(directionVent [2]);
          lcd1.print(char(223));
          lcd1.cursor_off();
        }
}
