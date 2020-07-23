#include <vector>
#include <string>
#include <array>
#include <memory>
#include "scale.h"
#include "rotacaoT.h"
#include "rotacaoV.h"
#include "translacaoT.h"
#include "translacaoV.h"
#include "modeloText.h"
#include "luz.h"

using namespace std;

class SceneGraph {

    // variaveis
	// transformacoes nao baseadas em tempo
    Scale scale;
    TranslacaoV trans;
    RotacaoV rot;

	//transformacoes baseadas em tempo
	TranslacaoT curva;
	RotacaoT eixo;

	// modelos guardados na scenegraph para props de materiais e texturas
	vector<ModTex> modTex;

	//luzes na cena
	vector<shared_ptr<Luz> > luzes;

	// inteiro responsavel pelos VBOS
	GLuint vbo;

	// Descendencia do SceneGraph
        vector<SceneGraph> filhos;
        
        public:
        // Construtores 
        SceneGraph();

		// Setters
        void setScale( Scale ); 
        void setTrans( TranslacaoV );
        void setRot( RotacaoV ); 
		void setCurva( TranslacaoT );
		void setEixo( RotacaoT );
		void setLuzes( vector<shared_ptr<Luz> > );
		void setTexturas( vector<ModTex> );

		// Funcoes adicionais
        void addFilho( SceneGraph ); 

		// Funcao que trata de inicializar os VBOS
		void prep();

		// Funcao responsavel por desenhar a estrutura
        void draw( bool );
};


