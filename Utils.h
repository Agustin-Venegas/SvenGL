#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>
#include <vector>


using namespace std;

class Utils
{
    public:

    static GLFWwindow* window;
    //static unsigned int textureBuffer; //buffer de pantalla

    static float deltatime; //tiempo frame
    static bool CheckShaderCompile(GLuint shader);
    static bool CheckProgramCompile(GLuint program);
    static string ReadFile(const char *filename);
    static void CompileShader(const GLuint& shader, string source);

    //funciones matematicas
    static glm::vec3 MatPos(glm::mat4 matr);

    //funciones texturas
    static unsigned int loadTexture(string path);
    static unsigned int loadCubemap(vector<std::string> faces);

    //funcion VBO
    static unsigned int CreateVBO(float vert[], int amt);

    //funcs uniforms
    static void USetBool(GLuint id, const string &name, bool value);
    static void USetInt(GLuint id, const string &name, int value);
    static void USetFloat(GLuint id, const string &name, float value);
    static void USetVec3(GLuint id, const string &name, const glm::vec3 &value);
    static void USetVec3(GLuint id, const string &name, float x, float y, float z);
    static void USetMat4(GLuint id, const string &name, const glm::mat4 &value);

    static glm::mat4 projection;
    static GLuint program; //ID programa shaders default
};