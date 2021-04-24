#include "utils.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

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

string Utils::ReadFile(string filename) 
{
    string content;
    ifstream fileStream(filename, std::ios::in);

    if(!fileStream.is_open()) {
        std::cerr << "Could not read file " << filename << ". File does not exist." << std::endl;
        return "";
    }

    string line = "";
    while(!fileStream.eof()) {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    return content;
}