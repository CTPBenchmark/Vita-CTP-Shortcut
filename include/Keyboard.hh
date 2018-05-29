//
// Created by Applelo
//

#ifndef KEYBOARD_HH
#define KEYBOARD_HH

#include "Utils.h"


class Keyboard {

private:
    SceUInt32 _length;
    SceUInt32 _type;
    SceUInt32 _mode;
    SceUInt32 _option;
    bool _keyboardStarted;

public:
    Keyboard();
    Keyboard(int length, int type);
    Keyboard(int length, int type, int option, int mode);
    virtual ~Keyboard();
    void display(char *title, char *initial_text);
    void oslOskGetText(char *text);
    void utf16_to_utf8(uint16_t *src, uint8_t *dst);
    void utf8_to_utf16(uint8_t *src, uint16_t *dst);


};


#endif //KEYBOARD_HH
