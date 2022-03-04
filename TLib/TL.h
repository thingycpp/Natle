#ifndef TL_H_INCLUDED
#define TL_H_INCLUDED

/*
    READ:

        Your while loop should look a little something like if using NatleGUI

        TLInitUI();
        while (!TLWindowShouldClose())
        {
             TLBegin();


            renderer->Clear(true);
            //Draw Under Here

            TLNatleGUI();
            TLRenderUI();

            TLEnd();
        }

        Dont forget to use TLTerminate(true);
*/

// ALSO DO NOT USE THE CAMERA STUFF WITH THE GUI, IT SCREWS EVERYTHING UP

/*

Example code:

    #include "TLib/TL.h"

    Renderer* renderer;


    int main(void)
    {

        TLCreateWindow(1280, 720, "TLib Example", true);


        TLBeginExampleShaders();

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        TLEndShaders();


        while (!TLWindowShouldClose())
        {

            TLBegin();


            renderer->Clear(false);


            TLEnd();

        }

        TLTerminate(false);
        return 0;
    }

*/

/*
Example code with camera:

#include "TLib/TL.h"

void keyInput(double dtime);

bool useUI = false;

Renderer* renderer;
Camera camera(glm::vec3(0.0f, 0.0f, 0.0f));

float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main()
{

	TLCreateWindow(1280, 720, "TLib: Camera Example", true);

	TLBeginExampleShaders();

	GLuint VAO;
	GLuint VBO;

	static float tri[] = {
		-1.0f, -1.0f, 5.0f,
		1.0f, -1.0f, 5.0f,
		0.0f,  1.0f, 5.0f
	};

	//TLMakeObj3D(tri, 50.0f);
	camera.Settings(1280, 720, ShaderDef::getShaders());

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), tri, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	TLEndShaders();

	while (!TLWindowShouldClose())
	{
		double currentTime = glfwGetTime();
		deltaTime = currentTime - lastFrame;
		lastFrame = currentTime;

		TLBegin();

		TLCameraCallbacks(camera);

		keyInput(deltaTime);

		renderer->Clear(false);
		camera.Update(glm::vec3(0.0f, 0.0f, 0.0f));

	   // Draw whatever you want here in opengl context!
		glDrawArrays(GL_TRIANGLES, 0, 3);

		TLEnd();
	}

	TLDeleteShaders();
	TLTerminate(false);
	return 0;
}

void keyInput(double dtime) {

	if (Keyboard::key(GLFW_KEY_ESCAPE)) {
		TLSetWindowShouldClose(true);
	}

}
*/

#include <iostream>
#include <fstream>
#include <string>

#include "GUI.h"
#include "Mouse.h"
#include "Camera.h"
#include "Shaders.h"
#include "Keyboard.h"


struct ShaderDef {
    static Shaders getShaders();
    static void BeginExShaders();
    static void BeginShaders(const std::string& vs, const std::string& fs);
    static void EndShaders();
};

struct tlwinstuff {
    static GLFWwindow* win;
    static int width;
    static int height;
    static void CreateWindow(int Width, int Height, const std::string& Name, bool useVsync);
};

inline void begin() {

    glViewport(0, 0, tlwinstuff::width, tlwinstuff::height);
	glfwSetKeyCallback(tlwinstuff::win, Keyboard::keyCallback);
	glfwSetCursorPosCallback(tlwinstuff::win, Mouse::CursorPosCB);
	glfwSetMouseButtonCallback(tlwinstuff::win, Mouse::MouseButtonCB);
	glfwSetScrollCallback(tlwinstuff::win, Mouse::MouseWheelCB);
    glfwSetInputMode(tlwinstuff::win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwPollEvents();
    glLoadIdentity();

}

inline void end() {
    
    glfwSwapBuffers(tlwinstuff::win);

}

// Shader Macros

#define TLBeginExampleShaders() ShaderDef::BeginExShaders();
#define TLBeginShaders(vs, fs)  ShaderDef::BeginShaders(vs, fs);
#define TLEndShaders()          ShaderDef::EndShaders();
#define TLDeleteShaders()       ShaderDef::getShaders().Delete();


// Window Macros

#define TLCreateWindow(w, h, n, vs) tlwinstuff::CreateWindow(w, h, n, vs);

inline void TLSetWindowShouldClose(bool sosnt) {

    glfwSetWindowShouldClose(tlwinstuff::win, sosnt);

}

inline int TLWindowShouldClose() {
    
    //Not a macro but screw it
    return glfwWindowShouldClose(tlwinstuff::win);

}

// General Macros

#define TLBegin() begin();
#define TLEnd()   end();

#define TLTerminate(usingUI) if(usingUI){ TLCleanupUI(); } glfwTerminate();

// Rendering Shinanigons

class Renderer {
public:

    void AddToDrawCall(float vertices[]);
    void Clear(bool usingUI);
    void Render();

private:

    Renderer() { }
    ~Renderer() { }
};

#endif
