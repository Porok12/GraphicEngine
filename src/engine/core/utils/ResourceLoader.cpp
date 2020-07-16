#include "ResourceLoader.h"

std::map<ResourceType, path> ResourceLoader::paths = {};

ResourceLoader::ResourceLoader(path root_path) {
    root_path.append("res");

    path shader_path(root_path);
    ResourceLoader::paths.insert(std::make_pair(SHADER, std::move(shader_path.append("shaders"))));

    path texture_path(root_path);
    ResourceLoader::paths.insert(std::make_pair(TEXTURE, std::move(texture_path.append("textures"))));

    path model_path(root_path);
    ResourceLoader::paths.insert(std::make_pair(MODEL, std::move(model_path.append("models"))));

    path font_path(root_path);
    ResourceLoader::paths.insert(std::make_pair(FONT, std::move(font_path.append("fonts"))));
}

std::string ResourceLoader::getPath(std::string name, ResourceType type) {
    std::string result = path(paths.at(type)).append(name).string();
    return result;
}

GLuint ResourceLoader::loadTexture(std::string name) {
    std::string full_path = path(paths.at(TEXTURE)).append(name).string();

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
            BOOST_LOG_TRIVIAL(warning) << "Number of components not supported";

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        BOOST_LOG_TRIVIAL(info) << "Texture " << name.c_str() << " was loaded";

        SOIL_free_image_data(data);
    } else {
        const char* result = SOIL_last_result();
        BOOST_LOG_TRIVIAL(error) << "Texture failed to load at path: " << full_path.c_str() << ". Reason " << result;
        SOIL_free_image_data(data);
    }

    return textureID;
}
