//vertex shader simple, sin uv ni normales
//para dibujar objetos sin iluminacion ni texturas

#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 perVertexColor;

out vec3 VertColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() 
{
    VertColor = perVertexColor;

    gl_Position = projection * view * model * vec4(aPos, 1.0);
}