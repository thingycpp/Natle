#include "TL.h"
using namespace tl;

GLFWwindow* tlwinstuff::win = NULL;

void tlwinstuff::CreateWindow(int Width, int Height, const std::string& Name, bool useVsync) {

	if (!glfwInit())
		return;

	win = glfwCreateWindow(Width, Height, Name.c_str(), nullptr, nullptr);
	if (!win) {

		glfwTerminate();
		return;

	}


	glfwMakeContextCurrent(win);
	glewInit();
	if (useVsync)
		glfwSwapInterval(1);

}


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

void Renderer::Clear(bool usingUI) const {

	int display_w, display_h;
	GLCall(glfwGetFramebufferSize(tlwinstuff::win, &display_w, &display_h));
	GLCall(glViewport(0, 0, display_w, display_h))

	if (usingUI) {
		GLCall(glClearColor(tl::NatleGUI::clear_color.x, tl::NatleGUI::clear_color.y, tl::NatleGUI::clear_color.z, tl::NatleGUI::clear_color.w));
	}

	GLCall(glClear(GL_COLOR_BUFFER_BIT));

}

void Renderer::Draw(unsigned int amount) const {



}
