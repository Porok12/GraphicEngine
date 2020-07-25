#version 330 core

out vec4 FragColor;

in vec2 TexPos;

uniform sampler2D myTexture;

uniform bool horizontal;
uniform int kernelSize;
uniform float kernel[32];

void main() {
    vec2 tex_offset = 1.0 / textureSize(myTexture, 0);
    vec3 result = texture(myTexture, TexPos).rgb * kernel[0];

    if (horizontal) {
        for (int i = 1; i <= kernelSize/2; ++i) {
            result += texture(myTexture, TexPos + vec2(tex_offset.x * i, 0.0)).rgb * kernel[i];
            result += texture(myTexture, TexPos - vec2(tex_offset.x * i, 0.0)).rgb * kernel[i];
        }
    } else {
        for (int i = 1; i <= kernelSize/2; ++i) {
            result += texture(myTexture, TexPos + vec2(0.0, tex_offset.y * i)).rgb * kernel[i];
            result += texture(myTexture, TexPos - vec2(0.0, tex_offset.y * i)).rgb * kernel[i];
        }
    }

    FragColor = vec4(result, 1.0);
}