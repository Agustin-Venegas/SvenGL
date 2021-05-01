#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Scene.h"

#include <vector>

class SceneManager 
{
    public:
    SceneManager();
    void AddScene(Scene* scene);
    void Update(float time);
    void Draw();
    void ChangeScene(int i);

    static SceneManager Instance;

    private:
    std::vector<Scene*> scenes;
    Scene* actualScene;
};