#ifndef VITA_MATERIAL_KIT_UI_TEXT_HPP
#define VITA_MATERIAL_KIT_UI_TEXT_HPP


#include <map>
#include <iostream>
#include <math.h>
#include <algorithm>

#include <psp2/io/fcntl.h>
#include <psp2/io/dirent.h>

#include "vita2d.h"
#include "UiTheme.hpp"


#define DEFAULT_FONT_COLOR RGBA8(0, 0, 0, 255)
#define DEFAULT_FONTS_PATH "app0:assets/fonts/"
#define DEFAULT_SIZE_OFFSET 12

//see https://material.io/design/typography/the-type-system.html#type-scale
typedef enum TextStyle {
    H1,
    H2,
    H3,
    H4,
    H5,
    H6,
    Sub1,
    Sub2,
    Body1,
    Body2,
    Button,
    Caption,
    Overline
} TextStyle;


typedef struct TextStyleData {
    const char *type;
    unsigned int size;
    bool uppercase;
    double offset;
} TextStyleData;

typedef struct TextData {
    int width;
    int height;

} TextData;

typedef enum TextThemeColor {
    TEXT_PRIMARY,
    TEXT_SECONDARY
} TextThemeColor;

class UiTexts {
private:
    std::map<std::string, vita2d_font*> fonts;
    TextData textData;
    TextStyleData textStyleData;
    UiTheme *theme;

    std::string toUppercase(std::string text);
    void drawFinal(int x, int y, TextStyle textStyle, unsigned int color, bool italic, std::string text);
    void drawFinal(int x, int y, TextStyleData _textStyleData, unsigned int color, std::string text);

    void calcTextData(std::string text, TextStyle textStyle, bool italic = false);

protected:
    virtual void calcTextStyleData(TextStyle textStyle, bool italic = false);
public:
    UiTexts();
    UiTexts(UiTheme *theme);
    UiTexts(std::string family);
    UiTexts(std::string family, UiTheme *theme);

    ~UiTexts();

    void init(std::string family);

    //Material Style
    void draw(int x, int y, TextStyle textStyle, std::string text);
    void draw(int x, int y, TextStyle textStyle, TextThemeColor textThemeColor, std::string text);
    void draw(int x, int y, TextStyle textStyle, unsigned int color, std::string text);
    void draw(int x, int y, TextStyle textStyle, unsigned int color, bool italic, std::string text);
    void draw(int x, int y, TextStyle textStyle, TextThemeColor textThemeColor, bool italic, std::string text);

    void drawF(int x, int y, TextStyle textStyle, unsigned int color, bool italic, const char *text, ...);
    void drawF(int x, int y, TextStyle textStyle, TextThemeColor textThemeColor, bool italic, const char *text, ...);


        //Do with your style
    void draw(int x, int y, TextStyleData _textStyleData, std::string text);
    void draw(int x, int y, TextStyleData _textStyleData, unsigned int color, std::string text);

    void drawF(int x, int y, TextStyleData _textStyleData, unsigned int color, const char *text, ...);


    TextData getTextData(std::string text, TextStyle textStyle, bool italic = false);
    TextData getTextData(std::string text, TextStyleData _textStyleData);

};


#endif //VITA_MATERIAL_KIT_UI_TEXT_HPP
