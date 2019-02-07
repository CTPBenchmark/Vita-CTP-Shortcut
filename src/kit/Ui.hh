#ifndef VITAMATERIALKIT_UI_HH
#define VITAMATERIALKIT_UI_HH


#include "ui/UiTheme.hpp"
#include "ui/UiIcons.hpp"
#include "ui/UiTexts.hpp"
#include "ui/UiButtons.hpp"
#include "../ui/LayoutTheme.hh"


class Ui {
protected:
    colorSchemeHEX primaryThemeColor;
    colorSchemeHEX secondaryThemeColor;
    void initTheme();
    void init();
public:
    UiTheme     *theme;
    UiTexts     *texts;
    UiButtons   *buttons;
    UiIcons     *icons;
    LayoutTheme *layoutTheme;

    Ui();
};


#endif //VITAMATERIALKIT_UI_HH
