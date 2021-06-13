//Shader Vertex para objetos con materiales/UV mapping
#version 330 core

layout (location = 0) in vec3 Pos; //pos vertex
layout (location = 1) in vec3 aNormal; //normal
layout (location = 2) in vec2 UV; //coordenada textura

//valores salida
out vec3 FragPos; //deben ser iguales a los del shader
out vec3 Normal;
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() 
{
    FragPos = vec3(model * vec4(Pos, 1.0)); //cambiar con la matriz
    Normal = mat3(transpose(inverse(model))) * aNormal; //obtener inverso de la matriz

    TexCoords = UV; //se pasa el parametro sin cambios al Fragment Shader

    //guardar
    gl_Position = projection * view * vec4(FragPos, 1.0f);
}

