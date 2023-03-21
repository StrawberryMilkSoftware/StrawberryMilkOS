#pragma once
#include "../numbers/math.h"
#include "Framebuffer.h"
#include "psf1-font.h" 
#include <stdint.h>

class BasicRenderer{
    public:
    BasicRenderer(Framebuffer* targetFramebuffer, PSF1_FONT* psf1_Font);
    Point CursorPosition;
    Framebuffer* TargetFramebuffer;
    PSF1_FONT* PSF1_Font;
    unsigned int Color;
    unsigned int ClearColor;
    void Print(const char* str);
    void PrintNoIncPos(const char* str);
    void PutChar(char chr, unsigned int xOff, unsigned int yOff);
    void PutChar(char chr);
    void ClearChar();
    void Clear();
    void Next();
};

extern BasicRenderer* GlobalRenderer;