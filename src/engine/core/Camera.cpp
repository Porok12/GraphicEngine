
#include <math/Vec3.h>
#include "Camera.h"

Camera::Camera(const fVec3 &Position) : Position(Position) {
    const float YAW = -90.0f;
    const float PITCH = 0.0f;
    const float SPEED = 4.0f;
    const float SENSITIVITY = 0.1f;
    enabled = false;

    Yaw = YAW;
    Pitch = PITCH;
    MovementSpeed = SPEED;
    MouseSensitivity = SENSITIVITY;

    updateCameraVectors();
}

Mat4 Camera::getViewMatrix() {
//    std::cout << Mat4::lookAt(Position, Position + Front);
//    test = !test;
//    std::cout << Front.x << " " << Front.y << " " << Front.z << std::endl;
//    std::cout << this << std::endl;
    return Mat4::lookAt(Position, Position + Front, Up);
}

void Camera::updateCameraVectors() {
    const double D2R = M_PI / 180.0;
    fVec3 front;
    front.x = std::cos(Yaw * D2R) * std::cos(Pitch * D2R);
    front.y = std::sin(Pitch * D2R);
    front.z = std::sin(Yaw * D2R) * std::cos(Pitch * D2R);
    Front = front.normalize();
//    std::cout << this << std::endl;
//    std::cout << Front.x << " " << Front.y << " " << Front.z << std::endl;
    Right = Front.cross(fVec3(0, 1, 0)).normalize();
    Up = Right.cross(Front);
}

void Camera::processMouseMovement(const double &x, const double &y) {
    if (enabled) {
        double xoffset = x * MouseSensitivity;
        double yoffset = -y * MouseSensitivity;

        Yaw   += xoffset;
        Pitch += yoffset;

//    std::cout << Yaw << std::endl;

        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;

        updateCameraVectors();
    }
}

void Camera::processKeyboard(Camera_Movement direction, float deltaTime) {
    if (enabled) {
        float velocity = MovementSpeed * deltaTime;
        if (direction == FORWARD)
            Position += Front * velocity;
        if (direction == BACKWARD)
            Position -= Front * velocity;
        if (direction == LEFT)
            Position -= Right * velocity;
        if (direction == RIGHT)
            Position += Right * velocity;
    }
}

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

void Camera::toggle() {
    enabled = !enabled;
}

bool Camera::isEnabled() const {
    return enabled;
}

void Camera::reset() {
    const float YAW = -90.0f;
    const float PITCH = 0.0f;

    Yaw = YAW;
    Pitch = PITCH;
    Position = fVec3(0);

    updateCameraVectors();
}
