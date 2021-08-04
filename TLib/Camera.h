#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include "libs/glm/glm/glm.hpp"
#include "libs/glm/glm/gtc/matrix_transform.hpp"

enum class CameraDir {
	NONE = 0,
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class Camera {
public:
	glm::vec3 cameraPos;

	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
	glm::vec3 cameraRight;

	glm::vec3 worldUp;

	float yaw;
	float pitch;
	float camSpeed;
	float camZoom;

	Camera(glm::vec3 p_camPos);

	void UpdateCameraDirection(float dx, float dy);
	void UpdateCameraPosition(CameraDir dir, double dtime);
	void UpdateCameraZoom(float dy);

	glm::mat4 GetViewMatrix();

private:
	void UpdateCameraVectors();

};

#endif
