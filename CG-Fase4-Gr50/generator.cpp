#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

struct Ponto {
    float x;
    float y;
    float z;
};

vector<float> pushVert(vector<float> vertices, float a, float b, float c) {
    vertices.push_back(a);
    vertices.push_back(b);
    vertices.push_back(c);

    return vertices;
}

vector<float> pushNormal(vector<float> norm, float a, float b, float c) {
    norm.push_back(a);
    norm.push_back(b);
    norm.push_back(c);
    return norm;
}

vector<float> pushText(vector<float> text, float a, float b) {
    text.push_back(a);
    text.push_back(b);
    return text;
}

void plane(float length, float width, char* filename) {
    char fic[9+strlen(filename)] = "3Dfiles/";
    strcat(fic,filename);
    std::ofstream outfile(fic);

    float x = length/2;         //coordenada no eixo x
    float z = width/2;          //coordenada eixo z

    vector<float> vertices; 
    vector<float> normais;
    vector<float> textura;

    /* ----- PLANE -----    

    - PONTOS:
        A _____ B
         /\    /
        /  \  /
      D/____\/C
    
    - Normais:
        No caso de um plano XZ é trivialmente verdade que a normal é a mesma em todos os pontos do plano,
        em particular nas extremidades, e que é igual a (0,1,0)
    - Textura:
    (0,1) ___(1,1)
         |   |
    (0,0)|___|(1,0)
        
        Mapear as extremidades do plano para a extremidade correspondente da textura
        A para (0,1), B para (1,1), C para (1,0) e D para (0,0)

    */

    //Triangulo ABC virado para a frente
    //A
    vertices = pushVert(vertices,-x,0.0,z);
    normais = pushNormal(normais,0.0,1.0,0.0);
    textura = pushText(textura,0.0,1.0);
    //C
    vertices = pushVert(vertices,x,0.0,-z);
    normais = pushNormal(normais,0.0,1.0,0.0);
    textura = pushText(textura,1.0,0.0);
    //B
    vertices = pushVert(vertices,x,0.0,z);
    normais = pushNormal(normais,0.0,1.0,0.0);
    textura = pushText(textura,1.0,1.0);

    //Triangulo ABC virado para a trás
    //A
    vertices = pushVert(vertices,-x,0.0,z);
    normais = pushNormal(normais,0.0,1.0,0.0);
    textura = pushText(textura,0.0,1.0);
    //B
    vertices = pushVert(vertices,x,0.0,z);
    normais = pushNormal(normais,0.0,1.0,0.0);
    textura = pushText(textura,1.0,1.0);
    //C
    vertices = pushVert(vertices,x,0.0,-z);
    normais = pushNormal(normais,0.0,1.0,0.0);
    textura = pushText(textura,1.0,0.0);

    //Triangulo ADC virado para a frente
    //A
    vertices = pushVert(vertices,-x,0.0,z);
    normais = pushNormal(normais,0.0,1.0,0.0);
    textura = pushText(textura,0.0,1.0);
    //D
    vertices = pushVert(vertices,-x,0.0,-z);
    normais = pushNormal(normais,0.0,1.0,0.0);
    textura = pushText(textura,0.0,0.0);
    //C
    vertices = pushVert(vertices,x,0.0,-z);
    normais = pushNormal(normais,0.0,1.0,0.0);
    textura = pushText(textura,1.0,0.0);

    //Triangulo ADC virado para a trás
    //A
    vertices = pushVert(vertices,-x,0.0,z);
    normais = pushNormal(normais,0.0,1.0,0.0);
    textura = pushText(textura,0.0,1.0);
    //C
    vertices = pushVert(vertices,x,0.0,-z);
    normais = pushNormal(normais,0.0,1.0,0.0);
    textura = pushText(textura,1.0,0.0);    
    //D
    vertices = pushVert(vertices,-x,0.0,-z);
    normais = pushNormal(normais,0.0,1.0,0.0);
    textura = pushText(textura,0.0,0.0);

    outfile << "36" << endl;

    //print vertices
    for( float i: vertices ){
        outfile << i << endl;
    }

    //print normais
    for( float i: normais ){
        outfile << i << endl;
    }

    //print textura
    for( float i: textura ){
        outfile << i << endl;
    }

    outfile.close();
}


