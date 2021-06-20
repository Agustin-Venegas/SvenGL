#pragma once

#include "Drawable.h"
#include "glm/glm.hpp"

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
    glm::vec3 pos;
    glm::vec3 rot;
    glm::vec3 scale;
    glm::mat4 Transform;

    unsigned int VBO;
    unsigned int Texture;


    void Init() override;
    void Update(float dt) override;
    void Draw() override;
};