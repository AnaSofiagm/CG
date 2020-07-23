#define _USE_MATH_DEFINES
#include "ponto.h"
#include <math.h>

#define tvector(t) {powf(t, 3.0f), powf(t, 2.0f), t, 1.0f}

#define mult1441(a, b) a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3]

void multMatrixVector(float *m, float *v, float *res);


void getCatmullRomPoint(float t, Pontos p0, Pontos p1, Pontos p2, Pontos p3, Pontos *pos);


void getGlobalCatmullRomPoint(float gt, Pontos *pontos, int nmrpontos, Pontos *pos);


