#include "keyboard.h"

    bool isLeftShiftPressed;
    bool isRightShiftPressed;

void HandleKeyboard(uint8_t scancode){

    switch (scancode){
        case LeftShift:
            isLeftShiftPressed = true;
            return;
        case LeftShift + 0x80:
            isLeftShiftPressed = false;
            return;
        case RightShift:
            isRightShiftPressed = true;
            return;
        case RightShift + 0x80:
            isRightShiftPressed = false;
            return;
        case Enter:
            GlobalRenderer->Next();
            return;
        case Spacebar:
            GlobalRenderer->PutChar(' ');
            return;
        case BackSpace:
            GlobalRenderer->ClearChar();
            return;
        case LeftArrow:
            GlobalRenderer->CursorPosition.x -= 8;
            return;
        case RightArrow:
            GlobalRenderer->CursorPosition.x += 8;
            return;
        case UpArrow:
            GlobalRenderer->CursorPosition.y -= 16;
            return;
        case DownArrow:
            GlobalRenderer->CursorPosition.y += 16;
            return;
    }

    char ascii = QWERTYKeyboard::Translate(scancode, isLeftShiftPressed | isRightShiftPressed);

    if (ascii != 0){
        GlobalRenderer->PutChar(ascii);
    }

}