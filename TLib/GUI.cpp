#include "GUI.hpp"
using namespace tl;

//Class Variables

bool NatleGUI::showEntSettings = true;
bool NatleGUI::showDesc = true;
ImVec4 NatleGUI::clear_color = ImVec4(0.45f, 0.65f, 0.70f, 1.00f);
const char* NatleGUI::NatleDesc = "Natle is an app made in glfw and glew using ImGui. The name is complete random and has no significance at all, I just like it... I created Natle to show how different window settings could effect the window and how a certain hue looks or how ImGui can be used simply to speed up the development of whatever you're working on. All in all I hope that Natle can help both me and whoever ends up reading this in the future.";
float NatleGUI::fontSize = 18.0f;

void NatleGUI::initUI(GLFWwindow* p_window) {

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui_ImplGlfwGL3_Init(p_window, true);

    io.FontDefault = io.Fonts->AddFontFromFileTTF("Assets/Fonts/OpenSans-Regular.ttf", fontSize);

    ImGui::StyleColorsDark();

    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 0.0f;
    style.Colors[ImGuiCol_WindowBg].w = 1.0f;

    TLDarkTheme();

}

void NatleGUI::UI() {

    ImGui_ImplGlfwGL3_NewFrame();

    {

        ImGui::Begin("Window Settings", nullptr, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
        if (ImGui::BeginMenuBar()) {

            if (ImGui::BeginMenu("CLOSE")) {

                if (showEntSettings)
                    if (ImGui::MenuItem("Entity Settings", "Ctrl+I")) { showEntSettings = false; }
                if (showDesc)
                    if (ImGui::MenuItem("Why Natle", "Ctrl+O")) { showDesc = false; }

                ImGui::EndMenu();
            }

            if (!showEntSettings || !showDesc) {

                if (ImGui::BeginMenu("RE-OPEN")) {

                    if (!showEntSettings)
                        if (ImGui::MenuItem("Entity Settings", "Ctrl+K")) { showEntSettings = true; }
                    if (!showDesc)
                        if (ImGui::MenuItem("What is Natle?", "Ctrl+L")) { showDesc = true; }

                    ImGui::EndMenu();

                }

            }

            ImGui::EndMenuBar();
        }


        ImGui::SetWindowPos(ImVec2(0, 0), true);
        ImGui::SetWindowSize(ImVec2(360, 720), true);

        ImGui::ColorEdit3("Background Color", (float*)&clear_color);


        ImGui::Text("Natle's average ms, %.3f, and framerate, %.1f", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

        if (showEntSettings) {

            ImGui::Begin("Entity Settings", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
            ImGui::SetWindowPos(ImVec2(920, 0), true);
            ImGui::SetWindowSize(ImVec2(360, 720), true);
            //Under here would go all the object position color ext.

            ImGui::Text("I can't seem to find any entitys....");


            ImGui::End();

        }

        if (showDesc) {
            ImGui::Begin("Why Natle", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
            ImGui::SetWindowPos(ImVec2(360, 360), true);
            ImGui::SetWindowSize(ImVec2(560, 360), true);

            ImGui::TextWrapped(NatleDesc);

            ImGui::End();
        }

        ImGui::End();

    }

}
