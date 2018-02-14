#ifndef _TRAMEINIMEAC_H
#define _TRAMEINIMEAC_H

#if	defined(ARDUINO) && ARDUINO >= 100									// Permet de rendre compatible le programme pour toute les version d'arduino
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <String.h>

class Inimeac{
	private:
		char* m_Trame;
		char m_Debug;
	public:
		Inimeac();
		~Inimeac();
		char setTrame(const char* VitesseVent="000.00", const char* DirectionVent="000.0", const char* Temperature="000.00",const char* Hygrometrie="000.00", const char* Pression="1013.25", const char* Validite="N");
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
};

#endif

/*
Exemple de Trame INIMEAC:

&#!INIMEAC;!SWD::000.00::KTS;!DWD::000.0::D;!TMP::000.00::C;!RHY::000.00::%;!RPA::1013.25::hPa;!VAD::N:!

*/