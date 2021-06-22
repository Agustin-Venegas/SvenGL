#include "EscenaCubemap.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Utils.h"
#include "Cubo.h"
#include "Text.h"
#include "SceneManager.h"

void EscenaCubemap::Init() 
{
    //inicializar las cosas de los cubos
    Cube::InitVals();

    float skyboxVertices[] = {
        // positions          
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };

    //Crear Shader
    unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
    Utils::CompileShader(vs, Utils::ReadFile("SkyboxVertex.shader"));

    unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
    Utils::CompileShader(fs, Utils::ReadFile("SkyboxFragment.shader"));

    skyShader = glCreateProgram();
    glAttachShader(skyShader, vs);
    glAttachShader(skyShader, fs);
    glLinkProgram(skyShader);
    Utils::CheckProgramCompile(skyShader);
    glDeleteShader(vs);
    glDeleteShader(fs);
    
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    std::vector<std::string> skyfaces 
    {
        "sky/right.png",
        "sky/left.png",
        "sky/up.png",
        "sky/down.png",
        "sky/forward.png",
        "sky/back.png"
    };

    skyTex = Utils::loadCubemap(skyfaces);

}

EscenaCubemap::EscenaCubemap()
{
    Init();

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
    pos = glm::vec3(-0.5f,0.0f,-1.0f);
    rot = glm::radians(0.0f);
    t = glm::translate(t, pos);
    t = glm::rotate(t,rot, glm::vec3(1.0f, 1.0f, 0.0f));
    t = glm::scale(t, scale);

    walls.push_back(Cube(f,t));

    //tercera
    t = glm::mat4(1.0f);
    pos = glm::vec3(3.0f,0.0f,-1.0f);
    rot = glm::radians(0.0f);
    t = glm::translate(t, pos);
    t = glm::rotate(t,rot, glm::vec3(0.0f, 1.0f, 0.0f));
    t = glm::scale(t, scale);

    walls.push_back(Cube(f,t));

    //puerta izq
    t = glm::mat4(1.0f);
    pos = glm::vec3(2.25f, 0.0f, -2.75f);
    rot = glm::radians(90.0f);
    scale = glm::vec3(0.5f, 2.0f, 1.1f);
    
    t = glm::translate(t, pos);
    t = glm::rotate(t,rot, glm::vec3(0.0f, 1.0f, 0.0f));
    t = glm::scale(t, scale);

    walls.push_back(Cube(f,t));

    //puerta derecha
    t = glm::mat4(1.0f);
    pos = glm::vec3(0.25f, 0.0f, -2.75f);
    rot = glm::radians(90.0f);
    scale = glm::vec3(0.5f, 2.0f, 1.1f);
    
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

    //cuadro
    t = glm::mat4(1.0f);
    pos = glm::vec3(1.25f, 0.4f, 1.0f);
    rot = glm::radians(0.0f);
    scale = glm::vec3(1.0f, 1.0f, 0.1f);
    
    t = glm::translate(t, pos);
    t = glm::rotate(t,rot, glm::vec3(0.0f, 1.0f, 0.0f));
    t = glm::scale(t, scale);

    walls.push_back(Cube(std::string("underwater.png"),t));

    //cubo rotatorio
    t = glm::mat4(1.0f);
    pos = glm::vec3(1.25f, 0.5f, -5.0f);
    rot = glm::radians(0.0f);
    scale = glm::vec3(0.75f, 0.75f, 0.75f);
    
    t = glm::translate(t, pos);
    t = glm::rotate(t,rot, glm::vec3(0.0f, 1.0f, 0.0f));
    t = glm::scale(t, scale);

    rc = RotatingCube(std::string("disk.png"),t);


}

void EscenaCubemap::Update(float dt)
{
    auto window = Utils::window;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, dt);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, dt);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, dt);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, dt);


    rc.Update(dt);

    //deteccion de portal
    float dist = glm::length(camera.Position-glm::vec3(1.25f, 0.5f, -5.0f));
    if (dist<0.5f) 
    {
        SceneManager::Instance->ChangeScene(0);
    }
}

void EscenaCubemap::Draw(float dt) 
{
    Cube::PreDraw(camera);

    //SETEAR LUCES
    SetLights();

    for (Cube c:walls) 
    {
        c.Draw();
    }

    rc.Draw();

    //El Skybox se dibuja despues de la escena
    glDepthFunc(GL_LEQUAL);  //se dibujara solo donde no hayamos dibujado la escena
    glUseProgram(skyShader);
    
    auto view = glm::mat4(glm::mat3(camera.GetViewMatrix())); //obtener solo la direccion de la camara
    Utils::USetMat4(skyShader, "view", view);
    Utils::USetMat4(skyShader, "projection", Utils::projection);

    // skybox cube
    glBindVertexArray(skyboxVAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skyTex);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glDepthFunc(GL_LESS); //poner la funcion de corte a la normalidad


}

void EscenaCubemap::ProcessMouse(double x, double y) 
{

    float xoffset = x - lastx;
    float yoffset = lasty - y; //y es de arriba pa abajo

    lastx = x;
    lasty = y;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void EscenaCubemap::SetLights() 
{
    //SETEAR LUCES
    //Luz ambiental direccional
    Utils::USetVec3(Cube::CubeShader, "dirLight.direction", glm::vec3(0.2f, -1.0f, 0.3f));
    Utils::USetVec3(Cube::CubeShader,"dirLight.ambient", glm::vec3(0.68f, 0.55f, 0.55f)*0.5f);
    Utils::USetVec3(Cube::CubeShader, "dirLight.diffuse", glm::vec3(0.9f, 0.76f, 0.76f));
    Utils::USetVec3(Cube::CubeShader, "dirLight.specular", glm::vec3(0.3f, 0.3f, 0.3f));

    // spotLight
    Utils::USetBool(Cube::CubeShader, "flash", false);
    Utils::USetVec3(Cube::CubeShader, "spotLight.position", camera.Position);
    Utils::USetVec3(Cube::CubeShader, "spotLight.direction", glm::normalize(camera.Front));
    Utils::USetVec3(Cube::CubeShader, "spotLight.ambient", glm::vec3(0.0f, 0.0f, 0.0f));
    Utils::USetVec3(Cube::CubeShader, "spotLight.diffuse", glm::vec3(1.0f, 0.7f, 0.3f));
    Utils::USetVec3(Cube::CubeShader, "spotLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    Utils::USetFloat(Cube::CubeShader, "spotLight.constant", 1.0f);
    Utils::USetFloat(Cube::CubeShader, "spotLight.linear", 0.09);
    Utils::USetFloat(Cube::CubeShader, "spotLight.quadratic", 0.032);
    Utils::USetFloat(Cube::CubeShader, "spotLight.cutOff", glm::cos(glm::radians(12.5f)));
    Utils::USetFloat(Cube::CubeShader, "spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

    //luz
    Utils::USetVec3(Cube::CubeShader, "pointLights[0].position", glm::vec3(1.0f,0.9f,0.1f));
    Utils::USetVec3(Cube::CubeShader, "pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
    Utils::USetVec3(Cube::CubeShader, "pointLights[0].diffuse", 0.4f, 0.4f, 0.4f);
    Utils::USetVec3(Cube::CubeShader, "pointLights[0].specular", 0.4f, 0.4f, 0.4f);
    Utils::USetFloat(Cube::CubeShader, "pointLights[0].constant", 0.3f);
    Utils::USetFloat(Cube::CubeShader, "pointLights[0].linear", 0.09);
    Utils::USetFloat(Cube::CubeShader, "pointLights[0].quadratic", 0.022);
}