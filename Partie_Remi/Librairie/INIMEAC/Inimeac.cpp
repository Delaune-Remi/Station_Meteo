#include "Inimeac.h"

Inimeac::Inimeac(){
	this->m_Trame=new char [104];
  this->m_TrameBluetooth=new char [65];

}

Inimeac::~Inimeac(){
	delete (m_Trame);
  delete (m_TrameBluetooth);
}

char Inimeac::setTrame (const char* VitesseVent,const char* DirectionVent,const char* Temperature,const char* Hygrometrie, const char* Pression, const char* Validite){


  /* Trame realiser pour le site Web et l'afficheur d'Alexandre */

	strcpy (this->m_Trame,"&#!INIMEAC");
	strcat (this->m_Trame,";!SWD::");
	strcat (this->m_Trame,VitesseVent);
	strcat (this->m_Trame,"::KTS");
	strcat (this->m_Trame,";!DWD::");
	strcat (this->m_Trame,DirectionVent);
	strcat (this->m_Trame,"::D");
	strcat (this->m_Trame,";!TMP::");
	strcat (this->m_Trame,Temperature);
	strcat (this->m_Trame,"::C");
	strcat (this->m_Trame,";!RHY::");
	strcat (this->m_Trame,Hygrometrie);
	strcat (this->m_Trame,"::%");
	strcat (this->m_Trame,";!RPA::");
	strcat (this->m_Trame,Pression);
	strcat (this->m_Trame,"::hPa");
	strcat (this->m_Trame,";!VAD::");
	strcat (this->m_Trame,Validite);
	strcat (this->m_Trame,":!");

  /* Trame realiser pour l'application d'Erwan */

  strcpy (this->m_TrameBluetooth,"!");
  strcat (this->m_TrameBluetooth,VitesseVent);
  strcat (this->m_TrameBluetooth,"!");
  strcat (this->m_TrameBluetooth,DirectionVent);
  strcat (this->m_TrameBluetooth,"!");
  strcat (this->m_TrameBluetooth,Temperature);
  strcat (this->m_TrameBluetooth,"!");
  strcat (this->m_TrameBluetooth,Hygrometrie);
  strcat (this->m_TrameBluetooth,"!");
  strcat (this->m_TrameBluetooth,Pression);

	if (Validite == "Y"){
		return 'V';
	}else{
		return 'E';
	}
}

char* Inimeac::getTrame (){
	return (this->m_Trame);
}

char* Inimeac::getTrameBluetooth(){
  return (this->m_TrameBluetooth);
}

char Inimeac::decodeTrameINIMEAC(String m_TrameDecode,bool trameComplete,char* const VitesseVent, char* const DirectionVent, char* const Temperature, char* const Hygrometrie,char* const Pression){

  if (trameComplete==true) {

    Serial.println(m_TrameDecode);

    VitesseVent[0]= m_TrameDecode[17];
    VitesseVent[1]= m_TrameDecode[18];
    VitesseVent[2]= m_TrameDecode[19];
    VitesseVent[3]= m_TrameDecode[20];
    VitesseVent[4]= m_TrameDecode[21];
    VitesseVent[5]= m_TrameDecode[22];

    DirectionVent[0]= m_TrameDecode[36];
    DirectionVent[1]= m_TrameDecode[37];
    DirectionVent[2]= m_TrameDecode[38];
    DirectionVent[3]= m_TrameDecode[39];
    DirectionVent[4]= m_TrameDecode[40];

    Temperature[0]= m_TrameDecode[52];
    Temperature[1]= m_TrameDecode[53];
    Temperature[2]= m_TrameDecode[54];
    Temperature[3]= m_TrameDecode[55];
    Temperature[4]= m_TrameDecode[56];

    Hygrometrie[1]= m_TrameDecode[25];
    Hygrometrie[2]= m_TrameDecode[26];
    Hygrometrie[3]= m_TrameDecode[27];
    Hygrometrie[4]= m_TrameDecode[28];
    Hygrometrie[5]= m_TrameDecode[29];

    if (m_TrameDecode[40] != '1'){m_TrameDecode[40]='0';}

    Pression[0]= m_TrameDecode[40];
    Pression[1]= m_TrameDecode[41];
    Pression[2]= m_TrameDecode[42];
    Pression[3]= m_TrameDecode[43];
    Pression[4]= m_TrameDecode[44];
    Pression[5]= m_TrameDecode[45];
    Pression[6]= m_TrameDecode[46];

    trameComplete=false;
    m_TrameDecode="";
  }
}

/*
Exemple de Trame INIMEAC:

&#!INIMEAC;!SWD::000.00::KTS;!DWD::000.0::D;!TMP::00.00::C;!RHY::000.00::%;!RPA::1013.25::hPa;!VAD::N:!

*/
