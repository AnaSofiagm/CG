#include "draw.h"

// SceneGraph
// Construtor

SceneGraph::SceneGraph() {
	this->scale.fill(1.0f);
	this->trans.fill(0.0f);
	this->rot.fill(0.0f);
	this->cor.fill(0.0f);
}

// Setters 
void SceneGraph::setScale( array<float, 3> escala) { 
	this->scale = escala; 
}

void SceneGraph::setTrans( array<float, 3> transl ) { 
	this->trans = transl; 
}

void SceneGraph::setCor( array<float, 3> cr ) { 
	this->cor = cr; 
}
                
void SceneGraph::setRot( array<float, 4> rota) { 
	this->rot = rota; 
}

void SceneGraph::setModelo(vector<vector<Pontos>> pontos) {
	this->modelos = pontos;
}

// Getters                
array<float, 3> SceneGraph::getScale() { 
	return this->scale; 
}
                
array<float, 3> SceneGraph::getTrans() {    	
	return this->trans; 
}

array<float, 3> SceneGraph::getCor() {    	
	return this->cor; 
}
                
array<float, 4> SceneGraph::getRot() { 
	return this->rot; 
}
               
vector<vector<Pontos>> SceneGraph::getModelos() { 
	return this-> modelos; 
}
                
vector<SceneGraph> SceneGraph::getFilhos() { 
	return this->filhos; 
}

// Funcoes Adicionais
                
void SceneGraph::addFilho( SceneGraph c ) { 
	this->filhos.push_back( c ); 
}
               
void SceneGraph::addModelo( vector<Pontos> c ) { 
	this->modelos.push_back( c ); 
}


// Funcao responsavel por desenhar a estrutra
void SceneGraph::draw() const {

	glPushMatrix();

	glScalef(scale[0], scale[1], scale[2]);
	glRotatef(rot[0], rot[1], rot[2], rot[3]);
	glTranslatef(trans[0], trans[1], trans[2]);
	glColor3f(cor[0], cor[1], cor[2]);
	
	glBegin(GL_TRIANGLES);
	
	for( vector<Pontos> const &pnts : this->modelos ) {	
		for( Pontos const &p : pnts ) {
        		glVertex3f(p.a, p.b, p.c);
    		}
	}

	glEnd();

	for( SceneGraph const &tmp : this->filhos ) {
		tmp.draw();
	}

	glPopMatrix();

}
