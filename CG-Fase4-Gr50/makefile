FLAGS= tinyxml2.cpp engine.cpp draw.cpp pointLight.cpp directionLight.cpp spotLight.cpp modeloText.cpp catmull.cpp rotacaoT.cpp translacaoT.cpp scale.cpp timedsg.cpp translacaoV.cpp rotacaoV.cpp -lGL -lGLU -lglut -lIL -lGLEW

make: generator.cpp sistemaSolar.cpp
		make clear
		make generator
		make solar

gen: gen.cpp
	$(CXX) generator.cpp -o generator 

solar: sistemaSolar.cpp
	$(CXX) sistemaSolar.cpp -o solar -Wall $(FLAGS)

cleanfigures:
	rm -f 3D/*.3d
	rm -f XML/*.xml
	
clear: 
	rm -f generator
	rm -f solar
