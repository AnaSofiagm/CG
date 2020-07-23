#include "spotLight.h"

SLight::SLight() {
	this->pos.fill(0.0f);
	this->dir.fill(0.0f);
	this->cutoff = 0.0f;
}

SLight::SLight(array<float, 3> pos, array<float, 3> dir, float cut, GLenum luz) {
	this->setPos(pos);
	this->setDir(dir);
	this->setCutoff(cut);
	this->setLuz(luz);

}

void SLight::setPos( array<float, 3> pos ) {
	this->pos[0] = pos[0];
	this->pos[1] = pos[1];
	this->pos[2] = pos[2];
	this->pos[3] = 1.0f;
}

void SLight::setDir( array<float, 3> dir) {
	this->dir = dir;
}

void SLight::setCutoff( float cutoff ) {
	this->cutoff = cutoff;
}

void SLight::setLuz( GLenum luz) {
	this->luz = luz;
}

void SLight::prep() {
    glEnable(this->luz);
}


void SLight::aplica() {
	glLightfv(this->luz, GL_POSITION, this->pos.data());
	glLightfv(this->luz, GL_SPOT_DIRECTION, this->dir.data());
	glLightfv(this->luz, GL_SPOT_CUTOFF, &this->cutoff);
}
