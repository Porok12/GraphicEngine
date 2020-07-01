#include "ResourceLoader.h"

std::map<ResourceType, path> ResourceLoader::paths = {};

ResourceLoader::ResourceLoader(path root_path) {
    root_path.append("res");

    path shader_path(root_path);
    ResourceLoader::paths.insert(std::make_pair(SHADER, shader_path.append("shaders")));

    BOOST_LOG_TRIVIAL(info) << paths.at(SHADER).c_str();
}

std::string ResourceLoader::getPath(std::string name, ResourceType type) {
    std::string result = path(paths.at(type)).append(name).string();
    return result;
}
