#include "Scene.h"
#include <vector>

class SceneManager 
{
    public:
    static SceneManager Instance;

    SceneManager();
    std::vector<Scene> scenes;

    void Update(float dt);
    void Draw(float dt);

    void AddScene(Scene s);

};