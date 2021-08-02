#include "TLib/TL.h"

Renderer* renderer;


int main(void)
{

    TLCreateWindow(1280, 720, "Natle: Alpha 0.1 Windows Edition - TheRand()House", true);

    TLInitUI();

    TLBeginExampleShaders();

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    TLEndShaders();

    /* Loop until the user closes the window */
    while (!TLWindowShouldClose())
    {
        TLBegin();

        
        renderer->Clear(true);
        
        TLNatleGUI();
        TLRenderUI();

        TLEnd();
    }

    TLTerminate(true);
    return 0;
}