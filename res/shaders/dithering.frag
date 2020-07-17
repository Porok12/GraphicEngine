#version 330 core

out vec4 FragColor;

in vec2 TexPos;
in vec3 FragPos;
in vec3 debug;

uniform bool enableNormalMap;
uniform bool enableSpecularMap;
uniform vec3 viewPos;

uniform sampler2D myTexture;

void main() {
    mat2 threshold = mat2(0.25, 0.75, 1.0, 0.5);

    vec3 color = texture(myTexture, TexPos).rgb;
    //color = textureOffset(myTexture​, TexPos, ivec2(0, 0)).rgb;
    //textureSize(myTexture, 0);
    //    vec3 luminosity = vec3(0.30, 0.59, 0.11);
    //    float lum = dot(luminosity, color);

    float R = color.r;
    float G = color.g;
    float B = color.b;

    mat3 YUV = mat3(
    0.299,  0.587,  0.114,
    -0.147, -0.289,  0.437,
    0.615, -0.515, -0.100
    );

    float Y = 0.299 * R + 0.587 * G + 0.114 * B;
    float U = 0.492 * (B - Y);
    float V = 0.877 * (R - Y);

    vec3 newColor = YUV * color;
    newColor.b = 0;
    newColor = inverse(YUV) * newColor;

    ivec2 siz = textureSize(myTexture, 0);
    //vec2 tex_offset = 1.0 / textureSize(myTexture, 0);
    ivec2 UV = ivec2(TexPos.x * siz.x, TexPos.y * siz.y);

    int i = UV.x % 2;
    int j = UV.y % 2;

    float T = 0;
    if (Y > threshold[i][j])
    T = 1;

    FragColor = vec4(vec3(T), 1.0);

    //vec2 tex_offset = 1.0 / textureSize(myTexture, 0);
    //vec3 result = texture(myTexture, TexPos).rgb * weight[0];

    //
    //    if (lum < 0.9)
    //    {
    //        value = float(int((fract(v/2.0))+(fract(h/2.0))));
    //        gl_FragColor.rgb *= vec3(value, value, value);
    //    }
    //
    //    if (lum < 0.75)
    //    {
    //        value = float(int((fract(v+v/2.0))+(fract(h+h/2.0))));
    //        gl_FragColor.rgb *= vec3(value, value, value);
    //    }
    //
    //    if (lum < 0.5)
    //    {
    //        value = float(int((fract(v+v+v/2.0))+(fract(h+h/2.0))));
    //        gl_FragColor.rgb *= vec3(value, value, value);
    //    }
    //
    //    if (lum < 0.25)
    //    {
    //        value = float(int((fract(v+v/2.0))+(fract(h+h+h/2.0))));
    //        gl_FragColor.rgb *= vec3(value, value, value);
    //    }
}