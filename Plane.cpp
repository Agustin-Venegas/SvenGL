#include "Plane.h"
#include "Utils.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

unsigned int Plane::VAO = 0;
unsigned int Plane::VBO = 0;
unsigned int Plane::Shader = 0;

void Plane::InitVals() 
{
    //shader
    unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
    Utils::CompileShader(vs, Utils::ReadFile("PlaneVertex.shader"));

    unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
    Utils::CompileShader(fs, Utils::ReadFile("PlaneFragment.shader"));

    Plane::Shader = glCreateProgram();
    glAttachShader(Plane::Shader, vs);
    glAttachShader(Plane::Shader, fs);
    glLinkProgram(Plane::Shader);
    Utils::CheckProgramCompile(Plane::Shader);
    glDeleteShader(vs);
    glDeleteShader(fs);

    glUseProgram(Plane::Shader);

    //crear VAO
    glGenVertexArrays(1, &Plane::VAO);
    glBindVertexArray(Plane::VAO);

    float quadVertices[] = { //en coordenadas de pantalla (-1, 1)
        1.0f,  1.0f, 0.0f, 1.0f, 1.0f, // top right
        1.0f, -1.0f, 0.0f, 1.0f, 0.0f, // bottom right
        -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,  // top left
        1.0f, -1.0f, 0.0f, 1.0f, 0.0f, // bottom right
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, // bottom left
        -1.0f,  1.0f, 0.0f, 0.0f, 1.0f  // top left
    };

    // screen quad VAO
    glGenBuffers(1, &(Plane::VBO));
    glBindBuffer(GL_ARRAY_BUFFER, Plane::VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    Utils::USetInt(Shader, "screenTexture", 0);

    glBindVertexArray(0);
}

Plane::Plane() 
{
    Texture = 0;
    transform = glm::mat4(1.0f);
}

Plane::Plane(std::string file) //a partir de archivo
{
    Texture = Utils::loadTexture(file);

    transform = glm::mat4(1.0f);
    transform = glm::scale(transform, glm::vec3(1.0f,1.0f,1.0f));
}

Plane::Plane(unsigned int tex) //a partir de textura
{
    Texture = tex;
    transform = glm::mat4(1.0f);
    transform = glm::scale(transform, glm::vec3(1.0f,1.0f,1.0f));
}

void Plane::Draw() 
{
    //glEnable(GL_DEPTH_TEST);
    //glDepthFunc(GL_LEQUAL);
    //glDisable(GL_CULL_FACE);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, Texture);
    //Utils::USetInt(Plane::Shader, "screenTexture", Texture);

    glUseProgram(Plane::Shader);
    
    glBindVertexArray(Plane::VAO);
    glBindBuffer(GL_ARRAY_BUFFER, Plane::VBO);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

    
    
    //Utils::USetMat4(Shader, "transform", transform);
    
    glDrawArrays(GL_TRIANGLES, 0, 6);
}