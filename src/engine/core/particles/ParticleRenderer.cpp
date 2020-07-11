#include "ParticleRenderer.h"

std::unique_ptr<ParticleRenderer> ParticleRenderer::instance = nullptr;

ParticleRenderer *ParticleRenderer::getInstance() {
    if (!instance) {
        instance.reset(new ParticleRenderer);
    }

    return instance.get();
}

ParticleRenderer::ParticleRenderer() {
    init();
}

void ParticleRenderer::init() {
    float vertices[] = {
       -1.0f,  1.0f, 0.0f,
       -1.0f, -1.0f, 0.0f,
        1.0f,  1.0f, 0.0f,
        1.0f, -1.0f, 0.0f
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &meshVBO);
    glGenBuffers(1, &dataVBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, meshVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*3, (void*) nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ARRAY_BUFFER, dataVBO);
//    glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_STREAM_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float)*4, (void*) nullptr);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(float)*4, (void*) (sizeof(float)*3));
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glVertexAttribDivisor(0, 0);
    glVertexAttribDivisor(1, 1);
    glVertexAttribDivisor(2, 1);

    glBindVertexArray(0);
}

ParticleRenderer *ParticleRenderer::setProgram(const std::shared_ptr<ShaderProgram> &program) {
    this->program = program;
    return this;
}

ParticleRenderer *ParticleRenderer::setTexture(const GLuint &texture, const int &rows, const int &columns) {
    this->texture = texture;
    this->rows = rows;
    this->columns = columns;
    return this;
}

ParticleRenderer *ParticleRenderer::setProjection(const Mat4 &projection) {
    this->projection = projection;
    return this;
}

void ParticleRenderer::render(const std::vector<Particle> &particles, float lifeTime) {
    std::vector<float> data;
    for (const auto& p: particles) {
        data.push_back((float)p.Position.x);
        data.push_back((float)p.Position.y);
        data.push_back((float)p.Position.z);
        data.push_back(p.LifeTime);
    }

//    std::cout << particles[0].LifeTime << "/" << lifeTime << std::endl;

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, dataVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*data.size(), &data[0], GL_STREAM_DRAW);

    program->use().setMatrix4("u_proj", projection);
    program->set1f("lifeTime", lifeTime).set1i("rows", rows).set1i("columns", columns);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, static_cast<GLsizei>(data.size()));
    glBindVertexArray(0);
}
