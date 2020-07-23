FLAGS = tinyxml2.cpp eng.cpp draw.cpp -lGL -lGLU -lglut 

make: generator.cpp sistemaSolar.cpp
		make clear
		make generator
		make solar

generator: generator.cpp
	$(CXX) generator.cpp -o generator 

solar: sistemaSolar.cpp
	$(CXX) sistemaSolar.cpp -o solar $(FLAGS)

cleanfigures:
	rm -f 3D/*.3d
	rm -f XML/*.xml
	
clear: 
	rm -f generator
	rm -f solar
