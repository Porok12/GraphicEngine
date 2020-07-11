#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aOffset;
layout (location = 2) in float aLifeTime;

out vec2 currentTexCoord;
out vec2 nextTextCoord;
out float factor;

uniform vec3 camera;
uniform mat4 u_proj;
uniform int rows, columns;
uniform float lifeTime;

void main() {
    float scale = 1.0f;

    gl_Position = u_proj * vec4(aPos * scale + aOffset, 1.0);

    int images = rows * columns;
    float fimage = images * (1.0-aLifeTime/lifeTime);
    int iimage = int(fimage);
    factor = fimage - iimage;
    int id = iimage;

    float uv_x = (id%8)/8.0f;
    float uv_y = (id/8)/8.0f;
    float off = 1.0f/8.0f;

    if (gl_VertexID == 0) {
        currentTexCoord = vec2(uv_x+off, uv_y);
    } else if (gl_VertexID == 1) {
        currentTexCoord = vec2(uv_x, uv_y);
    } else if (gl_VertexID == 2) {
        currentTexCoord = vec2(uv_x+off, uv_y+off);
    } else if (gl_VertexID == 3) {
        currentTexCoord = vec2(uv_x, uv_y+off);
    }

    id = id + 1;

    uv_x = (id%8)/8.0f;
    uv_y = (id/8)/8.0f;

    if (gl_VertexID == 0) {
        nextTextCoord = vec2(uv_x+off, uv_y);
    } else if (gl_VertexID == 1) {
        nextTextCoord = vec2(uv_x, uv_y);
    } else if (gl_VertexID == 2) {
        nextTextCoord = vec2(uv_x+off, uv_y+off);
    } else if (gl_VertexID == 3) {
        nextTextCoord = vec2(uv_x, uv_y+off);
    }
}