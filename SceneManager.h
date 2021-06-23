#pragma once

#include "Scene.h"
#include <vector>
#include <memory>
#include "Plane.h"

class SceneManager 
{
    public:
    static std::shared_ptr<SceneManager> Instance;

    SceneManager();
    std::vector<Scene*> scenes;
    Scene* actualScene;

    void Update(float dt);
    void Draw(float dt);

    void AddScene(Scene& s);
    void ChangeScene(int i);

    void MouseMovement(double x, double y); //ve si la escena usa mouse

    private:
    bool loading;
    float timer;
    Plane screen;
};