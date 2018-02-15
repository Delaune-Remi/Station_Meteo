#include "Inimeac.h"

Inimeac::Inimeac(){
	this->m_Trame=new char [104];
}

Inimeac::~Inimeac(){
	delete (this->m_Trame);
}

char Inimeac::setTrame (const char* VitesseVent,const char* DirectionVent,const char* Temperature,const char* Hygrometrie, const char* Pression, const char* Validite){
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

char Inimeac::decodeTrameINIMEAC(){
  
}

