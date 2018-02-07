#include "CapteurCV3F.h"

CapteurCV3F::CapteurCV3F(const char* nom){
	m_DirectionVent=new char [6];
	m_VitesseVent=new char [7];
	m_Temperature=new char [6];
	m_TrameNMEA_MWV=new char [26];
	m_TrameNMEA_XDR=new char [22];
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
	setTrameNMEA();
}

void CapteurCV3F::setTrameNMEA (){
	Serial3.begin(4800);
	Serial3.read(); 					// Lecture de RX3 et envoie au moniteur serie
}