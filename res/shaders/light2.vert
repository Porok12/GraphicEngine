#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexPos;
layout (location = 2) in vec3 aNormal;

out vec2 TexPos;
out vec3 FragPos;
out vec3 Normal;
out vec3 Color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

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

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform vec3 viewPos;
uniform PointLight pointLight;
uniform DirLight dirLight;
uniform SpotLight spotLight;
uniform Material material;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, float shininess, float diffuse, float specular);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main() {
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;
    TexPos = aTexPos;

    gl_Position = projection * view * vec4(FragPos, 1.0);


    vec3 objectColor = normalize(vec3(220, 150, 10));
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 result = CalcDirLight(dirLight, norm, viewDir, 32, 1.0, 0.5);
    //    result += CalcPointLight(pointLight, norm, FragPos, viewDir);
    //    result += CalcSpotLight(spotLight, norm, FragPos, viewDir);

    result *= objectColor;
    Color = result;
}

// calculates the color when using a directional light.
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexPos));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexPos));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexPos));
    return (ambient + diffuse + specular);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, float _shininess, float _diffuse, float _specular) {
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), _shininess);
    // combine results
    vec3 ambient = light.ambient * vec3(_diffuse);
    vec3 diffuse = light.diffuse * diff * vec3(_diffuse);
    vec3 specular = light.specular * spec * vec3(_specular);
    return (ambient + diffuse + specular);
}

// calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexPos));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexPos));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexPos));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

// calculates the color when using a spot light.
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexPos));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexPos));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexPos));
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}