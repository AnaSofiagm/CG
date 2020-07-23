#include <vector>
#include <string>
#include <array>
#include <GL/glut.h>

#ifndef __ESTRUTURAS__
#define __ESTRUTURAS__

using namespace std;

/*
 * Estrutura usada para guardar as coordenadas de um ponto
 * num espaco 3D 
 */
struct ponto {
	float a;
	float b;
	float c;
};

typedef struct ponto Pontos;

/*
 * Class principal para codificacao de um SceneGraph basico
 * para os arrays que codificam certas rotacoes, etc a posicao 0 
 * simboliza a coordenada x, a posicao 1 codifca a coordenada y, etc.
 * No caso das rotacoes a posicao 0 codifica o angulo 
 * e de seguida sao dados os eixos de rotacao.
 *
 * A funcao de desenho considera escalas primeiro, rotacoes de seguida e 
 * finalmente translacoes
 */
class SceneGraph {

        // variaveis
        array<float, 3> scale;
        array<float, 3> trans;
        array<float, 3> cor;
        array<float, 4> rot;
        vector<vector<Pontos>> modelos;
        vector<SceneGraph> filhos;
        
        public:
                // Construtores 
                SceneGraph();

		// Setters
                void setScale( array<float, 3> ); 
                void setTrans( array<float, 3> );
                void setCor( array<float, 3> );
                void setRot( array<float, 4> ); 
                void setModelo( vector<vector<Pontos>> );

		// Getters
                array<float, 3> getScale(); 
                array<float, 3> getTrans();
                array<float, 3> getCor();
                array<float, 4> getRot();
                vector<vector<Pontos>> getModelos();
                vector<SceneGraph> getFilhos();

		// Funcoes adicionais
                void addFilho( SceneGraph ); 
                void addModelo( vector<Pontos> );

		// Funcao responsavel por desenhar a estrutura
                void draw() const;
};

#endif
