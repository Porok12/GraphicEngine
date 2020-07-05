#version 330 core

//layout (location = 0) in vec2 aPos;
//layout (location = 1) in vec2 aUVs;
layout (location = 0) in vec4 aPos;

out vec2 UVs;

uniform mat4 ortho;

void main() {
    gl_Position = ortho * vec4(aPos.xy, 0.0, 1.0);
    UVs = aPos.zw;
}