#include<stdio.h>
#include<stdlib.h>

#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include <IL/il.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#define ANG2RAD M_PI/180.0 

#define COWBOYS 8
#define RAIO_COWBOYS 5
#define INDIOS 16
#define RAIO_INDIOS 25
#define ARVORES 1000
#define STEP_COWBOY 1.0f
#define STEP_INDIO 0.5f


float step = 0.0;

float height = 2.0f;
float x = 0.0f;
float z = 0.0f;

//Variaveis para a VBO
int n_pontos;
GLuint buffer[1];

unsigned int t, tw, th;
unsigned char *imageData;

float camX = 0;
float camY = 2;
float camZ = 0;

int startX, startY, tracking = 0;

float alfa = 0.0;
float dx = 2;
float dy = 0;
float dz = 2;
int raio = 10;

int alpha = 0, beta = 45, r = 50;
float *vertexB;

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set the correct perspective
	gluPerspective(45,ratio,1,1000);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

//Numeros do imageData vão de 0 a 255
float h(int coluna, int linha){
    return imageData[linha*tw+coluna]/255.0 * 100;
}

float hf(float x, float z){
    float hx1z,hx2z,h_xz,fz,fx;
    int x1,x2,z1,z2;
    x1 = x;
    x2=x1+1;
    z1 = z;
    z2=z1+1;
    fz = z-z1;
    fx = x-x1;

    hx1z = h(x1,z1) * (1-fz) + h(x1,z2) * fz;
    hx2z = h(x2,z1) * (1-fz) + h(x2,z2) * fz;

    h_xz = hx1z * (1 - fx) + hx2z * fx;
    return h_xz;
}

//VBO do terreno
void construirVBO(float altura, float largura){
    float *vertexB=NULL, altura_aux=altura,largura_aux;
    int coluna,linha,i=0;
    
    altura/=th;
    largura/=tw;

    //Numero de coordenadas no array
    n_pontos=(tw*2*(th-1))*3;
    vertexB=(float*)malloc(n_pontos*sizeof(float));
    
    //Activar Buffers
    glEnableClientState(GL_VERTEX_ARRAY);

    //A cada iteração vamos buscar a altura dada pela função h(x,y)
    for (linha=0; linha<th-1; linha++) {
        largura_aux=0;
        for (coluna=0; coluna<tw; coluna++) {
            
            vertexB[i++]=altura_aux;
            vertexB[i++]=h(coluna,linha);
            vertexB[i++]=largura_aux;
            
            vertexB[i++]=altura_aux-altura;
            vertexB[i++]=h(coluna,linha+1);
            vertexB[i++]=largura_aux;
            
            largura_aux+=largura;
        }
        altura_aux-=altura;
    }

    //Aqui dizemos qual é GLuint que vamos usar e quandos buffers tem
    glGenBuffers(1, buffer);

    // Informamos qual vai ser o buffer que vamos usar para guardar a VBO
    glBindBuffer(GL_ARRAY_BUFFER,buffer[0]);

    //Temos 2 campos importantes (2º e 3º), no 2º metemos a memória necessária para guardar todas as coordenadas, e no 3º informamos o array que tem as coordenadas
    glBufferData(GL_ARRAY_BUFFER, n_pontos*sizeof(float), vertexB, GL_STATIC_DRAW);
    free(vertexB);    

}

void drawTerrain(){

    int i;
    glBindBuffer(GL_ARRAY_BUFFER,buffer[0]);
    glVertexPointer(3,GL_FLOAT,0,0);
    glPushMatrix();
    //Para ser mais facil de desenhar a VBO desenhei a parti de (0,0,0). Agora fazemos o translate para centrar o terreno
    glTranslatef(-(tw/2.0), 0, -(th/2.0));
   
    //Como estamos a desenhar no modo GL_TRIANGLE_STRIP temos de desenhar uma 'tira' de cada vez
    for (i=0; i<th; i++) {
        glDrawArrays(GL_TRIANGLE_STRIP, i*tw*2, 2*tw);
    }
    glPopMatrix();    
}

void drawTree() {

	glPushMatrix();
	glRotatef(-90, 1.0f, 0.0f, 0.0f);
	glColor3f(1.0, 1.0, 0.5);
	glutSolidCone(0.25f, 4, 5, 1);

	glColor3f(0.0f, 0.5f + rand() * 0.5f/RAND_MAX,0.0f);
	glTranslatef(0.0f, 0.0f, 2.0f);
	glutSolidCone(2.0f, 5.0f, 5.0f, 1.0f);
	glPopMatrix();
}

void placeTrees() {

	float r = 35.0;
	float alpha;
	float rr;
	float x,z;

	srand(31457);
	int arvores = 0;

	while (arvores < ARVORES) {

		rr = rand() * 150.0/ RAND_MAX;
		alpha = rand() * 6.28 / RAND_MAX;

		x = cos(alpha) * (rr + r);
		z = sin(alpha) * (rr + r);

		if (fabs(x) < 100 && fabs(z) < 100) {

			glPushMatrix();
			glTranslatef(x,h((z+tw/2),256-(x+th/2)),z);
			drawTree();
			glPopMatrix();
			arvores++;
		}
	}
}



