#include "rotacaoV.h"

using namespace std;

RotacaoV::RotacaoV() {
	this->rot.fill(0.0f);
}

void RotacaoV::setRot( array<float, 4> newrot ) {
	this->rot = newrot;
}

void RotacaoV::aplica() {
	glRotatef(this->rot[0], this->rot[1], this->rot[2], this->rot[3]);
}
