FLAGS = tinyxml2.cpp  -lGL -lGLU -lglut 

make: generator.cpp engine.cpp
		make clear
		make generator
		make engine

generator: generator.cpp
	$(CXX) generator.cpp -o generator

engine: engine.cpp
	$(CXX) engine.cpp -o engine $(FLAGS)

cleanfigures:
	rm -f 3D/*.3d
	rm -f XML/*.xml
	
clear: 
	rm -f generator
	rm -f engine