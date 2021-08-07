#include "TLib/TL.h"

void keyInput(double dtime);

bool useUI = false;

Renderer* renderer;
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main(void)
{

    TLCreateWindow(1280, 720, "TLib: Camera Example", true);

    TLBeginExampleShaders();

    float p_verts[6] = {
    -0.2f, -0.2f,
    0.0f, 0.2f,
    0.2f, -0.2f,
    };

    unsigned int p_buffer;

    camera.loadPerspective();

    glGenBuffers(1, &p_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, p_buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), p_verts, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    TLEndShaders();

    while (!TLWindowShouldClose())
    {
        double currentTime = glfwGetTime();
        deltaTime = currentTime - lastFrame;
        lastFrame = currentTime;

        TLBegin();

        camera.loadPerspective();

        TLCameraCallbacks();

        keyInput(deltaTime);

        renderer->Clear(false);

        // Draw whatever you want here in opengl context!
        glDrawArrays(GL_TRIANGLES, 0, 3);

        TLModelViewProjectionMatrix(camera);

        TLEnd();
    }

    TLTerminate(false);
    return 0;
}

void keyInput(double dtime) {

    if (Keyboard::key(GLFW_KEY_ESCAPE)) {
        TLSetWindowShouldClose(true);
    }

    if (Keyboard::key(GLFW_KEY_W)) {
        camera.UpdateCameraPosition(CameraDir::FORWARD, dtime);
    }
    if (Keyboard::key(GLFW_KEY_A)) {
        camera.UpdateCameraPosition(CameraDir::LEFT, dtime);
    }
    if (Keyboard::key(GLFW_KEY_S)) {
        camera.UpdateCameraPosition(CameraDir::BACKWARD, dtime);
    }
    if (Keyboard::key(GLFW_KEY_D)) {
        camera.UpdateCameraPosition(CameraDir::RIGHT, dtime);
    }
    if (Keyboard::key(GLFW_KEY_SPACE)) {
        camera.UpdateCameraPosition(CameraDir::UP, dtime);
    }
    if (Keyboard::key(GLFW_KEY_C)) {
        camera.UpdateCameraPosition(CameraDir::DOWN, dtime);
    }

}