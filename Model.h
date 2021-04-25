#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <stdlib.h>

class Model
{
    public:
    Model(); //crear modelo vacio
    Model(const float *vertex, bool color = false); //modelo sin colores

    GLuint getBO(); //regresa el bufferObject

    private:
    GLuint bufferObject;
};