#include "TLib/TL.h"

void keyInput(double dtime);

Renderer* renderer;
Camera camera(glm::vec3(0.0f, 0.0f, -3.0f));

float deltaTime = 0.0f;
float lastFrame = 0.0f;
bool playing = false;

int main() {

	TLCreateWindow(1280, 720, "Natle", false);

	TLBeginExampleShaders();

    float vertices[] = {

        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f

    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(VAO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

	TLEndShaders();

  //TLInitUI();

	while (!TLWindowShouldClose())
	{
		double currentTime = glfwGetTime();
		deltaTime = currentTime - lastFrame;
		lastFrame = currentTime;

		camera.UpdateCameraMatrices(ShaderDef::getShaders());

		TLBegin();

		keyInput(deltaTime);

		renderer->Clear(true);

    //TLNatleGUI();
    //TLRenderUI();

        glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		TLEnd();
	}

	TLDeleteShaders();
	TLTerminate(false);
	return 0;
}

void keyInput(double dtime) {

    if (Keyboard::keyPressed(GLFW_KEY_P)) {
        playing = true;
    }

    if (Keyboard::keyPressed(GLFW_KEY_O)) {
        playing = false;
    }

    if (playing) {

        if (Keyboard::keyDown(GLFW_KEY_ESCAPE)) {
            TLSetWindowShouldClose(true);
        }

        if (Keyboard::keyDown(GLFW_KEY_W))
        {
            camera.UpdateCameraPos(CameraDirection::FORWARD, dtime);
        }
        if (Keyboard::keyDown(GLFW_KEY_A))
        {
            camera.UpdateCameraPos(CameraDirection::LEFT, dtime);
        }
        if (Keyboard::keyDown(GLFW_KEY_S))
        {
            camera.UpdateCameraPos(CameraDirection::BACKWARD, dtime);
        }
        if (Keyboard::keyDown(GLFW_KEY_D))
        {
            camera.UpdateCameraPos(CameraDirection::RIGHT, dtime);
        }
        if (Keyboard::keyDown(GLFW_KEY_SPACE))
        {
            camera.UpdateCameraPos(CameraDirection::UP, dtime);
        }
        if (Keyboard::keyDown(GLFW_KEY_C))
        {
            camera.UpdateCameraPos(CameraDirection::DOWN, dtime);
        }

        double dx = Mouse::GetDX(), dy = Mouse::GetDY();
        if (dx != 0 || dy != 0) {
            camera.UpdateCameraDirection(dx, dy);
        }
    }
}
