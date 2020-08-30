#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <assimp/Importer.hpp>
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include <engine/core/utils/ResourceLoader.h>
#include <engine/core/shaders/ShaderProgram.h>
#include <engine/math/Vec2.h>
#include <engine/math/Vec3.h>

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
    GLuint VBO, EBO;
    GLuint buffer[3];
    bool eboAvailable = true;

    void setupMesh(bool bumpMapping);
    void calculateFlatNormals();

public:
    vector <Vertex> vertices;
    vector <Vertex> flatVertices;
    vector <VertexTangent> tangents;
    vector<unsigned int> indices;
    vector <Texture> textures;
    unsigned int VAO;

    Mesh() = default;
    ~Mesh() = default;
    Mesh(vector <Vertex> vertices);
    Mesh(vector <Vertex> vertices, vector<unsigned int> indices);
    Mesh(vector <Vertex> vertices, vector<unsigned int> indices, vector <Texture> textures);
    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector <Texture> textures, vector <VertexTangent> tangents);

    void draw(const ShaderProgram &shaderProgram) const;
    void useFlatNormals(bool enable);
};

#endif // MESH_H