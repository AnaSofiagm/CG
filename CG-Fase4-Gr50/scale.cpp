#include "scale.h"

using namespace std;

Scale::Scale() {
	this->scale.fill(1.0f);
}

void Scale::setAxis( array<float, 3> newAxs ) {
	this->scale = newAxs;
}

void Scale::aplica() {
	glScalef(this->scale[0], this->scale[1], this->scale[2]);
}
