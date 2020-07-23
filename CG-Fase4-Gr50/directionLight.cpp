#include "directionLight.h"

DLight::DLight() {
	this->dLight.fill(0.0f);
}

DLight::DLight( array<float, 3> axs, GLenum luz ) {
	this->setDirectionLight( axs );
	this->setLuz(luz);
}

void DLight::setDirectionLight( array<float, 3> axs ) {
	this->dLight = axs;
}

void DLight::setLuz( GLenum luz ) {
	this->luz = luz;
}

void DLight::prep() {
    glEnable(this->luz);
}


void DLight::aplica() {
	float pos[4] = {this->dLight[0], this->dLight[1], this->dLight[2], 0.0f}; // 0.0 indica luz direcional
	glLightfv(this->luz, GL_POSITION, pos);
}

