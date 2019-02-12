#include "UiTexts.hpp"

using namespace ufal::unilib;

UiTexts::UiTexts() {
    family = "Roboto";
}

UiTexts::UiTexts(UiTheme *theme) {
    this->theme = theme;
    this->family = "Roboto";
}

UiTexts::UiTexts(std::string family) {
    this->family = std::move(family);
}

UiTexts::UiTexts(std::string family, UiTheme *theme) {
    this->theme = theme;
    this->family = std::move(family);
}

UiTexts::~UiTexts() {
    this->cleanFonts();
}

void UiTexts::drawFinal(int x, int y, TextStyle textStyle, unsigned int color, bool italic, std::string text) {
    this->calcTextStyleData(textStyle, italic);
    this->loadFont(textStyleData.type, textStyleData.size);

    vita2d_font_draw_text(fonts[keyFont], x, (int) floor(y + textStyleData.size - textStyleData.offset), color, textStyleData.size, textStyleData.uppercase ? this->toUppercase(text).c_str() : text.c_str());
}

void UiTexts::drawFinal(int x, int y, TextStyleData _textStyleData, unsigned int color, std::string text) {
    this->loadFont(_textStyleData.type, _textStyleData.size);

    vita2d_font_draw_text(fonts[keyFont], x, (int) floor(y + _textStyleData.size - _textStyleData.offset), color, _textStyleData.size, _textStyleData.uppercase ? this->toUppercase(text).c_str() : text.c_str());
}

//Draw with Material Style
void UiTexts::draw(int x, int y, TextStyle textStyle, std::string text) {
    this->drawFinal(x, y, textStyle, TEXTS_DEFAULT_FONT_COLOR, false, std::move(text));
}

void UiTexts::draw(int x, int y, TextStyle textStyle, unsigned int color, std::string text) {
    this->drawFinal(x, y, textStyle, color, false, std::move(text));
}

void UiTexts::draw(int x, int y, TextStyle textStyle, TypeTheme textThemeColor, std::string text) {
    this->drawFinal(x, y, textStyle, textThemeColor == THEME_PRIMARY ? theme->getPrimaryRGBA().text : theme->getSecondaryRGBA().text, false, std::move(text));
}


void UiTexts::draw(int x, int y, TextStyle textStyle, unsigned int color, bool italic, std::string text) {
    this->drawFinal(x, y, textStyle, color, italic, std::move(text));
}

void UiTexts::draw(int x, int y, TextStyle textStyle, TypeTheme textThemeColor, bool italic, std::string text) {
    this->drawFinal(x, y, textStyle, textThemeColor == THEME_PRIMARY ? theme->getPrimaryRGBA().text : theme->getSecondaryRGBA().text, italic, std::move(text));
}

void UiTexts::drawF(int x, int y, TextStyle textStyle, unsigned int color, bool italic, const char *text, ...) {
    char buf[1024];
    va_list argPtr;

    va_start(argPtr, text);
    vsnprintf(buf, sizeof(buf), text, argPtr);
    va_end(argPtr);

    this->drawFinal(x, y, textStyle, color, italic, buf);
}

void UiTexts::drawF(int x, int y, TextStyle textStyle, TypeTheme textThemeColor, bool italic, const char *text, ...) {
    char buf[1024];
    va_list argPtr;

    va_start(argPtr, text);
    vsnprintf(buf, sizeof(buf), text, argPtr);
    va_end(argPtr);

    this->drawFinal(x, y, textStyle, textThemeColor == THEME_PRIMARY ? theme->getPrimaryRGBA().text : theme->getSecondaryRGBA().text, italic, buf);
}


//Draw with your style
void UiTexts::draw(int x, int y, TextStyleData _textStyleData, std::string text) {
    this->drawFinal(x, y, std::move(_textStyleData), TEXTS_DEFAULT_FONT_COLOR, std::move(text));
}

void UiTexts::draw(int x, int y, TextStyleData _textStyleData, unsigned int color, std::string text) {
    this->drawFinal(x, y, std::move(_textStyleData), color, std::move(text));
}

void UiTexts::drawF(int x, int y, TextStyleData _textStyleData, unsigned int color, const char *text, ...) {
    char buf[1024];
    va_list argPtr;

    va_start(argPtr, text);
    vsnprintf(buf, sizeof(buf), text, argPtr);
    va_end(argPtr);

    this->drawFinal(x, y, std::move(_textStyleData), color, buf);
}

void UiTexts::drawF(int x, int y, TextStyleData _textStyleData, TypeTheme typeTheme, const char *text, ...) {
    char buf[1024];
    va_list argPtr;

    va_start(argPtr, text);
    vsnprintf(buf, sizeof(buf), text, argPtr);
    va_end(argPtr);

    this->drawFinal(x, y, std::move(_textStyleData), typeTheme == THEME_PRIMARY ? this->theme->getPrimaryRGBA().text : this->theme->getSecondaryRGBA().text, buf);
}


//utils
TextData UiTexts::getTextData(std::string text, TextStyle textStyle, bool italic) {
    this->calcTextData(std::move(text), textStyle, italic);
    return textData;
}


//private

void UiTexts::calcTextData(std::string text, TextStyle textStyle, bool italic) {

    this->calcTextStyleData(textStyle, italic);
    this->loadFont(textStyleData.type, textStyleData.size);

    vita2d_font_text_dimensions(fonts[keyFont], textStyleData.size, textStyleData.uppercase ? this->toUppercase(text).c_str() : text.c_str(), &textData.width, &textData.height);
}


