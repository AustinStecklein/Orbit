mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
PROJECT_PATH := $(patsubst %/,%,$(dir $(mkfile_path)))
SFML_PATH := $(PROJECT_PATH)/core/framework/SFML
export LD_LIBRARY_PATH=$(SFML_PATH)/SFML-2.6.0/lib

SFML_LIB := $(SFML_PATH)/SFML-2.6.0/lib
SFML_LINKS := -lsfml-graphics -lsfml-window -lsfml-system
SFML_INCLUDE := -I$(SFML_PATH)/SFML-2.6.0/include

SOURCE_INCLUDES := ./core/src/CelestialBody.h ./core/src/Vector3D.h ./core/src/GameObject.h ./core/src/Display.h


#build main project
main.o: ./core/main.cpp
	g++ -c -g ./core/main.cpp -I./core/

#build src dir
Orbit.o: ./core/src/Orbit.h ./core/src/Orbit.cpp $(SOURCE_INCLUDES)
	g++ -c -g ./core/src/Orbit.cpp $(SFML_INCLUDE) -I./core/

#build parse dir
FileInput.o: ./core/Parser/FileInput.h ./core/Parser/FileInput.cpp
	g++ -c -g ./core/Parser/FileInput.cpp -I./core/

TestVectors.o: ./core/test/TestVectors.cpp
	g++ -c -g ./core/test/TestVectors.cpp -I./core/

Display.o: ./core/src/Display.h ./core/src/Display.cpp
	g++ -c -g ./core/src/Display.cpp $(SFML_INCLUDE) -I./core/

compile: main.o Orbit.o FileInput.o Display.o
	g++ main.o Orbit.o FileInput.o Display.o -g -o sim -L$(SFML_LIB) $(SFML_LINKS) 

run: 
	./sim

clean: 
	rm ./sim main.o Orbit.o FileInput.o Display.o

all:
	export LD_LIBRARY_PATH=/home/austin/projects/SFML/SFML-2.6.0/lib
	make clean
	make compile
	make run

test: TestVectors.o
	g++ TestVectors.o
	./a.out



