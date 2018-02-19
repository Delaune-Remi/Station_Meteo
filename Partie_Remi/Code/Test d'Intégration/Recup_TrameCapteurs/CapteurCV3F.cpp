#include "CapteurCV3F.h"

CapteurCV3F::CapteurCV3F(const char* nom){
	m_DirectionVent=new char [5];
	m_VitesseVent=new char [6];
	m_Temperature=new char [6];
	m_TrameNMEA_MWV=new char [28];
	m_TrameNMEA_XDR=new char [21];
	m_Nom=new char [8];
}

CapteurCV3F::~CapteurCV3F(){
	delete this->m_DirectionVent ;
	delete this->m_VitesseVent ;
	delete this->m_Temperature ;
	delete this->m_TrameNMEA_MWV ;
	delete this->m_TrameNMEA_XDR ;
	delete this->m_Nom ;
}

const char* CapteurCV3F::getDirectionVent(){
  setDirectionVent();
	return (this->m_DirectionVent);
}

const char* CapteurCV3F::getVitesseVent(){
  setVitesseVent();
	return (this->m_VitesseVent);
}

const char* CapteurCV3F::getTemperature(){
	return (this->m_Temperature);
}

bool CapteurCV3F::setDirectionVent(){
	 setTrameNMEA();
  if (validationTrameNMEA_MWV()==true){
    for (int i=0;i<5;i++){
      m_DirectionVent[i]=m_TrameNMEA_MWV[7+i];
    }
    return true;
  }else{
    return false;
  }
}

bool CapteurCV3F::setVitesseVent(){
  setTrameNMEA();
  if (validationTrameNMEA_MWV()==true){
    for (int i=0;i<=5;i++){
      m_VitesseVent[i]=m_TrameNMEA_MWV[15+i];
    }
    return true;
  }else{
    return false;
  }
}

bool CapteurCV3F::setTemperature(){
  
}

void CapteurCV3F::setTrameNMEA (){
	Serial3.begin(4800);
	char trameNMEA [28];
	Serial3.readBytesUntil('\n',trameNMEA,28);
	Serial3.end();
	if (trameNMEA[0] == '$' && trameNMEA[1] == 'I'){
	//  Serial.println("TRAME_MWV");
    for (int i=0;i<=27;i++)
    {
 //  Serial.println(trameNMEA[i]);
      m_TrameNMEA_MWV[i] = trameNMEA[i];
    }
	}
	
	if (trameNMEA[0] == '$' && trameNMEA[1] == 'W'){
		for (int i=0;i<=20;i++)
    {
      m_TrameNMEA_XDR[i] = trameNMEA[i];
    }
	}
}

const char* const CapteurCV3F::getTrameNMEA_MWV(){
	setTrameNMEA();
	return m_TrameNMEA_MWV;
}

const char* const CapteurCV3F::getTrameNMEA_XDR(){
  setTrameNMEA();
  return m_TrameNMEA_XDR;
}

bool CapteurCV3F::validationTrameNMEA_MWV(){
  if (m_TrameNMEA_MWV[24] == 'A'){
    return true;
  }else{
    return false;
  }
}

