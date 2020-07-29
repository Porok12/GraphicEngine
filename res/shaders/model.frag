#version 330 core

out vec4 FragColor;

in vec2 UVs;

uniform sampler2D texture_diffuse1;

uniform int colorTarget = 0;

void main() {
    vec3 color = vec3(texture(texture_diffuse1, UVs).rgb);

    mat3 YUVmatrix = mat3(
        0.299,  0.587,  0.114,
        -0.147, -0.2886,  0.436,
        0.615, -0.51499, -0.1001
    );

    YUVmatrix = transpose(YUVmatrix);

    vec3 YUV = (YUVmatrix) * color;
    float Vmax = 0.615;
    float Umax = 0.436;

    if (colorTarget == 0) {
        FragColor = vec4(color, 1.0);
    } else if (colorTarget == 1) {
        YUV.y = 0;
        YUV.z = 0;
        YUV = inverse((YUVmatrix)) * YUV;
        FragColor = vec4(YUV, 1.0);
    } else if (colorTarget == 2) {
        YUV.x = 0;
        YUV.z = -Vmax;
        YUV = inverse((YUVmatrix)) * YUV;
        FragColor = vec4((YUV), 1.0);
    } else if (colorTarget == 3) {
        YUV.x = 0;
        YUV.y = -Umax;
        YUV = inverse((YUVmatrix)) * YUV;
        FragColor = vec4((YUV), 1.0);
    }
}
