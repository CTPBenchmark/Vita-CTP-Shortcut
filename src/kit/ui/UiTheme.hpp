//see https://material.io/tools/color/#!/
#ifndef VITA_MATERIAL_KIT_UI_THEME_HPP
#define VITA_MATERIAL_KIT_UI_THEME_HPP

#include <cstdio>
#include <vita2d.h>

typedef enum TypeTheme {
    THEME_PRIMARY,
    THEME_SECONDARY
} TypeTheme;

typedef struct{
    const char *normal;
    const char *light;
    const char *dark;
    const char *text;
} colorSchemeHEX;

typedef struct{
    unsigned int normal;
    unsigned int light;
    unsigned int dark;
    unsigned int text;
} colorSchemeRGBA;

class UiTheme {
private:
    colorSchemeHEX primaryHEX;
    colorSchemeHEX secondaryHEX;
    colorSchemeRGBA primaryRGBA;
    colorSchemeRGBA secondaryRGBA;

    colorSchemeRGBA colorSchemeHEXToColorShemeRGBA(colorSchemeHEX hex);

public:
    UiTheme();
    UiTheme(const colorSchemeHEX &primary, const colorSchemeHEX &secondary);

    const colorSchemeHEX &getPrimaryHEX() const;

    const colorSchemeHEX &getSecondaryHEX() const;

    const colorSchemeRGBA &getPrimaryRGBA() const;

    const colorSchemeRGBA &getSecondaryRGBA() const;

    unsigned int convertHexToRGBA(const char *hex, unsigned int alpha = 255);

};


#endif //VITA_MATERIAL_KIT_UI_THEME_HPP
