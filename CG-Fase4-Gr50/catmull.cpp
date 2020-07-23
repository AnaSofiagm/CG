#include "catmull.h"


void multMatrixVector(float *m, float *v, float *res) {

	for (int j = 0; j < 4; ++j) {
		res[j] = 0;
		for (int k = 0; k < 4; ++k) {
			res[j] += v[k] * m[j * 4 + k];
		}
	}

}

void getCatmullRomPoint(float t, Pontos p0, Pontos p1, Pontos p2, Pontos p3, Pontos *pos) {
	

	// matriz 4x4 de Catmull em formato linha
	float mCat[16] = { -0.5f,  1.5f, -1.5f,  0.5f,
		   	    1.0f, -2.5f,  2.0f, -0.5f,
			   -0.5f,  0.0f,  0.5f,  0.0f,
		   	    0.0f,  1.0f,  0.0f,  0.0f};

	float pts[3][4] = { { p0.a, p1.a, p2.a, p3.a }, 
			    { p0.b, p1.b, p2.b, p3.b },
			    { p0.c, p1.c, p2.c, p3.c } };

	float ts[4] = tvector(t);
	float aux[4];
	float posaux[3];
	
	for(int i = 0; i < 3; i++) {
		multMatrixVector(mCat, pts[i], aux);
		posaux[i] = mult1441(ts, aux);	
	}

	pos->a = posaux[0];
	pos->b = posaux[1];
	pos->c = posaux[2];

}

void getGlobalCatmullRomPoint(float gt, Pontos *pontos, int nmrpontos, Pontos *pos) {

	float t = gt * nmrpontos;
	int index = floor(t);
	int indices[4];

	t = t - index;
	indices[0] = (index + nmrpontos - 1) % nmrpontos;
	indices[1] = (indices[0] + 1) % nmrpontos;
	indices[2] = (indices[1] + 1) % nmrpontos;
	indices[3] = (indices[2] + 1) % nmrpontos;

	getCatmullRomPoint(t, pontos[indices[0]], pontos[indices[1]], pontos[indices[2]], pontos[indices[3]], pos);

}
