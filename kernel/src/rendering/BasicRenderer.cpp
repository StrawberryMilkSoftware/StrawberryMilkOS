#include "BasicRenderer.h"

BasicRenderer* GlobalRenderer;

BasicRenderer::BasicRenderer(Framebuffer* targetFramebuffer, PSF1_FONT* psf1_Font)
{
    TargetFramebuffer = targetFramebuffer;
    PSF1_Font = psf1_Font;
    Color = 0xfff09ffe;
    CursorPosition = {0, 0};
}

void BasicRenderer::PutPix(uint32_t x, uint32_t y, uint32_t color){
    *(uint32_t*)((uint64_t)TargetFramebuffer->BaseAddress + (x * 4) + (y * TargetFramebuffer->PixelsPerScanLine * 4)) = color;
}

void BasicRenderer::ClearMouseCursor(uint8_t* mouseCursor, Point pos) {
    if (!MouseDrawn) return;
    
    int xMax = 16;
    int yMax = 16;
    int differenceX = TargetFramebuffer->Width - pos.x;
    int differenceY = TargetFramebuffer->Width - pos.y;

    if (differenceX < 16) xMax = differenceX;
    if (differenceY < 16) yMax = differenceY;

    for (int y = 0; y < yMax; y++) {
        for (int x = 0; x < xMax; x++) {
            int bit = (y * 16) + x;
            int byte = bit / 8;
            if ((mouseCursor[byte] & (0b10000000 >> (x % 8)))){
                if (GetPix(pos.x + x, pos.y + y) == MouseCursorBufferAfter[x+y * 16]){
                    PutPix(pos.x + x, pos.y + y, MouseCursorBuffer[x+y*16]);
                }
            }
        }
    }
}

uint32_t BasicRenderer::GetPix(uint32_t x, uint32_t y){
    return *(uint32_t*)((uint64_t)TargetFramebuffer->BaseAddress + (x * 4) + (y * TargetFramebuffer->PixelsPerScanLine * 4)); 

}

void BasicRenderer::DrawOverlayMouseCursor(uint8_t* mouseCursor, Point pos, uint32_t color){
    int xMax = 16;
    int yMax = 16;
    int differenceX = TargetFramebuffer->Width - pos.x;
    int differenceY = TargetFramebuffer->Width - pos.y;

    if (differenceX < 16) xMax = differenceX;
    if (differenceY < 16) yMax = differenceY;

    for (int y = 0; y < yMax; y++) {
        for (int x = 0; x < xMax; x++) {
            int bit = (y * 16) + x;
            int byte = bit / 8;
            if ((mouseCursor[byte] & (0b10000000 >> (x % 8)))){
                MouseCursorBuffer[x+y*16]=GetPix(pos.x+x, pos.y+y);
                PutPix(pos.x + x, pos.y + y, color);
                MouseCursorBufferAfter[x+y*16]=GetPix(pos.x+x, pos.y+y);
            }
        }
    }

    MouseDrawn = true;

}   

void BasicRenderer::Clear(){
    uint64_t fbBase = (uint64_t)TargetFramebuffer->BaseAddress;
    uint64_t bytesPerScanline = TargetFramebuffer->PixelsPerScanLine * 4;
    uint64_t fbHeight = TargetFramebuffer->Height;
    uint64_t fbSize = TargetFramebuffer->BufferSize;

    for (int verticalScanline = 0; verticalScanline < fbHeight; verticalScanline ++){
        uint64_t pixPtrBase = fbBase + (bytesPerScanline * verticalScanline);
        for (uint32_t* pixPtr = (uint32_t*)pixPtrBase; pixPtr < (uint32_t*)(pixPtrBase + bytesPerScanline); pixPtr ++){
            *pixPtr = ClearColor;
        }
    }
}

void BasicRenderer::ClearChar(){

    if (CursorPosition.x == 0){
        CursorPosition.x = TargetFramebuffer->Width;
        CursorPosition.y -= 16;
        if (CursorPosition.y < 0) CursorPosition.y = 0;
    }

    unsigned int xOff = CursorPosition.x;
    unsigned int yOff = CursorPosition.y;

    unsigned int* pixPtr = (unsigned int*)TargetFramebuffer->BaseAddress;
    for (unsigned long y = yOff; y < yOff + 16; y++){
        for (unsigned long x = xOff - 8; x < xOff; x++){
                    *(unsigned int*)(pixPtr + x + (y * TargetFramebuffer->PixelsPerScanLine)) = ClearColor;
        }
    }

    CursorPosition.x -= 8;

    if (CursorPosition.x < 0){
        CursorPosition.x = TargetFramebuffer->Width;
        CursorPosition.y -= 16;
        if (CursorPosition.y < 0) CursorPosition.y = 0;
    }

}

void BasicRenderer::Next(){
    CursorPosition.x = 10;
    CursorPosition.y += 16;
}

void BasicRenderer::Print(const char* str)
{
    
    char* chr = (char*)str;
    while(*chr != 0){
        PutChar(*chr, CursorPosition.x, CursorPosition.y);
        CursorPosition.x+=8;
        if(CursorPosition.x + 8 > TargetFramebuffer->Width)
        {
            CursorPosition.x = 0;
            CursorPosition.y += 16;
        }
        chr++;
    }
    Next();
}

void BasicRenderer::PrintNoIncPos(const char* str)
{
    
    char* chr = (char*)str;
    while(*chr != 0){
        PutChar(*chr, CursorPosition.x, CursorPosition.y);
        CursorPosition.x+=8;
        if(CursorPosition.x + 8 > TargetFramebuffer->Width)
        {
            CursorPosition.x = 0;
            CursorPosition.y += 16;
        }
        chr++;
    }
}

void BasicRenderer::PutChar(char chr, unsigned int xOff, unsigned int yOff)
{
    unsigned int* pixPtr = (unsigned int*)TargetFramebuffer->BaseAddress;
    char* fontPtr = (char*)PSF1_Font->glyphBuffer + (chr * PSF1_Font->psf1_Header->charsize);
    for (unsigned long y = yOff; y < yOff + 16; y++){
        for (unsigned long x = xOff; x < xOff+8; x++){
            if ((*fontPtr & (0b10000000 >> (x - xOff))) > 0){
                    *(unsigned int*)(pixPtr + x + (y * TargetFramebuffer->PixelsPerScanLine)) = Color;
                }

        }
        fontPtr++;
    }
}

void BasicRenderer::PutChar(char chr)
{
    PutChar(chr, CursorPosition.x, CursorPosition.y);
    CursorPosition.x += 8;
    if (CursorPosition.x + 8 > TargetFramebuffer->Width){
        CursorPosition.x = 0; 
        CursorPosition.y += 16;
    }
}