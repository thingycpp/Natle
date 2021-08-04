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

}

ShaderUtil shaderUtil;

void ShaderDef::BeginExShaders()
{
	shaderUtil.Load("vs.shader", "fs.shader");
}

void ShaderDef::BeginShaders(const std::string& vs, const std::string& fs)
{
	shaderUtil .Load(vs, fs);
}

void ShaderDef::EndShaders()
{
	shaderUtil.Use();
}


GLuint vbo;

void Renderer::DrawTri(glm::fvec2 v_1, glm::fvec2 v_2, glm::fvec2 v_3, int index) {

	float verticies[6] = {
		v_1.x, v_1.y,
		v_2.x, v_2.y,
		v_3.x, v_3.y
	};

	

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

	glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(index);

}

void Renderer::Clear(bool usingUI) const {

	if (usingUI) {
		GLCall(glClearColor(tl::NatleGUI::clear_color.x, tl::NatleGUI::clear_color.y, tl::NatleGUI::clear_color.z, tl::NatleGUI::clear_color.w));
	}

	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

}

void Renderer::Draw(unsigned int amount) const {

	glDrawArrays(GL_TRIANGLES, 0, 6*amount);

}
