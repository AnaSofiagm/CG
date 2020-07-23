#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <vector>

using namespace std;

struct Ponto {
	float a;
	float b;
	float c;
};

void invalidOption() {
	printf("Invalid comand\nAvailable Options:\n");
	printf("plane <length> <width> <filename>\n");
	printf("box <length> <width> <heigth> <filename>\n");
	printf("sphere <radius> <slices> <stacks> <filename>\n");
	printf("cone <bottom radius> <heigth> <slices> <stacks> <filename>\n");
	printf("bezier <tesselation> <inputFilename> <outputFilename>\n");
}

void plane(float length, float width, char* filename) {
	char fic[9+strlen(filename)] = "3Dfiles/";
	strcat(fic,filename);
	std::ofstream outfile(fic);

	float x = length/2;			//coordenada no eixo x
	float z = width/2;			//coordenada eixo z

	/* PLANE		 
		A _____ B
		 /\	   /
		/  \  /
	  D/____\/C
	*/

	//Triangulo ABC virado para a frente
	outfile << -x << " 0 " << -z << endl;  			//A
	outfile << x << " 0 " << z << endl;				//C
	outfile << x << " 0 " << -z << endl;			//B
	//Triangulo ABC virado para a trás
	outfile << -x << " 0 " << -z << endl;  			//A
	outfile << x << " 0 " << -z << endl;			//B
	outfile << x << " 0 " << z << endl;				//C

	//Triangulo ADC virado para a frente
	outfile << -x << " 0 " << -z << endl;			//A
	outfile << -x << " 0 " << z << endl;			//D
	outfile << x << " 0 " << z << endl;				//C
	//Triangulo ADC virado para a trás
	outfile << -x << " 0 " << -z << endl;			//A
	outfile << x << " 0 " << z << endl;				//C
	outfile << -x << " 0 " << z << endl;			//D

	outfile.close();
}

void box(float length, float width, float heigth, char* filename) {
	char fic[9+strlen(filename)] = "3Dfiles/";
	strcat(fic,filename);
	std::ofstream outfile(fic);

	/* BOX, missing lines AE, BF, CG, DH
			     A _____ B 			A outfile << -x << y << -z
				 /\	   /			B outfile << x << y << -z
				/  \  /				C outfile << -x << -y << -z
	 		  C/____\/D  			D outfile << x << -y << -z
		  E_____F  					E outfile << -x << y << z
		 /\	   /					F outfile << x << y << z
		/  \  /						G outfile << -x << -y << z
	  G/____\/H 					H outfile << x << -y << z
	*/

	float x = length/2;
	float y = heigth/2;
	float z = width/2;

	/*ABDC */
	outfile << -x << " " << y << " " << -z << endl;		//A
	outfile << x << " " << y << " " << -z << endl;		//B
	outfile << x << " " << -y << " " << -z << endl;		//D

	outfile << x << " " << -y << " " << -z << endl;		//D
	outfile << -x << " " << -y << " " << -z << endl;	//C
	outfile << -x << " " << y << " " << -z << endl;		//A

	/*EGHF */
	outfile << -x << " " << y << " " << z << endl;		//E
	outfile << -x << " " << -y << " " << z << endl;		//G
	outfile << x << " " << -y << " " << z << endl;		//H

	outfile << x << " " << -y << " " << z << endl;		//H
	outfile << x << " " << y << " " << z << endl;		//F
	outfile << -x << " " << y << " " << z << endl;		//E
	
	/*AEFB */
	outfile << -x << " " << y << " " << -z << endl;		//A
	outfile << -x << " " << y << " " << z << endl;		//E
	outfile << x << " " << y << " " << z << endl;		//F

	outfile << x << " " << y << " " << z << endl;		//F
	outfile << x << " " << y << " " << -z << endl;		//B
	outfile << -x << " " << y << " " << -z << endl;		//A

	/*BFHD*/
	outfile << x << " " << y << " " << -z << endl;		//B
	outfile << x << " " << y << " " << z << endl;		//F
	outfile << x << " " << -y << " " << z << endl;		//H

	outfile << x << " " << -y << " " << z << endl;		//H
	outfile << x << " " << -y << " " << -z << endl;		//D
	outfile << x << " " << y << " " << -z << endl;		//B

	/*ACGE - */
	outfile << -x << " " << y << " " << -z << endl;		//A
	outfile << -x << " " << -y << " " << -z << endl;	//C
	outfile << -x << " " << -y << " " << z << endl;		//G

	outfile << -x << " " << -y << " " << z << endl;		//G
	outfile << -x << " " << y << " " << z << endl;		//E
	outfile << -x << " " << y << " " << -z << endl;		//A

	/*GCDH*/
	outfile << -x << " " << -y << " " << -z << endl;	//C
	outfile << x << " " << -y << " " << -z << endl;		//D
	outfile << x << " " << -y << " " << z << endl;		//H

	outfile << x << " " << -y << " " << z << endl;		//H
	outfile << -x << " " << -y << " " << z << endl;		//G
	outfile << -x << " " << -y << " " << -z << endl;	//C

	outfile.close();
}

