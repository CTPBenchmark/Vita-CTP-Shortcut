#ifndef VITA_MATERIAL_KIT_UI_TEXT_HH
#define VITA_MATERIAL_KIT_UI_TEXT_HH


#include <map>
#include <iostream>
#include <math.h>
#include <algorithm>
#include <stdarg.h>

#include <psp2/io/fcntl.h>
#include <psp2/io/dirent.h>

#include "vita2d.h"
#include "../lib/unilib/unicode.h"
#include "../lib/unilib/utf8.h"

#include "UiTheme.hh"


#define TEXTS_DEFAULT_FONT_COLOR (unsigned int) RGBA8(0, 0, 0, 255)
#define TEXTS_DEFAULT_FONTS_PATH "app0:assets/fonts/"
#define TEXTS_DEFAULT_SIZE_OFFSET 12

//see https://material.io/design/typography/the-type-system.html#type-scale
typedef enum TextStyle {
    H1 = 1,
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
    std::string type;
    unsigned int size;
    bool uppercase;
    double offset;
} TextStyleData;

typedef struct TextData {
    int width;
    int height;
} TextData;

typedef enum TextLimit {
    TEXT_LIMIT_START,
    TEXT_LIMIT_END
} TextLimit;

class UiTexts {
private:
    std::map< std::pair<std::string, unsigned int>, vita2d_font *> fonts;
    TextData textData;
    TextStyleData textStyleData;
    UiTheme *theme;
    std::pair<std::string, unsigned int> keyFont;
    std::string family, fontPath;

    std::u32string text32;
    TextData textDataText;
    TextData substringTextData;
    std::string subString;
    unsigned int pos;
    int adjust, posEnd;

    unsigned int posBreak;

    void drawFinal(int x, int y, TextStyle textStyle, unsigned int color, bool italic, std::string text);
    void drawFinal(int x, int y, TextStyleData _textStyleData, unsigned int color, std::string text);

    void calcTextData(std::string text, TextStyle textStyle, bool italic = false);
    std::pair<std::string, unsigned int> loadFont(std::string type, unsigned int size);

protected:
    virtual void calcTextStyleData(TextStyle textStyle, bool italic = false);
public:
    UiTexts();
    UiTexts(UiTheme *theme);
    UiTexts(std::string family);
    UiTexts(std::string family, UiTheme *theme);

    ~UiTexts();

    //Material Style
    void draw(int x, int y, TextStyle textStyle, std::string text);
    void draw(int x, int y, TextStyle textStyle, TypeTheme textThemeColor, std::string text);
    void draw(int x, int y, TextStyle textStyle, unsigned int color, std::string text);
    void draw(int x, int y, TextStyle textStyle, unsigned int color, bool italic, std::string text);
    void draw(int x, int y, TextStyle textStyle, TypeTheme textThemeColor, bool italic, std::string text);

    void drawF(int x, int y, TextStyle textStyle, unsigned int color, bool italic, const char *text, ...);
    void drawF(int x, int y, TextStyle textStyle, TypeTheme textThemeColor, bool italic, const char *text, ...);


        //Do with your style
    void draw(int x, int y, TextStyleData _textStyleData, std::string text);
    void draw(int x, int y, TextStyleData _textStyleData, unsigned int color, std::string text);

    void drawF(int x, int y, TextStyleData _textStyleData, unsigned int color, const char *text, ...);
    void drawF(int x, int y, TextStyleData _textStyleData,  TypeTheme textThemeColor, const char *text, ...);

    //TextData functions
    TextData getTextData(std::string text, TextStyle textStyle, bool italic = false);
    TextData getTextData(std::string text, TextStyleData _textStyleData);
    TextStyleData getTextStyleData(TextStyle textStyle, bool italic = false);

    //Dynamic import
    void cleanFonts();
    void cleanFont(std::string type, int size);

    //Helpers functions
    int keySearch(const std::string& s, const std::string& key);
    std::string applyTextWidthLimit(std::string text, int width, TextStyleData textStyleData);
    std::string applyTextHeightLimitCut(std::string text, int height, TextStyleData textStyleData, TextLimit textLimit = TEXT_LIMIT_END);

    //transformation text
    std::string toUppercase(std::string text);
    std::string toLowercase(std::string text);
    std::string toTitleCase(std::string text);

};


#endif //VITA_MATERIAL_KIT_UI_TEXT_HH
