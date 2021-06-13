#include "Scene.h"
#include "Svenium.h"
#include "Cubo.h"

#include <glm/glm.hpp>

class Scene1 : public Scene 
{
    public:
    Scene1();
    static glm::mat4 cam;

    void Init() override;
    void Update(float dt) override;
    void Draw(float dt) override;

    CuboLuz cube;
    CuboLuz sun;
    Svenium sven;
};