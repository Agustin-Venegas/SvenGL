# build an executable named myprog from myprog.c
all: main.cpp
	g++ -g -Wall -o Tarea1 main.cpp -lGL -lGLEW -lglfw

clean: 
	$(RM) Tarea1