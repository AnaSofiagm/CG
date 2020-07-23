#ifndef __DIRECTION_LIGHT__
#define __DIRECTION_LIGHT__

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <array>

#include "luz.h"

using namespace std;

class DLight : public Luz {
	
	array<float, 3> dLight;
	GLenum luz;

	public:
		DLight();
		DLight( array<float, 3>, GLenum );
		void setDirectionLight( array<float, 3> );
		void setLuz( GLenum );
		void prep();
		void aplica();
};

#endif