void sphere(float radius, float slices, float stacks, char* filename) {
	char fic[9+strlen(filename)] = "3Dfiles/";
	strcat(fic,filename);
	std::ofstream outfile(fic);

	/* 	
		slices = nº de subdivisoes em volta do eixo X
		stacks = nº de subdivisoes em volta do eixo Y

			----- Cartesian coordinates -----
			z = r * cos(Beta) * cos(Alpha)
			x = r * cos(Beta) * sin(Alpha)
			y = r * sin(Beta)

		entre cada par de stacks existe um nº dado de slices, formando 4 pontos em cada slice,
		ou seja desenhar quadrados <=> 2 triangulos em cada slice.
	*/

	float b = M_PI/stacks;					//variação entre cada stack
	float a = (2*M_PI)/slices;				//variacao entra cada slice
	/*
		ciclo exterior percore as stacks;
		ciclo interior percore as slices;
	*/
	for(float betha = -(M_PI/2); betha<(M_PI/2); betha += b) {
		for(float alpha = 0; alpha<(2*M_PI); alpha += a) {
			/*
				Considerando o rectangulo formado entre cada par de slices:
				D____C
				|    |
				|    |
				A____B

			*/
			//Triangulo ABC
			outfile << (radius*cos(betha)*sin(alpha))<< " " << (radius*sin(betha)) << " " << (radius*cos(betha)*cos(alpha)) << endl;
			outfile << (radius*cos(betha)*sin(alpha+a))<< " " << (radius*sin(betha)) << " " << (radius*cos(betha)*cos(alpha+a)) << endl;
			outfile << (radius*cos(betha+b)*sin(alpha+a))<< " " << (radius*sin(betha+b)) << " " << (radius*cos(betha+b)*cos(alpha+a)) << endl;

			//Triangulo CDA
			outfile << (radius*cos(betha+b)*sin(alpha+a))<< " " << (radius*sin(betha+b)) << " " << (radius*cos(betha+b)*cos(alpha+a)) << endl;
			outfile << (radius*cos(betha+b)*sin(alpha))<< " " << (radius*sin(betha+b)) << " " << (radius*cos(betha+b)*cos(alpha)) << endl;
			outfile << (radius*cos(betha)*sin(alpha))<< " " << (radius*sin(betha)) << " " << (radius*cos(betha)*cos(alpha)) << endl;
		}
	}
	outfile.close();
}

