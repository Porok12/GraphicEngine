#include "ResourceLoader.h"

std::map<ResourceType, path> ResourceLoader::paths = {};

ResourceLoader::ResourceLoader(path root_path) {
    root_path /= "res";

    path shader_path(root_path);
    shader_path /= "shaders";
    ResourceLoader::paths.insert(std::make_pair(SHADER, std::move(shader_path)));

    path texture_path(root_path);
    texture_path /= "textures";
    ResourceLoader::paths.insert(std::make_pair(TEXTURE, std::move(texture_path)));

    path model_path(root_path);
    model_path /= "models";
    ResourceLoader::paths.insert(std::make_pair(MODEL, std::move(model_path)));

    path font_path(root_path);
    font_path /= "fonts";
    ResourceLoader::paths.insert(std::make_pair(FONT, std::move(font_path)));
}

std::string ResourceLoader::getPath(std::string name, ResourceType type) {
    std::string result = (path(paths.at(type)) /= name).string();
    return result;
}

GLuint ResourceLoader::loadTexture(std::string name) {
    std::string full_path = (path(paths.at(TEXTURE)) /= name).string();

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char * data = SOIL_load_image(full_path.c_str(), &width, &height, &nrComponents, 0);

    if (data) {
        GLenum format = GL_RED;
        if (nrComponents == 1)
            format = GL_RED;
        else if(nrComponents == 3)
            format = GL_RGB;
        else if(nrComponents == 4)
            format = GL_RGBA;
        else
            std::cerr << "Number of components not supported" << std::endl;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        std::cout << "Texture " << name.c_str() << " was loaded" << std::endl;

        SOIL_free_image_data(data);
    } else {
        const char* result = SOIL_last_result();
        std::cerr << "Texture failed to load at path: " << full_path.c_str() << ". Reason " << result << std::endl;
        SOIL_free_image_data(data);
    }

    return textureID;
}
