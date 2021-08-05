#include "TLib/TL.h"

Renderer* renderer;


int main(void)
{

    TLCreateWindow(1280, 720, "Natle: Alpha 0.1 Windows Edition - TheRand()House", true);

    TLInitUI();

    TLBeginExampleShaders();



    TLEndShaders();


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