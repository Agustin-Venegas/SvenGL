#pragma once

#include "utils.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>


class Scene 
{
    public:
    Scene();
    
    virtual void Update(float time); //cada hijo de escena edita esta funcion
    virtual void Init();

    static void InitVals(); //iniciar valores usados en todas las escenas

    static glm::mat4 projection;
    static Scene actualScene;

    private:
    glm::mat4 camera;
    glm::vec3 pos;
    glm::vec3 lookat;

    GLuint VAO;
    std::vector<GLuint> VBOs;
};