void drawDonut() {
	glPushMatrix();
	glTranslatef(0.0,0.5,0.0);
	glColor3f(1.0f,0.0f,1.0f);
	glutSolidTorus(0.5,1.25,8,16);
	glPopMatrix();
}


void drawIndios() {
	float angulo;
	glColor3f(1.0f,0.0f,0.0f);
	for (int i = 0; i < INDIOS; i++) {
		
		angulo = i * 360.0/INDIOS + step * STEP_INDIO;
		glPushMatrix();
		glRotatef(angulo,0.0,1.0,0.0);
		glTranslatef(0.0,0.0,RAIO_INDIOS);
		glutSolidTeapot(1);
		glPopMatrix();
	}
}


void drawCowboys() {
	float angulo;
	glColor3f(0.0f,0.0f,1.0f);
	for (int i = 0; i < COWBOYS; i++) {
		
		angulo = i * 360.0/COWBOYS + step * STEP_COWBOY;
		glPushMatrix();
		glRotatef(-angulo,0.0,1.0,0.0);
		glTranslatef(RAIO_COWBOYS,0.0,0.0);
		glutSolidTeapot(1);
		glPopMatrix();
	}
}


void drawScene() {
	glColor3f(0.3, 0.7, 0);
	drawTerrain();
	placeTrees();
	drawDonut();
	glPushMatrix();
	// move teapots up so that they are placed on top of the ground plane
	glTranslatef(0.0,1.0,0.0);
	drawCowboys();
	drawIndios();
	glPopMatrix();
}


void renderScene(void) {

	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(camX, camY, camZ, 
		      camX + sin(alfa),camY,camZ + cos(alfa),
			  0.0f,1.0f,0.0f);

	drawScene();
	step++;

	// End of frame
	glutSwapBuffers();
}


void processKeys(unsigned char key, int xx, int yy) {

    // put code to process regular keys in here
    switch (key) {

        case 's':
            dx = sin(alfa);
            dz = cos(alfa);
            camX = camX - dx;
            camZ = camZ - dz;
            camY = 2 + hf(camX+128,camZ+128);
            break;

        case 'w':
            dx = sin(alfa);
            dz = cos(alfa);
            camX = camX + dx;
            camZ = camZ + dz;
            camY = 2 + hf(camX+128,camZ+128);
            break;

        case 'd':
            alfa -= 0.5;
            break;

        case 'a':
            alfa += 0.5;
            break;

        case 'l': case 'L':
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            break;
        case 'p': case 'P': 
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
            break;
        case 'f': case 'F':
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            break;
    }
}



void processMouseButtons(int button, int state, int xx, int yy) {
	
	if (state == GLUT_DOWN)  {
		startX = xx;
		startY = yy;
		if (button == GLUT_LEFT_BUTTON)
			tracking = 1;
		else if (button == GLUT_RIGHT_BUTTON)
			tracking = 2;
		else
			tracking = 0;
	}
	else if (state == GLUT_UP) {
		if (tracking == 1) {
			alpha += (xx - startX);
			beta += (yy - startY);
		}
		else if (tracking == 2) {
			
			r -= yy - startY;
			if (r < 3)
				r = 3.0;
		}
		tracking = 0;
	}
}


void processMouseMotion(int xx, int yy) {

	int deltaX, deltaY;
	int alphaAux, betaAux;
	int rAux;

	if (!tracking)
		return;

	deltaX = xx - startX;
	deltaY = yy - startY;

	if (tracking == 1) {


		alphaAux = alpha + deltaX;
		betaAux = beta + deltaY;

		if (betaAux > 85.0)
			betaAux = 85.0;
		else if (betaAux < -85.0)
			betaAux = -85.0;

		rAux = r;
	}
	else if (tracking == 2) {

		alphaAux = alpha;
		betaAux = beta;
		rAux = r - deltaY;
		if (rAux < 3)
			rAux = 3;
	}
	camX = rAux * sin(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
	camZ = rAux * cos(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
	camY = rAux * 							     sin(betaAux * 3.14 / 180.0);
}





void init() {

	// Colocar aqui load da imagem que representa o mapa de alturas
	ilGenImages(1, &t);
	ilBindImage(t);
	ilLoadImage((ILstring) "terreno.jpg");
	ilConvertImage(IL_LUMINANCE, IL_UNSIGNED_BYTE);
	tw = ilGetInteger(IL_IMAGE_WIDTH);
	th = ilGetInteger(IL_IMAGE_HEIGHT);
	imageData = ilGetData();


	// alguns settings para OpenGL
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
}



int main(int argc, char **argv) {

	// inicialização
	ilInit();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(320,320);
	glutCreateWindow("CG@DI-UM");		

	// registo de funções 
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);

	// pôr aqui registo da funções do teclado e rato
	glutKeyboardFunc(processKeys);
	glutMouseFunc(processMouseButtons);
	glutMotionFunc(processMouseMotion);

    //Callback do GLEW - Tem de estar depois de todos os callbacks do GLUT
    glewInit();
    ilInit();

	init();
	construirVBO(th,tw);

	// entrar no ciclo do GLUT 
	glutMainLoop();
	
	return 0;
}

