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


unsigned int Cube::CubeShader = 0;
unsigned int Cube::VBO = 0;
unsigned int Cube::CubeVAO = 0;

Cube::Cube(std::string texture) 
{
    Transform = glm::mat4(1.0f);
    Texture = Utils::loadTexture(texture);
    useSpec = false;
}

Cube::Cube() 
{

}

Cube::Cube(std::string texture, glm::mat4 transform) 
{
    Transform = transform;
    Texture = Utils::loadTexture(texture);
    useSpec = false;
}

void Cube::Update(float dt) 
{

}

void Cube::Draw() 
{
    // bindear difuso
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, Texture);
    
    // bindear mapa specular
    glActiveTexture(GL_TEXTURE1);
    if (useSpec) 
    {
        glBindTexture(GL_TEXTURE_2D, Specular);
    }

    Utils::USetBool(CubeShader, "UseSpec", useSpec);
    Utils::USetMat4(CubeShader, "model", Transform);

    
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Cube::Init() {}
void Cube::InitVals() 
{
    //Crear Shader
    unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
    Utils::CompileShader(vs, Utils::ReadFile("LightVertex.shader"));
    unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
    Utils::CompileShader(fs, Utils::ReadFile("Light.shader"));
    CubeShader = glCreateProgram();
    glAttachShader(CubeShader, vs);
    glAttachShader(CubeShader, fs);
    glLinkProgram(CubeShader);
    Utils::CheckProgramCompile(CubeShader);
    glDeleteShader(vs);
    glDeleteShader(fs);

    //setear el VAO y VBO que todos usaran
    //crear VAO
    glGenVertexArrays(1, &CubeVAO);
    glBindVertexArray(CubeVAO);

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
}

//HACER ESTO UNA VEZ ANTES DE DIBUJAR LOS CUBOS
void Cube::PreDraw(Camera c) 
{
    glUseProgram(CubeShader);
    glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

    glBindVertexArray(CubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    Utils::USetFloat(CubeShader, "material.shininess", 32.0f);

    Utils::USetVec3(CubeShader, "viewPos", c.Position);
    Utils::USetMat4(CubeShader, "view", c.GetViewMatrix());
    Utils::USetMat4(CubeShader, "projection", Utils::projection);
}



void RotatingCube::Update(float dt) 
{
    trayectoria += dt/4.0f;

    Transform = glm::rotate(Transform, glm::radians(trayectoria), glm::vec3(0.0f, 1.0f, 0.0f));
}