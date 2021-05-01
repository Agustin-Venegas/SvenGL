#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

//Rotacion
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

// Include standard headers
#include <stdio.h>
#include <stdlib.h>

using namespace glm;

//#include <common/shader.hpp> :/


class Triangle
{
    
public:
    glm::vec3 vertices[3];
    quat rot = quat(vec3(0,0,0));
    glm::vec3 pos = vec3(0,0,0);
    void Rotate(vec3 eulerAngles);
    void PassToBuffer(GLfloat *vertexB);
};

Triangle triangle1, triangle2;

static GLfloat g_vertex_buffer_data1[];
GLfloat g_vertex_buffer_data2[];

void hacertriangulo();