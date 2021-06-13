#include "Svenium.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

#include "Utils.h"
#include "Scene1.h"

unsigned int Svenium::LightShader = 0;

unsigned int Svenium::sven;
unsigned int Svenium::sven_spec;
unsigned int Svenium::machine;
unsigned int Svenium::machine_spec;
unsigned int Svenium::stomach;
unsigned int Svenium::stomach_spec;

Svenium::Svenium() 
{
    Transform = glm::mat4(1.0f);

    pos = glm::vec3(0.0f);

    light1 = light2 = glm::vec3(0.0f);

    //Crear Shader
    unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
    Utils::CompileShader(vs, Utils::ReadFile("LightVertex.shader"));

    unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
    Utils::CompileShader(fs, Utils::ReadFile("Light.shader"));

    LightShader = glCreateProgram();
    glAttachShader(LightShader, vs);
    glAttachShader(LightShader, fs);
    glLinkProgram(LightShader);
    Utils::CheckProgramCompile(LightShader);
    glDeleteShader(vs);
    glDeleteShader(fs);

    Shader = LightShader;

    //crear VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    /*crear VBO y EBO
    float vert[] {
        //1era cara, frente
        0.5f, 0.5f, 0.5f, // derecha al fondo
        0.5f, 0.5f, -0.5f, //der cerca
        -0.5f, -0.5f, 0.5f, //izq fondo
        -0.5f, 0.5f, -0.5f, //der cerca
        0.0f, 0.70710678118655f, 0.0f //arriba

        //2da cara, izq

        //3era cara, atras

        //4ta cara, der

        //5 y 6ta cara, abajo
    };glGenBuffers(1, &EBO);

    int indices[] 
    {
        1, 2, 3,
        1, 3, 4,
        1, 5, 3,
        3, 4, 5,
        2, 4, 5,
        1, 2, 5
    };
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); 
    */

    //setear atributos VAO
    //posicion
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //normales
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //UV
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    Utils::USetInt(Shader,"material.diffuse", 0);
    Utils::USetInt(Shader, "material.specular", 1);


    //CREAR TEXTURAS
    sven = Utils::loadTexture("Sven.png");
    sven_spec = Utils::loadTexture("sven_spec.png");
    machine = Utils::loadTexture("Machien.png");
    machine_spec = Utils::loadTexture("Machien_spec.png");
    stomach = Utils::loadTexture("stomach.png");
    stomach_spec = Utils::loadTexture("stomach_spec.png");

    actualDiffuse = sven;
    actualSpecular = sven_spec;
}


void Svenium::Init() 
{

}

void Svenium::Update(float dt) 
{
    trayectoria += dt/4.0f;
    Transform = glm::mat4(1.0f);
    Transform = glm::translate(Transform, pos);
    Transform = glm::rotate(Transform, trayectoria, glm::vec3(0.0f, 1.0f, 0.0f));
    Transform = glm::scale(Transform, glm::vec3(size));
}

void Svenium::Draw() 
{
    glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

    glUseProgram(Shader);
    
    glBindVertexArray(VAO);
    //glEnableVertexAttribArray(0);
    //glEnableVertexAttribArray(1);
    //glEnableVertexAttribArray(2);


    //glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    
    glm::vec3 camPos = Utils::MatPos(Scene1::cam);

    Utils::USetVec3(Shader, "viewPos", camPos);
    Utils::USetFloat(Shader, "material.shininess", 32.0f);
    
    Utils::USetMat4(Shader, "model", Transform);
    Utils::USetMat4(Shader, "view", Scene1::cam);
    Utils::USetMat4(Shader, "projection", Utils::projection);

    //Luz ambiental direccional
    Utils::USetVec3(Shader, "dirLight.direction", glm::vec3(0.2f, -1.0f, -0.3f));
    Utils::USetVec3(Shader,"dirLight.ambient", glm::vec3(0.05f, 0.05f, 0.05f));
    Utils::USetVec3(Shader, "dirLight.diffuse", glm::vec3(0.3f, 0.0f, 0.0f));
    Utils::USetVec3(Shader, "dirLight.specular", glm::vec3(0.3f, 0.1f, 0.1f));    
    

    //luz 1
    Utils::USetVec3(Shader, "pointLights[0].position", light1);
    Utils::USetVec3(Shader, "pointLights[0].ambient", glm::vec3(0.05f, 0.05f, 0.05f)*light1Val);
    Utils::USetVec3(Shader, "pointLights[0].diffuse", glm::vec3(0.8f, 0.8f, 0.8f)*light1Val);
    Utils::USetVec3(Shader, "pointLights[0].specular", glm::vec3(1.0f, 1.0f, 1.0f)*light1Val);
    Utils::USetFloat(Shader, "pointLights[0].constant", light1Val);
    Utils::USetFloat(Shader, "pointLights[0].linear", 0.09);
    Utils::USetFloat(Shader, "pointLights[0].quadratic", 0.032);

    //luz2
    Utils::USetVec3(Shader, "pointLights[1].position", light2);
    Utils::USetVec3(Shader, "pointLights[1].ambient", 0.8f, 0.05f, 0.05f);
    Utils::USetVec3(Shader, "pointLights[1].diffuse", 0.8f, 0.8f, 0.1f);
    Utils::USetVec3(Shader, "pointLights[1].specular", 1.0f, 1.0f, 1.0f);
    Utils::USetFloat(Shader, "pointLights[1].constant", 0.60f);
    Utils::USetFloat(Shader, "pointLights[1].linear", 0.09);
    Utils::USetFloat(Shader, "pointLights[1].quadratic", 0.022);

    // spotLight
    Utils::USetBool(Shader, "flash", flash);
    Utils::USetVec3(Shader, "spotLight.position", camPos);
    Utils::USetVec3(Shader, "spotLight.direction", glm::normalize(pos-camPos));
    Utils::USetVec3(Shader, "spotLight.ambient", glm::vec3(0.0f, 0.0f, 0.0f));
    Utils::USetVec3(Shader, "spotLight.diffuse", glm::vec3(1.0f, 0.7f, 0.3f));
    Utils::USetVec3(Shader, "spotLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    Utils::USetFloat(Shader, "spotLight.constant", 1.0f);
    Utils::USetFloat(Shader, "spotLight.linear", 0.09);
    Utils::USetFloat(Shader, "spotLight.quadratic", 0.032);
    Utils::USetFloat(Shader, "spotLight.cutOff", glm::cos(glm::radians(12.5f)));
    Utils::USetFloat(Shader, "spotLight.outerCutOff", glm::cos(glm::radians(15.0f))); 


    // bindear difuso
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, actualDiffuse);
    
    // bindear mapa specular
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, actualSpecular);

    
    glDrawArrays(GL_TRIANGLES, 0, 36);
    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}