TextData UiTexts::getTextData(std::string text, TextStyleData _textStyleData) {

    this->loadFont(std::string(_textStyleData.type), textStyleData.size);
    vita2d_font_text_dimensions(fonts[keyFont], _textStyleData.size, _textStyleData.uppercase ? this->toUppercase(text).c_str() : text.c_str(), &textData.width, &textData.height);

    return textData;
}

TextStyleData UiTexts::getTextStyleData(TextStyle textStyle, bool italic) {
    this->calcTextStyleData(textStyle, italic);
    return textStyleData;
}

//You can override this function to put your style here (if you don't want to use roboto at all)
void UiTexts::calcTextStyleData(TextStyle textStyle, bool italic) {

    textStyleData.type = "Regular";
    textStyleData.size = 16;
    textStyleData.uppercase = false;

    switch (textStyle) {
        case H1:
            textStyleData.type = italic ? "LightItalic" : "Light";
            textStyleData.size = 96;
            break;
        case H2:
            textStyleData.type = italic ? "LightItalic" : "Light";
            textStyleData.size = 60;
            break;
        case H3:
            textStyleData.type = italic ? "Italic" : "Regular";
            textStyleData.size = 48;
            break;
        case H4:
            textStyleData.type = italic ? "Italic" : "Regular";
            textStyleData.size = 34;
            break;
        case H5:
            textStyleData.type = italic ? "Italic" : "Regular";
            textStyleData.size = 24;
            break;
        case H6:
            textStyleData.type = italic ? "MediumItalic" : "Medium";
            textStyleData.size = 20;
            break;
        case Sub1:
        case Body1:
            textStyleData.type = italic ? "Italic" : "Regular";
            textStyleData.size = 16;
            break;
        case Sub2:
        case Body2:
            textStyleData.type = italic ? "MediumItalic" : "Medium";
            textStyleData.size = 14;
            break;
        case Button:
            textStyleData.type = italic ? "MediumItalic" : "Medium";
            textStyleData.size = 14;
            textStyleData.uppercase = true;
            break;
        case Caption:
            textStyleData.type = italic ? "Italic" : "Regular";
            textStyleData.size = 12;
            break;
        case Overline:
            textStyleData.type = italic ? "Italic" : "Regular";
            textStyleData.size = 10;
            textStyleData.uppercase = true;
            break;

    }
    textStyleData.size += TEXTS_DEFAULT_SIZE_OFFSET;

    textStyleData.offset = textStyleData.size * 0.24;//correct font position
}

//dynamic import
//app0:assets/fonts/family/family-type.ttf
std::pair<std::string, unsigned int> UiTexts::loadFont(std::string type, unsigned int size) {
    keyFont = std::make_pair(type, size);

    if (fonts.find(keyFont) == fonts.end()) {

        fontPath = TEXTS_DEFAULT_FONTS_PATH;
        fontPath.append(family);
        fontPath.append("/");
        fontPath.append(family);
        fontPath.append("-");
        fontPath.append(type);
        fontPath.append(".ttf");

        fonts[keyFont] = vita2d_load_font_file(fontPath.c_str());
    }

    return keyFont;
}

void UiTexts::cleanFonts() {
    for (const auto& kv : this->fonts) {
        vita2d_free_font(kv.second);
    }
    fonts.clear();
}

void UiTexts::cleanFont(std::string type, int size) {
    keyFont = std::make_pair(type, size);
    if (fonts.find(keyFont) == fonts.end()) {
        vita2d_free_font(fonts[keyFont]);
    }
    fonts.erase(keyFont);
}


//Helpers functions

//set text to uppercase
std::string UiTexts::toUppercase(std::string text) {

    utf8::decode(text, text32);

    for (auto&& chr :  text32) chr = unicode::uppercase(chr);

    utf8::encode(text32, text);

    return text;
}

//set text to lowercase
std::string UiTexts::toLowercase(std::string text) {

    utf8::decode(text, text32);

    for (auto&& chr :  text32) chr = unicode::lowercase(chr);

    utf8::encode(text32, text);

    return text;
}

int UiTexts::keySearch(const std::string& s, const std::string& key) {
    int count = 0;
    size_t pos=0;
    while ((pos = s.find(key, pos)) != std::string::npos) {
        ++count;
        ++pos;
    }
    return count;
}


std::string UiTexts::applyTextWidthLimit(std::string text, int width, TextStyleData textStyleData, TextLimit textLimit) {
    textDataText = this->getTextData(text, textStyleData);

    if (textDataText.width > width) {

        posBreak = (unsigned int) (this->keySearch(text, "\n") + 1);
        posBreak = posBreak * width;
        posBreak = posBreak / (int)(textStyleData.size * 0.7);

        std::string::size_type lastFound = text.find_last_of('\n');
        std::string::size_type found = text.find(' ', posBreak);

        //abort the mission
        if ((lastFound == std::string::npos && found == std::string::npos) || posBreak > text.length()) {
            return text;
        }

        if (lastFound == std::string::npos) {
            lastFound = 0;
        }

        if (found == std::string::npos) {
            found = text.length() - 1;
        }

        if ((found - lastFound) > 28) {
            text.insert(posBreak, "-\n");
        }
        else {
            text.replace(found, 1, "\n");
        }


        return this->applyTextWidthLimit(text, width, textStyleData, textLimit);
    }

    return text;
}

std::string UiTexts::applyTextHeightLimit(std::string text, int height, TextStyleData textStyleData, TextLimit textLimit) {
    textDataText = this->getTextData(text, textStyleData);


    if (textDataText.height > height) {

        if (textLimit == TEXT_LIMIT_START) {
            text = text.substr(0, text.length() - 2);
        }
        else {
            text = text.substr(1, text.length() - 1);
        }

        return this->applyTextHeightLimit(text, height, textStyleData, textLimit);

    }

    return text;
}


