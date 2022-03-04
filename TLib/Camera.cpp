#include "Camera.h"

#include <iostream>

Camera::Camera(glm::vec3 position /*= glm::vec3(0.0f)*/)
	: cameraPos(position),
      cameraUp(glm::vec3(0.0f, 1.0f, 0.0f)),
	  yaw(90.0f),
	  pitch(0.0f),
	  speed(2.5f),
	  sensitivity(1.0f),
	  fov(90.0f),
	  cameraFront(glm::vec3(-1.0f, 0.0f, 0.0f))
{
    UpdateCameraVectors();
}

Shaders SH;

void Camera::UpdateCameraMatrices(Shaders sh)
{

    SH = sh;

    glm::mat4 m = GetModelMatrix();
    glm::mat4 v = GetViewMatrix();
    glm::mat4 p = GetProjMatrix();

    sh.setMat4("model", m);
    sh.setMat4("view", v);
    sh.setMat4("projection", p);

}

void Camera::UpdateCameraDirection(double dx, double dy) {
    yaw += dx * (sensitivity / 10.0f);
    pitch += dy * (sensitivity / 10.0f);

    if (pitch > (fov-2)) {
        pitch = (fov-2);
    }
    if (pitch < -(fov-2)) {
        pitch = -(fov-2);
    }

    UpdateCameraVectors();
}

void Camera::UpdateCameraPos(CameraDirection direction, double dt) {
    float velocity = (float)dt * speed;

    switch (direction) {
    case CameraDirection::FORWARD:
        cameraPos += cameraFront * velocity;
        break;
    case CameraDirection::BACKWARD:
        cameraPos -= cameraFront * velocity;
        break;
    case CameraDirection::RIGHT:
        cameraPos += cameraRight * velocity;
        break;
    case CameraDirection::LEFT:
        cameraPos -= cameraRight * velocity;
        break;
    case CameraDirection::UP:
        cameraPos += cameraUp * velocity;
        break;
    case CameraDirection::DOWN:
        cameraPos -= cameraUp * velocity;
        break;
    }

    //std::cout << "X: " <<  cameraPos.x << " Y: " << cameraPos.y << " Z: " << cameraPos.z << std::endl;

    UpdateCameraMatrices(SH);
}

void Camera::UpdateCameraVectors() {
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);

    cameraRight = glm::normalize(glm::cross(cameraFront, cameraUp));
}