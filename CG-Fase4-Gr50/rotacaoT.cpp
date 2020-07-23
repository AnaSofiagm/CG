#include "rotacaoT.h"

RotacaoT::RotacaoT() {
	this->rot.fill(0.0f);
	this->segundos = 1;
	this->voltas = 0;
}

void RotacaoT::setRot( array<float, 3> axs ) {
	this->rot[1] = axs[0];
	this->rot[2] = axs[1];
	this->rot[3] = axs[2];
}

void RotacaoT::setGraus( int tempoVolta ) {
	this->rot[0] = 360.0f / tempoVolta;
	this->segundos = tempoVolta;
}

void RotacaoT::aplica( bool updt ) {
	
	if( updt ) {
		this->voltas = (this->voltas + 1) % this->segundos;
	}

	glRotatef(this->voltas * rot[0], rot[1], rot[2], rot[3]);
}
