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

//#include <common/shader.hpp>


class Triangle
{
    // An array of 3 vectors which represents 3 vertices
public:
    glm::vec3 vertices[3] = {
        vec3(-1, -1, 0),
        vec3(1, -1, 0),
        vec3(0, 1, 0)};
    quat rot = quat(vec3(0,0,0));
    glm::vec3 pos = vec3(0,0,0);
    void Rotate(vec3 eulerAngles){        
        rot = rot*quat(eulerAngles);
    } 
    void PassToBuffer(GLfloat *vertexB){
        int j = 0;
        for (int i = 0; i < 9; i += 3)
        {
            vec3 vector = vertices[j]*rot;
            vector += pos;
            vertexB[i] = vector.x;
            vertexB[i + 1] = vector.y;
            vertexB[i + 2] = vector.z;
            j++;
        }
    }
};

Triangle triangle1, triangle2;

static GLfloat g_vertex_buffer_data1[] = {
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    0.0f, 1.0f, 0.0f
    };
static GLfloat g_vertex_buffer_data2[] = {
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    0.0f, 1.0f, 0.0f
    };
    

void hacertriangulo();