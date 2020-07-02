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
//    void calculateTangentSpace(vector<Vertex> &vertices, vector<unsigned int> &indices);
protected:
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    void processNode(aiNode *node, const aiScene *scene);

public:

    vector<Texture> textures_loaded;
    vector<Mesh> meshes;
    bool gammaCorrection;
    const aiScene* loadModel(std::string const &path);

//    Model(std::string const &path, bool gamma = false);
//    Model(std::string const &path, bool bumpMapping, bool gamma);

    void draw(ShaderProgram shaderProgram);
    void setFakeNormals();

    bool bumpMapping;
};

#endif // MODEL_H