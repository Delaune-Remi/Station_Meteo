#include "CapteurCV3F.h"

CapteurCV3F::CapteurCV3F(const char* nom){
	m_DirectionVent=new char [6];
	m_VitesseVent=new char [7];
	m_Temperature=new char [6];
	m_TrameNMEA_MWV=new char [26];
}

CapteurCV3F::~CapteurCV3F(){
	delete m_DirectionVent [];
	delete m_VitesseVent [];
	delete m_Temperature [];
	delete m_TrameNMEA_MWV [];
}
