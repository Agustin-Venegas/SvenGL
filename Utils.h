#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>


using namespace std;

class Utils {
    public:
    static float deltatime;
    static bool CheckShaderCompile(GLuint shader);
    static bool CheckProgramCompile(GLuint program);
    static string ReadFile(const char *filename);
    static void CompileShader(const GLuint& shader, string source);

    static GLuint program; //ID programa shaders default
};