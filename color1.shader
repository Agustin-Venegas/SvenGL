#version 330 core

out vec4 FragColor;

uniform vec3 TriColor;

void main() {
    FragColor = vec4(TriColor, 1.0f);
}