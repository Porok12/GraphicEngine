#ifndef RESOURCELOADER_H
#define RESOURCELOADER_H

#include <boost/log/trivial.hpp>
#include <boost/filesystem.hpp>
#include <map>

using namespace boost::filesystem;

enum ResourceType {
    SHADER
};

class ResourceLoader {
private:
    static std::map<ResourceType, path> paths;
public:
    ResourceLoader(path);

    static std::string getPath(std::string name, ResourceType type);
};

#endif // RESOURCELOADER_H