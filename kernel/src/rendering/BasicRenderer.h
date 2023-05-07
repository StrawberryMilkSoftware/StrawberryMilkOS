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
    uint32_t MouseCursorBuffer[16 * 16];
    uint32_t MouseCursorBufferAfter[16 * 16];
    unsigned int Color;
    unsigned int ClearColor;
    void Print(const char* str);
    void PrintNoIncPos(const char* str);
    void PutChar(char chr, unsigned int xOff, unsigned int yOff);
    void PutChar(char chr);
    void PutPix(uint32_t x, uint32_t y, uint32_t color);
    uint32_t GetPix(uint32_t x, uint32_t y);
    void ClearChar();
    void Clear();
    void Next();
    void DrawOverlayMouseCursor(uint8_t* mouseCursor, Point pos, uint32_t color);
    void ClearMouseCursor(uint8_t* mouseCursor, Point pos);
    bool MouseDrawn;
};

extern BasicRenderer* GlobalRenderer;