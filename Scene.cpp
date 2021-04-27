#include "Utils.h"
#include "Scene.h"


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

glm::mat4 Scene::projection;

Scene::Scene() 
{
    camera = glm::lookAt(
    glm::vec3(4,3,3), // Camera is at (4,3,3), in World Space
    glm::vec3(0,0,0), // and looks at the origin
    glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
    );



    glGenVertexArrays(1, &VAO); //crear un VAO vacio, debe ser rellenado en edit
    VBOs = std::vector<GLuint>(); //vector de IDs vacio

    Init();

    //luego de inicializar lo especifico, usar esta camara
    unsigned int transformLoc = glGetUniformLocation(Utils::program, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(camera));
}

void Scene::Update(float time) //cada hijo de escena edita esta funcion
{

}

void Scene::Init() //cada hijo de escena edita esta funcion
{
    
}

void Scene::InitVals()
{
    //iniciar la cosa
    Scene::projection = glm::perspective(glm::radians(45.0f), (float)4/(float)3, 0.1f, 100.0f);

    //pasar la cosa a la otra cosa

    unsigned int transformLoc = glGetUniformLocation(Utils::program, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(Scene::projection));
}