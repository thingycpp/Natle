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

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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

