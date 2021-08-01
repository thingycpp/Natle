#include "Tlib/TL.hpp"

Renderer* renderer;

int main(void)
{
    /* Create a windowed mode window and its OpenGL context */
    
    GLFWwindow* win;

    if (!glfwInit())
        return -1;

    win = glfwCreateWindow(1280, 720, "Natle: Alpha 0.1 Windows Edition - TheRand()House", nullptr, nullptr);
    if (!win) {

        glfwTerminate();
        return -1;

    }


    glfwMakeContextCurrent(win);
    GLCall(glewInit());
    TLInitUI(win);

    TLBeginExampleShaders();

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    TLEndShaders();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(win))
    {
        glfwPollEvents();

        
        renderer->Clear(win, true);
        
        TLNatleGUI();
        TLRenderUI();

        glfwSwapBuffers(win);
    }

    TLTerminate(true);
    return 0;
}