void box(float length, float width, float heigth, char* filename) {
    char fic[9+strlen(filename)] = "3Dfiles/";
    strcat(fic,filename);
    std::ofstream outfile(fic);

    /* BOX, missing lines AE, BF, CG, DH
                 A _____ B          
                 /\    /            
                /  \  /             
              C/____\/D             
          E_____F                   
         /\    /                    
        /  \  /                     
      G/____\/H                     

    Normais:
        Paralelas a XY: (0,0,1), (0,0,-1)
        Paralelas a XZ: (0,1,0), (0,-1,0)
        Paralelas a YZ: (1,0,0), (0,0,0)

    Textura:
         ____________________
       E|   F|   B|   A|   F|
        |    |    |    |    |
       G|___H|___D|___C|___G|
       A|        B|G       H|
        |         |         |
       E|________F|C_______D|   

    Lados:
       A vertices = pushVert(vertices,-x,y,-z);
         textura = pushText(textura,0.75,1.0);
       B vertices = pushVert(vertices,x,y,-z);
         textura = pushText(textura,0.5,1.0);
       C vertices = pushVert(vertices,-x,-y,-z);
         textura = pushText(textura,0.75,0.5);
       D vertices = pushVert(vertices,x,-y,-z);
         textura = pushText(textura,0.5,0.5);
       E vertices = pushVert(vertices,-x,y,z);
         textura = pushText(textura,0.0,1.0);
       F vertices = pushVert(vertices,x,y,z);
         textura = pushText(textura,0.25,1.0);
       G vertices = pushVert(vertices,-x,-y,z);
         textura = pushText(textura,0.0,0.5);
       H vertices = pushVert(vertices,x,-y,z);
         textura = pushText(textura,0.25,0.5);

    */

    float x = length/2;
    float y = heigth/2;
    float z = width/2;

    vector<float> vertices; 
    vector<float> normais;
    vector<float> textura;

    /*ABDC */
    //A
    vertices = pushVert(vertices,-x,y,-z);
    normais = pushNormal(normais,0.0,0.0,-1.0);
    textura = pushText(textura,0.75,1.0);
    //B
    vertices = pushVert(vertices,x,y,-z);
    normais = pushNormal(normais,0.0,0.0,-1.0);
    textura = pushText(textura,0.5,1.0);
    //D
    vertices = pushVert(vertices,x,-y,-z);
    normais = pushNormal(normais,0.0,0.0,-1.0);
    textura = pushText(textura,0.5,0.5);  

    //D
    vertices = pushVert(vertices,x,-y,-z);
    normais = pushNormal(normais,0.0,0.0,-1.0);
    textura = pushText(textura,0.5,0.5); 
    //C
    vertices = pushVert(vertices,-x,-y,-z);
    normais = pushNormal(normais,0.0,0.0,-1.0);
    textura = pushText(textura,0.75,0.5); 
    //A
    vertices = pushVert(vertices,-x,y,-z);
    normais = pushNormal(normais,0.0,0.0,-1.0);
    textura = pushText(textura,0.75,1.0);

    /*EGHF */
    //E
    vertices = pushVert(vertices,-x,y,z);
    normais = pushNormal(normais,0.0,0.0,1.0);
    textura = pushText(textura,0.0,1.0);
    //G
    vertices = pushVert(vertices,-x,-y,z);
    normais = pushNormal(normais,0.0,0.0,1.0);
    textura = pushText(textura,0.0,0.5);
    //H
    vertices = pushVert(vertices,x,-y,z);
    normais = pushNormal(normais,0.0,0.0,1.0);
    textura = pushText(textura,0.25,0.5);  

    //H
    vertices = pushVert(vertices,x,-y,z);
    normais = pushNormal(normais,0.0,0.0,1.0);
    textura = pushText(textura,0.25,0.5); 
    //F
    vertices = pushVert(vertices,x,y,z);
    normais = pushNormal(normais,0.0,0.0,1.0);
    textura = pushText(textura,0.25,1.0); 
    //E
    vertices = pushVert(vertices,-x,y,z);
    normais = pushNormal(normais,0.0,0.0,1);
    textura = pushText(textura,0.0,1.0);
    
    /*AEFB */
    //A
    vertices = pushVert(vertices,-x,y,-z);
    normais = pushNormal(normais,0.0,1.0,0.0);
    textura = pushText(textura,0.0,0.5);
    //E
    vertices = pushVert(vertices,-x,y,z);
    normais = pushNormal(normais,0.0,1.0,0.0);
    textura = pushText(textura,0.0,0.0);
    //F
    vertices = pushVert(vertices,x,y,z);
    normais = pushNormal(normais,0.0,1.0,0.0);
    textura = pushText(textura,0.5,0.0);  

    //F
    vertices = pushVert(vertices,x,y,z);
    normais = pushNormal(normais,0.0,1.0,0.0);
    textura = pushText(textura,0.5,0.0); 
    //B
    vertices = pushVert(vertices,x,y,-z);
    normais = pushNormal(normais,0.0,1.0,0.0);
    textura = pushText(textura,0.5,0.5); 
    //A
    vertices = pushVert(vertices,-x,y,-z);
    normais = pushNormal(normais,0.0,1.0,0.0);
    textura = pushText(textura,0.0,0.5);

    /*BFHD*/
    //B
    vertices = pushVert(vertices,x,y,-z);
    normais = pushNormal(normais,1.0,0.0,0.0);
    textura = pushText(textura,0.5,1.0);
    //F
    vertices = pushVert(vertices,x,y,z);
    normais = pushNormal(normais,1.0,0.0,0.0);
    textura = pushText(textura,0.25,1.0);
    //H
    vertices = pushVert(vertices,x,-y,z);
    normais = pushNormal(normais,1.0,0.0,0.0);
    textura = pushText(textura,0.25,0.5);  

    //H
    vertices = pushVert(vertices,x,-y,z);
    normais = pushNormal(normais,1.0,0.0,0.0);
    textura = pushText(textura,0.25,0.5); 
    //D
    vertices = pushVert(vertices,x,-y,-z);
    normais = pushNormal(normais,1.0,0.0,0.0);
    textura = pushText(textura,0.5,0.5); 
    //B
    vertices = pushVert(vertices,x,y,-z);
    normais = pushNormal(normais,1.0,0.0,0.0);
    textura = pushText(textura,0.5,1.0);

    /*ACGE */    
    //A
    vertices = pushVert(vertices,-x,y,-z);
    normais = pushNormal(normais,-1.0,0.0,0.0);
    textura = pushText(textura,0.75,1.0);
    //C
    vertices = pushVert(vertices,-x,-y,-z);
    normais = pushNormal(normais,-1.0,0.0,0.0);
    textura = pushText(textura,0.75,0.5);
    //G
    vertices = pushVert(vertices,-x,-y,z);
    normais = pushNormal(normais,-1.0,0.0,0.0);
    textura = pushText(textura,1.0,0.5);  

    //G
    vertices = pushVert(vertices,-x,-y,z);
    normais = pushNormal(normais,-1.0,0.0,0.0);
    textura = pushText(textura,1.0,0.5); 
    //E
    vertices = pushVert(vertices,-x,y,z);
    normais = pushNormal(normais,-1.0,0.0,0.0);
    textura = pushText(textura,1.0,1.0); 
    //A
    vertices = pushVert(vertices,-x,y,-z);
    normais = pushNormal(normais,-1.0,0.0,0.0);
    textura = pushText(textura,0.75,1.0);

    /*GCDH*/
    //C
    vertices = pushVert(vertices,-x,-y,-z);
    normais = pushNormal(normais,0.0,-1.0,0.0);
    textura = pushText(textura,0.5,0.0);
    //D
    vertices = pushVert(vertices,x,-y,-z);
    normais = pushNormal(normais,0.0,-1.0,0.0);
    textura = pushText(textura,1.0,0.0);
    //H
    vertices = pushVert(vertices,x,-y,z);
    normais = pushNormal(normais,0.0,-1.0,0.0);
    textura = pushText(textura,1.0,0.5);  

    //H
    vertices = pushVert(vertices,x,-y,z);
    normais = pushNormal(normais,0.0,-1.0,0.0);
    textura = pushText(textura,1.0,0.5); 
    //G
    vertices = pushVert(vertices,-x,-y,z);
    normais = pushNormal(normais,0.0,-1.0,0.0);
    textura = pushText(textura,0.5,0.5); 
    //C
    vertices = pushVert(vertices,-x,-y,-z);
    normais = pushNormal(normais,0.0,-1.0,0.0);
    textura = pushText(textura,0.5,0.0);

    outfile << vertices.size() << endl;
    //print vertices
    for( float i: vertices ){
        outfile << i << endl;
    }

    //print normais
    for( float i: normais ){
        outfile << i << endl;
    }

    //print textura
    for( float i: textura ){
        outfile << i << endl;
    }

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

        Normais:
            sin(alpha)*cos(betha), sin(alpha)*sin(betha), cos(alpha)
        
        Textura:
            Sejam alpha e beta os ângulos que variam, respectivamente [0..2*PI] e [-PI/2 ... PI /2], facilmente se
            mapeiam para espaço textura (u e v ambos a variar entre 0 e 1 ) com as transformações:
                u = a / (2 * PI);
                v = (b / PI) + 0.5;
    */

    float b = M_PI/stacks;                  //variação entre cada stack
    float a = (2*M_PI)/slices;              //variacao entra cada slice

    vector<float> vertices; 
    vector<float> normais;
    vector<float> textura;

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
            vertices = pushVert(vertices,(radius*cos(betha)*sin(alpha)), (radius*sin(betha)), (radius*cos(betha)*cos(alpha)));
            normais = pushNormal(normais,sin(alpha)*cos(betha),sin(alpha)*sin(betha),cos(alpha));
            textura = pushText(textura,(alpha/(2*M_PI)),((betha/M_PI)+0.5));
                
            vertices = pushVert(vertices,(radius*cos(betha)*sin(alpha+a)), (radius*sin(betha)), (radius*cos(betha)*cos(alpha+a)));
            normais = pushNormal(normais,sin(alpha+a)*cos(betha),sin(alpha+a)*sin(betha),cos(alpha+a));
            textura = pushText(textura,((alpha+a)/(2*M_PI)),((betha/M_PI)+0.5));
                
            vertices = pushVert(vertices,radius*cos(betha+b)*sin(alpha+a), (radius*sin(betha+b)), (radius*cos(betha+b)*cos(alpha+a)));
            normais = pushNormal(normais,sin(alpha+a)*cos(betha+b),sin(alpha+a)*sin(betha+b),cos(alpha+a));
            textura = pushText(textura,((alpha+a)/(2*M_PI)),(((betha+b)/M_PI)+0.5));

            //Triangulo CDA
            vertices = pushVert(vertices,radius*cos(betha+b)*sin(alpha+a), (radius*sin(betha+b)), (radius*cos(betha+b)*cos(alpha+a)));
            normais = pushNormal(normais,sin(alpha+a)*cos(betha+b),sin(alpha+a)*sin(betha+b),cos(alpha+a));
            textura = pushText(textura,((alpha+a)/(2*M_PI)),(((betha+b)/M_PI)+0.5));
            
            vertices = pushVert(vertices,(radius*cos(betha+b)*sin(alpha)), (radius*sin(betha+b)), (radius*cos(betha+b)*cos(alpha)));
            normais = pushNormal(normais,sin(alpha)*cos(betha+b),sin(alpha)*sin(betha+b),cos(alpha));
            textura = pushText(textura,(alpha/(2*M_PI)),(((betha+b)/M_PI)+0.5));
                
            vertices = pushVert(vertices,(radius*cos(betha)*sin(alpha)), (radius*sin(betha)), (radius*cos(betha)*cos(alpha)));
            normais = pushNormal(normais,sin(alpha)*cos(betha),sin(alpha)*sin(betha),cos(alpha));
            textura = pushText(textura,(alpha/(2*M_PI)),((betha/M_PI)+0.5));

        }
    }

    outfile << vertices.size() << endl;
    //print vertices
    for( float i: vertices ){
        outfile << i << endl;
    }

    //print normais
    for( float i: normais ){
        outfile << i << endl;
    }

    //print textura
    for( float i: textura ){
        outfile << i << endl;
    }

    outfile.close();
}


