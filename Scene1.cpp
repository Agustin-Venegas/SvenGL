#include "Scene1.h"


scene1::scene1() : Scene() //constructor vacio, no se usa
{

}

scene1::scene1(GLuint program) : Scene(program) //constructor con el programa a usar
{

}

scene1::~scene1() {}


void scene1::Init() //cada hijo de escena edita esta funcion
{
    glVertexAttribPointer(
        0,        // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,        // size
        GL_FLOAT, // type
        GL_FALSE, // normalized?
        0,        // stride
        (void *)0 // array buffer offset
    ); 
}

void scene1::Update(float time) 
{

}

void scene1::Draw() 
{
    
}