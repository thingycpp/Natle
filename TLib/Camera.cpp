#include "Camera.h"

Camera::Camera(glm::vec3 p_camPos)
	: cameraPos(p_camPos), worldUp(glm::vec3(0.0f, 1.0f, 0.0f)), yaw(-90.0), 
	pitch(0.0), camSpeed(2.5f), cameraFront(glm::vec3(0.0f, 0.0f, -1.0f))
{
	UpdateCameraVectors();
}

void Camera::UpdateCameraDirection(double dx, double dy)
{
	yaw += dx;
	pitch += dy;

	if (pitch > 89.0f) {
		pitch = 89.0f;
	}
	else if (pitch < -89.0f) {
		pitch = -89.0f;
	}

	UpdateCameraVectors();
}

void Camera::UpdateCameraPosition(CameraDir dir, double dtime)
{
	float vel = (float)dtime * camSpeed;

	switch (dir) {
	case CameraDir::FORWARD:
		cameraPos += cameraFront * vel;
		break;
	case CameraDir::BACKWARD:
		cameraPos -= cameraFront * vel;
		break;
	case CameraDir::RIGHT:
		cameraPos += cameraRight * vel;
		break;
	case CameraDir::LEFT:
		cameraPos -= cameraRight * vel;
		break;
	case CameraDir::UP:
		cameraPos += cameraUp * vel;
		break;
	case CameraDir::DOWN:
		cameraPos -= cameraUp * vel;
		break;
	}
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void Camera::UpdateCameraVectors()
{
	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(direction);

	cameraRight = glm::normalize(glm::cross(cameraFront, worldUp));
	cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));

}

