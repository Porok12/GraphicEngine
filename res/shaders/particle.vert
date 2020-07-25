#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aOffset;
layout (location = 2) in float aLifeTime;
layout (location = 3) in float aTransparency;
layout (location = 4) in vec2 aTrans;
layout (location = 5) in int aSelect;

out vec2 currentTexCoord;
out vec2 nextTextCoord;
out float factor;
out float transparency;

uniform vec3 camera, right, up;
uniform mat4 projection, view;
uniform int rows, columns;
uniform float lifeTime;

mat4 lookAt(vec3 pos, vec3 tar) {
    vec3 up = vec3(0, 1, 0);
    vec3 forward = normalize(pos - tar);
    vec3 right = cross(up, forward);
    up = normalize(cross(forward, right));

    mat4 mat;
    mat[0][0] = right[0];        mat[0][1] = up[0];        mat[0][2] = forward[0];        mat[0][3] = 0;
    mat[1][0] = right[1];        mat[1][1] = up[1];        mat[1][2] = forward[1];        mat[1][3] = 0;
    mat[2][0] = right[2];        mat[2][1] = up[2];        mat[2][2] = forward[2];        mat[2][3] = 0;
    mat[3][0] = -dot(right, pos); mat[3][1] = -dot(up, pos); mat[3][2] = -dot(forward, pos); mat[3][3] = 1;

    return mat;
}

void main() {
    transparency = aTransparency;

//    vec3 toCenter = aOffset - camera;
//    vec3 toVertex = (aPos) - camera;//(aPos + aOffset) - camera;
//    vec3 distance = normalize(toVertex) * 5;//length(toCenter);
//    vec3 diffrence = toVertex - distance;
//
//    vec3 tmp = normalize(camera - aPos);

//    gl_Position = projection * view * vec4(aOffset + aPos, 1.0);

    vec2 pos2d = vec2(aPos.xy * aTrans.x);
    gl_Position = projection * view * vec4(aOffset + right * pos2d.x + up * pos2d.y, 1.0);

    int images = rows * columns;
    int id;

    if (aSelect >= 0) {
        id = aSelect;
        factor = 0;
    } else {
        float fimage = images * (1.0-aLifeTime/lifeTime);
        int iimage = int(fimage);
        factor = fimage - iimage;
        id = iimage;
    }

    float uv_x = (id%rows) / float(rows);
    float uv_y = (id/columns) / float(columns);
    float xoff = 1.0f / float(rows);
    float yoff = 1.0f / float(columns);

    if (gl_VertexID == 0) {
        currentTexCoord = vec2(uv_x+xoff, uv_y);
    } else if (gl_VertexID == 1) {
        currentTexCoord = vec2(uv_x, uv_y);
    } else if (gl_VertexID == 2) {
        currentTexCoord = vec2(uv_x+xoff, uv_y+yoff);
    } else if (gl_VertexID == 3) {
        currentTexCoord = vec2(uv_x, uv_y+yoff);
    }

    if (id > (id+1)%rows) {
        factor = 0;
    }
    id = id + 1;

    uv_x = (id%rows) / float(rows);
    uv_y = (id/columns) / float(columns);

    if (gl_VertexID == 0) {
        nextTextCoord = vec2(uv_x+xoff, uv_y);
    } else if (gl_VertexID == 1) {
        nextTextCoord = vec2(uv_x, uv_y);
    } else if (gl_VertexID == 2) {
        nextTextCoord = vec2(uv_x+xoff, uv_y+yoff);
    } else if (gl_VertexID == 3) {
        nextTextCoord = vec2(uv_x, uv_y+yoff);
    }
}