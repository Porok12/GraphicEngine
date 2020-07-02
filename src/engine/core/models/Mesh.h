#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <assimp/Importer.hpp>
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include "../utils/ResourceLoader.h"
#include "../shaders/ShaderProgram.h"
#include <math/Vec2.h>
#include <math/Vec3.h>

using std::vector;
using uint = unsigned int;

struct Vertex {
    Vec3<float> Position;
    Vec2<float> TexCoords;
    Vec3<float> Normal;
};

struct VertexTangent {
    Vec3<float> Tangent;
    Vec3<float> Bitangent;
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

    Mesh(vector <Vertex> vertices, vector<unsigned int> indices, vector <Texture> textures,
         vector <VertexTangent> tangents);


    void draw(ShaderProgram shaderProgram);

//    MeshType meshType;
};

#endif // MESH_H