#ifndef VITAMATERIALKIT_UIPARENTBOXES_HH
#define VITAMATERIALKIT_UIPARENTBOXES_HH

#include "../UiTheme.hpp"
#include "../UiTexts.hpp"
#include "../UiIcons.hpp"

#define BOXES_DEFAULT_SIZE 40
#define BOXES_DEFAULT_SELECTOR_ALPHA 100
#define BOXES_DEFAULT_COLOR_UNCHECKED (unsigned int) RGBA8(92, 92, 92, 255)

class UiParentBoxes {
private:
    unsigned int selectorColorPrimary, selectorColorSecondary;
    UiTheme *theme;
    UiIcons *icons;
    UiTexts *texts;
protected:
    UiParentBoxes(UiTheme *theme);
    UiParentBoxes(UiTheme *theme, UiIcons *icons);
    UiParentBoxes(UiTheme *theme, UiIcons *icons, UiTexts *texts);

    void drawSelector(int x, int y, bool selector, TypeTheme theme, unsigned int size = BOXES_DEFAULT_SIZE);

    TextData drawText(int x, int y, int size, std::string text, TextStyle textStyle = Body1, unsigned int color = TEXTS_DEFAULT_FONT_COLOR);

    void drawBoxButton(int x, int y, const char* icon, TypeTheme theme, unsigned int size = BOXES_DEFAULT_SIZE);
    void drawBoxButton(int x, int y, const char* icon, unsigned int color, unsigned int size = BOXES_DEFAULT_SIZE);

};


#endif //VITAMATERIALKIT_UIPARENTBOXES_HH
