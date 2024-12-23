#ifndef MODELRENDERER_H
#define MODELRENDERER_H

#include <memory>
#include <engine/core/shaders/ShaderProgram.h>
#include "Model.h"
#include "InstancedModel.h"

class ModelRenderer {
private:
    std::shared_ptr<ShaderProgram> program;
    Mat4 projection, view, model;

    static std::unique_ptr<ModelRenderer> instance;
public:
    void setProgram(const std::shared_ptr<ShaderProgram> &program);
    void setProjection(const Mat4 &projection);
    void setView(const Mat4 &view);
    void setModel(const Mat4 &model);

    void render(const Model &model);
    void render(const Model &model, ShaderProgram &program);
    void render(const InstancedModel &model, ShaderProgram &program);

    static ModelRenderer* getInstance();

    ShaderProgram *getProgram();

    const Mat4 &getProjection() const;

    const Mat4 &getView() const;
};

#endif // MODELRENDERER_H