#ifndef RESOURCELOADER_H
#define RESOURCELOADER_H

//#include <SOIL/SOIL.h>
//#include <GL/glew.h>
#include <boost/filesystem.hpp>
#include <iostream>
#include <map>

using namespace boost::filesystem;

enum ResourceType {
    SHADER,
    TEXTURE,
    MODEL,
    FONT
};

class ResourceLoader {
private:
    static std::map<ResourceType, path> paths;
public:
    ResourceLoader(path);

    static std::string getPath(std::string name, ResourceType type);
    static unsigned int loadTexture(std::string name);
};

#endif // RESOURCELOADER_H