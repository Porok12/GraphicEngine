#include <engine/core/models/Model.h>

Model::Model() : bumpMapping(false) {

}

const aiScene* Model::loadModel(std::string const& path) {
    Assimp::Importer importer;
    int settings = aiProcess_Triangulate | aiProcess_FlipUVs;
    if(bumpMapping) {
        settings |= aiProcess_CalcTangentSpace;
    }
    const aiScene* scene = importer.ReadFile(path, (aiPostProcessSteps)settings);

    if(!scene || (scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) || !scene->mRootNode) {
        std::cerr << "Assimp error: " << importer.GetErrorString() << std::endl;
        return nullptr;
    }

    std::cout << "Loaded path at " << path.c_str() << std::endl;

    processNode(scene->mRootNode, scene);

    return const_cast<const aiScene*>(scene);
}

void Model::processNode(aiNode* node, const aiScene* scene) {
    for(unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }

    for(unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene) {
    vector<Vertex> vertices;
    vector<VertexTangent> tangents;
    vector<unsigned int> indices;
    vector<Texture> textures;

    for(unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;
        fVec3 vec;
        vec.x = mesh->mVertices[i].x;
        vec.y = mesh->mVertices[i].y;
        vec.z = mesh->mVertices[i].z;
        vertex.Position = vec;
        vec.x = mesh->mNormals[i].x;
        vec.y = mesh->mNormals[i].y;
        vec.z = mesh->mNormals[i].z;
        vertex.Normal = vec;

        if(mesh->mTextureCoords[0]) {
            fVec2 v;
            v.x = mesh->mTextureCoords[0][i].x;
            v.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = v;
        } else {
            vertex.TexCoords = fVec2(0.0f);
        }

        vertices.push_back(vertex);

        if (mesh->HasTangentsAndBitangents()) {
            VertexTangent vertTangent;
            vec.x = mesh->mTangents[i].x;
            vec.y = mesh->mTangents[i].y;
            vec.z = mesh->mTangents[i].z;
            vertTangent.Tangent = vec;
            vec.x = mesh->mBitangents[i].x;
            vec.y = mesh->mBitangents[i].y;
            vec.z = mesh->mBitangents[i].z;
            vertTangent.Bitangent = vec;

            tangents.push_back(vertTangent);
        }
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];

        for(unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

    vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

    // OBJ specular -> aiTextureType_SHININESS
    vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SHININESS, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

    // OBJ normal -> aiTextureType_HEIGHT
    vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

    if (bumpMapping) {
        return Mesh(vertices, indices, textures, tangents);
    }

    return Mesh(vertices, indices, textures);
}

vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName) {
    vector<Texture> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
        aiString str;
        mat->GetTexture(type, i, &str);
        bool skip = false;

        for (unsigned int j = 0; j < textures_loaded.size(); j++) {
            if (std::strcmp(textures_loaded[j].path.C_Str(), str.C_Str()) == 0) {
                textures.push_back(textures_loaded[j]);
                skip = true;
                break;
            }
        }

        if (!skip) {
            Texture texture;
            texture.id = ResourceLoader::loadTexture(str.C_Str());
            texture.type = typeName;
            texture.path = str;
            textures.push_back(texture);
            textures_loaded.push_back(texture);
        }
    }

    return textures;
}

void Model::setFakeNormals() {
    for(unsigned int i = 0; i < meshes.size(); i++) {
        for(unsigned int j = 0; j < meshes[i].vertices.size(); j++) {
            meshes[i].vertices[j].Normal = fVec3(0.0f, 1.0f, 0.0f);
        }

        meshes[i] = Mesh(meshes[i].vertices, meshes[i].indices, meshes[i].textures);
    }
}

void Model::draw(const ShaderProgram &shaderProgram) const {
    for (unsigned int i = 0; i < meshes.size(); i++) {
        meshes[i].draw(shaderProgram);
    }
}

void Model::enableBumpMapping(bool enable) {
    this->bumpMapping = enable;
}

void Model::useFlatNormals(bool enable) {
    for (unsigned int i = 0; i < meshes.size(); i++) {
        meshes[i].useFlatNormals(enable);
    }
}

Model::Model(Mesh mesh) {
    meshes.push_back(std::move(mesh));
}

Model::Model(vector<Mesh> &meshes) {
    for (auto &m: meshes) {
        this->meshes.push_back(m);
    }
}

