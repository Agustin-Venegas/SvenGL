#include "EscenaInicial.h"
#include "Utils.h"
#include "SceneManager.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

Font EscenaInicial::font;

EscenaInicial::EscenaInicial() 
{
    Plane::InitVals();
    unsigned int tex = Utils::loadTexture(std::string("menu.png")); 
    img = Plane(tex);
    font = Text::LoadFont("Hack.ttf");
}

void EscenaInicial::Init() {}
void EscenaInicial::Update(float dt) 
{
    auto window = Utils::window;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        SceneManager::Instance->ChangeScene(2);
}

void EscenaInicial::Draw(float dt) 
{
    img.Draw();
    font.RenderText(std::string("Presiona Espacio para continuar"), 10.0f ,400.0f, 0.6f, glm::vec3(1.0f,1.0f,1.0f));
    font.RenderText(std::string("Objetivo: Encontrar el Disco"), 10.0f,500.0f, 0.5f, glm::vec3(1.0f, 0.9f, 0.9f));
    font.RenderText(std::string("Creado por Agustin Venegas y Gabriel Jimenez"), 200.0f,100.0f, 0.4f, glm::vec3(1.0f, 0.9f, 0.9f));
}