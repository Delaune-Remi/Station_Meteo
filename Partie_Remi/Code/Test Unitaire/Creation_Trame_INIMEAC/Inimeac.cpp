#include "Inimeac.h"

Inimeac::Inimeac(){
	this->m_Trame=new char [104];
  this->m_TrameDecode=new char [94];
}

Inimeac::~Inimeac(){
	delete (this->m_Trame);
  delete (this->m_TrameDecode);
}

char Inimeac::setTrame (const char* const VitesseVent,const char* DirectionVent,const char* Temperature,const char* Hygrometrie, const char* Pression, const char* Validite){
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
	if (Validite == 'Y'){
		return 'V';
	}else{
		return 'E';
	}
}

char* Inimeac::getTrame (){
	return (this->m_Trame);
}

char Inimeac::decodeTrameINIMEAC( char* const VitesseVent,char* const DirectionVent,char* const Temperature, char* const Hygrometrie,char* const Pression){
  if ( Serial2.find("&#!INIMEAC") == true){
    Serial2.readBytes(this->m_TrameDecode,94);
    Serial.write (this->m_TrameDecode);
  }
  if (this->m_TrameDecode[91] == 'Y'){
    VitesseVent[0]= m_TrameDecode[7];
    VitesseVent[1]= this->m_TrameDecode[8];
    VitesseVent[2]= this->m_TrameDecode[9];
    VitesseVent[3]= this->m_TrameDecode[10];
    VitesseVent[4]= this->m_TrameDecode[11];
    VitesseVent[5]= this->m_TrameDecode[12];

    DirectionVent[0]= this->m_TrameDecode[25];
    DirectionVent[1]= this->m_TrameDecode[26];
    DirectionVent[2]= this->m_TrameDecode[27];
    DirectionVent[3]= this->m_TrameDecode[28];
    DirectionVent[4]= this->m_TrameDecode[29];

    Temperature[0]= this->m_TrameDecode[40];
    Temperature[1]= this->m_TrameDecode[41];
    Temperature[2]= this->m_TrameDecode[42];
    Temperature[3]= this->m_TrameDecode[43];
    Temperature[4]= this->m_TrameDecode[44];
    Temperature[5]= this->m_TrameDecode[45];

    Hygrometrie[0]= this->m_TrameDecode[56];
    Hygrometrie[1]= this->m_TrameDecode[57];
    Hygrometrie[2]= this->m_TrameDecode[58];
    Hygrometrie[3]= this->m_TrameDecode[59];
    Hygrometrie[4]= this->m_TrameDecode[60];
    Hygrometrie[5]= this->m_TrameDecode[61];

    Pression[0]= this->m_TrameDecode[72];
    Pression[1]= this->m_TrameDecode[73];
    Pression[2]= this->m_TrameDecode[74];
    Pression[3]= this->m_TrameDecode[75];
    Pression[4]= this->m_TrameDecode[76];
    Pression[5]= this->m_TrameDecode[77];
    Pression[6]= this->m_TrameDecode[78];
    
    return 'V';
  }

  return 'E';
}

/*
Exemple de Trame INIMEAC:

&#!INIMEAC;!SWD::000.00::KTS;!DWD::000.0::D;!TMP::000.00::C;!RHY::000.00::%;!RPA::1013.25::hPa;!VAD::N:!

*/
