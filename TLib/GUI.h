#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED

#include "libs/glew/include/GL/glew.h"
#include "libs/glfw/include/GLFW/glfw3.h"
#include "libs/imgui/imgui.h"
#include "libs/imgui/imgui_impl_glfw_gl3.h"

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

#define TLDarkTheme()      TLDark();
#define TLLightTheme()     TLLight();
#define TLNatleGUI()       tl::NatleGUI::UI();
#define TLInitUI()         tl::NatleGUI::initUI(tlwinstuff::win);
#define TLRenderUI()       ImGui::Render(); ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
#define TLCleanupUI()      ImGui::DestroyContext(); ImGui_ImplGlfwGL3_Shutdown();


namespace tl {

	// Natle's GUI, of course updated as it went along
	class NatleGUI {

	public:

		static void initUI(GLFWwindow* p_window);

		static void UI();

		static bool showEntSettings;
		static bool showDesc;
		static ImVec4 clear_color;

		static float fontSize;

		static const char* NatleDesc;

	private:
		NatleGUI() {}
		~NatleGUI() {}

	};

}

#endif

