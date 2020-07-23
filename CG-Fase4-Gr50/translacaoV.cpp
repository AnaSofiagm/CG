#include "translacaoV.h"

using namespace std;

TranslacaoV::TranslacaoV() {
	this->trans.fill(0.0f);
}

void TranslacaoV::setTrans( array<float, 3> trans ) {
	this->trans = trans;
}

void TranslacaoV::aplica() {
	glTranslatef(trans[0], trans[1], trans[2]);
}
