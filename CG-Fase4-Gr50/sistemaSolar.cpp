#define _CRT_SECURE_NO_WARNINGS 
#define _USE_MATH_DEFINES

#include <list>
#include "il.h"
#include "timedsg.h"



using namespace tinyxml2;

TimedSG ts_g;
SceneGraph s_gg;

#define GROWF 0.01

double alfa = M_PI / 4;
double beta = M_PI / 4;
float raio = 500.0f;

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
    gluLookAt(raio * cos(beta) * sin(alfa), raio * sin(beta), raio * cos(beta) * cos(alfa),
              0.0f, 0.0f, 0.0f,
              0.0f,1.0f,0.0f);
    glTranslatef(tx,0,tz);

    //glColor3f(1.0f,1.0f,1.0f);
    ts_g.draw();

	// End of frame
	glutSwapBuffers();
}


void processSpecialKeys(int key, int xx, int yy) {
// put code to process special keys in here
    switch(key) {
        case GLUT_KEY_LEFT:
            alfa += GROWF;
            break;
        case GLUT_KEY_RIGHT:
            alfa -= GROWF;
            break;
        case GLUT_KEY_UP:
            beta += GROWF;
            break;
        case GLUT_KEY_DOWN:
            beta -= GROWF;
            break;
        default:
            ;
    }
    glutPostRedisplay();

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
            raio--;
            break;
        case '-':
            raio++;
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

void init(tinyxml2::XMLNode *scene) {
#ifndef __APPLE__
// init GLEW
    glewInit();
#endif

    // OpenGL Settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glClearColor(0, 0, 0, 0);

    glEnable(GL_LIGHTING);

    glEnable(GL_TEXTURE_2D);
    s_gg = doGroup(scene->FirstChildElement("group"));
    ts_g.setSG(s_gg);
    ts_g.prep();

}



int main(int argc, char **argv) {

    tinyxml2::XMLDocument doc;
    //new file
    doc.LoadFile("./XML/input.xml");
    tinyxml2::XMLNode *scene = doc.FirstChild();
    if (scene == nullptr) perror("Erro de Leitura.\n");


// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@DI-UM");
		
// Required callback registry 
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);
	
// Callback registration for keyboard processing
	glutSpecialFunc(processSpecialKeys);
    glutKeyboardFunc(processKeys);


// Init function Call
    init(scene);

// enter GLUT's main cycle
	glutMainLoop();

	return 1;
}
