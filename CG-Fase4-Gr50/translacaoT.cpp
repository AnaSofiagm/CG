#include "translacaoT.h"

using namespace std;

TranslacaoT::TranslacaoT() {
	this->voltas = 0;
}

void TranslacaoT::setCurva( vector<Pontos> pntCnt, int tempoVolta ) {
	 
	
	Pontos aux;
	float tseg = 1.0f / tempoVolta;

	if( !pntCnt.empty() ) {
		for(int i = 0; i < tempoVolta; i++) {
			getGlobalCatmullRomPoint(i * tseg, pntCnt.data(), pntCnt.size(), &aux);	
			this->pntsCurva.push_back(aux);		
		}
	}
}

void TranslacaoT::aplica( bool updt ) {
	
	Pontos aux;
	if( !this->pntsCurva.empty() ) {
		if( updt ) {
			this->voltas = ( this->voltas + 1 ) % this->pntsCurva.size();
		}
		aux = this->pntsCurva[this->voltas];
		glTranslatef(aux.a, aux.b, aux.c);
	}
}
