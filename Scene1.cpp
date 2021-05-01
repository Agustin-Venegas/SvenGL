#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Scene1.h"
#include <time.h>
#include <chrono>


// This will identify our vertex buffer
GLuint vertexbuffer[2];

GLuint programID;
GLuint programID2;

scene1::scene1() : Scene() //constructor vacio, no se usa
{

}

scene1::scene1(GLuint program) : Scene(program) //constructor con el programa a usar
{

}

scene1::~scene1() {}


void scene1::Init() //cada hijo de escena edita esta funcion
{
    double deltaTime;
    static float yDirection = 1;
    // Draw triangle...

    // 1st attribute buffer : vertices
    glEnableVertexAttribArray(0);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_DRAW_BUFFER);
    //glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[0]);
    //glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[1]);
    glVertexAttribPointer(
        0,        // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,        // size
        GL_FLOAT, // type
        GL_FALSE, // normalized?
        0,        // stride
        (void *)0 // array buffer offset
    );
    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
    glDisableVertexAttribArray(0);

    if (g_vertex_buffer_data1[1] > 1 && yDirection > 0)
    {
        yDirection = -1;
        g_vertex_buffer_data1[1] -= (g_vertex_buffer_data1[1] - 1);
    }
    else if (g_vertex_buffer_data1[1] < -1 && yDirection < 0)
    {
        yDirection = 1;
        g_vertex_buffer_data1[1] -= (g_vertex_buffer_data1[1] + 1);
    }
    g_vertex_buffer_data1[1] += deltaTime * yDirection * 2;
}


void scene1::Update(float time, GLFWwindow *window) 
{

    triangle1.Rotate(vec3(0,0,time));
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        triangle1.pos += vec3(-time,0,0);
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        triangle2.pos += vec3(time,0,0);
    }

    triangle2.Rotate(vec3(0,-time,time));

    triangle1.PassToBuffer(g_vertex_buffer_data1);
    triangle2.PassToBuffer(g_vertex_buffer_data2);


    
}


void scene1::Draw() 
{
    
}