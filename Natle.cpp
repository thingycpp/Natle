#include "TLib/TL.h"

Renderer* renderer;
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main(void)
{

    TLCreateWindow(1280, 720, "Natle: Alpha 0.1 Windows Edition - TheRand()House", true);

    TLInitUI();

    TLKeyInput();

    TLBeginExampleShaders();



    TLEndShaders();

    /* Loop until the user closes the window */
    while (!TLWindowShouldClose())
    {
        TLBegin();

        
        renderer->Clear(true);
        //renderer->Draw(1);
        
        TLNatleGUI();
        TLRenderUI();

        TLEnd();
    }

    TLTerminate(true);
    return 0;
}