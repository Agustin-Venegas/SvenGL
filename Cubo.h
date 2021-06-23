#pragma once

#include "Drawable.h"
#include "glm/glm.hpp"
#include "Camera.h"

#include <string>

//cubo que usa el shader chico
class CuboLuz : public Drawable
{
    public:
    CuboLuz();
    CuboLuz(float dist, glm::vec3 col);

    glm::mat4 Transform;
    float trayectoria = 0.0f; //angulo
    float intensidad = 0.0f;
    float rad = 1;

    glm::vec3 lightColor;

    unsigned int VBO;

    void Init() override;
    void Update(float dt) override;
    void Draw() override;

    //valores usados en varios cubos
    static unsigned int SimpleShader;
    static unsigned int SimpleVAO;

    static void InitValues();
};

class Cube : public Drawable 
{
    public:
    Cube();
    Cube(std::string texture);
    Cube(std::string texture, glm::mat4 transform);
    
    glm::vec3 pos;
    glm::vec3 rot;
    glm::vec3 scale;
    glm::mat4 Transform;

    static unsigned int VBO;
    static unsigned int CubeVAO; 
    unsigned int Texture;
    unsigned int Specular;
    bool useSpec; 

    static unsigned int CubeShader;

    static void InitVals(); //para setear otros valores static
    static void PreDraw(Camera c); //para setear el shader antes de dibujar todos los cubos, en la escena

    void Init() override;
    virtual void Update(float dt);
    void Draw() final;
};

class RotatingCube : public Cube 
{
    public:
    using Cube::Cube;
    float trayectoria = 0;
    void Update(float dt) override;
};