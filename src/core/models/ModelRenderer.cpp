#include <engine/core/models/ModelRenderer.h>

std::unique_ptr<ModelRenderer> ModelRenderer::instance = nullptr;

ModelRenderer *ModelRenderer::getInstance() {
    if (!instance) {
        instance = std::unique_ptr<ModelRenderer>(new ModelRenderer);
    }

    return instance.get();
}

void ModelRenderer::setProgram(const std::shared_ptr <ShaderProgram> &program) {
    this->program = program;
}

void ModelRenderer::setProjection(const Mat4 &projection) {
    this->projection = projection;
}

void ModelRenderer::setView(const Mat4 &view) {
    this->view = view;
}

void ModelRenderer::setModel(const Mat4 &model) {
    this->model = model;
}

void ModelRenderer::render(const Model &model) {
    program->use();
    program->setMatrix4("projection", projection);
    program->setMatrix4("view", view);
    program->setMatrix4("model", this->model);
    model.draw(*program.get());
}

void ModelRenderer::render(const Model &model, ShaderProgram &program) {
    program.use();
    program.setMatrix4("projection", projection);
    program.setMatrix4("view", view);
    program.setMatrix4("model", this->model);
    model.draw(program);
}

ShaderProgram *ModelRenderer::getProgram() {
    return program.get();
}

const Mat4 &ModelRenderer::getProjection() const {
    return projection;
}

const Mat4 &ModelRenderer::getView() const {
    return view;
}

void ModelRenderer::render(const InstancedModel &model, ShaderProgram &program) {
    program.use();
    program.setMatrix4("projection", projection);
    program.setMatrix4("view", view);
    program.setMatrix4("model", this->model);
    model.draw(program);
}
