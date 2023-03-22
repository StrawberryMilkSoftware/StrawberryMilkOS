#include "./smOS-kernelUtil/kernelUtil.h"


extern "C" void _start(BootInfo* bootInfo){
    
    KernelInfo kernelInfo = InitKernel(bootInfo);
    PageTableManager* pageTableManager = kernelInfo.pageTableManager;

    // Begin printing things here
    GlobalRenderer->Print("                 ___  ____");
    GlobalRenderer->Print(" ___ _ __ ___  / _ \\/ ___|");
    GlobalRenderer->Print("/ __| '_ ` _ \\| | | \\___ \\ ");
    GlobalRenderer->Print("\\__ \\ | | | | | |_| |___) |");
    GlobalRenderer->Print("|___/_| |_| |_|\\___/|____/ ");

    GlobalRenderer->Print("Welcome to smOS!");
    GlobalRenderer->Print("Version Discovery-d0.2 Build Edition C++");
    GlobalRenderer->Print("Copyright (c) 2023 Strawberry Milk Software.");
    GlobalRenderer->Print("--------------------------------------------");

    while (true){
        ProcessMousePacket();
    }

    while(true);
}