void cone(float radius, float heigth, float slices, float stacks, char* filename) {
	char fic[9+strlen(filename)] = "3Dfiles/";
	strcat(fic,filename);
	std::ofstream outfile(fic);

	/* BASE - circunferenciaf formada por triangulos virados para baixo */
	float a = (2*M_PI)/slices;				//variacao entra cada slice

	for(float alpha=0; alpha<(2*M_PI);alpha+=a) {
		outfile << "0" << " 0 " << " 0 " << endl;
		outfile << radius*sin(alpha+a) << " 0 " << radius*cos(alpha+a) << endl;
		outfile << radius*sin(alpha) << " 0 " << radius*cos(alpha) << endl;
	}

	/*
 	y				/\				|s
 	|			   /  \             |t
	|___x		  /    \            |a
	0			 /      \           |c
				/        \          |k
				----------          |s
				s|l|i|c|e|s
	*/
	float hvar = heigth/stacks;					//variaçao entre cada stack
	float r = radius/stacks;					//variaçao do raio em cada stack
	/*
		ciclo exterior percore as stacks;
		ciclo interior percore as slices;
	*/
	for(float y=0; y<heigth-hvar; y+=hvar) {
		for(float alpha = 0; alpha<(2*M_PI); alpha += a) {
			/*
				Considerando o rectangulo formado entre cada par de slices:
				D____C
				|    |
				|    |
				A____B

			*/
			//Triangulo ABC
			outfile << radius*sin(alpha) << " " << y << " " << radius*cos(alpha) << endl;
			outfile << radius*sin(alpha+a) << " " << y << " " << radius*cos(alpha+a) << endl;
			outfile << (radius-r)*sin(alpha+a) << " " << y+hvar << " " << (radius-r)*cos(alpha+a) << endl;

			//Triangulo CDA
			outfile << (radius-r)*sin(alpha+a) << " " << y+hvar << " " << (radius-r)*cos(alpha+a) << endl;
			outfile << (radius-r)*sin(alpha) << " " << y+hvar << " " << (radius-r)*cos(alpha) << endl;
			outfile << radius*sin(alpha) << " " << y << " " << radius*cos(alpha) << endl;
		}
		radius = radius - r;
	}
	outfile.close();
}

