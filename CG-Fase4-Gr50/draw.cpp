#include "draw.h"

using namespace std;

// SceneGraph
// Construtor

// Setters 

SceneGraph::SceneGraph() {

}

void SceneGraph::setScale( Scale novaesc ) { 

	this->scale = novaesc; 

}

void SceneGraph::setTrans( TranslacaoV novatrans ) { 

	this->trans = novatrans; 

}
                
void SceneGraph::setRot( RotacaoV novorot ) { 

	this->rot = novorot; 

}

void SceneGraph::setCurva( TranslacaoT novacurva ) {
	
	this->curva = novacurva;

}

void SceneGraph::setEixo( RotacaoT novoeixo ) {
	
	this->eixo = novoeixo;

}

void SceneGraph::setLuzes( vector<shared_ptr<Luz> > l ) {

	this->luzes = l;

}

void SceneGraph::setTexturas( vector<ModTex> vec ) {

	this->modTex = vec;

}

// Funcoes Adicionais
                
void SceneGraph::addFilho( SceneGraph c ) { 
	
	this->filhos.push_back( c ); 

}

               
void SceneGraph::prep() {

	for( auto &l : this->modTex )
		l.prep();

	for ( shared_ptr<Luz> l : this->luzes )
	    l->prep();

	for( SceneGraph &tmp : this->filhos ) {
		tmp.prep();
	}
}

// Funcao responsavel por desenhar a estrutra
void SceneGraph::draw( bool updt ) {

	glPushMatrix();

	this->scale.aplica();
	this->rot.aplica();
	this->trans.aplica();

	this->curva.aplica( updt );
	this->eixo.aplica( updt );

	for( ModTex l : this->modTex )
		l.aplica();


	for ( shared_ptr<Luz> l : this->luzes ) {
		l->aplica();
	}

	for( SceneGraph &tmp : this->filhos ) {
		tmp.draw( updt );
	}

	glPopMatrix();

}
