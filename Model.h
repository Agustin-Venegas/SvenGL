#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>


#include <stdlib.h>

class Model
{
    public:
    Model(); //crear modelo vacio
    Model(const float *vertex, bool color = false); //modelo sin colores
    glm::mat4 matriz1;
    


    GLuint getBO(); //regresa el bufferObject

    void Rotar();
    void Trasladar();

    private:
    GLuint bufferObject;

void HacerMatriz();

glm::vec4 Trasladar(glm::vec4 myVector);
glm::mat4 Rotar(glm::vec3 myRotationAxis, float);

void Dibujar();

};