/*
	Recebe a tesselacao, e o nome dos ficheiros de input(bezier patch)
	e output(ficheiro .3d destino), fazendo entra as transformações necessárias
*/
void bezier(int tesselation, const char* patchfilename, const char* savefilename){
    //--- PARSING PATCH ---//
    std::fstream f;
    f.open(patchfilename,std::ios::in);
    int nPatches=0;
    int nCtrPoints=0;
    std::vector<std::vector<int> > indicesPatch;
    std::vector<Ponto> ctrPoints;
    
	/* ---- Leitura Input -----
		number of patches

		1,2,3..,n \
		1,2,3..,n --- Indices for the patches
		1,2,3..,n /

		number of control points

		px, py, pz \
		px, py, pz --- Control points
		px, py, pz /
	*/    
    if(f.is_open()){
        std::string line;
        if(getline(f,line)) sscanf(line.c_str(),"%d\n",&nPatches);
        for(int i=0; i<nPatches ;i++){
             std::vector<int> aux;
            if(getline(f,line)){
                int n1=0,n2=0,n3=0,n4=0,n5=0,n6=0,n7=0,n8=0,n9=0,n10=0,n11=0,n12=0,n13=0,n14=0,n15=0,n16=0;
                sscanf(line.c_str(),"%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d\n",&n1,&n2,&n3,&n4,&n5,&n6,&n7,&n8,&n9,&n10,&n11,&n12,&n13,&n14,&n15,&n16);
                aux.push_back(n1);
                aux.push_back(n2);
                aux.push_back(n3);
                aux.push_back(n4);
                aux.push_back(n5);
                aux.push_back(n6);
                aux.push_back(n7);
                aux.push_back(n8);
                aux.push_back(n9);
                aux.push_back(n10);
                aux.push_back(n11);
                aux.push_back(n12);
                aux.push_back(n13);
                aux.push_back(n14);
                aux.push_back(n15);
                aux.push_back(n16);
            }
            
            indicesPatch.push_back(aux);
        }
        if(getline(f,line)) sscanf(line.c_str(),"%d\n",&nCtrPoints);
        for(int i=0; i<nCtrPoints ;i++){
            float x=0,y=0,z=0;
            if(getline(f,line)) sscanf(line.c_str(),"%f, %f, %f\n",&x,&y,&z);
  
            Ponto p;
            p.a = x; p.b = y; p.c = z;
            
            ctrPoints.push_back(p);
        }
        
        f.close();
    }
    else { 
    	printf("Error: Not possible acess patch file..."); 
    	exit(0); 
    }
    
    //--- DESENHAR PATCHES ---//
    float res[3];
    float t;
    int index, indices[4];
    float q[4][tesselation][3],r[tesselation][tesselation][3],tess = 1/((float)tesselation-1);
    float pontos = nPatches*(tesselation)*2*(tesselation)*3*3;
    
    std::fstream g;
    char fic[9+strlen(savefilename)] = "3Dfiles/";
    strcat(fic,savefilename);
    g.open(fic,std::ios::out);
    
    if(g.is_open()){   
    	//numero de pontos
        g << pontos; g << '\n';
        for(int n=0; n<nPatches; n++){
            //recolher os vértices do array ctrPoints para o x y e z
            float p[16][3];
            for(int m=0; m<16; m++){
                p[m][0] = ctrPoints[indicesPatch[n][m]].a;
                p[m][1] = ctrPoints[indicesPatch[n][m]].b;
                p[m][2] = ctrPoints[indicesPatch[n][m]].c;
            }
            int j=0,k=0;
            //desenhar as 4 curvas
            for(int i=0; i<15; i+=4){
                indices[0] = i;
                indices[1] = i+1;
                indices[2] = i+2;
                indices[3] = i+3;
                //calcular a curva
                for(int a=0; a<tesselation-1; a++){
                    t = a*tess;
                    index = floor(t);
                    t = t - index;
                    res[0] = (-p[indices[0]][0] +3*p[indices[1]][0] -3*p[indices[2]][0] +p[indices[3]][0])*t*t*t + (3*p[indices[0]][0] -6*p[indices[1]][0] +3*p[indices[2]][0])*t*t + (-3*p[indices[0]][0] +3*p[indices[1]][0])*t + p[indices[0]][0];
                    res[1] = (-p[indices[0]][1] +3*p[indices[1]][1] -3*p[indices[2]][1] +p[indices[3]][1])*t*t*t + (3*p[indices[0]][1] -6*p[indices[1]][1] +3*p[indices[2]][1])*t*t + (-3*p[indices[0]][1] +3*p[indices[1]][1])*t + p[indices[0]][1];
                    res[2] = (-p[indices[0]][2] +3*p[indices[1]][2] -3*p[indices[2]][2] +p[indices[3]][2])*t*t*t + (3*p[indices[0]][2] -6*p[indices[1]][2] +3*p[indices[2]][2])*t*t + (-3*p[indices[0]][2] +3*p[indices[1]][2])*t + p[indices[0]][2];
                    q[j][k][0] = res[0];
                    q[j][k][1] = res[1];
                    q[j][k][2] = res[2];
                    k++;
                }
                
                t = 1;
                
                res[0] = (-p[indices[0]][0] +3*p[indices[1]][0] -3*p[indices[2]][0] +p[indices[3]][0])*t*t*t + (3*p[indices[0]][0] -6*p[indices[1]][0] +3*p[indices[2]][0])*t*t + (-3*p[indices[0]][0] +3*p[indices[1]][0])*t + p[indices[0]][0];
                res[1] = (-p[indices[0]][1] +3*p[indices[1]][1] -3*p[indices[2]][1] +p[indices[3]][1])*t*t*t + (3*p[indices[0]][1] -6*p[indices[1]][1] +3*p[indices[2]][1])*t*t + (-3*p[indices[0]][1] +3*p[indices[1]][1])*t + p[indices[0]][1];
                res[2] = (-p[indices[0]][2] +3*p[indices[1]][2] -3*p[indices[2]][2] +p[indices[3]][2])*t*t*t + (3*p[indices[0]][2] -6*p[indices[1]][2] +3*p[indices[2]][2])*t*t + (-3*p[indices[0]][2] +3*p[indices[1]][2])*t + p[indices[0]][2];
                
                q[j][k][0] = res[0];
                q[j][k][1] = res[1];
                q[j][k][2] = res[2];
                j++;
                k=0;
            }
            
            for(int j=0; j<tesselation; j++){
                for(int a=0; a<tesselation-1; a++){
                    t = a*tess;;
                    index = floor(t);
                    t = t - index;
                    
                    res[0] = (-q[0][j][0] +3*q[1][j][0] -3*q[2][j][0] +q[3][j][0])*t*t*t + (3*q[0][j][0] -6*q[1][j][0] +3*q[2][j][0])*t*t + (-3*q[0][j][0] +3*q[1][j][0])*t + q[0][j][0];
                    res[1] = (-q[0][j][1] +3*q[1][j][1] -3*q[2][j][1] +q[3][j][1])*t*t*t + (3*q[0][j][1] -6*q[1][j][1] +3*q[2][j][1])*t*t + (-3*q[0][j][1] +3*q[1][j][1])*t + q[0][j][1];
                    res[2] = (-q[0][j][2] +3*q[1][j][2] -3*q[2][j][2] +q[3][j][2])*t*t*t + (3*q[0][j][2] -6*q[1][j][2] +3*q[2][j][2])*t*t + (-3*q[0][j][2] +3*q[1][j][2])*t + q[0][j][2];
                    r[j][k][0] = res[0];
                    r[j][k][1] = res[1];
                    r[j][k][2] = res[2];
                    k++;
                }
                
                t = 1;
                
                res[0] = (-q[0][j][0] +3*q[1][j][0] -3*q[2][j][0] +q[3][j][0])*t*t*t + (3*q[0][j][0] -6*q[1][j][0] +3*q[2][j][0])*t*t + (-3*q[0][j][0] +3*q[1][j][0])*t + q[0][j][0];
                res[1] = (-q[0][j][1] +3*q[1][j][1] -3*q[2][j][1] +q[3][j][1])*t*t*t + (3*q[0][j][1] -6*q[1][j][1] +3*q[2][j][1])*t*t + (-3*q[0][j][1] +3*q[1][j][1])*t + q[0][j][1];
                res[2] = (-q[0][j][2] +3*q[1][j][2] -3*q[2][j][2] +q[3][j][2])*t*t*t + (3*q[0][j][2] -6*q[1][j][2] +3*q[2][j][2])*t*t + (-3*q[0][j][2] +3*q[1][j][2])*t + q[0][j][2];
                
                r[j][k][0] = res[0];
                r[j][k][1] = res[1];
                r[j][k][2] = res[2];
                k=0;
            }
            
            for(int i=0; i<tesselation-1; i++)
                for(int j=0; j<tesselation-1; j++){
                    g << r[i][j][0] 	<< " " << r[i][j][1] 	<< " " << r[i][j][2] 	<< '\n';
                    g << r[i+1][j][0] 	<< " " << r[i+1][j][1] 	<< " " << r[i+1][j][2] 	<< '\n';
                    g << r[i][j+1][0] 	<< " " << r[i][j+1][1] 	<< " " << r[i][j+1][2] 	<< '\n';
                    
                    g << r[i+1][j][0] 	<< " " 	<< r[i+1][j][1] 	<< " " << r[i+1][j][2] 		<< '\n';
                    g << r[i+1][j+1][0] << " "	<< r[i+1][j+1][1] 	<< " " << r[i+1][j+1][2] 	<< '\n';
                    g << r[i][j+1][0] 	<< " "	<< r[i][j+1][1] 	<< " " << r[i][j+1][2] 		<< '\n';
                }
        }
        g.close();
    }
    else { printf("Error: Cannot open file...\n"); exit(0); }
}

int main(int argc, char **argv) {
	if(argc==1) {
		invalidOption();
	} else if(strcmp("plane",argv[1]) == 0) {
		if(argc!=5) {
			invalidOption();
		} else {
			plane(atof(argv[2]),atof(argv[3]),argv[4]);
		}
	} else if(strcmp("box",argv[1]) == 0) {
		if(argc!=6) {
			invalidOption();
		} else {
			box(atof(argv[2]),atof(argv[3]),atof(argv[4]),argv[5]);
		}
	} else if(strcmp("sphere",argv[1]) == 0) {
		if(argc!=6) {
			invalidOption();
		} else {
			sphere(atof(argv[2]),atof(argv[3]),atof(argv[4]),argv[5]);
		}
	} else if(strcmp("cone",argv[1]) == 0) {
		if(argc!=7) {
			invalidOption();
		} else {
			cone(atof(argv[2]),atof(argv[3]),atof(argv[4]),atof(argv[5]),argv[6]);
		}
	}else if(strcmp("bezier",argv[1]) == 0 ){
		if(argc!=5) {
			invalidOption();
		} else {
			bezier(atoi(argv[2]), argv[3], argv[4]);
		}
	} else {
		invalidOption();
	}
	return 0;
}

