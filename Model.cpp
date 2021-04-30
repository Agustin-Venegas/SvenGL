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

void Model::Rotar(glm::vec3 myRotationAxis, float)
{

glm::vec3 myRotationAxis( 5.f, 5.f, 5.f );
glm::rotate( 5.f, myRotationAxis );

}
glm::vec4 Model::Trasladar(glm::vec4 myVector)
{

glm::vec4 transformedVector = matriz1 * myVector; // Again, in this order ! this is important.

return transformedVector;
}

GLuint Model::getBO()
{
    return bufferObject;
}