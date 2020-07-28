#include "FreeCamera.h"

FreeCamera::FreeCamera(const fVec3 &Position) {
    this->Position = Position;

    const float YAW = -90.0f;
    const float PITCH = 0.0f;
    const float SPEED = 4.0f;
    const float SENSITIVITY = 0.1f;
    enabled = false;

    Yaw = YAW;
    Pitch = PITCH;
    MovementSpeed = SPEED;
    MouseSensitivity = SENSITIVITY;

    update();
}

Mat4 FreeCamera::getViewMatrix() {
    return Mat4::lookAt(Position, Position + Front, Up);
}

void FreeCamera::update() {
    const double D2R = M_PI / 180.0;
    fVec3 front;
    front.x = std::cos(Yaw * D2R) * std::cos(Pitch * D2R);
    front.y = std::sin(Pitch * D2R);
    front.z = std::sin(Yaw * D2R) * std::cos(Pitch * D2R);
    Front = front.normalize();
    Right = Front.cross(fVec3(0, 1, 0)).normalize();
    Up = Right.cross(Front);
}

void FreeCamera::processMouseMovement(const double &x, const double &y) {
    if (enabled) {
        double xoffset = x * MouseSensitivity;
        double yoffset = -y * MouseSensitivity;

        Yaw   += xoffset;
        Pitch += yoffset;

        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;

        update();
    }
}

void FreeCamera::processKeyboard(Camera_Movement direction, float deltaTime) {
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

void FreeCamera::toggle() {
    enabled = !enabled;
}

bool FreeCamera::isEnabled() const {
    return enabled;
}

void FreeCamera::reset() {
    const float YAW = -90.0f;
    const float PITCH = 0.0f;

    Yaw = YAW;
    Pitch = PITCH;
    Position = fVec3(0);

    update();
}
