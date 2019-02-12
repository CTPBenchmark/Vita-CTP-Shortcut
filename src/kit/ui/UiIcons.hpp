// https://material.io/tools/color/#!/?view.left=0&view.right=0&primary.color=212121&secondary.color=90A4AE&secondary.text.color=FAFAFA&primary.text.color=FAFAFA

#ifndef VITA_MATERIAL_KIT_UI_ICONS_HPP
#define VITA_MATERIAL_KIT_UI_ICONS_HPP

#include <vita2d.h>
#include <string>

#include "UiIconsCodes.hh"
#include "UiTheme.hpp"
#include <math.h>

#define DEFAULT_MATERIAL_ICON_COLOR (unsigned int) RGBA8(255, 255, 255, 255)
#define DEFAULT_MATERIAL_ICON_SIZE (unsigned int) 50
#define DEFAULT_MATERIAL_ICON_PATH "app0:assets/fonts/mdi/" FONT_ICON_FILE_NAME_MDI

class UiIcons {
    private:
        UiTheme *theme;
        vita2d_font *font;
    public:
        UiIcons();
        UiIcons(UiTheme *theme);
        UiIcons(const char *path);
        UiIcons(const char *path, UiTheme *theme);

        void draw(const char* iconCode, int x, int y, unsigned int color = DEFAULT_MATERIAL_ICON_COLOR, unsigned int size = DEFAULT_MATERIAL_ICON_SIZE);
        void draw(const char* iconCode, int x, int y, TypeTheme iconThemeColor, unsigned int size = DEFAULT_MATERIAL_ICON_SIZE);
};


#endif //VITA_MATERIAL_KIT_UI_ICONS_HPP