void cone(float radius, float heigth, float slices, float stacks, char* filename) {
    char fic[9+strlen(filename)] = "3Dfiles/";
    strcat(fic,filename);
    std::ofstream outfile(fic);

    /*  
        Formato textura:
        
        Cone:
        (0,1)       ----------------(1,1)
                    |               |
                    |               |
        (0,0,375)   |_______________|(1,0.375)
                    |________|BASE__|
                         (0.625,0)   (1,0)
    */

    /* BASE - circunferenciaf formada por triangulos virados para baixo 
        
        Virado para baixo centrado em 0 => normal = 0,-1,0
        
        Textura
            posicionar no centro da circunferência(0.8125,0.1875), e obter os pontos da circunferência
            (0.8125+1.875*sinf(alpha),0.1875+0.1875*cos(alpha))
    */
    float a = (2*M_PI)/slices;              //variacao entra cada slice

    vector<float> vertices; 
    vector<float> normais;
    vector<float> textura;

    for(float alpha=0; alpha<(2*M_PI); alpha+=a) {
        vertices = pushVert(vertices,0,0,0);
        normais = pushNormal(normais,0,0,-1);
        textura = pushText(textura,0.8125+1.875*sin(0),0.8125+0.1875*cos(0));
            
        vertices = pushVert(vertices, (sin(alpha+a)), 0, (radius*cos(alpha+a)));
        normais = pushNormal(normais,0,0,-1);
        textura = pushText(textura,0.8125+1.875*sin(alpha+a),0.8125+0.1875*cos(alpha+a));
                
        vertices = pushVert(vertices,(radius*sin(alpha)), 0, (radius*cos(alpha)));
        normais = pushNormal(normais,0,0,-1);
        textura = pushText(textura,0.8125+1.875*sin(alpha),0.8125+0.1875*cos(alpha));
    }
    /*
    y               /\              |s
    |              /  \             |t
    |___x         /    \            |a
    0            /      \           |c
                /        \          |k
                ----------          |s
                s|l|i|c|e|s

        Textura:
            (1/slice,0.375+(0.625/stack));

    */
    float hvar = heigth/stacks;                 //variaçao entre cada stack
    float r = radius/stacks;                    //variaçao do raio em cada stack
    /*
        ciclo exterior percore as stacks;
        ciclo interior percore as slices;
    */
    for(float y=0; y<stacks; y++) {
        for(float alpha = 0; alpha<(2*M_PI); alpha += a) {
            /*
                Considerando o rectangulo formado entre cada par de slices:
                D____C
                |    |
                |    |
                A____B

            */

            //Triangulo ABC
            vertices = pushVert(vertices,radius*sin(alpha),hvar*y,radius*cos(alpha));
            normais = pushNormal(normais,sin(alpha),(hvar*y),cos(alpha));
            textura = pushText(textura,alpha/(2*M_PI),0.375+(0.625/y));

            vertices = pushVert(vertices,radius*sin(alpha+a),(hvar*y),radius*cos(alpha+a));
            normais = pushNormal(normais,sin(alpha+a),(hvar*y),cos(alpha+a));
            textura = pushText(textura,(alpha+a)/(2*M_PI),0.375+(0.625/y));
                
            vertices = pushVert(vertices,(radius-r)*sin(alpha+a),hvar*(y+1),(radius-r)*cos(alpha+a));
            normais = pushNormal(normais,sin(alpha+a),hvar*(y+1),cos(alpha+a));
            textura = pushText(textura,(alpha+a)/(2*M_PI),0.375+(0.625/(y+hvar)));

            //Triangulo CDA
            vertices = pushVert(vertices,(radius-r)*sin(alpha+a),hvar*(y+1),(radius-r)*cos(alpha+a));
            normais = pushNormal(normais,sin(alpha+a),hvar*(y+1),cos(alpha+a));
            textura = pushText(textura,(alpha+a)/(2*M_PI),0.375+(0.625/(y+hvar)));
            
            vertices = pushVert(vertices,(radius-r)*sin(alpha),hvar*(y+1),(radius-r)*cos(alpha));
            normais = pushNormal(normais,sin(alpha),hvar*(y+1),cos(alpha));
            textura = pushText(textura,alpha/(2*M_PI),0.375+(0.625/(y+hvar)));
                
            vertices = pushVert(vertices,radius*sin(alpha),(hvar*y),radius*cos(alpha));
            normais = pushNormal(normais,sin(alpha),(hvar*y),cos(alpha));
            textura = pushText(textura,alpha/(2*M_PI),0.375+(0.625/y));
        }
        radius = radius - r;
    }

    outfile << vertices.size() << endl;
    //print vertices
    for( float i: vertices ){
        outfile << i << endl;
    }

    //print normais
    for( float i: normais ){
        outfile << i << endl;
    }

    //print textura
    for( float i: textura ){
        outfile << i << endl;
    }

    outfile.close();
}


