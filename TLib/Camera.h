#ifndef CAMERA_H
#define CAMERA_H

#include "libs/glew/include/GL/glew.h" 
#include "libs/glm/glm/gtc/matrix_transform.hpp" 

#include "Shaders.h"

enum class CameraDirection {
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
    
    float yaw;
    float pitch;
    float speed;
    float sensitivity;
    float fov;
    
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f));
    void UpdateCameraMatrices(Shaders sh);
    void UpdateCameraDirection(double dx, double dy);
    void UpdateCameraPos(CameraDirection direction, double dt);
    
    private:
    
    glm::mat4 GetModelMatrix()
    {
        return glm::mat4(1.0f);
    }
    glm::mat4 GetProjMatrix()
    {
        return glm::perspective(glm::radians(fov), 1280.0f / 720.0f, 0.1f, 100.0f);
    }
    glm::mat4 GetViewMatrix()
    {
        return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    }
    
    void UpdateCameraVectors();
};

#endif