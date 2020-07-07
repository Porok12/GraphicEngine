#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;

out vec4 color;

uniform mat4 ortho;

void main() {
    gl_Position = ortho * vec4(aPos, 1.0);
    color = aColor;
}