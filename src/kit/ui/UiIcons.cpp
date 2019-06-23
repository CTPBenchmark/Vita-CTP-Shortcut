#include <string.h>
#include "UiIcons.hh"

UiIcons::UiIcons() {
    mdi = vita2d_load_font_file(DEFAULT_MATERIAL_ICON_PATH);
    psvita = vita2d_load_custom_pvf(DEFAULT_PSVITA_ICON_PATH);
}

UiIcons::UiIcons(UiTheme *theme) {
    mdi = vita2d_load_font_file(DEFAULT_MATERIAL_ICON_PATH);
    psvita = vita2d_load_custom_pvf(DEFAULT_PSVITA_ICON_PATH);
    this->theme = theme;
}


void UiIcons::draw(const char* iconCode, int x, int y, unsigned int color, unsigned int size) {
    y = y + size - (int) floor(size * 0.12);
    vita2d_font_draw_text(mdi, x, y, color, size, iconCode);
}

void UiIcons::draw(const char* iconCode, int x, int y, TypeTheme iconThemeColor, unsigned int size) {
   this->draw(iconCode, x, y, iconThemeColor == THEME_PRIMARY ? theme->getPrimaryRGBA().text : theme->getSecondaryRGBA().text, size);
}

//Note: don't work with Vita3K
void UiIcons::drawPSVita(const char* iconCode, int x, int y, unsigned int color, float scale) {
    if (psvita != nullptr)//prevent vita3k crash
        vita2d_pvf_draw_text(psvita, x, y, color, scale, iconCode);
}

//Note: don't work with Vita3K
void UiIcons::drawPSVita(const char* iconCode, int x, int y, TypeTheme iconThemeColor, float scale) {
    this->drawPSVita(iconCode, x, y, iconThemeColor == THEME_PRIMARY ? theme->getPrimaryRGBA().text : theme->getSecondaryRGBA().text, scale);
}
