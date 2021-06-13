//Shader simple de colores por vertice
//sin iluminacion ni texturas
#version 330 core

out vec4 FragColor;

//usa los valores del vertex shader
in vec3 VertColor;

void main()
{
    FragColor = vec4(VertColor, 1.0f);
}