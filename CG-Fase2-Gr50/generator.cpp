#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>

#define _USE_MATH_DEFINE
#include <math.h>

using namespace std;

void invalidOption() {
	printf("Invalid comand\nAvailable Options:\n");
	printf("plane <length> <width> <filename>\n");
	printf("box <length> <width> <heigth> <filename>\n");
	printf("sphere <radius> <slices> <stacks> <filename>\n");
	printf("cone <bottom radius> <heigth> <slices> <stacks> <filename>\n");
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
	} else {
		invalidOption();
	}
	return 0;
}
