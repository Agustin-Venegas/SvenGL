#include "Cubo.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Utils.h"
#include "Scene1.h"

//asignar valor inicial de las vars staticas
unsigned int CuboLuz::SimpleShader;
unsigned int CuboLuz::SimpleVAO;

void CuboLuz::InitValues() 
{
    //Crear SimpleShader
    unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
    Utils::CompileShader(vs, Utils::ReadFile("Vertex.shader"));

    unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
    Utils::CompileShader(fs, Utils::ReadFile("VertexFragment.shader"));

    SimpleShader = glCreateProgram();
    glAttachShader(SimpleShader, vs);
    glAttachShader(SimpleShader, fs);
    glLinkProgram(SimpleShader);
    Utils::CheckProgramCompile(SimpleShader);
    glDeleteShader(vs);
    glDeleteShader(fs);

    //crear SimpleVAO
    glGenVertexArrays(1, &SimpleVAO);
    glBindVertexArray(SimpleVAO);

    //atributo de posicion
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    //atributo de color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

CuboLuz::CuboLuz()
{
    Shader = CuboLuz::SimpleShader;
    VAO = CuboLuz::SimpleVAO;

    Transform = glm::mat4(1.0f);    
    rad = 1;

    glm::vec3 color = glm::vec3(1.6f, 1.6f, 1.0f);

    float cube[] = { //vertices y colores para el cubo
        -0.5f, -0.5f, -0.5f,  color.x, color.y, color.z,
         0.5f, -0.5f, -0.5f,  color.x, color.y, color.z,
         0.5f,  0.5f, -0.5f,  color.x, color.y, color.z,
         0.5f,  0.5f, -0.5f,  color.x, color.y, color.z,
        -0.5f,  0.5f, -0.5f,  color.x, color.y, color.z,
        -0.5f, -0.5f, -0.5f,  color.x, color.y, color.z,
		
        -0.5f, -0.5f,  0.5f,  color.x, color.y, color.z,
         0.5f, -0.5f,  0.5f,  color.x, color.y, color.z,
         0.5f,  0.5f,  0.5f,  color.x, color.y, color.z,
         0.5f,  0.5f,  0.5f,  color.x, color.y, color.z,
        -0.5f,  0.5f,  0.5f,  color.x, color.y, color.z,
        -0.5f, -0.5f,  0.5f,  color.x, color.y, color.z,

        -0.5f,  0.5f,  0.5f, color.x, color.y, color.z,
        -0.5f,  0.5f, -0.5f, color.x, color.y, color.z,
        -0.5f, -0.5f, -0.5f, color.x, color.y, color.z,
        -0.5f, -0.5f, -0.5f, color.x, color.y, color.z,
        -0.5f, -0.5f,  0.5f, color.x, color.y, color.z,
        -0.5f,  0.5f,  0.5f, color.x, color.y, color.z,

         0.5f,  0.5f,  0.5f,  color.x, color.y, color.z,
         0.5f,  0.5f, -0.5f,  color.x, color.y, color.z,
         0.5f, -0.5f, -0.5f,  color.x, color.y, color.z,
         0.5f, -0.5f, -0.5f,  color.x, color.y, color.z,
         0.5f, -0.5f,  0.5f,  color.x, color.y, color.z,
         0.5f,  0.5f,  0.5f,  color.x, color.y, color.z,

        -0.5f, -0.5f, -0.5f,  color.x, color.y, color.z,
         0.5f, -0.5f, -0.5f,  color.x, color.y, color.z,
         0.5f, -0.5f,  0.5f,  color.x, color.y, color.z,
         0.5f, -0.5f,  0.5f,  color.x, color.y, color.z,
        -0.5f, -0.5f,  0.5f,  color.x, color.y, color.z,
        -0.5f, -0.5f, -0.5f,  color.x, color.y, color.z,

        -0.5f,  0.5f, -0.5f,  color.x, color.y, color.z,
         0.5f,  0.5f, -0.5f,  color.x, color.y, color.z,
         0.5f,  0.5f,  0.5f,  color.x, color.y, color.z,
         0.5f,  0.5f,  0.5f,  color.x, color.y, color.z,
        -0.5f,  0.5f,  0.5f,  color.x, color.y, color.z,
        -0.5f,  0.5f, -0.5f,  color.x, color.y, color.z,
    };

    glBindVertexArray(VAO);
    VBO = Utils::CreateVBO(cube, 216);
    
    //atributo de posicion
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    //atributo de color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}


CuboLuz::CuboLuz(float dist, glm::vec3 col)
{
    Shader = CuboLuz::SimpleShader;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    //atributo de posicion
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    //atributo de color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    Transform = glm::mat4(1.0f);
    rad = dist;

    lightColor = col;

    float cube[] = { //vertices y colores para el cubo
        -0.5f, -0.5f, -0.5f,  lightColor.x, lightColor.y, lightColor.z,
         0.5f, -0.5f, -0.5f,  lightColor.x, lightColor.y, lightColor.z,
         0.5f,  0.5f, -0.5f,  lightColor.x, lightColor.y, lightColor.z,
         0.5f,  0.5f, -0.5f,  lightColor.x, lightColor.y, lightColor.z,
        -0.5f,  0.5f, -0.5f,  lightColor.x, lightColor.y, lightColor.z,
        -0.5f, -0.5f, -0.5f,  lightColor.x, lightColor.y, lightColor.z,
		
        -0.5f, -0.5f,  0.5f,  lightColor.x, lightColor.y, lightColor.z,
         0.5f, -0.5f,  0.5f,  lightColor.x, lightColor.y, lightColor.z,
         0.5f,  0.5f,  0.5f,  lightColor.x, lightColor.y, lightColor.z,
         0.5f,  0.5f,  0.5f,  lightColor.x, lightColor.y, lightColor.z,
        -0.5f,  0.5f,  0.5f,  lightColor.x, lightColor.y, lightColor.z,
        -0.5f, -0.5f,  0.5f,  lightColor.x, lightColor.y, lightColor.z,

        -0.5f,  0.5f,  0.5f, lightColor.x, lightColor.y, lightColor.z,
        -0.5f,  0.5f, -0.5f, lightColor.x, lightColor.y, lightColor.z,
        -0.5f, -0.5f, -0.5f, lightColor.x, lightColor.y, lightColor.z,
        -0.5f, -0.5f, -0.5f, lightColor.x, lightColor.y, lightColor.z,
        -0.5f, -0.5f,  0.5f, lightColor.x, lightColor.y, lightColor.z,
        -0.5f,  0.5f,  0.5f, lightColor.x, lightColor.y, lightColor.z,

         0.5f,  0.5f,  0.5f,  lightColor.x, lightColor.y, lightColor.z,
         0.5f,  0.5f, -0.5f,  lightColor.x, lightColor.y, lightColor.z,
         0.5f, -0.5f, -0.5f,  lightColor.x, lightColor.y, lightColor.z,
         0.5f, -0.5f, -0.5f,  lightColor.x, lightColor.y, lightColor.z,
         0.5f, -0.5f,  0.5f,  lightColor.x, lightColor.y, lightColor.z,
         0.5f,  0.5f,  0.5f,  lightColor.x, lightColor.y, lightColor.z,

        -0.5f, -0.5f, -0.5f,  lightColor.x, lightColor.y, lightColor.z,
         0.5f, -0.5f, -0.5f,  lightColor.x, lightColor.y, lightColor.z,
         0.5f, -0.5f,  0.5f,  lightColor.x, lightColor.y, lightColor.z,
         0.5f, -0.5f,  0.5f,  lightColor.x, lightColor.y, lightColor.z,
        -0.5f, -0.5f,  0.5f,  lightColor.x, lightColor.y, lightColor.z,
        -0.5f, -0.5f, -0.5f,  lightColor.x, lightColor.y, lightColor.z,

        -0.5f,  0.5f, -0.5f,  lightColor.x, lightColor.y, lightColor.z,
         0.5f,  0.5f, -0.5f,  lightColor.x, lightColor.y, lightColor.z,
         0.5f,  0.5f,  0.5f,  lightColor.x, lightColor.y, lightColor.z,
         0.5f,  0.5f,  0.5f,  lightColor.x, lightColor.y, lightColor.z,
        -0.5f,  0.5f,  0.5f,  lightColor.x, lightColor.y, lightColor.z,
        -0.5f,  0.5f, -0.5f,  lightColor.x, lightColor.y, lightColor.z,
    };

    glBindVertexArray(VAO);
    VBO = Utils::CreateVBO(cube, 216);
    
    //atributo de posicion
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    //atributo de color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void CuboLuz::Init() 
{

}

void CuboLuz::Draw() 
{
    glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

    glUseProgram(Shader);
    
    glBindVertexArray(VAO);
    //glEnableVertexAttribArray(0);
    //glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    

    Utils::USetMat4(Shader, "model", Transform);
    Utils::USetMat4(Shader, "view", Scene1::cam);
    Utils::USetMat4(Shader, "projection", Utils::projection);


    

    
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void CuboLuz::Update(float dt) 
{
    trayectoria += dt;

    Transform = glm::mat4(1.0f);
    Transform = glm::rotate(Transform, trayectoria/rad, glm::vec3(0.0f, 1.0f, 0.0f));
    Transform = glm::translate(Transform, glm::vec3(0.0f, 0.0f, rad));
    Transform = glm::scale(Transform, glm::vec3(0.25f,0.25f,0.25f));

    intensidad += dt*4.0f;
    if (intensidad >= 1) 
    {
        intensidad = 0;
    }
}