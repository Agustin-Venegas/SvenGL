# build an executable named myprog from myprog.c
all : Utils.cpp Model.cpp Scene.cpp SceneManager.cpp Scene1.cpp main.cpp
	g++ -g -Wall -Wextra -o Tarea1 Utils.cpp Model.cpp Scene.cpp SceneManager.cpp Scene1.cpp main.cpp -lGL -lGLEW -lglfw

clean:
	$(RM) Tarea1