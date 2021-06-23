#include "SceneManager.h"
#include "Utils.h"


std::shared_ptr<SceneManager> SceneManager::Instance = std::make_shared<SceneManager>();

SceneManager::SceneManager() 
{
    timer = 0.0f;
    loading = false;
    scenes = std::vector<Scene*>();

    screen = Plane();
}

void SceneManager::Update(float dt) 
{
    actualScene->Update(dt);
}

void SceneManager::Draw(float dt) 
{
    glEnable(GL_DEPTH_TEST);

    if (timer == 0.0f) 
    {
        actualScene->Draw(dt);
    } else 
    {
        screen.Draw();
    }
    
    if (loading) 
    {
        if (timer == 0.0f) 
        {
            screen.Texture = Utils::loadTexture(std::string("load.png"));
        }
        
        timer +=dt;
        if (timer > 3.0f) 
        {
            loading = false;
            timer = 0.0f;
        }
    }
}

void SceneManager::AddScene(Scene& s) 
{   
    actualScene = &s; 
    scenes.push_back(&s);
}

void SceneManager::ChangeScene(int i) 
{
    if (scenes.size() > i) actualScene = scenes[i];
    loading = true;
}

void SceneManager::MouseMovement(double x, double y) 
{
    MouseScene* ms=dynamic_cast<MouseScene*>(actualScene);
    if (ms) ms->ProcessMouse(x,y);
}