#include <vector>
#include <array>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif


using namespace std;

class ModTex {

	vector<float> pontos;
	vector<float> normais;
	vector<float> textura;
	array<GLuint, 3> vbos;
    array<float, 4> ambiente;
    array<float, 4> specular;
    array<float, 4> emissive;
    array<float, 4> difusa;
	GLuint nrpontos;
	GLuint texID;

	public:
		ModTex();
		void setPontos( vector<float> );
		void setNormais( vector<float> );
		void setTexturas( vector<float> );
		void setTexID( GLuint );
        void setAmbiente( array<float, 4> );
        void setSpecular( array<float, 4> );
        void setEmissive( array<float, 4> );
        void setDifusa( array<float, 4> );
		void prep();
		void aplica();

};


