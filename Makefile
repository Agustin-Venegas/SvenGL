# build an executable named myprog from myprog.c
all : load_stb_image.cpp Utils.cpp Svenium.cpp Cubo.cpp Scene1.cpp main.cpp
	g++ -g -Wall -Wextra -o Tarea2 load_stb_image.cpp Utils.cpp Svenium.cpp Cubo.cpp Scene1.cpp main.cpp -lGL -lGLEW -lglfw

clean:
	$(RM) Tarea2