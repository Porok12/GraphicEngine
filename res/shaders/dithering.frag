#version 330 core

out vec4 FragColor;

in vec2 TexPos;
in vec3 FragPos;
in vec3 debug;

uniform sampler2D myTexture;
uniform vec3 palette[64];
uniform int paletteSize;
uniform int size;

vec3 nearest_palette_color(vec3 color, float m) {
    vec3 diff = color + (1.0 / paletteSize) * (m - 0.5);

    int j = 0;
    float minDist = distance(diff, palette[j]);
    for (int i = 1; i < paletteSize; i++) {
        float dist = distance(diff, palette[i]);
        if (dist < minDist) {
            minDist = dist;
            j = i;
        }
    }

    return palette[j];
}

void main() {
    mat2 threshold = mat2(0.25, 0.75, 1.0, 0.5);
    mat4 threshold4 = mat4(0, 8, 2, 10, 12, 4, 14, 6, 3, 11, 1, 9, 15, 7, 13, 5) / 16;
    float threshold8[64] = float[](
     0, 32, 8, 40, 2, 34, 10, 42,
    48, 16, 56, 24, 50, 18, 58, 26,
    12, 44, 4, 36, 14, 46, 6, 38,
    60, 28, 52, 20, 62, 30, 54, 22,
     3, 35, 11, 43, 1, 33, 9, 41,
    51, 19, 59, 27, 49, 17, 57, 25,
    15, 47, 7, 39, 13, 45, 5, 37,
    63, 31, 55, 23, 61, 29, 53, 21);

    for (int i = 0; i < 64; i++) {
        threshold8[i] /= 64;
    }

    vec3 color = texture(myTexture, TexPos).rgb;

    ivec2 siz = textureSize(myTexture, 0);
    ivec2 UV = ivec2(TexPos.x * siz.x, TexPos.y * siz.y);

    vec3 T;
    if (size == 0) {
        int i = UV.x % 2;
        int j = UV.y % 2;
        T = nearest_palette_color(color, threshold[i][j]);
    } else if (size == 1) {
        int i = UV.x % 4;
        int j = UV.y % 4;
        T = nearest_palette_color(color, threshold4[i][j]);
    } else {
        int i = UV.x % 8;
        int j = UV.y % 8;
        T = nearest_palette_color(color, threshold8[i*8+j]);
    }

    FragColor = vec4(T, 1.0);
}