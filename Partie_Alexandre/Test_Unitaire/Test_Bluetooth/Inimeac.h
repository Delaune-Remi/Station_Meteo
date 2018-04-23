#ifndef _TRAMEINIMEAC_H
#define _TRAMEINIMEAC_H

#if	defined(ARDUINO) && ARDUINO >= 100									// Permet de rendre compatible le programme pour toute les version d'arduino
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <string.h>

class Inimeac{
	private:
		char* m_Trame;
		char m_Debug;
	public:
		Inimeac();
		~Inimeac();
		char setTrame(const char* VitesseVent="000.00", const char*  DirectionVent="000.0", const char*  Temperature="00.00",const char*  Hygrometrie="000.00", const char*  Pression="1013.25", const char*  Validite="N");
		/*
		 * La fonction renvoie un caractere referencant si il y a eu un probleme
		 * ex: 
		 *	- V pour trame bien creer
		 *	- E pour trame erronnee
		 */
		 char* getTrame();
		/*
		 * La fonction permet de recuperer la trame INIMEAC
		 */
     char decodeTrameINIMEAC( String trame,bool trameComplete,char* const vitesse,char* const directionVent,char* const temperature,char* const hygrometrie,char* const pression);
     /*
      * La fonction permet de decoder la trame INMEAC reçue
      * Elle accepte 6 parametres qui permettent de stocker la valeur des donnees.  
      * La fonction renvoie un caractere referencant si il y a eu un probleme
     * ex: 
     *  - V pour trame bien decoder
     *  - E pour trame erronnee
      */
};

#endif

/*
Exemple de Trame INIMEAC:

&#!INIMEAC;!SWD::000.00::KTS;!DWD::000.0::D;!TMP::00.00::C;!RHY::000.00::%;!RPA::1013.25::hPa;!VAD::N:!

*/
