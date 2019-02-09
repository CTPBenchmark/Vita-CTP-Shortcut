#include "UtilsTexts.hh"

using namespace ufal::unilib;


void UtilsTexts::utf16ToUtf8(uint16_t *src, uint8_t *dst) {
    for (i = 0; src[i]; i++) {
        if ((src[i] & 0xFF80) == 0) {
            *(dst++) = (uint8_t) (src[i] & 0xFF);
        } else if((src[i] & 0xF800) == 0) {
            *(dst++) = (uint8_t) (((src[i] >> 6) & 0xFF) | 0xC0);
            *(dst++) = (uint8_t) ((src[i] & 0x3F) | 0x80);
        } else if((src[i] & 0xFC00) == 0xD800 && (src[i + 1] & 0xFC00) == 0xDC00) {
            *(dst++) = (uint8_t) ((((src[i] + 64) >> 8) & 0x3) | 0xF0);
            *(dst++) = (uint8_t) ((((src[i] >> 2) + 16) & 0x3F) | 0x80);
            *(dst++) = (uint8_t) (((src[i] >> 4) & 0x30) | 0x80 | ((src[i + 1] << 2) & 0xF));
            *(dst++) = (uint8_t) ((src[i + 1] & 0x3F) | 0x80);
            i += 1;
        } else {
            *(dst++) = (uint8_t) (((src[i] >> 12) & 0xF) | 0xE0);
            *(dst++) = (uint8_t) (((src[i] >> 6) & 0x3F) | 0x80);
            *(dst++) = (uint8_t) ((src[i] & 0x3F) | 0x80);
        }
    }

    *dst = '\0';
}

void UtilsTexts::utf8ToUtf16(uint8_t *src, uint16_t *dst) {
    for (i = 0; src[i];) {
        if ((src[i] & 0xE0) == 0xE0) {
            *(dst++) = (uint16_t) (((src[i] & 0x0F) << 12) | ((src[i + 1] & 0x3F) << 6) | (src[i + 2] & 0x3F));
            i += 3;
        } else if ((src[i] & 0xC0) == 0xC0) {
            *(dst++) = (uint16_t) (((src[i] & 0x1F) << 6) | (src[i + 1] & 0x3F));
            i += 2;
        } else {
            *(dst++) = src[i];
            i += 1;
        }
    }

    *dst = '\0';
}


//set text to uppercase
std::string UtilsTexts::toUppercase(std::string text) {

    utf8::decode(text, text32);

    for (auto&& chr :  text32) chr = unicode::uppercase(chr);

    utf8::encode(text32, text);

    return text;
}

//set text to lowercase
std::string UtilsTexts::toLowercase(std::string text) {

    utf8::decode(text, text32);

    for (auto&& chr :  text32) chr = unicode::lowercase(chr);

    utf8::encode(text32, text);

    return text;
}
