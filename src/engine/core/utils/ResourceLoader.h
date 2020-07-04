#ifndef RESOURCELOADER_H
#define RESOURCELOADER_H

#include <SOIL.h>
#include <GL/glew.h>
#include <boost/log/trivial.hpp>
#include <boost/filesystem.hpp>
#include <map>

using namespace boost::filesystem;

enum ResourceType {
    SHADER,
    TEXTURE,
    MODEL
};

class ResourceLoader {
private:
    static std::map<ResourceType, path> paths;
public:
    ResourceLoader(path);

    static std::string getPath(std::string name, ResourceType type);
    static GLuint loadTexture(std::string name);
};

#endif // RESOURCELOADER_H