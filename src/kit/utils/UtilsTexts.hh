#ifndef VITAMATERIALKIT_UTILSTEXTS_HH
#define VITAMATERIALKIT_UTILSTEXTS_HH

#include <string>

#include "../lib/unilib/unicode.h"
#include "../lib/unilib/utf8.h"
#include "../lib/unilib/utf16.h"

class UtilsTexts {
private:
    int i;
    std::u32string text32;
public:
    void utf16ToUtf8(uint16_t *src, uint8_t *dst);
    void utf8ToUtf16(uint8_t *src, uint16_t *dst);

    //transformation text
    std::string toUppercase(std::string text);
    std::string toLowercase(std::string text);
};


#endif //VITAMATERIALKIT_UTILSTEXTS_HH
