#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUVs;

out vec2 UVs;
out vec4 color;

uniform int id;
uniform mat4 u_proj;
uniform vec3 u_offset = vec3(0.0f);
uniform vec4 u_color = vec4(1.0f);

void main() {
    float scale = 1.0f;
    gl_Position = u_proj * vec4(aPos * scale + u_offset, 1.0);
    color = u_color;
    UVs = aUVs;
}