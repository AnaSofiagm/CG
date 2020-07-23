#include <vector>
#include <string>

#include "scale.h"
#include "rotacao.h"
#include "rotacaoV.h"
#include "translacao.h"
#include "translacaoV.h"
#include "cor.h"

using namespace std;

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
	// transformacoes nao baseadas em tempo
	Scale scale;
	TranslacaoV trans;
	RotacaoV rot;
	Cor cor;

	//transformacoes baseadas em tempo
	Translacao curva;
	Rotacao eixo;

	// modelos guardados na scenegraph
	vector<float> modelos;

	// inteiro responsavel pelos VBOS
	GLuint vbo;

	// Descendencia do SceneGraph
	vector<SceneGraph> filhos;

	public:
	// Construtores 
	SceneGraph();

	// Setters
	void setScale( Scale );
	void setCor( Cor );
	void setTrans( TranslacaoV );
	void setRot( RotacaoV );
	void setModelo( vector<float> );
	void setCurva( Translacao );
	void setEixo( Rotacao );

	// Funcoes adicionais
	void addFilho( SceneGraph );

	// Funcao que trata de inicializar os VBOS
	void prep();

	// Funcao responsavel por desenhar a estrutura
	void draw( bool );
};


