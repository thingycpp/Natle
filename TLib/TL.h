#ifndef TL_H_INCLUDED
#define TL_H_INCLUDED

/*
    READ:

        Your while loop should look a little something like if using NatleGUI
        
        Note

        while (!TLWindowShouldClose)
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
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main(void)
{

    TLCreateWindow(1280, 720, "TLib: Camera Example", true);

    TLBeginExampleShaders();

    TLEndShaders();

    while (!TLWindowShouldClose())
    {
        double currentTime = glfwGetTime();
        deltaTime = currentTime - lastFrame;
        lastFrame = currentTime;

        TLBegin();

        TLCameraCallbacks();

        keyInput(deltaTime);

        renderer->Clear(false);

        // Draw whatever you want here in opengl context!

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
*/

#include <iostream>
#include <fstream>
#include <string>
#include "libs/stb_image/stb_image.h"

#include "GUI.h"
#include "Mouse.h"
#include "Camera.h"
#include "Keyboard.h"
#include "ShaderUtil.h"


struct ShaderDef {
    static void BeginExShaders();
    static void MVPmatrices(Camera camera);
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

    glfwPollEvents();

}

inline void end() {
    
    glfwSwapBuffers(tlwinstuff::win);

}

#define ASSERT(x) if (!(x)) __debugbreak();
// GLCall because staying consistent with how I learned opengl
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

inline void GLClearError() {

    while (glGetError() != GL_NO_ERROR);

}

inline bool GLLogCall(const char* function, const char* file, int line) {

    while (GLenum error = glGetError()) {

        std::cout << "[OpenGL Error] (" << error << "): " << function << " " << file << ":" << line << std::endl;
        return false;

    }
    return true;

}

// Shader Macros

#define TLBeginExampleShaders() ShaderDef::BeginExShaders();
#define TLBeginShaders(vs, fs)  ShaderDef::BeginShaders(vs, fs);
#define TLEndShaders()          ShaderDef::EndShaders();

// Window Macros

#define TLCreateWindow(w, h, n, vs) tlwinstuff::CreateWindow(w, h, n, vs);

inline void TLSetWindowShouldClose(bool sosnt) {

    glfwSetWindowShouldClose(tlwinstuff::win, sosnt);

}

inline int TLWindowShouldClose() {
    
    //Not a macro but screw it
    return glfwWindowShouldClose(tlwinstuff::win);

}

// Callback Macros

inline void CamCallbacks() {

    glfwSetKeyCallback(tlwinstuff::win, Keyboard::keyCallback);

    glfwSetCursorPosCallback(tlwinstuff::win, Mouse::CursorPosCB);

    glfwSetMouseButtonCallback(tlwinstuff::win, Mouse::MouseButtonCB);

    glfwSetScrollCallback(tlwinstuff::win, Mouse::MouseWheelCB);

    // Extra bit placed here to make my life easier

    glfwSetInputMode(tlwinstuff::win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

}

#define TLCameraCallbacks() CamCallbacks();

// General Macros

#define TLBegin() begin();
#define TLEnd()   end();

#define TLTerminate(usingUI) if(usingUI){ TLCleanupUI(); } glfwTerminate();

// Stuff Macros

#define TLModelViewProjectionMatrix(camera) ShaderDef::MVPmatrices(camera);


class Renderer {
public:

    void Clear(bool usingUI) const;

private:

    Renderer() { }
    ~Renderer() { }
};

#endif
