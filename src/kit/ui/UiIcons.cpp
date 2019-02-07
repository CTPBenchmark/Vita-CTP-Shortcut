#include "UiIcons.hpp"

UiIcons::UiIcons() {
    font = vita2d_load_font_file(DEFAULT_MATERIAL_ICON_PATH);
}

UiIcons::UiIcons(UiTheme *theme) {
    font = vita2d_load_font_file(DEFAULT_MATERIAL_ICON_PATH);
    this->theme = theme;
}

UiIcons::UiIcons(const char *path) {
    font = vita2d_load_font_file(path);
}

UiIcons::UiIcons(const char *path, UiTheme *theme) {
    font = vita2d_load_font_file(path);
    this->theme = theme;
}

void UiIcons::draw(const char* iconCode, int x, int y, unsigned int color, unsigned int size) {
    y = y + size - (int) floor(size * 0.12);
    vita2d_font_draw_text(font, x, y, color, size, iconCode);
}

void UiIcons::draw(const char* iconCode, int x, int y, TypeTheme iconThemeColor, unsigned int size) {
   this->draw(iconCode, x, y, iconThemeColor == THEME_PRIMARY ? theme->getPrimaryRGBA().text : theme->getSecondaryRGBA().text, size);
}