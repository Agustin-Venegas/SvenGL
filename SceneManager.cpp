#include "SceneManager.h"

#include <iostream>


SceneManager::SceneManager() 
{
    scenes = std::vector<Scene*>();
    actualScene = NULL;
}

//no se si esto sirve para el singleton
SceneManager SceneManager::Instance = SceneManager();

void SceneManager::AddScene(Scene* scene) 
{
    if (actualScene == NULL) actualScene = scene;

    scenes.push_back(scene);
}

void SceneManager::Update(float time) 
{
    actualScene->Update(time);
}

void SceneManager::Draw() 
{
    actualScene->Draw();
}

void SceneManager::ChangeScene(int i) 
{
    if (scenes.size() < i) 
    {
        actualScene = scenes[i];
    } else 
    {
        std::cerr << "Error: Revisar vector de Escenas" << std::endl;
    }
}