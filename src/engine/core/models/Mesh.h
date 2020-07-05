#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <assimp/Importer.hpp>
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include "../utils/ResourceLoader.h"
#include "../shaders/ShaderProgram.h"
#include <math/Vec2.h>
#include <math/Vec3.h>

using std::vector;
using uint = unsigned int;

struct Vertex {
    fVec3 Position;
    fVec2 TexCoords;
    fVec3 Normal;
};

struct VertexTangent {
    fVec3 Tangent;
    fVec3 Bitangent;
};

struct Texture {
    unsigned int id;
    std::string type;
    aiString path;
};

class Mesh {
private:
    unsigned int VBO, EBO;
    unsigned int buffer[3];

    void setupMesh();

public:
    vector <Vertex> vertices;
    vector <VertexTangent> tangents;
    vector<unsigned int> indices;
    vector <Texture> textures;
    unsigned int VAO;

    Mesh() {}
    ~Mesh() {}

    Mesh(vector <Vertex> vertices, vector<unsigned int> indices, vector <Texture> textures);

    void draw(ShaderProgram &shaderProgram);


};

#endif // MESH_H