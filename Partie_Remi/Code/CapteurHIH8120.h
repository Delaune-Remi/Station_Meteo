#ifndef _CAPTEURHIH8120_H
#define _CAPTEURHIH8120_H

#if	defined(ARDUINO) && ARDUINO >= 100		// Permet de rendre compatible le programme pour toute les version d'arduino
#include <Arduino.h> 
#else
#include <WProgram.h>
#endif

class CapteurHIH8120 {						// Objet CapteurHIH8120
	private:
		int reading;						// Variable membre permettant de stocker la valeurs du capteur
		double humidity;					// Variable membre permettant de stocker la valeur du taux d'humidite
		double temperature;					// Variable membre permettant de stocker la valeur de la temperature
		void setTemperature(double&);		// Fonction membre permettant de stocker la temperature dans temperature
		void setHumidity (double&);			// Fonction membre permettant de stocker le taux d'Humidite dans humidity
	public:
		CapteurHIH8120 ();
		double getTemperature();			// Fonction membre permettant de lire la valeur de la temperature
		double getHumidite();				// Fonction membre permettant de lire la valeur de l'humidite
};
#endf