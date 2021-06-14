#include "SceneManager.h"

SceneManager::SceneManager() 
{
    SceneManager::Instance = this;
}

void SceneManager::Update(float dt) 
{

}

void SceneManager::Draw(float dt) 
{

}

void SceneManager::AddScene(Scene s) 
{   
    if (scenes.size() == 0) actualScene = s; 
    scenes.push_back(s);
}

void SceneManager::ChangeScene(int i) 
{
    if (scenes.size() > i) actualScene = scenes[i];
}