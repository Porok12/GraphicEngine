#include <engine/core/Camera.h>

const fVec3 &Camera::getPos() const {
    return Position;
}

const fVec3 &Camera::getFront() const {
    return Front;
}

const fVec3 &Camera::getUp() const {
    return Up;
}

const fVec3 &Camera::getRight() const {
    return Right;
}