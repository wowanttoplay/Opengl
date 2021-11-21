//
// Created by virgil on 2021/11/21.
//

#ifndef OPENGL_CAMERA_H
#define OPENGL_CAMERA_H
#include "glog/logging.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

enum class Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};
const float kCameraYaw         = -90.0f;
const float kCameraPitch       =  0.0f;
const float kCameraSpeed       =  2.5f;
const float kSensitivity =  0.1f;
const float kZoom        =  45.0f;

class Camera
{
public:
    // constructor with vectors
    explicit Camera(glm::vec3 position = glm::vec3(0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = kCameraYaw, float pitch = kCameraPitch);

    virtual ~Camera();

    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    const glm::mat4& GetViewMatrix() const {return view_matrix_;}

    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard(Camera_Movement direction, float deltaTime);

    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);

    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(float yoffset);

private:
    // calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors();

    // 打印cameara 的信息
    void Print();

private:
    // camera Attributes
    glm::vec3 position_;
    glm::vec3 front_;
    glm::vec3 up_;
    glm::vec3 right_;
    glm::vec3 world_up_;
    // euler Angles
    float yaw_;
    float pitch_;
    // camera options
    float speed_;
    float mouse_sensitivity_;
    float fov_;

    glm::mat4 view_matrix_;
};


#endif //OPENGL_CAMERA_H
