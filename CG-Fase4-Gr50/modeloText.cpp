#include "modeloText.h"

using namespace std;

ModTex::ModTex() {

    this->ambiente.fill(0.0f);
    this->specular.fill(0.0f);
    this->emissive.fill(0.0f);
    this->difusa.fill(0.0f);
    this->texID = 0;
}

void ModTex::setPontos( vector<float> vec ) {
	this->pontos = vec;
}

void ModTex::setNormais( vector<float> vec ) {
	this->normais = vec;
}

void ModTex::setTexturas( vector<float> vec ) {
	this->textura = vec;
}

void ModTex::setTexID( GLuint id ) {
	this->texID = id;
}

void ModTex::setAmbiente( array<float, 4> amb ) {
    this->ambiente = amb;
}

void ModTex::setSpecular( array<float, 4> sp ) {
    this->specular = sp;
}

void ModTex::setEmissive( array<float, 4> emi ) {
    this->emissive = emi;
}

void ModTex::setDifusa( array<float, 4> dif ) {
    this->difusa = dif;
}

void ModTex::prep() {

	this->nrpontos = this->pontos.size() / 3;
	
	glGenBuffers(1, &(this->vbos[0]));
	glBindBuffer(GL_ARRAY_BUFFER, this->vbos[0]); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * this->pontos.size(), this->pontos.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &(this->vbos[1]));
	glBindBuffer(GL_ARRAY_BUFFER, this->vbos[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * this->normais.size(), this->normais.data(), GL_STATIC_DRAW);
	
	glGenBuffers(1, &(this->vbos[2]));
	glBindBuffer(GL_ARRAY_BUFFER, this->vbos[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * this->textura.size(), this->textura.data(), GL_STATIC_DRAW);

	vector<float>().swap(this->pontos);
	vector<float>().swap(this->normais);
	vector<float>().swap(this->textura);
}

void ModTex::aplica() {

	float white[4] = {1,1,1,1};

	glBindTexture(GL_TEXTURE_2D, this->texID);

    glMaterialfv(GL_FRONT, GL_AMBIENT, this->ambiente.data());
    glMaterialfv(GL_FRONT, GL_SPECULAR, this->specular.data());
    glMaterialfv(GL_FRONT, GL_EMISSION, this->emissive.data());
    glMaterialfv(GL_FRONT, GL_DIFFUSE, this->difusa.data());

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
	
	glBindBuffer(GL_ARRAY_BUFFER, this->vbos[0]);
	glVertexPointer(3, GL_FLOAT, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, this->vbos[1]);
	glNormalPointer(GL_FLOAT, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, this->vbos[2]);
	glTexCoordPointer(2, GL_FLOAT, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, this->nrpontos);

    glBindTexture(GL_TEXTURE_2D, 0);
}