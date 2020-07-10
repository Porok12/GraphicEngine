#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aOffset;
//layout (location = 2) in vec2 aOffset;

out vec2 UVs;
out vec2 UVs2;
out vec4 color;

uniform int id;
uniform vec3 camera;
uniform mat4 u_proj;
uniform vec3 u_offset = vec3(0.0f);
uniform vec4 u_color = vec4(1.0f);

void main() {
    float scale = 1.0f;
//    if(gl_InstanceID == 0) { Instanced
//        scale = 5.0f;
//    }

    gl_Position = u_proj * vec4((aPos+aOffset) * scale + u_offset, 1.0);
    color = u_color;
//    UVs = aUVs;

    float uv_x = (id%8)/8.0f;
    float uv_y = (id/8)/8.0f;
    float off = 1.0f/8.0f;

    if (gl_VertexID == 0) {
        UVs = vec2(uv_x+off, uv_y);
    } else if (gl_VertexID == 1) {
        UVs = vec2(uv_x, uv_y);
    } else if (gl_VertexID == 2) {
        UVs = vec2(uv_x+off, uv_y+off);
    } else if (gl_VertexID == 3) {
        UVs = vec2(uv_x, uv_y+off);
    }

    int nid = id + 1;

    uv_x = (nid%8)/8.0f;
    uv_y = (nid/8)/8.0f;

    if (gl_VertexID == 0) {
        UVs2 = vec2(uv_x+off, uv_y);
    } else if (gl_VertexID == 1) {
        UVs2 = vec2(uv_x, uv_y);
    } else if (gl_VertexID == 2) {
        UVs2 = vec2(uv_x+off, uv_y+off);
    } else if (gl_VertexID == 3) {
        UVs2 = vec2(uv_x, uv_y+off);
    }
}