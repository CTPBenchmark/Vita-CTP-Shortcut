/*
 **
 ** Made by Applelo
 ** Inspired by LPP Vita Code by Rinnegatamante & Nanni
 **
 */



#include "../include/Keyboard.hh"



Keyboard::Keyboard() {
    _keyboardStarted = false;
    _length = SCE_IME_DIALOG_MAX_TEXT_LENGTH;
    _type = SCE_IME_TYPE_BASIC_LATIN;
    _mode = SCE_IME_DIALOG_TEXTBOX_MODE_DEFAULT;
    _option = 0;
}

Keyboard::Keyboard(int length, int type) {
    _keyboardStarted = false;
    _length = length;
    _type = type;
    _mode = SCE_IME_DIALOG_TEXTBOX_MODE_DEFAULT;
    _option = 0;
}

Keyboard::Keyboard(int length, int type, int option, int mode) {
    _keyboardStarted = false;
    _length = length;
    _type = type;
    _mode = mode;
    _option = option;
}

Keyboard::~Keyboard() {
}


void Keyboard::display(char *title, char *initial_text) {
    utf8_to_utf16((uint8_t *)title, ime_title_utf16);
    utf8_to_utf16((uint8_t *)initial_text, ime_initial_text_utf16);

    SceImeDialogParam param;
    sceImeDialogParamInit(&param);

    param.sdkVersion = 0x03150021,
    param.supportedLanguages = 0x0001FFFF;
    param.languagesForced = SCE_TRUE;
    param.type = SCE_IME_TYPE_BASIC_LATIN;
    param.title = ime_title_utf16;
    param.maxTextLength = 3;
    param.initialText = ime_initial_text_utf16;
    param.inputTextBuffer = ime_input_text_utf16;

    sceImeDialogInit(&param);
    return ;
}



void Keyboard::utf16_to_utf8(uint16_t *src, uint8_t *dst) {
    int i;
    for (i = 0; src[i]; i++) {
        if ((src[i] & 0xFF80) == 0) {
            *(dst++) = src[i] & 0xFF;
        } else if((src[i] & 0xF800) == 0) {
            *(dst++) = ((src[i] >> 6) & 0xFF) | 0xC0;
            *(dst++) = (src[i] & 0x3F) | 0x80;
        } else if((src[i] & 0xFC00) == 0xD800 && (src[i + 1] & 0xFC00) == 0xDC00) {
            *(dst++) = (((src[i] + 64) >> 8) & 0x3) | 0xF0;
            *(dst++) = (((src[i] >> 2) + 16) & 0x3F) | 0x80;
            *(dst++) = ((src[i] >> 4) & 0x30) | 0x80 | ((src[i + 1] << 2) & 0xF);
            *(dst++) = (src[i + 1] & 0x3F) | 0x80;
            i += 1;
        } else {
            *(dst++) = ((src[i] >> 12) & 0xF) | 0xE0;
            *(dst++) = ((src[i] >> 6) & 0x3F) | 0x80;
            *(dst++) = (src[i] & 0x3F) | 0x80;
        }
    }

    *dst = '\0';
}

void Keyboard::utf8_to_utf16(uint8_t *src, uint16_t *dst) {
    int i;
    for (i = 0; src[i];) {
        if ((src[i] & 0xE0) == 0xE0) {
            *(dst++) = ((src[i] & 0x0F) << 12) | ((src[i + 1] & 0x3F) << 6) | (src[i + 2] & 0x3F);
            i += 3;
        } else if ((src[i] & 0xC0) == 0xC0) {
            *(dst++) = ((src[i] & 0x1F) << 6) | (src[i + 1] & 0x3F);
            i += 2;
        } else {
            *(dst++) = src[i];
            i += 1;
        }
    }

    *dst = '\0';
}

void Keyboard::oslOskGetText(char *text){
    // Convert UTF16 to UTF8
    utf16_to_utf8(ime_input_text_utf16, ime_input_text_utf8);
    strcpy(text,(char*)ime_input_text_utf8);
}






