#include "Bloom.h"

Bloom::Bloom() {
    glGenFramebuffers(2, FBOs);
    glGenTextures(2, textures);

    for (unsigned int i = 0; i < 2; i++) {
        glBindFramebuffer(GL_FRAMEBUFFER, FBOs[i]);
        glBindTexture(GL_TEXTURE_2D, textures[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, IMAGE_WIDTH, IMAGE_HEIGHT, 0, GL_RGBA, GL_FLOAT, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textures[i], 0);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
            BOOST_LOG_TRIVIAL(error) << "Framebuffer not complete!";
        }
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
    program = std::make_shared<ShaderProgram>("gaussian");

    calculateKernel();
    updateKernel();
}

Bloom::~Bloom() {
//    BOOST_LOG_TRIVIAL(debug) << "Bloom destructor";
//    glDeleteTextures(2, textures);
//    glDeleteFramebuffers(2, FBOs);
}

void Bloom::calculateKernel() {
    double mean = kernelSize/2;
    double sum = 0.0;

    for (int x = 0; x < kernelSize; ++x) {
        kernel[x] = exp( -0.5 * pow((x-mean)/sigma, 2.0) ) / sqrt(2 * M_PI * sigma * sigma);
        sum += kernel[x];
    }

    for (int x = 0; x < kernelSize; ++x) {
        kernel[x] /= sum;
    }
}

void Bloom::updateKernel() {
    program->use();
    program->set1i("kernelSize", kernelSize);
    for (int x = 0; x <= kernelSize/2; ++x) {
        std::stringstream ss;
        ss << "kernel" << '[' << x << ']';
        program->set1f(ss.str(), static_cast<float>(kernel[kernelSize/2 + x]));
    }
}

const GLuint & Bloom::apply(const GLuint &textureID) {
    GLint data[4];
    glGetIntegerv(GL_VIEWPORT, data);

    glViewport(0, 0, IMAGE_WIDTH, IMAGE_HEIGHT);
    program->use();
    bool horizontal = true;
    glBindFramebuffer(GL_FRAMEBUFFER, FBOs[horizontal]);
    program->set1b("horizontal", horizontal);
    glBindTexture(GL_TEXTURE_2D, textureID);
    drawQuad();

    horizontal = false;
    glBindFramebuffer(GL_FRAMEBUFFER, FBOs[horizontal]);
    program->set1b("horizontal", horizontal);
    glBindTexture(GL_TEXTURE_2D, textures[!horizontal]);
    drawQuad();

    for (int i = 0; i < iterations; ++i) {
        horizontal = true;
        glBindFramebuffer(GL_FRAMEBUFFER, FBOs[horizontal]);
        program->set1b("horizontal", horizontal);
        glBindTexture(GL_TEXTURE_2D, textures[!horizontal]);
        drawQuad();

        horizontal = false;
        glBindFramebuffer(GL_FRAMEBUFFER, FBOs[horizontal]);
        program->set1b("horizontal", horizontal);
        glBindTexture(GL_TEXTURE_2D, textures[!horizontal]);
        drawQuad();
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(data[0], data[1], data[2], data[3]);

    return textures[0];
}

void Bloom::drawQuad() {
    if (quadVAO == 0) {
        float quadVertices[] = {
                -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
                -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
                1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
                1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        };

        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) nullptr);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) (3 * sizeof(float)));
    }

    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}

void Bloom::setKernelSize(unsigned int kernelSize) {
    Bloom::kernelSize = kernelSize;
    calculateKernel();
    updateKernel();
}

void Bloom::setSigma(double sigma) {
    Bloom::sigma = sigma;
    calculateKernel();
    updateKernel();
}

void Bloom::setIterations(unsigned int iterations) {
    Bloom::iterations = iterations;
}
