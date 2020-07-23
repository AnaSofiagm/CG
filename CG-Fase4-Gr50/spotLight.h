#ifndef SPOTLIGHT
#define SPOTLIGHT

#include <array>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include "luz.h"


using namespace std;

class SLight: public Luz {
	
	array<float, 4> pos;
	array<float, 3> dir;
	float cutoff;
	GLenum luz;	

	public:
		SLight();
		SLight( array<float, 3>, array<float, 3>, float, GLenum );
		void setPos( array<float, 3> );
		void setDir( array<float, 3> );
		void setCutoff( float );
		void setLuz( GLenum );
		void prep();
		void aplica();

};

#endif
