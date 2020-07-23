#include "ParticleRenderer.h"
#include "ParticleGenerator.h"

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
    std::cerr << sizeof(ParticleData) << std::endl;
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(ParticleData), (void*) nullptr);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(ParticleData), (void*) (sizeof(float)*3));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(ParticleData), (void*) (sizeof(float)*4));
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, sizeof(ParticleData), (void*) (sizeof(float)*5));
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 1, GL_FLOAT, GL_FALSE, sizeof(ParticleData), (void*) (sizeof(float)*7));
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glVertexAttribDivisor(0, 0);
    glVertexAttribDivisor(1, 1);
    glVertexAttribDivisor(2, 1);
    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);

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

void ParticleRenderer::render(const ParticleGenerator *generator) {
    render(generator->getParticles(), generator->getLifeTime(), generator->getTexture());
}

void ParticleRenderer::render(const std::vector<std::shared_ptr<Particle>> &particles, float lifeTime, const GLuint &texture) {
    std::vector<ParticleData> data;
    for (const auto& p: particles) {
        if (p->LifeTime < 0.01) continue;
        data.push_back(ParticleData(*p));
//        std::cout << p->Select << std::endl;
        data.emplace_back(*p);
    }


    auto cam = this->cameraPos;
    auto right = this->right;
    auto up = this->up;
    auto sortRule = [&cam, &right, &up](const ParticleData &a, const ParticleData &b) -> bool {
        float aDist =
                (cam.x-a.x)*(cam.x-a.x)+
                (cam.y-a.y)*(cam.y-a.y)+
                (cam.z-a.z)*(cam.z-a.z);
        float bDist =
                (cam.x-b.x)*(cam.x-b.x)+
                (cam.y-b.y)*(cam.y-b.y)+
                (cam.z-b.z)*(cam.z-b.z);
        return aDist > bDist;
    };

    std::sort(data.begin(), data.end(), sortRule);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, dataVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(ParticleData)*data.size(), &data[0], GL_STREAM_DRAW);

    program->use().setMatrix4("projection", projection).setMatrix4("view", view)
            .set3f("camera", cameraPos.x, cameraPos.y, cameraPos.z)
            .set3f("right", right.x, right.y, right.z)
            .set3f("up", up.x, up.y, up.z);
    program->set1f("lifeTime", lifeTime).set1i("rows", rows).set1i("columns", columns);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->texture);

    glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, static_cast<GLsizei>(data.size()));
    glBindVertexArray(0);
}

ParticleRenderer* ParticleRenderer::setView(const Mat4 &view) {
    this->view = view;
    return this;
}

ParticleRenderer* ParticleRenderer::setCamera(fVec3 cameraPos) {
    this->cameraPos = cameraPos;
    return this;
}

ParticleRenderer *ParticleRenderer::setRight(const fVec3 &right) {
    this->right = right;
    return this;
}

ParticleRenderer *ParticleRenderer::setUp(const fVec3 &up) {
    this->up = up;
    return this;
}

ParticleRenderer::ParticleData::ParticleData(const Particle& particle)
        : x(particle.Position.x), y(particle.Position.y), z(particle.Position.z),
          lifeTime(particle.LifeTime), transparency(particle.Transparency),
          size(particle.Size), angle(particle.Angle), select(particle.Select) {
}

//ParticleRenderer::ParticleData::ParticleData(float x, float y, float z, float lifeTime)
//        : x(x), y(y), z(z), lifeTime(lifeTime), transparency(1) {
//
//}
//
//
//ParticleRenderer::ParticleData::ParticleData(float x, float y, float z, float lifeTime, float transparency)
//        : x(x), y(y), z(z), lifeTime(lifeTime), transparency(transparency) {
//
//}
