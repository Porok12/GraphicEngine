#ifndef MODEL_H
#define MODEL_H

#include <SOIL/SOIL.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>

#include <engine/math/Vec2.h>
#include <engine/math/Vec3.h>
//#include <engine/core/models/Mesh.h>
#include "../../../../src/core/models/Mesh.h"

using std::vector;

class Model {
private:
    vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
protected:
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    void processNode(aiNode *node, const aiScene *scene);

public:

    Model();

    vector<Texture> textures_loaded;
    vector<Mesh> meshes;
    bool bumpMapping;

    const aiScene* loadModel(std::string const &path);
    void draw(const ShaderProgram &shaderProgram) const;

    void enableBumpMapping(bool enable);
    void setFakeNormals();
    void useFlatNormals(bool enable);
};

#endif // MODEL_H