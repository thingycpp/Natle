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


#include <iostream>
#include <fstream>
#include <string>
#include "libs/stb_image/stb_image.h"

#include "GUI.h"
#include "Camera.h"
#include "Keyboard.h"
#include "ShaderUtil.h"


struct ShaderDef {
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

inline int TLWindowShouldClose() {
    
    //Not a macro but screw it
    return glfwWindowShouldClose(tlwinstuff::win);

}

// Callback Macros

#define TLKeyInput() glfwSetKeyCallback(tlwinstuff::win, Keyboard::key_callback);

// General Macros

#define TLBegin() begin();
#define TLEnd()   end();

#define TLTerminate(usingUI) if(usingUI){ TLCleanupUI(); } glfwTerminate();


class Renderer {
private:


public:

    // The index can't be an index you've already used before, also make sure this ends up right below TLBeginExampleShaders(), or TLBeginShaders(vs, fs)
    void DrawTri(glm::fvec2 v_1, glm::fvec2 v_2, glm::fvec2 v_3, int index);

    void Clear(bool usingUI) const;
    void Draw(unsigned int amount) const;

private:

    Renderer() { }
    ~Renderer() { }
};

#endif
