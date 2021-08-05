#include "TL.h"
using namespace tl;

GLFWwindow* tlwinstuff::win = NULL;
int tlwinstuff::width = 0;
int tlwinstuff::height = 0;

void tlwinstuff::CreateWindow(int Width, int Height, const std::string& Name, bool useVsync) {

	if (!glfwInit())
		return;

	win = glfwCreateWindow(Width, Height, Name.c_str(), nullptr, nullptr);
	if (!win) {

		glfwTerminate();
		return;

	}

	width = Width;
	height = Height;

	glfwMakeContextCurrent(win);
	glewInit();
	if (useVsync)
		glfwSwapInterval(1);

	glViewport(0, 0, Width, Height);

}

ShaderUtil shaderUtil;

void ShaderDef::BeginExShaders()
{
	shaderUtil.Load("vs.shader", "fs.shader");

	GLCall(glEnable(GL_DEPTH_TEST));

	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
}

void ShaderDef::MVPmatrices(Camera camera) {

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);
	model = glm::rotate(model, (float)glfwGetTime() * glm::radians(-55.0f), glm::vec3(0.5f, 0.5f, 0.5f));

	view = camera.GetViewMatrix();
	projection = glm::perspective(glm::radians(45.0f), (float)1280 / (float)720, 0.1f, 100.0f);

	shaderUtil.SetMat4("model", model);
	shaderUtil.SetMat4("view", view);
	shaderUtil.SetMat4("projection", projection);

}

void ShaderDef::BeginShaders(const std::string& vs, const std::string& fs)
{
	shaderUtil.Load(vs, fs);

	GLCall(glEnable(GL_DEPTH_TEST));

	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
}

void ShaderDef::EndShaders()
{
	shaderUtil.Use();
}


void Renderer::Clear(bool usingUI) const {

	if (usingUI) {
		GLCall(glClearColor(tl::NatleGUI::clear_color.x, tl::NatleGUI::clear_color.y, tl::NatleGUI::clear_color.z, tl::NatleGUI::clear_color.w));
	}

	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

}
