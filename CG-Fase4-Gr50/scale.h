#include <array>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif



using namespace std;

class Scale {

	array<float, 3> scale;

	public:
		Scale();
		void setAxis( array<float, 3> );
		void aplica();
};


