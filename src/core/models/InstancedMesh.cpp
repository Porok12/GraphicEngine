#include <engine/core/models/InstancedMesh.h>

//InstancedMesh::InstancedMesh(std::vector<Vertex> &vertices) {
////    glGenVertexArrays(1, &VAO);
////    glBindVertexArray(VAO);
////    glGenBuffers(2, &buffer[0]);
////
////    glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
////    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
////    glEnableVertexAttribArray(0);
////    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, Position));
////    glEnableVertexAttribArray(1);
////    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, TexCoords));
////    glEnableVertexAttribArray(2);
////    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, Normal));
////
////    glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
//////    glBufferData(GL_ARRAY_BUFFER, sizeof(positions[0]) * positions.size(), &positions[0], GL_STATIC_DRAW);
////    glEnableVertexAttribArray(3);
////    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) nullptr);
////    glVertexAttribDivisor(3, 1);
////
////    glBindBuffer(GL_ARRAY_BUFFER, 0);
////    glBindVertexArray(0);
////
////    for (int i = 0; i < vertices.size(); i += 3) {
////        fVec3 one = vertices[i+0].Position;
////        fVec3 two = vertices[i+1].Position;
////        fVec3 three = vertices[i+2].Position;
////        vertices[i+0].Normal = (one - two).cross(one - three).normalize();
////        vertices[i+1].Normal = (one - two).cross(one - three).normalize();
////        vertices[i+2].Normal = (one - two).cross(one - three).normalize();
////    }
////
////    this->vertices = std::move(vertices);
//}

void InstancedMesh::draw(std::vector<fVec3> &positions) const {
    glBindVertexArray(VAO);
    glDrawArraysInstanced(GL_TRIANGLES, 0, vertices.size(), positions.size());
    glBindVertexArray(0);
}

void InstancedMesh::draw() const {
    glBindVertexArray(VAO);
    glDrawArraysInstanced(GL_TRIANGLES, 0, vertices.size(), positions.size());
    glBindVertexArray(0);
}

void InstancedMesh::setPositions(std::vector<fVec3> positions) {
    std::vector<float> data;

    for (auto &p: positions) {
        data.push_back((float ) p.x);
        data.push_back((float ) p.y);
        data.push_back((float ) p.z);
    }

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data[0]) * data.size(), &data[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    this->positions = std::move(positions);
}

void InstancedMesh::loadMesh(vector<Vertex> vertices) {
    for (int i = 0; i < vertices.size(); i += 3) {
        fVec3 one = vertices[i+0].Position;
        fVec3 two = vertices[i+1].Position;
        fVec3 three = vertices[i+2].Position;
        vertices[i+0].Normal = (one - two).cross(one - three).normalize();
        vertices[i+1].Normal = (one - two).cross(one - three).normalize();
        vertices[i+2].Normal = (one - two).cross(one - three).normalize();
    }

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(2, &buffer[0]);

    glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, Position));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, TexCoords));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, Normal));
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(float)*3, (void*) nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glVertexAttribDivisor(3, 1);

    glBindVertexArray(0);

    this->vertices = std::move(vertices);
}
