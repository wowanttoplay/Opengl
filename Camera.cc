//
// Created by virgil on 2021/11/21.
//

#include "Camera.h"
#include "glm/gtx/string_cast.hpp"
using namespace google;

Camera::~Camera() {
    LOG_AT_LEVEL(ERROR) << "~Camera()";
}


Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) :
        front_(glm::vec3(0.0f, 0.0f, -1.0f)),
        speed_(kCameraSpeed),
        mouse_sensitivity_(kSensitivity),
        fov_(kZoom)
{
    LOG_AT_LEVEL(ERROR) << "Camera()";
    position_ = position;
    world_up_ = up;
    yaw_ = yaw;
    pitch_ = pitch;
    updateCameraVectors();
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime) {
    float velocity = speed_ * deltaTime;
    if (direction == Camera_Movement::FORWARD)
        position_ += front_ * velocity;
    if (direction == Camera_Movement::BACKWARD)
        position_ -= front_ * velocity;
    if (direction == Camera_Movement::LEFT)
        position_ -= right_ * velocity;
    if (direction == Camera_Movement::RIGHT)
        position_ += right_ * velocity;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch) {
    xoffset *= mouse_sensitivity_;
    yoffset *= mouse_sensitivity_;

    yaw_   += xoffset;
    pitch_ += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (pitch_ > 89.0f)
            pitch_ = 89.0f;
        if (pitch_ < -89.0f)
            pitch_ = -89.0f;
    }

    // update front_, right_ and up_ Vectors using the updated Euler angles
    updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset) {
    fov_ -= (float)yoffset;
    if (fov_ < 1.0f)
        fov_ = 1.0f;
    if (fov_ > 45.0f)
        fov_ = 45.0f;
}

void Camera::updateCameraVectors() {
    // calculate the new front_ vector
    glm::vec3 front;
    front.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
    front.y = sin(glm::radians(pitch_));
    front.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));
    front_ = glm::normalize(front);
    // also re-calculate the right_ and up_ vector
    right_ = glm::normalize(glm::cross(front_, world_up_));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    up_    = glm::normalize(glm::cross(right_, front_));
    view_matrix_ = glm::lookAt(position_, position_ + front_, up_);
}

void Camera::Print() {
    LOG(INFO) << "position_" << glm::to_string(position_);
    LOG(INFO) << "front_" << glm::to_string(front_);
    LOG(INFO) << "up_" << glm::to_string(up_);
    LOG(INFO) << "right_" << glm::to_string(right_);
    LOG(INFO) << "world_up_" << glm::to_string(world_up_);
    LOG(INFO) << "yaw_" << yaw_;
    LOG(INFO) << "pitch_" << pitch_;
    LOG(INFO) << "speed_" << speed_;
    LOG(INFO) << "mouse_sensitivity_" << mouse_sensitivity_;
    LOG(INFO) << "fov_" << fov_;
    LOG(INFO) << "view matrix" << glm::to_string(view_matrix_);
}
