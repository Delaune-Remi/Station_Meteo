#ifndef _CAPTEURCV3F_H													//Permet d'eviter les inclusions multiples
#define _CAPTEURCV3F_H

#if	defined(ARDUINO) && ARDUINO >= 100									// Permet de rendre compatible le programme pour toute les version d'arduino
#include <Arduino.h> 
#else
#include <WProgram.h>
#endif

class CapteurCV3F {
	private:
		char* m_DirectionVent;										                       // Variable permettant de stocker la direction du vent
		char* m_VitesseVent;											                       // Variable permettant de stocker la vitesse du vent
		char* m_Temperature;											                       // Variable permettant de stocker la temperature de l'air
		char* m_TrameNMEA_MWV;											                     // Variable permettant de stocker la trame NMEA contenant les informations sur la vitesse et la direction du vent
		bool m_TrameNMEA_MWV_Valide;								                   // Variable permettant de verifier la validite de la trame NMEA_MWV
		char* m_TrameNMEA_XDR;											                     // Variable permettant de stocker la trame NMEA contenant les informations sur la temperature de l'air
		char* m_Nom;													                           // Variable permettant de stocker le nom du capteur
		bool setDirectionVent();										                   // Fonction permettant de stocker dans la variable m_DirectionVentVent la valeur de la direction du vent issue de la trame NMEA_MWV
		bool setVitesseVent();											            // Fonction permettant de stocker dans la variable m_VitesseVent la valeur de la vitesse du vent issue de la trame NMEA_MWV
		bool setTemperature();											// Fonction permettant de stocker dans la variable m_Temperature la valeur de la temperature issue de la trame NMEA_XDR
		void setTrameNMEA();											
		bool validationTrameNMEA_MWV(const char* const m_TrameNMEA_MWV);// Fonction permettant de savoir si la trame NMEA_MWV est correct (true or false)
	public:
		CapteurCV3F(const char* nom = "CAPTEUR");			// Constructeur permettant d'initialiser les valeurs des variables
		~CapteurCV3F();													      // Destructeur permettant de liberer l'espace memoire 
		const char* getDirectionVent();								// Fonction permettant de recuperer la direction du vent 
		const char* getVitesseVent();									// Fonction permettant de recuperer la vitesse du vent 
		const char* getTemperature();									// Fonction permettant de recuperer la temperature a l'exterieur
		const char* const getTrameNMEA_MWV();         //
    const char* const getTrameNMEA_XDR();         //
};

#endif
