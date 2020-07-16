#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexPos;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;

out vec2 TexPos;
out vec3 FragPos;
out vec3 Normal;
//out vec3 TangentLightPos;
out vec3 TangentViewPos;
out vec3 TangentFragPos;
out mat3 oTBN;
out vec3 debug;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 viewPos;

void main() {
    FragPos = vec3(model * vec4(aPos, 1.0));
    mat3 normalMatrix = transpose(inverse(mat3(model)));
    Normal = normalize(normalMatrix * aNormal);
    TexPos = aTexPos;

    //mat3 normalMatrix = transpose(inverse(mat3((model)))); // transpose
    vec3 T = normalize(normalMatrix * aTangent);
    vec3 N = normalize(normalMatrix * aNormal);
    vec3 B = normalize(normalMatrix * aBitangent);

    mat3 TBN = mat3(T, B, N);
    //    TangentLightPos = TBN * lightPos;
    TangentViewPos = TBN * viewPos;
    TangentFragPos = TBN * vec3(model * vec4(aPos, 1.0)); //FragPos;
    oTBN = (TBN);
    debug = N;

    gl_Position = projection * view * vec4(FragPos, 1.0);
}