#include "Scene.h"
#include <vector>
#include <memory>

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

    private:
    bool loading;
    float timer;
};