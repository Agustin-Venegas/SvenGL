#include "Model.h"

Model::Model() 
{

}

Model::Model(const float *vertex, bool color = false) 
{

}

void Model::HacerMatriz() //con esto se crea la matriz
{
    glm::mat4 matriz1 = glm::translate(glm::mat4(), glm::vec3(10.0f, 0.0f, 0.0f));
    glm::vec4 myVector(10.0f, 10.0f, 10.0f, 0.0f);
    glm::vec4 transformedVector = matriz1 * myVector; // guess the result
}

glm::mat4 Model::Rotar(glm::vec3 myRotationAxis, float angulo)
{
    return glm::rotate( angulo, myRotationAxis );
}

glm::vec4 Model::Trasladar(glm::vec4 myVector)
{
    glm::vec4 transformedVector = matriz1 * myVector; // Again, in this order ! this is important.
    return transformedVector;  
}


void Dibujar(){

}

GLuint Model::getBO()
{
    return bufferObject;
}