#pragma once

#include "Scene.h"
#include "Camera.h"
#include <string>
#include "Cubo.h"

class EscenaCubemap : public Scene , public MouseScene
{
    public:
    Camera camera;
    unsigned int skyShader;
    unsigned int skyboxVAO;
    unsigned int skyboxVBO;
    unsigned int skyTex;

    EscenaCubemap();
    void Init() override;
    void Update(float dt) override;
    void Draw(float dt) override;

    void ProcessMouse(double x, double y) override;

    private:
    double lastx = 0;
    double lasty = 0;

    std::vector<Cube> walls;
    RotatingCube rc;
    RotatingCube eduardo;

    void SetLights();
};

