#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

//include tinyxml header
#include <iostream>
#include "tinyxml2.h"
#include <string>
#include <vector>
#include <fstream>

using namespace tinyxml2;

struct Pontos {
    float a;
    float b;
    float c;
};

std::vector<Pontos> pontos;

float angleAlpha = 0.5 , angleBeta = 0.5 , radius = 10 ;

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

void guardaPontos(std::string ficheiro) {
    std::ifstream file;
    std::string s = "./";
    s.append(ficheiro.c_str());
    file.open(s.c_str());
    float a,b,c;
    while(file >> a >> b >> c) {
        Pontos aux;
        aux.a = a;
        aux.b = b;
        aux.c = c;
        pontos.push_back(aux);
    }
}

//Função que gera floats aleatorios
float RandomFloat(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

void printPontos(std::vector<Pontos> pontos) {
    for(int i = 0; i < pontos.size(); i++) {
        glVertex3f(pontos[i].a, pontos[i].b, pontos[i].c);
        glColor3f(RandomFloat(0.0,1.0),RandomFloat(0.0,1.0),RandomFloat(0.0,1.0));
        }
}

void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(cos(angleBeta)*sin(angleAlpha)*radius, sin(angleBeta)*radius, cos(angleBeta)*cos(angleAlpha)*radius,
              0.0, 0.0, -1.0,
              0.0f, 1.0f, 0.0f);

    glBegin(GL_TRIANGLES);
    printPontos(pontos);
    glEnd();
    
	// End of frame
	glutSwapBuffers();
}

void processKeys(unsigned char key, int xx, int yy) {
    // put code to process regular keys in here
    switch (key) {
        case 'l': case 'L':
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            break;
        case 'p': case 'P': 
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
            break;
        case 'f': case 'F':
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            break;
        case '+':
            radius--;
            break;
        case '-':
            radius++;
            break;
    }
    glutPostRedisplay();
}

void processSpecialKeys(int key, int xx, int yy) { 
    // put code to process special keys in here
    switch (key){
        case GLUT_KEY_LEFT :
        angleAlpha -= 0.1;
        break;
        case GLUT_KEY_RIGHT :
        angleAlpha += 0.1;
        break;
        case GLUT_KEY_UP :
        if(angleBeta < M_PI/2)
        angleBeta += 0.1;
        break;
        case GLUT_KEY_DOWN :
        if(angleBeta > -M_PI/2)
        angleBeta -= 0.1;
        break;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    tinyxml2::XMLDocument doc;

    doc.LoadFile(argv[1]);

    tinyxml2::XMLNode *scene = doc.FirstChild();
    const char * file;
    while(scene) {
        for(tinyxml2::XMLElement* model = scene->FirstChildElement(); model != NULL; model = model->NextSiblingElement()) {
            
            file = model->Attribute("file");
            guardaPontos(file);
        }
        scene = scene->NextSiblingElement();
    }
    
    // init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@DI-UM");
		
    // Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	
    // Callback registration for keyboard processing
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);

    //  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
    // enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