/*
    Recebe a tesselacao, e o nome dos ficheiros de input(bezier patch)
    e output(ficheiro .3d destino), fazendo entra as transformações necessárias
*/
/*
void bezier(int tesselation, const char* patchfilename, const char* savefilename){
    //--- PARSING PATCH ---//
    std::fstream f;
    f.open(patchfilename,std::ios::in);
    int nPatches=0;
    int nCtrPoints=0;
    std::vector<std::vector<int> > indicesPatch;
    std::vector<Ponto> ctrPoints;
    */
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
/*
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
            p.x = x; p.y = y; p.z = z;
            
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
                p[m][0] = ctrPoints[indicesPatch[n][m]].x;
                p[m][1] = ctrPoints[indicesPatch[n][m]].y;
                p[m][2] = ctrPoints[indicesPatch[n][m]].z;
            }
            int j=0,k=0;
            //desenhar as 4 curvas
            for(int i=0; i<15; i+=4){
                indices[0] = i;
                indices[1] = i+1;
                indices[2] = i+2;
                indices[3] = i+3;
                //calcular a curva
                for(int x=0; x<tesselation-1; x++){
                    t = x*tess;
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
                for(int x=0; x<tesselation-1; x++){
                    t = x*tess;;
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
                    g << r[i][j][0]     << "\n" << r[i][j][1]   << "\n" << r[i][j][2]   << '\n';
                    g << r[i+1][j][0]   << "\n" << r[i+1][j][1]     << "\n" << r[i+1][j][2]     << '\n';
                    g << r[i][j+1][0]   << "\n" << r[i][j+1][1]     << "\n" << r[i][j+1][2]     << '\n';
                    
                    g << r[i+1][j][0]   << "\n"     << r[i+1][j][1]     << "\n" << r[i+1][j][2]         << '\n';
                    g << r[i+1][j+1][0] << "\n" << r[i+1][j+1][1]   << "\n" << r[i+1][j+1][2]   << '\n';
                    g << r[i][j+1][0]   << "\n" << r[i][j+1][1]     << "\n" << r[i][j+1][2]         << '\n';
                }
        }
        g.close();
    }
    else { printf("Error: Cannot open file...\n"); exit(0); }
}*/

