FLAGS = -lGL -lGLU -lglut -lIL -lGLEW

make: catmull-rom.cpp
		make clear
		make catmull-rom

catmull-rom: catmull-rom.cpp
	$(CXX) catmull-rom.cpp -o main $(FLAGS)

clear: 
	rm -f main