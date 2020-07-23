#include "pointLight.h"

PLight::PLight() {
	this->pLight.fill(0.0f);
}

PLight::PLight(array<float, 3> axs, GLenum luz) {
	this->setPointLight( axs );
	this->setLuz(luz);
}

void PLight::setPointLight( array<float, 3> axs ) {
	this->pLight[0] = axs[0];
	this->pLight[1] = axs[1];
	this->pLight[2] = axs[2];
	this->pLight[3] = 1.0f; // ponto de luz 1.0
}

void PLight::setLuz( GLenum luz ) {
	this->luz = luz;
}

void PLight::prep() {
    glEnable(this->luz);
}

void PLight::aplica() {
	glLightfv(this->luz, GL_POSITION, this->pLight.data());
}
