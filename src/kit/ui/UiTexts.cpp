#include <stdarg.h>
#include "UiTexts.hpp"

UiTexts::UiTexts() {
    this->init("Roboto");
}

UiTexts::UiTexts(UiTheme *theme) {
    this->theme = theme;
    this->init("Roboto");
}

UiTexts::UiTexts(std::string family) {
    this->init(std::move(family));
}

UiTexts::UiTexts(std::string family, UiTheme *theme) {
    this->theme = theme;
    this->init(std::move(family));
}

UiTexts::~UiTexts() {
    for (const auto& kv : this->fonts) {
        vita2d_free_font(kv.second);
    }
}

void UiTexts::init(std::string family) {
    SceIoDirent gDir;
    std::string fontsPath = DEFAULT_FONTS_PATH;
    fontsPath = fontsPath + family;

    int fd = sceIoDopen(fontsPath.c_str());//open fonts folder

    std::string fontPath, fileName, fontName;

    fontsPath.append("/");//add slash for folder

    while (sceIoDread(fd, &gDir) > 0) {
        fileName = gDir.d_name;
        fontPath = fontsPath + fileName;//get the path of the file

        fontName = fileName.erase(0, family.length() + 1);//remove the family name and -
        fontName = fontName.erase(fontName.length() - 4, fontName.length());//remove .ttf
        fonts[fontName] = vita2d_load_font_file(fontPath.c_str());

    }

    sceIoClose(fd);
}

void UiTexts::drawFinal(int x, int y, TextStyle textStyle, unsigned int color, bool italic, std::string text) {
    this->calcTextStyleData(textStyle, italic);

    vita2d_font_draw_text(fonts[textStyleData.type], x, (int) floor(y + textStyleData.size - textStyleData.offset), color, textStyleData.size, textStyleData.uppercase ? this->toUppercase(text).c_str() : text.c_str());
}

void UiTexts::drawFinal(int x, int y, TextStyleData _textStyleData, unsigned int color, std::string text) {
    vita2d_font_draw_text(fonts[_textStyleData.type], x, (int) floor(y + _textStyleData.size - _textStyleData.offset), color, _textStyleData.size, _textStyleData.uppercase ? this->toUppercase(text).c_str() : text.c_str());
}

//Draw with Material Style
void UiTexts::draw(int x, int y, TextStyle textStyle, std::string text) {
    this->drawFinal(x, y, textStyle, DEFAULT_FONT_COLOR, false, std::move(text));
}

void UiTexts::draw(int x, int y, TextStyle textStyle, unsigned int color, std::string text) {
    this->drawFinal(x, y, textStyle, color, false, std::move(text));
}

void UiTexts::draw(int x, int y, TextStyle textStyle, TextThemeColor textThemeColor, std::string text) {
    this->drawFinal(x, y, textStyle, textThemeColor == TEXT_PRIMARY ? theme->getPrimaryRGBA().text : theme->getSecondaryRGBA().text, false, std::move(text));
}


void UiTexts::draw(int x, int y, TextStyle textStyle, unsigned int color, bool italic, std::string text) {
    this->drawFinal(x, y, textStyle, color, italic, std::move(text));
}

void UiTexts::draw(int x, int y, TextStyle textStyle, TextThemeColor textThemeColor, bool italic, std::string text) {
    this->drawFinal(x, y, textStyle, textThemeColor == TEXT_PRIMARY ? theme->getPrimaryRGBA().text : theme->getSecondaryRGBA().text, italic, std::move(text));
}

void UiTexts::drawF(int x, int y, TextStyle textStyle, unsigned int color, bool italic, const char *text, ...) {
    char buf[1024];
    va_list argPtr;

    va_start(argPtr, text);
    vsnprintf(buf, sizeof(buf), text, argPtr);
    va_end(argPtr);

    this->drawFinal(x, y, textStyle, color, italic, buf);
}

void UiTexts::drawF(int x, int y, TextStyle textStyle, TextThemeColor textThemeColor, bool italic, const char *text, ...) {
    char buf[1024];
    va_list argPtr;

    va_start(argPtr, text);
    vsnprintf(buf, sizeof(buf), text, argPtr);
    va_end(argPtr);

    this->drawFinal(x, y, textStyle, textThemeColor == TEXT_PRIMARY ? theme->getPrimaryRGBA().text : theme->getSecondaryRGBA().text, italic, buf);
}


//Draw with your style
void UiTexts::draw(int x, int y, TextStyleData _textStyleData, std::string text) {
    this->drawFinal(x, y, _textStyleData, DEFAULT_FONT_COLOR, std::move(text));
}

void UiTexts::draw(int x, int y, TextStyleData _textStyleData, unsigned int color, std::string text) {
    this->drawFinal(x, y, _textStyleData, color, std::move(text));
}

void UiTexts::drawF(int x, int y, TextStyleData _textStyleData, unsigned int color, const char *text, ...) {
    char buf[1024];
    va_list argPtr;

    va_start(argPtr, text);
    vsnprintf(buf, sizeof(buf), text, argPtr);
    va_end(argPtr);

    this->drawFinal(x, y, _textStyleData, color, buf);
}


//utils
TextData UiTexts::getTextData(std::string text, TextStyle textStyle, bool italic) {
    this->calcTextData(std::move(text), textStyle, italic);
    return textData;
}

//private

//set text to uppercase
std::string UiTexts::toUppercase(std::string text) {
    std::transform(text.begin(), text.end(),text.begin(), ::toupper);
    return text;
}

void UiTexts::calcTextData(std::string text, TextStyle textStyle, bool italic) {

    this->calcTextStyleData(textStyle, italic);

    vita2d_font_text_dimensions(fonts[textStyleData.type], textStyleData.size, textStyleData.uppercase ? this->toUppercase(text).c_str() : text.c_str(), &textData.width, &textData.height);
}


TextData UiTexts::getTextData(std::string text, TextStyleData _textStyleData) {

    vita2d_font_text_dimensions(fonts[_textStyleData.type], _textStyleData.size, _textStyleData.uppercase ? this->toUppercase(text).c_str() : text.c_str(), &textData.width, &textData.height);

    return textData;
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
    textStyleData.size += DEFAULT_SIZE_OFFSET;

    textStyleData.offset = textStyleData.size * 0.24;//correct font position
}
