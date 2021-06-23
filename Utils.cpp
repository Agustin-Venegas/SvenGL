#include "Utils.h"
#include <iostream>
#include <fstream>

//libreria externa para cargar imagenes de forma comoda
#include "stb_image.h"

#include <glm/gtc/matrix_transform.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <vector>

using namespace std;

GLuint Utils::program;//no borrar

GLFWwindow* Utils::window;

//unsigned int Utils::textureBuffer = 0; //buffer de pantalla

glm::mat4 Utils::projection = glm::perspective(glm::radians(45.0f), (float)800/(float)600, 0.1f, 100.0f);

float Utils::deltatime = 0;//clock

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
    int success = 1;

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

glm::vec3 Utils::MatPos(glm::mat4 matr) 
{
    return glm::vec3(matr[3]);
}

//funcion para cargar una textura. Regresa un id. ESPERA PNG PORQUE SOY UN IDIOTA
unsigned int Utils::loadTexture(string path)
{

    //voltear imagen
    stbi_set_flip_vertically_on_load(true);  

    //crear ID
    unsigned int textureID;
    glGenTextures(1, &textureID);

    //variables para guardar info regresada de load
    int width, height, nrComponents;
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);

    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        //liberar memoria
        stbi_image_free(data);
    }
    else
    {
        //ERROR
        std::cout << "ERROR al cargar textura: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

//cargar una textura como cubemap
//orden: X, -X, Y, -Y, Z, -Z
unsigned int Utils::loadCubemap(vector<std::string> faces)
{
    //voltear imagen
    stbi_set_flip_vertically_on_load(true); 
    
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}


//pide un pointer a un array de floats, y la cantidad de floats en ese array
//Hay que bindear el VAO primero
unsigned int Utils::CreateVBO(float vert[], int amt) 
{
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO); //se bindea asi que hay que hacer otra cosa pa desbindear o crear otros
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * amt, vert, GL_STATIC_DRAW);
	
	return VBO;
}


//FUNCIONES UNIFORM
void Utils::USetBool(GLuint id, const string &name, bool value) 
{
    glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value); //bool e int son como iguales
}

void Utils::USetInt(GLuint id, const string &name, int value)
{
     glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void Utils::USetFloat(GLuint id, const string &name, float value)
{
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void Utils::USetVec3(GLuint id, const string &name, const glm::vec3 &value)
{
    glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
}
void Utils::USetVec3(GLuint id, const string &name, float x, float y, float z)
{
    glUniform3f(glGetUniformLocation(id, name.c_str()), x, y, z);
}

void Utils::USetMat4(GLuint id, const string &name, const glm::mat4 &value)
{
    glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &value[0][0]);
}