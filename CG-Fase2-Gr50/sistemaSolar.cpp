#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _CRT_SECURE_NO_WARNINGS 
#define _USE_MATH_DEFINES
#include <math.h>

//include tinyxml header
#include <iostream>
#include "tinyxml2.h"
#include <string>
#include <vector>
#include <fstream>
#include <list>
#include "eng.h"
#include "draw.h"

using namespace tinyxml2;

SceneGraph s_gg;

float angleAlpha = 0.5 , angleBeta = 0.5 , radius = 350.f ;
float tx = 0, tz = 0;

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

void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(cos(angleBeta)*sin(angleAlpha)*radius, sin(angleBeta)*radius, cos(angleBeta)*cos(angleAlpha)*radius,
              0.0, 0.0, 0.0,
              0.0f, 1.0f, 0.0f);

	glTranslatef(tx,0,tz);

    s_gg.draw();
    
	// End of frame
	glutSwapBuffers();
}


void processKeys(unsigned char key, int xx, int yy) {
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
        case 'a': case 'A':
			tx++;
			break;
		case 'd': case 'D':
			tx--;
			break;
		case 'w': case 'W':
			tz++;
			break;
		case 's': case'S':
			tz--;
			break;
    }
    glutPostRedisplay();
}


void processSpecialKeys(int key, int xx, int yy) {
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
    
    doc.LoadFile("./XML/input.xml");

    tinyxml2::XMLNode *scene = doc.FirstChild();
    if (scene == nullptr) perror("Erro de Leitura.\n");

    s_gg = doGroup(scene->FirstChildElement("group"));
    
    // init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(600,600);
	glutCreateWindow("CG@DI-UM");
		
    // Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);
	
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
