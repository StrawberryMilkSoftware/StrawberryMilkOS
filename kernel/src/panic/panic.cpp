#include "panic.h"
#include "../rendering/BasicRenderer.h"

void Panic(const char* panicMessage, const char* errorCode){
    GlobalRenderer->ClearColor = 0x00fe6262;
    GlobalRenderer->Clear();

    GlobalRenderer->CursorPosition = {10, 10};
    GlobalRenderer->Color = 0xfcf1fe;

    GlobalRenderer->Print("uhh..");
    GlobalRenderer->Print("looks like the computer is panicking...");
    GlobalRenderer->PrintNoIncPos("heres what it said went wrong: ");
    GlobalRenderer->Print(panicMessage);
    GlobalRenderer->PrintNoIncPos("here's a more complex way to say it: ");
    GlobalRenderer->Print(errorCode);

}   