void invalidOption() {
    printf("Invalid comand\nAvailable Options:\n");
    printf("plane <length> <width> <filename>\n");
    printf("box <length> <width> <heigth> <filename>\n");
    printf("sphere <radius> <slices> <stacks> <filename>\n");
    printf("cone <bottom radius> <heigth> <slices> <stacks> <filename>\n");
    //printf("bezier <tesselation> <inputFilename> <outputFilename>\n");
}

int main( int argc ,char **argv) {
    if(!strcmp("plane",argv[1])) {
        if(argc!=5) {
            invalidOption();
        } else {
            plane(atof(argv[2]),atof(argv[3]),argv[4]);
        }
    } else if(!strcmp("box", argv[1])){
        if(argc!=6) {
            invalidOption();
        } else {
            box( atoi(argv[2]), atof(argv[3]), atof(argv[4]), argv[5] );
        }
    } else if (!strcmp("sphere", argv[1])){
        if(argc!=6) {
            invalidOption();
        } else {
            sphere(atof(argv[2]), atoi(argv[3]), atoi(argv[4]), argv[5]);
        }
    } else if ( !strcmp("cone", argv[1])){
        if(argc!=7) {
            invalidOption();
        }
        else{    
            cone( atof(argv[2]), atof(argv[3]), atoi(argv[4]), atoi(argv[5]),argv[6]);
        }
    } /*}else if(strcmp("bezier",argv[1]) == 0 ){
        if(argc!=5) {
            invalidOption();
        } else {
            bezier(atoi(argv[2]), argv[3], argv[4]);
        }
    }
    */else {
        invalidOption();
    }
    return 0;
}







