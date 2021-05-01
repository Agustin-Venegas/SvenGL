#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Scene.h"

class Scene2 : public Scene 
{
    Scene2();
    Scene2(GLuint program);
    ~Scene2();

    virtual void Update(float time) override; 
    virtual void Init() override;
    virtual void Draw() override;
};