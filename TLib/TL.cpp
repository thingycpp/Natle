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
    
	glEnable(GL_DEPTH_TEST);
    
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
    
}

Shaders s;


void ShaderDef::BeginExShaders()
{
	s.Load("TLib/vs.shader", "TLib/fs.shader");
}

void ShaderDef::BeginShaders(const std::string& vs, const std::string& fs)
{
	s.Load(vs, fs);
}

void ShaderDef::EndShaders()
{
	s.Use();
}

Shaders ShaderDef::getShaders()
{
	return s;
}

void Renderer::AddToDrawCall(float vertices[]) {
	
}

void Renderer::Clear(bool usingUI) {
    
	if (usingUI) {
		glClearColor(tl::NatleGUI::clear_color.x, tl::NatleGUI::clear_color.y, tl::NatleGUI::clear_color.z, tl::NatleGUI::clear_color.w);
	}
    
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
    
}

void Renderer::Render() {

}