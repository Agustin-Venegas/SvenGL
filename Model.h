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

    GLuint getBO(); //regresa el bufferObject

    private:
    GLuint bufferObject;

void HacerMatriz(){

glm::mat4 myMatrix;
glm::vec4 myVector;
// fill myMatrix and myVector somehow
glm::vec4 transformedVector = myMatrix * myVector; // Again, in this order ! this is important.

}

void Trasladar(){

glm::mat4 myMatrix = glm::translate(glm::mat4(), glm::vec3(10.0f, 0.0f, 0.0f));
glm::vec4 myVector(10.0f, 10.0f, 10.0f, 0.0f);
glm::vec4 transformedVector = myMatrix * myVector; // guess the result

}

void Rotar(){

glm::vec3 myRotationAxis( 5.f, 5.f, 5.f );
glm::rotate( 5.f, myRotationAxis );

}

};