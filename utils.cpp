#include "utils.h"
#include <iostream>

bool CheckShaderCompile(GLuint shader)
{
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success); //pedimos el parametro compile status de shader

    if (!success)
    {
        char infoLog[512]; //aqui guardaremos el mensaje
        glGetShaderInfoLog(shader, 512, NULL, infoLog); //guardar mensaje del shader

        std::cout << "ERROR AL COMPILAR SHADER:\n"<<infoLog<<std::endl;
    }

    return success;
}


bool CheckProgramCompile(GLuint program) 
{
    int success = true;

    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    return success;
}