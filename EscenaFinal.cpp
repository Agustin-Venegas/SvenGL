#include "EscenaFinal.h"
#include "SceneManager.h"
#include "EscenaInicial.h"

EscenaFinal::EscenaFinal() 
{
    cam = Camera();

    walls = std::vector<Cube>();
    std::string f = std::string("wall.png");
    glm::vec3 pos = glm::vec3(1.25f, 0.0f, 1.25f);
    glm::vec3 scale = glm::vec3(0.5f, 2.0f, 4.0f);
    float rot = glm::radians(90.0f);
    
    //primera pared
    glm::mat4 t = glm::mat4(1.0f);
    t = glm::translate(t, pos);
    t = glm::rotate(t,rot, glm::vec3(0.0f, 1.0f, 0.0f));
    t = glm::scale(t, scale);

    walls.push_back(Cube(f,t));

    //otra pared
    t = glm::mat4(1.0f);
    pos = glm::vec3(1.25f,0.0f,-2.75f);
    t = glm::translate(t, pos);
    t = glm::rotate(t,rot, glm::vec3(0.0f, 1.0f, 0.0f));
    t = glm::scale(t, scale);

    walls.push_back(Cube(f,t));

    //otra pared
    t = glm::mat4(1.0f);
    pos = glm::vec3(-0.5f,0.0f,-1.0f);
    rot = glm::radians(0.0f);
    t = glm::translate(t, pos);
    t = glm::rotate(t,rot, glm::vec3(1.0f, 1.0f, 0.0f));
    t = glm::scale(t, scale);

    walls.push_back(Cube(f,t));

    //Ultima Pared
    t = glm::mat4(1.0f);
    pos = glm::vec3(3.0f,0.0f,-1.0f);
    rot = glm::radians(0.0f);
    t = glm::translate(t, pos);
    t = glm::rotate(t,rot, glm::vec3(0.0f, 1.0f, 0.0f));
    t = glm::scale(t, scale);

    walls.push_back(Cube(f,t));

    //techo
    t = glm::mat4(1.0f);
    pos = glm::vec3(1.25f, 1.25f, -0.75f);
    rot = glm::radians(0.0f);
    scale = glm::vec3(4.0f, 0.5f, 4.5f);
    
    t = glm::translate(t, pos);
    t = glm::rotate(t,rot, glm::vec3(0.0f, 1.0f, 0.0f));
    t = glm::scale(t, scale);

    walls.push_back(Cube(f,t));

    //suelo
    t = glm::mat4(1.0f);
    pos = glm::vec3(1.25f, -1.25f, -0.75f);
    rot = glm::radians(0.0f);
    scale = glm::vec3(4.0f, 0.5f, 4.5f);
    
    t = glm::translate(t, pos);
    t = glm::rotate(t,rot, glm::vec3(0.0f, 1.0f, 0.0f));
    t = glm::scale(t, scale);

    walls.push_back(Cube(f,t));


    //cuadros
    t = glm::mat4(1.0f);
    pos = glm::vec3(1.25f, 0.4f, 1.0f);
    rot = glm::radians(0.0f);
    scale = glm::vec3(1.0f, 1.0f, 0.1f);

    t = glm::translate(t, pos);
    t = glm::rotate(t,rot, glm::vec3(0.0f, 1.0f, 0.0f));
    t = glm::scale(t, scale);

    sven = Cube(std::string("Sven.png"), t);

    t = glm::mat4(1.0f);
    pos = glm::vec3(-0.25f, 0.4f, -0.50f);
    rot = glm::radians(90.0f);
    scale = glm::vec3(1.0f, 1.0f, 0.1f);

    t = glm::translate(t, pos);
    t = glm::rotate(t,rot, glm::vec3(0.0f, 1.0f, 0.0f));
    t = glm::scale(t, scale);

    barriga = Cube(std::string("stomach.png"), t);

    t = glm::mat4(1.0f);
    pos = glm::vec3(2.75f, 0.4f, -0.50f);
    rot = glm::radians(90.0f);
    scale = glm::vec3(1.0f, 1.0f, 0.1f);

    t = glm::translate(t, pos);
    t = glm::rotate(t,rot, glm::vec3(0.0f, 1.0f, 0.0f));
    t = glm::scale(t, scale);

    rojas = Cube(std::string("Machien.png"), t);

    t = glm::mat4(1.0f);
    pos = glm::vec3(1.25f, 0.4f, -2.50f);
    rot = glm::radians(0.0f);
    scale = glm::vec3(1.0f, 1.0f, 0.1f);

    t = glm::translate(t, pos);
    t = glm::rotate(t,rot, glm::vec3(0.0f, 1.0f, 0.0f));
    t = glm::scale(t, scale);

    besoain = Cube(std::string("felipe.png"), t);

}

void EscenaFinal::Init() {}

