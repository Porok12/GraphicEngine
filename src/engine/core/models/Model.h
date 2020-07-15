#ifndef MODEL_H
#define MODEL_H

#include <SOIL.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>

#include <math/Vec2.h>
#include <math/Vec3.h>
#include "Mesh.h"

using std::vector;

class Model {
private:
    vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
protected:
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    void processNode(aiNode *node, const aiScene *scene);

public:

    vector<Texture> textures_loaded;
    vector<Mesh> meshes;
    bool gammaCorrection;
    const aiScene* loadModel(std::string const &path);

    void draw(const ShaderProgram &shaderProgram) const;
//    void draw(const ShaderProgram *shaderProgram);
    void setFakeNormals();

    bool bumpMapping;

    void enableBumpMapping(bool enable);

    void useFlatNormals(bool enable);
};

#endif // MODEL_H