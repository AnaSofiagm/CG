#ifndef __POINTLIGHT__
#define __POINTLIGHT__

#include <array>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include "luz.h"


using namespace std;

class PLight : public Luz {
	
	array<float, 4> pLight;
	GLenum luz;

	public:
		PLight();
		PLight( array<float, 3>, GLenum );
		void setPointLight( array<float, 3> );
		void setLuz( GLenum );
		void prep();
		void aplica();
};

#endif
