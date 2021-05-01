#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include "Scene.h"

class scene1:public Scene{

public:

    scene1();
    scene1(GLuint program);
    ~scene1();

    virtual void Update(float time) override; 
    virtual void Init() override;
    virtual void Draw() override;

};

