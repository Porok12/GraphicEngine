#version 330 core

out vec4 FragColor;

in vec2 TexPos;
in vec3 Normal;
in vec3 FragPos;
in vec3 TangentFragPos;
in vec3 TangentViewPos;
in mat3 oTBN;
in vec3 debug;

struct DirLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
    float constant;
    float linear;
    float quadratic;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform bool enableNormalMap;
uniform bool enableSpecularMap;
uniform vec3 viewPos;
uniform PointLight pointLight;
uniform DirLight dirLight;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_normal1;
//uniform sampler2D texture_height1;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main() {
    vec3 norm = Normal;
    if (enableNormalMap) {
        norm = texture(texture_normal1, TexPos).rgb;
        norm = normalize(oTBN * (norm * 2.0 - 1.0));
    }

    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 result = vec3(0);
    result += CalcDirLight(dirLight, norm, viewDir);
    result += CalcPointLight(pointLight, norm, FragPos, viewDir);

    FragColor = vec4(result, 1.0);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64); //material.shininess); // texture(texture_specular1, TexPos).r)
    vec3 ambient = light.ambient * texture(texture_diffuse1, TexPos).rgb;
    vec3 diffuse = light.diffuse * diff * texture(texture_diffuse1, TexPos).rgb;
    vec3 specular = light.specular * spec;
    if (enableSpecularMap)
        specular *= texture(texture_specular1, TexPos).rgb;
    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightPos = light.position;
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64); //texture(texture_specular1, TexPos).r); //material.shininess);
    float distance = length(lightPos - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    vec3 ambient = light.ambient * texture(texture_diffuse1, TexPos).rgb;
    vec3 diffuse = light.diffuse * diff * texture(texture_diffuse1, TexPos).rgb;
    vec3 specular = light.specular * spec;
    if (enableSpecularMap)
        specular *= texture(texture_specular1, TexPos).rgb;
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}