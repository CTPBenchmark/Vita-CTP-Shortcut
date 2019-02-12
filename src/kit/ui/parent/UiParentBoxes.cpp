#include "UiParentBoxes.hh"

UiParentBoxes::UiParentBoxes(UiTheme *theme) : theme(theme) {
    this->selectorColorPrimary = theme->convertHexToRGBA(theme->getPrimaryHEX().light, BOXES_DEFAULT_SELECTOR_ALPHA);
    this->selectorColorSecondary = theme->convertHexToRGBA(theme->getSecondaryHEX().light, BOXES_DEFAULT_SELECTOR_ALPHA);
}

UiParentBoxes::UiParentBoxes(UiTheme *theme, UiIcons *icons) : theme(theme), icons(icons) {
    this->selectorColorPrimary = theme->convertHexToRGBA(theme->getPrimaryHEX().light, BOXES_DEFAULT_SELECTOR_ALPHA);
    this->selectorColorSecondary = theme->convertHexToRGBA(theme->getSecondaryHEX().light, BOXES_DEFAULT_SELECTOR_ALPHA);
}

UiParentBoxes::UiParentBoxes(UiTheme *theme, UiIcons *icons, UiTexts *texts) : theme(theme), icons(icons), texts(texts) {
    this->selectorColorPrimary = theme->convertHexToRGBA(theme->getPrimaryHEX().light, BOXES_DEFAULT_SELECTOR_ALPHA);
    this->selectorColorSecondary = theme->convertHexToRGBA(theme->getSecondaryHEX().light, BOXES_DEFAULT_SELECTOR_ALPHA);
}

void UiParentBoxes::drawSelector(int x, int y, bool selector, TypeTheme theme, unsigned int size) {
    if (selector) {
        vita2d_draw_fill_circle(x + size, y + size, (int) (size * 0.75), theme == THEME_PRIMARY ? selectorColorPrimary : selectorColorSecondary);
    }
}

void UiParentBoxes::drawBoxButton(int x, int y, const char *icon, TypeTheme typeTheme, unsigned int size) {
    this->drawBoxButton(x, y, icon, typeTheme == THEME_PRIMARY ? theme->getPrimaryRGBA().normal : theme->getSecondaryRGBA().normal, size);
}

void UiParentBoxes::drawBoxButton(int x, int y, const char *icon, unsigned int color, unsigned int size) {
    icons->draw(icon, x + (size / 2), y + (size / 2), color, size);
}

TextData UiParentBoxes::drawText(int x, int y, int size, std::string text, TextStyle textStyle, unsigned int color) {
    texts->draw(x + (size * 2), y + (int) (size * 0.75), textStyle, color, text);
    return texts->getTextData(text, textStyle);
}


