#include <array>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif


using namespace std;

class RotacaoV {
	
	array<float, 4> rot;

	public:
		RotacaoV();
		void setRot( array<float, 4> );
		void aplica(); 
}; 


