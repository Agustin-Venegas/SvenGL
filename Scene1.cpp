#include "Scene1.h"
#include "Utils.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

glm::mat4 Scene1::cam = glm::lookAt(glm::vec3(0.0f,-1.0f,0-5.0f), glm::vec3(0.0f,0.0f,-2.0f), glm::vec3(0.0f, 1.0f, 0.0f));

#include <GL/glew.h>
#include <GLFW/glfw3.h>

Scene1::Scene1()
{
    CuboLuz::InitValues();

    sven = Svenium();
    
    sun = CuboLuz(2, glm::vec3(1.0f,0.88f, 0.0f));
    cube = CuboLuz();
}

void Scene1::Init() 
{
    
}

void Scene1::Update(float dt) 
{

    if (glfwGetKey(Utils::window, GLFW_KEY_KP_ADD) == GLFW_PRESS)
		if (sven.size < 5.0f) sven.size += 0.33f*dt; else sven.size = 5.0f;
	if (glfwGetKey(Utils::window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS)
		if (sven.size > 0.1f) sven.size -= 0.33f*dt; else sven.size = 0.1f;


    if (glfwGetKey(Utils::window, GLFW_KEY_P) == GLFW_PRESS)
        sven.flash = !sven.flash;

    if (glfwGetKey(Utils::window, GLFW_KEY_KP_8) == GLFW_PRESS)
		sven.pos += glm::vec3(0,0,1.0f*dt);
	if (glfwGetKey(Utils::window, GLFW_KEY_KP_2) == GLFW_PRESS)
		sven.pos += glm::vec3(0,0,-1.0f*dt);
	if (glfwGetKey(Utils::window, GLFW_KEY_KP_4) == GLFW_PRESS)
		sven.pos += glm::vec3(-1.0f*dt,0,0);
	if (glfwGetKey(Utils::window, GLFW_KEY_KP_6) == GLFW_PRESS)
		sven.pos += glm::vec3(1.0f*dt,0,0);

    if(glfwGetKey(Utils::window, GLFW_KEY_1)==GLFW_PRESS){
        sven.actualDiffuse = Svenium::sven;
        sven.actualSpecular = Svenium::sven_spec;
	}
	else if(glfwGetKey(Utils::window, GLFW_KEY_2)==GLFW_PRESS){
		sven.actualDiffuse = Svenium::machine;
        sven.actualSpecular = Svenium::machine_spec;
	}
	else if(glfwGetKey(Utils::window, GLFW_KEY_3)==GLFW_PRESS){
		sven.actualDiffuse = Svenium::stomach;
        sven.actualSpecular = Svenium::stomach_spec;
	}
}

void Scene1::Draw(float dt) 
{
    sun.Update(dt);
    sun.Draw();

    cube.Update(dt);
    cube.Draw();
    
    sven.light1 = Utils::MatPos(cube.Transform);
    sven.light1Val = cube.intensidad;

    sven.light2 = Utils::MatPos(sun.Transform);

    sven.Update(dt);
    sven.Draw();
}