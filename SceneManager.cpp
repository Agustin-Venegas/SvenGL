#include "SceneManager.h"

std::shared_ptr<SceneManager> SceneManager::Instance = std::make_shared<SceneManager>();

SceneManager::SceneManager() 
{
    timer = 0;
    loading = false;
    scenes = std::vector<Scene*>();
}

void SceneManager::Update(float dt) 
{
    actualScene->Update(dt);
}

void SceneManager::Draw(float dt) 
{
    actualScene->Draw(dt);
}

void SceneManager::AddScene(Scene& s) 
{   
    actualScene = &s; 
    scenes.push_back(&s);
}

void SceneManager::ChangeScene(int i) 
{
    if (scenes.size() > i) actualScene = scenes[i];
}