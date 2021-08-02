#ifndef TL_H_INCLUDED
#define TL_H_INCLUDED

/*
    READ:

        Your while loop should look a little something like if using NatleGUI

        while (!glfwWindowShouldClose(window))
        {
            glfwPollEvents();


            renderer->Clear(window, true);

            TLNatleGUI();
            TLRenderUI();

            glfwSwapBuffers(window);
        }

        Dont forget to use TLTerminate(true);
*/

/*

Example code:

    #include "Tlib/TL.h"

    Renderer* renderer;

    int main(void)
    {
        GLFWwindow* window;


        if (!glfwInit())
            return -1;

        window = glfwCreateWindow(1280, 720, "TLib Example Window", NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            return -1;
        }

        glfwMakeContextCurrent(window);
        GLCall(glewInit());
    

        TLBeginExampleShaders();

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        TLEndShaders();

        while (!glfwWindowShouldClose(window))
        {
            glfwPollEvents();


            renderer->Clear(window, false);


            glfwSwapBuffers(window);
        }

        TLEnd(false);
        return 0;
    }

*/


#include <iostream>
#include <fstream>
#include <string>
#include "libs/glew/include/GL/glew.h"
#include "libs/glfw/include/GLFW/glfw3.h"
#include "libs/imgui/imgui.h"
#include "libs/imgui/imgui_impl_glfw_gl3.h"
#include "libs/stb_image/stb_image.h"

#include "GUI.hpp"
#include "tlShader.hpp"


struct ShaderDef {
    static void BeginExShaders();
    static void BeginShaders(const std::string& vs, const std::string& fs);
    static void EndShaders();
};


inline void TLDark() {

    auto& colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.105f, 0.11f, 1.0f };

    // Headers
    colors[ImGuiCol_Header] = ImVec4{ 0.35f, 0.355f, 0.351f, 1.0f };
    colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.48f, 0.485f, 0.48f, 1.0f };
    colors[ImGuiCol_HeaderActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

    // Buttons
    colors[ImGuiCol_Button] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
    colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
    colors[ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

    // Frame BG
    colors[ImGuiCol_FrameBg] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
    colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
    colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

    // Title
    colors[ImGuiCol_TitleBg] = ImVec4{ 0.19f, 0.1905f, 0.191f, 1.0f };
    colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.14f, 0.1405f, 0.141f, 1.0f };
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

}


inline void TLLight() {

    auto& colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_WindowBg] = ImVec4{ 0.7f, 0.705f, 0.71f, 1.0f };

    // Headers
    colors[ImGuiCol_Header] = ImVec4{ 0.8f, 0.805f, 0.81f, 1.0f };
    colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.9f, 0.905f, 0.91f, 1.0f };
    colors[ImGuiCol_HeaderActive] = ImVec4{ 0.75f, 0.7505f, 0.751f, 7.0f };

    // Buttons
    colors[ImGuiCol_Button] = ImVec4{ 0.8f, 0.805f, 0.81f, 1.0f };
    colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.9f, 0.905f, 0.91f, 1.0f };
    colors[ImGuiCol_ButtonActive] = ImVec4{ 0.75f, 0.7505f, 0.751f, 1.0f };

    // Frame BG
    colors[ImGuiCol_FrameBg] = ImVec4{ 0.8f, 0.805f, 0.81f, 1.0f };
    colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.9f, 0.905f, 0.91f, 1.0f };
    colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.75f, 0.7505f, 0.751f, 1.0f };

    // Title
    colors[ImGuiCol_TitleBg] = ImVec4{ 0.78f, 0.7805f, 0.781f, 1.0f };
    colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.75f, 0.7505f, 0.751f, 1.0f };
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.75f, 0.7505f, 0.751f, 1.0f };

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

// UI Macros

#define TLDarkTheme()      TLDark();
#define TLLightTheme()     TLLight();
#define TLNatleGUI()       tl::NatleGUI::UI();
#define TLInitUI(p_window) tl::NatleGUI::initUI(p_window);
#define TLRenderUI()       ImGui::Render(); ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
#define TLCleanupUI()      ImGui::DestroyContext(); ImGui_ImplGlfwGL3_Shutdown();

// Shader Macros

#define TLBeginExampleShaders() ShaderDef::BeginExShaders();
#define TLBeginShaders(vs, fs)  ShaderDef::BeginShaders(vs, fs);
#define TLEndShaders()          ShaderDef::EndShaders();

// General Macros

#define TLTerminate(usingUI) if(usingUI){ TLCleanupUI(); } glfwTerminate();

struct Renderer {      
   void Clear(GLFWwindow* p_window, bool usingUI) const;
   void Draw(unsigned int p_amount) const;
};

#endif
