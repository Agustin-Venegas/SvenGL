#pragma once
#include <string>
#include "glm/glm.hpp"

class Plane //para dibujar texturas
{
    public:
    Plane();
    Plane(std::string file); //a partir de archivo
    Plane(unsigned int tex); //a partir de textura

    void Draw();
    glm::mat4 transform;
    unsigned int Texture;

    static unsigned int VAO;
    static unsigned int VBO;
    static unsigned int Shader;

    static void InitVals(); //inicializar VBO
};