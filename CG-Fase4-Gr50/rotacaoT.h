#include <array>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
using namespace std;

class RotacaoT {
	
	array<float, 4> rot;
	int segundos;
	int voltas;

	public:
		RotacaoT();
		void setRot( array<float, 3> );
		void setGraus( int );
		void aplica( bool );

};


