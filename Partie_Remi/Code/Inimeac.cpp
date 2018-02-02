#include "Inimeac.h"

Inimeac::Inimeac(){
	this->m_Trame=new char [101];
}

Inimeac::~Inimeac(){
	delete [] (this->m_Trame);
}