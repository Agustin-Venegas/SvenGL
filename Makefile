# build an executable named myprog from myprog.c
all: main.cpp utils.cpp Model.cpp Scene.cpp
	g++ -g -Wall -o Tarea1 main.cpp utils.cpp Model.cpp Scene.cpp -lGL -lGLEW -lglfw

clean: 
	$(RM) Tarea1