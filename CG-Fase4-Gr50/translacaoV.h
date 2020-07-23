#include <array>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

using namespace std;

class TranslacaoV {

	array<float, 3> trans;

	public:
		TranslacaoV();
		void setTrans( array<float, 3> );
		void aplica();
        
};

