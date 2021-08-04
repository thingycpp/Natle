#include "TLib/TL.h"

Renderer* renderer;


int main(void)
{

    TLCreateWindow(1280, 720, "TLib Example", true);

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