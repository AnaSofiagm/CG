#include "engine.h"

class TimedSG {

	SceneGraph sg;

	public:
		TimedSG();
		void setSG( SceneGraph );
		void prep();	
		void draw();
};


