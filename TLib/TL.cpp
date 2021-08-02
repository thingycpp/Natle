#include "TL.h"
using namespace tl;

Shader shader;

void ShaderDef::BeginExShaders()
{
	shader.Load("vs.shader", "fs.shader");
}

void ShaderDef::BeginShaders(const std::string& vs, const std::string& fs)
{
	shader.Load(vs, fs);
}

void ShaderDef::EndShaders()
{
	shader.Use();
}

void Renderer::Clear(GLFWwindow* p_window, bool usingUI) const {

	int display_w, display_h;
	GLCall(glfwGetFramebufferSize(p_window, &display_w, &display_h));
	GLCall(glViewport(0, 0, display_w, display_h))

	if (usingUI) {
		GLCall(glClearColor(tl::NatleGUI::clear_color.x, tl::NatleGUI::clear_color.y, tl::NatleGUI::clear_color.z, tl::NatleGUI::clear_color.w));
	}

	GLCall(glClear(GL_COLOR_BUFFER_BIT));

}

void Renderer::Draw(unsigned int amount) const {



}
