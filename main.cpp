#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "utils.h"
#include "Scene.h"

using namespace std; //the

int main()
{    
	glewExperimental = true; // Needed for core profile
	if( !glfwInit() )
	{
    	fprintf( stderr, "Failed to initialize GLFW\n" );
    	return -1;
	}

	//variables de ventana
	glfwWindowHint(GLFW_SAMPLES, 4); //antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); 
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window;
	window = glfwCreateWindow( 800, 600, "La Ventana", NULL, NULL);
	if( window == NULL ){
    	fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
    	glfwTerminate();
    	return -1;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
    	fprintf(stderr, "Failed to initialize GLEW\n");
    	return -1;
	}

	//Cargar Shaders y programa
	GLuint vertex;
	vertex = glCreateShader(GL_VERTEX_SHADER);
	Utils::CompileShader(vertex, Utils::ReadFile("vertex.elformato"));

	GLuint fragment;
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	Utils::CompileShader(fragment, Utils::ReadFile("fragment.elformato"));
	
	Utils::program = glCreateProgram();
	glAttachShader(Utils::program, vertex);
	glAttachShader(Utils::program, fragment);
	glLinkProgram(Utils::program);
	Utils::CheckProgramCompile(Utils::program);

	glDeleteShader(vertex); //se pueden borrar sin problemas dice
    glDeleteShader(fragment);


	//Iniciar Escenas
	Scene::InitVals();

	//Ciclo Principal de Dibujado
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	do {
    	//Borrar la ventana con el color
    	glClear( GL_COLOR_BUFFER_BIT );

    	// Aqui va todo lo que se dibuja y actualiza
		Scene::actualScene.Update((float)glfwGetTime());

    	// Cambiar buffers (imagen de antes/imagen de ahora)
    	glfwSwapBuffers(window);
    	glfwPollEvents();

	} while
	(glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && !glfwWindowShouldClose(window));

    
    cout << "Hello World!" << endl;
    return 0;
}