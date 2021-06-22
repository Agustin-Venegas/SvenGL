#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <chrono>

#include "Utils.h"
#include "Cubo.h"
#include "Scene1.h"
#include "EscenaCubemap.h"
#include "EscenaInicial.h"
#include "SceneManager.h"
#include "Svenium.h"
#include "Text.h"
#include "Plane.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


//Cosas nuestras
GLFWwindow* window; //ventana static
int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "SvenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }


    Utils::window = window;

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);

    //Capturar el mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glewExperimental = true; //Si borro esto no corre
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

    auto t_start = std::chrono::high_resolution_clock::now();
    auto t_end = std::chrono::high_resolution_clock::now();
	
	
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);

    glEnable(GL_DEPTH_TEST);

    Text::Init();
    

	Scene1 scene = Scene1();
    EscenaCubemap scene2 = EscenaCubemap();
    EscenaInicial scene0 = EscenaInicial();
    SceneManager::Instance->AddScene(scene);
    SceneManager::Instance->AddScene(scene2);
    SceneManager::Instance->AddScene(scene0);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
		t_start = t_end;
        t_end = std::chrono::high_resolution_clock::now();
		
		Utils::deltatime = std::chrono::duration<float>(t_end - t_start).count();
		
        // input
        // -----
        processInput(window);


        // render
        // ------
        glClearColor(0.15f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        SceneManager::Instance->Update(Utils::deltatime);
        SceneManager::Instance->Draw(Utils::deltatime);
 
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
	
	

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
}

void processInput(GLFWwindow *window) 
{

}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    SceneManager::Instance->MouseMovement(xpos, ypos);
}