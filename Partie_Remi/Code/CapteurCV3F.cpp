#include "CapteurCV3F.h"

CapteurCV3F::CapteurCV3F(const char* nom){
	m_DirectionVent=new char [6];
	m_VitesseVent=new char [7];
	m_Temperature=new char [6];
	m_TrameNMEA_MWV=new char [30];
	m_TrameNMEA_XDR=new char [30];
	m_Nom=new char [8];
}

CapteurCV3F::~CapteurCV3F(){
	delete m_DirectionVent [];
	delete m_VitesseVent [];
	delete m_Temperature [];
	delete m_TrameNMEA_MWV [];
	delete m_TrameNMEA_XDR [];
	delete m_Nom [];
}

const char* CapteurCV3F::getDirectionVent(){
	return (this->m_DirectionVent);
}

const char* CapteurCV3F::getVitesseVent(){
	return (this->m_VitesseVent);
}

const char* CapteurCV3F::getTemperature(){
	return (this->m_Temperature);
}

bool CapteurCV3F::setDirectionVent(){
	
}

void CapteurCV3F::setTrameNMEA (){
	Serial3.begin(4800);
	
	char trameNMEA [30];
	Serial3.readBytesUntil('\n',trameNMEA,30);
	
	trameNMEA[29]='\0';
	
	if (trameNMEA[0] == '$' && trameNMEA[1] == 'I'){
		this->m_TrameNMEA_MWV = trameNMEA;
	}
	
	if (trameNMEA[0] == '$' && trameNMEA[2] == 'I'){
		this->m_TrameNMEA_XDR = trameNMEA;
	}
}

const char* const CapteurCV3F::getTrameNMEA_MWV(){
	setTrameNMEA();
	return this->m_TrameNMEA_MWV;
}