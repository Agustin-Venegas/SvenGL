#include "Utils.h"
#include <iostream>
#include <fstream>

using namespace std;

GLuint Utils::program;//no borrar

float Utils::deltatime = 0;//cock

bool Utils::CheckShaderCompile(GLuint shader)
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


bool Utils::CheckProgramCompile(GLuint program) 
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

std::string Utils::ReadFile(const char *filename) {
    std::string content;
    ifstream fileStream(filename, std::ios::in);

    if(!fileStream.is_open()) {
        std::cerr << "Could not read file " << filename << ". File does not exist." << std::endl;
        return "";
    }

    std::string line = "";
    while(!fileStream.eof()) {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    return content;
}

void Utils::CompileShader(const GLuint& shader, string source) 
{
    const char *const_source = source.c_str();
    glShaderSource(shader, 1, &const_source, NULL);
    glCompileShader(shader);

    if (!CheckShaderCompile(shader)) 
    {
        std::cout << "ERROR FATAL" << std::endl;
        return;
    }

}