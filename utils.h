#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>


using namespace std;
class Utils {
    public:
    static bool CheckShaderCompile(GLuint shader);
    static bool CheckProgramCompile(GLuint program);
    static string ReadFile(const string filename);
    static void CompileShader(const GLuint& shader, string source);
};