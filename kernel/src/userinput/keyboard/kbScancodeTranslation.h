#pragma once
#include <stdint.h>

#pragma once
#include <stdint.h>

namespace QWERTYKeyboard{

    #define LeftShift 0x2A
    #define RightShift 0x36
    #define Enter 0x1C
    #define BackSpace 0x0E
    #define Spacebar 0x39
    #define LeftArrow 0x4B
    #define RightArrow 0x4D
    #define UpArrow 0x48
    #define DownArrow 0x50

    extern const char ASCIITable[];
    char Translate(uint8_t scancode, bool uppercase);
}