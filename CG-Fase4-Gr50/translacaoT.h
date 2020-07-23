#include <vector>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include "catmull.h"

using namespace std;

class TranslacaoT {

	vector<Pontos> pntsCurva;
	int voltas;
	
	public:
		TranslacaoT();
		void setCurva( vector<Pontos>, int);
		void aplica( bool );

};


