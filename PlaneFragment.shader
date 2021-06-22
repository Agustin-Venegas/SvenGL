#version 330 core

out vec4 FragColor;

in vec2 texcoords;

uniform sampler2D screenTexture;

void main()
{
    vec3 col = vec3(texture(screenTexture, texcoords));
    FragColor = vec4(col, 1.0);
} 