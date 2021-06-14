#include "Scene.h"
#include <vector>

class SceneManager 
{
    public:
    static SceneManager* Instance;

    SceneManager();
    std::vector<Scene> scenes;
    Scene actualScene;

    void Update(float dt);
    void Draw(float dt);

    void AddScene(Scene s);
    void ChangeScene(int i);
};