#version 330 core

in vec2 currentTexCoord;
in vec2 nextTextCoord;
in float factor;
in float transparency;

out vec4 FragColor;

uniform sampler2D sprite;

void main() {
    vec4 texColor = mix(texture(sprite, currentTexCoord), texture(sprite, nextTextCoord), factor);
//    if(texColor.a < 0.01)
//        discard;

    if (texColor.a > transparency) {
        texColor.a = transparency;
    }

    FragColor = texColor;
}
