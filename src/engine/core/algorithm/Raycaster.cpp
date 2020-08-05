#include "Raycaster.h"

GLint Raycaster::data[4];
double Raycaster::x, Raycaster::y, Raycaster::z;

bool Raycaster::raycastPlane(const fVec3 &rayOrigin, const fVec3 &rayDirection, const fVec3 &normal, const fVec3 &center, fVec3 &hit) {
    float denom = normal.dot(rayDirection);

    if (abs(denom) > 0.0001f) {
        float t = (center - rayOrigin).dot(normal) / denom;
        if (t > 0) { // 0 - behind
            fVec3 tmp = rayOrigin + rayDirection * t;
            hit.x = tmp.x; hit.y = tmp.y; hit.z = tmp.z;

            return true;
        }
    }

    return false;
}

fVec3 Raycaster::cursorToWorld(const double &mouse_x, const double &mouse_y) {
    glGetIntegerv(GL_VIEWPORT, data);
    Raycaster::x = 1.0f - (2.0f * mouse_x) / data[2];
    Raycaster::y = 1.0f - (2.0f * mouse_y) / data[3];
    Raycaster::z = 1.0f;

    fVec3 ray_nds = fVec3(Raycaster::x, Raycaster::y, Raycaster::z);
    fVec4 ray_clip = fVec4(ray_nds.x, ray_nds.y, -1.0, 1.0);

    Mat4 projection_matrix = ModelRenderer::getInstance()->getProjection();
    projection_matrix.inverse();
    Mat4 view_matrix = ModelRenderer::getInstance()->getView();
    view_matrix.inverse();

    fVec4 ray_eye = projection_matrix * ray_clip;
    ray_eye = fVec4(ray_eye.x, ray_eye.y, -1.0, 0.0);

    fVec4 tmp = view_matrix * ray_eye;
    fVec3 ray_wor = fVec3(tmp.x, tmp.y, tmp.z);
    ray_wor.normalize();

    return ray_wor;
}
