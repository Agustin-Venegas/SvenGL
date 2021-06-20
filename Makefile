CC = g++
CPPFLAGS = -g -Wall

all : load_stb_image.cpp Utils.cpp Svenium.cpp Text.cpp Cubo.cpp Scene.cpp Scene1.cpp SceneManager.cpp main.cpp
	g++ -g -Wall -Wextra -o SvenGL load_stb_image.cpp Text.cpp Utils.cpp Svenium.cpp Cubo.cpp Scene.cpp Scene1.cpp SceneManager.cpp main.cpp -lGL -lGLEW -lglfw -I /usr/include/freetype2 -lfreetype

easy : load_stb_image.cpp Utils.cpp Svenium.cpp Cubo.cpp Scene1.cpp main.cpp
	g++ *.cpp -I. -o SvenGL

clean:
	$(RM) SvenGL