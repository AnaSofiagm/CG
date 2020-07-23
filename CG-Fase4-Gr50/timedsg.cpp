#include "timedsg.h"


TimedSG::TimedSG() {

}

void TimedSG::setSG( SceneGraph novoSG ) {

	this->sg = novoSG;

}

void TimedSG::prep() {

	this->sg.prep();

}

	int basetime;
	float fps;
	int frame;

bool updateTime() {

	frame++;

	int aux = glutGet(GLUT_ELAPSED_TIME);

	if(aux - basetime >= 1000) {
		fps = frame*1000.0/(aux - basetime); 
		basetime = aux;
		frame = 0; 
		return true;
	}

	return false;

}

void TimedSG::draw() {

	bool aux = updateTime();
	this->sg.draw( aux );
}
