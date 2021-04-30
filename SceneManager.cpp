#include "SceneManager.h"

SceneManager::SceneManager() 
{
    scenes = std::vector<Scene>();
    actualScene = NULL;
}

void SceneManager::AddScene(Scene* scene) 
{
    actualScene = scene;
}

void SceneManager::Update(float time) 
{
    actualScene->Update(time);
}

void SceneManager::Draw() 
{
    actualScene->Draw();
}