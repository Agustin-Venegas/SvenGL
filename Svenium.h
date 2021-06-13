#pragma once

#include "Drawable.h"
#include "glm/glm.hpp"

class Svenium : public Drawable 
{
    public:
    Svenium(); //solo haremos un svenium asi q se ejecuta una vez

    static unsigned int LightShader;

    glm::mat4 Transform;
    float trayectoria = 0.0f; //rotacion actual
    float size = 1.0f;
    glm::vec3 pos;

    bool flash = true;

    glm::vec3 light1, light2;
    float light1Val=0;

    unsigned int VBO;
    //unsigned int EBO;

    //texturas
    unsigned int actualDiffuse;
    unsigned int actualSpecular;

    static unsigned int sven;
    static unsigned int sven_spec;
    static unsigned int machine;
    static unsigned int machine_spec;
    static unsigned int stomach;
    static unsigned int stomach_spec;


    void Init() override;
    void Update(float dt) override;
    void Draw() override;
};