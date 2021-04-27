# build an executable named myprog from myprog.c
all : Utils.cpp Scene.cpp main.cpp
	g++ -g -Wall -Wextra -o Tarea1 Utils.cpp Scene.cpp main.cpp -lGL -lGLEW -lglfw

clean:
	$(RM) Tarea1