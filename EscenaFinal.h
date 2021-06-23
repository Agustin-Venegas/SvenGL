#include "Scene.h"
#include "Utils.h"


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Plane.h"
#include "Cubo.h"
#include "Camera.h"

class EscenaFinal : public Scene, public MouseScene
{
    public:
    EscenaFinal();
    void Init() override;
    void Update(float dt) override;
    void Draw(float dt) override;

    void ProcessMouse(double x, double y) override;

    private:
    Camera cam;

    std::vector<Cube> walls;
    
    Cube barriga;
    Cube sven;
    Cube rojas;
    Cube besoain;

    void SetLights();

    double lastx = 0;
    double lasty = 0;
};