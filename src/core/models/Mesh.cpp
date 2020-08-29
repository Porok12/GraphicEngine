#include "Mesh.h"
#include <utility>

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures) {
    this->vertices = std::move(vertices);
    this->indices = std::move(indices);
    this->textures = std::move(textures);

    setupMesh(false);
}

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures, vector<VertexTangent> tangents) {
    this->vertices = std::move(vertices);
    this->indices = std::move(indices);
    this->textures = std::move(textures);
    this->tangents = std::move(tangents);

    setupMesh(true);
}


void Mesh::setupMesh(bool bumpMapping) {
    calculateFlatNormals();

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &EBO);
    glGenBuffers(2, &buffer[0]);

    glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, Position));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, TexCoords));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, Normal));

    if (bumpMapping) {
        glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(tangents[0]) * tangents.size(), &tangents[0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexTangent), (void*) offsetof(VertexTangent, Tangent));
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(VertexTangent), (void*) offsetof(VertexTangent, Bitangent));
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    glBindVertexArray(0);
}

void Mesh::draw(const ShaderProgram &shaderProgram) const {
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;


    for(unsigned int i = 0; i < textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);

        std::stringstream ss;
        std::string number;
        std::string name = textures[i].type;
        if(name == "texture_diffuse")
            ss << diffuseNr++;
        else if (name == "texture_specular")
            ss << specularNr++;
        else if (name == "texture_normal")
            ss << normalNr++;
        else if (name == "texture_height")
            ss << heightNr++;
        number = ss.str();

        glUniform1i(glGetUniformLocation(shaderProgram.getId(), (name + number).c_str()), i);

        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }

    glBindVertexArray(VAO);

    if (eboAvailable) {
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    } else {
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    }


    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Mesh::calculateFlatNormals() {
    std::copy(vertices.begin(), vertices.end(), std::back_inserter(flatVertices));

    for (int i = 0; i < indices.size(); i += 3) {
        fVec3 one = vertices[indices[i+0]].Position;
        fVec3 two = vertices[indices[i+1]].Position;
        fVec3 three = vertices[indices[i+2]].Position;
        flatVertices[indices[i+0]].Normal = (one - two).cross(one - three).normalize();
        flatVertices[indices[i+1]].Normal = (one - two).cross(one - three).normalize();
        flatVertices[indices[i+2]].Normal = (one - two).cross(one - three).normalize();
    }
}

void Mesh::useFlatNormals(bool enable) {
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
    if (enable) {
        glBufferData(GL_ARRAY_BUFFER, sizeof(flatVertices[0]) * flatVertices.size(), &flatVertices[0], GL_STATIC_DRAW);
    } else {
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices) {
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &buffer[0]);

    glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, Position));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, TexCoords));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, Normal));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    glBindVertexArray(0);

    this->vertices = std::move(vertices);
    this->indices = std::move(indices);

    calculateFlatNormals();
}

Mesh::Mesh(vector<Vertex> vertices) {
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &buffer[0]);

    glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, Position));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, TexCoords));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, Normal));

    glBindVertexArray(0);

    std::copy(vertices.begin(), vertices.end(), std::back_inserter(flatVertices));
    for (int i = 0; i < vertices.size(); i += 3) {
        fVec3 one = vertices[i+0].Position;
        fVec3 two = vertices[i+1].Position;
        fVec3 three = vertices[i+2].Position;
        flatVertices[i+0].Normal = (one - two).cross(one - three).normalize();
        flatVertices[i+1].Normal = (one - two).cross(one - three).normalize();
        flatVertices[i+2].Normal = (one - two).cross(one - three).normalize();
    }

    this->vertices = std::move(vertices);
    this->eboAvailable = false;
}
