// https://material.io/tools/color/#!/?view.left=0&view.right=0&primary.color=212121&secondary.color=90A4AE&secondary.text.color=FAFAFA&primary.text.color=FAFAFA

#ifndef VITA_MATERIAL_KIT_UI_ICONS_HH
#define VITA_MATERIAL_KIT_UI_ICONS_HH

#include <vita2d.h>
#include <string>

#include "UiIconsCodesPSVita.hh"
#include "../lib/IconFontCppHeaders/IconsMaterialDesignIcons.h"
#include "UiTheme.hh"
#include <math.h>

#define DEFAULT_ICON_COLOR (unsigned int) RGBA8(255, 255, 255, 255)
#define DEFAULT_MATERIAL_ICON_SIZE (unsigned int) 50
#define DEFAULT_PSVITA_ICON_SCALE 1.5f
#define DEFAULT_MATERIAL_ICON_PATH "app0:assets/fonts/mdi/" FONT_ICON_FILE_NAME_MDI
#define DEFAULT_PSVITA_ICON_PATH "sa0:data/font/pvf/psexchar.pvf"

class UiIcons {
    private:
        UiTheme *theme;
        vita2d_font *mdi;
        vita2d_pvf  *psvita;
    public:
        UiIcons();
        UiIcons(UiTheme *theme);

        void draw(const char* iconCode, int x, int y, unsigned int color = DEFAULT_ICON_COLOR, unsigned int size = DEFAULT_MATERIAL_ICON_SIZE);
        void draw(const char* iconCode, int x, int y, TypeTheme iconThemeColor, unsigned int size = DEFAULT_MATERIAL_ICON_SIZE);

        void drawPSVita(const char *iconCode, int x, int y, unsigned int color = DEFAULT_ICON_COLOR, float scale = DEFAULT_PSVITA_ICON_SCALE);
        void drawPSVita(const char *iconCode, int x, int y, TypeTheme iconThemeColor, float scale = DEFAULT_PSVITA_ICON_SCALE);
};


#endif //VITA_MATERIAL_KIT_UI_ICONS_HH