void EscenaFinal::Update(float dt) 
{
    auto window = Utils::window;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cam.ProcessKeyboard(FORWARD, dt);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cam.ProcessKeyboard(BACKWARD, dt);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cam.ProcessKeyboard(LEFT, dt);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cam.ProcessKeyboard(RIGHT, dt);
}

void EscenaFinal::Draw(float dt) 
{
    Cube::PreDraw(cam);

    SetLights();
    
    for (Cube c:walls) 
    {
        c.Draw();
    }

    sven.Draw();
    barriga.Draw();
    rojas.Draw();
    besoain.Draw();

    //deteccion de portal
    glm::vec3 pos = cam.Position;

    float dist = glm::length(pos-glm::vec3(1.25f, 0.4f, 1.25f));
    if (dist<1.0f) 
    {
        EscenaInicial::font.RenderText(std::string("Sven von Brand"), 100.0f ,100.0f, 0.6f, glm::vec3(1.0f,1.0f,1.0f));
    }

    dist = glm::length(pos-glm::vec3(-0.25f, 0.4f, -0.50f));
    if (dist<1.0f) 
    {
        EscenaInicial::font.RenderText(std::string("Nicolas Barriga"), 80.0f ,100.0f, 0.6f, glm::vec3(1.0f,1.0f,1.0f));
    }

    dist = glm::length(pos-glm::vec3(2.75f, 0.4f, -0.50f));
    if (dist<1.0f) 
    {
        EscenaInicial::font.RenderText(std::string("Pablo Rojas"), 120.0f ,100.0f, 0.6f, glm::vec3(1.0f,1.0f,1.0f));
    }

    pos -= glm::vec3(1.25f, 0.4f, -2.50f);;
    if ((pos.x < 0.5f && pos.x> -0.5) && ((pos.y < 0.5f && pos.y> -0.5)) && (pos.z < 0.05f && pos.z> -0.05))
    {
        cam.Position = glm::vec3(0.0f,0.0f,0.0f);
        SceneManager::Instance->ChangeScene(3);
    }
}

void EscenaFinal::SetLights() 
{
    //SETEAR LUCES
    //Luz ambiental direccional
    Utils::USetVec3(Cube::CubeShader, "dirLight.direction", glm::vec3(0.2f, -1.0f, 0.3f));
    Utils::USetVec3(Cube::CubeShader,"dirLight.ambient", glm::vec3(0.1f, 0.1f, 0.1f)*0.5f);
    Utils::USetVec3(Cube::CubeShader, "dirLight.diffuse", glm::vec3(0.05f, 0.05f, 0.05f));
    Utils::USetVec3(Cube::CubeShader, "dirLight.specular", glm::vec3(0.02f, 0.02f, 0.02f));

    // spotLight
    Utils::USetBool(Cube::CubeShader, "flash", true);
    Utils::USetVec3(Cube::CubeShader, "spotLight.position", cam.Position);
    Utils::USetVec3(Cube::CubeShader, "spotLight.direction", glm::normalize(cam.Front));
    Utils::USetVec3(Cube::CubeShader, "spotLight.ambient", glm::vec3(0.0f, 0.0f, 0.0f));
    Utils::USetVec3(Cube::CubeShader, "spotLight.diffuse", glm::vec3(1.0f, 0.7f, 0.3f));
    Utils::USetVec3(Cube::CubeShader, "spotLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    Utils::USetFloat(Cube::CubeShader, "spotLight.constant", 0.8f);
    Utils::USetFloat(Cube::CubeShader, "spotLight.linear", 0.09);
    Utils::USetFloat(Cube::CubeShader, "spotLight.quadratic", 0.032);
    Utils::USetFloat(Cube::CubeShader, "spotLight.cutOff", glm::cos(glm::radians(12.5f)));
    Utils::USetFloat(Cube::CubeShader, "spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

    //luz
    Utils::USetVec3(Cube::CubeShader, "pointLights[0].position", glm::vec3(1.0f,0.9f,0.1f));
    Utils::USetVec3(Cube::CubeShader, "pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
    Utils::USetVec3(Cube::CubeShader, "pointLights[0].diffuse", 0.1f, 0.1f, 0.1f);
    Utils::USetVec3(Cube::CubeShader, "pointLights[0].specular", glm::vec3(0.3f, 0.3f, 0.3f)*0.3f);
    Utils::USetFloat(Cube::CubeShader, "pointLights[0].constant", 0.1f);
    Utils::USetFloat(Cube::CubeShader, "pointLights[0].linear", 0.09);
    Utils::USetFloat(Cube::CubeShader, "pointLights[0].quadratic", 0.022);
}


void EscenaFinal::ProcessMouse(double x, double y) 
{

    float xoffset = x - lastx;
    float yoffset = lasty - y; //y es de arriba pa abajo

    lastx = x;
    lasty = y;

    cam.ProcessMouseMovement(xoffset, yoffset);
}
