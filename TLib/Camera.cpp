#include "Camera.h"

#define M_PI 3.14159

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

void setProjectionMatrix(const float& angleOfView, const float& near, const float& far, Matrix44f& M)
{
	float scale = 1 / tan(angleOfView * 0.5 * M_PI / 180);
	M[0][0] = scale;
	M[1][1] = scale;
	M[2][2] = -far / (far - near);
	M[3][2] = -far * near / (far - near);
	M[2][3] = -1;
	M[3][3] = 0;
}


void Camera::loadPerspective()
{

	

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

