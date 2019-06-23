#ifndef VITAMATERIALKIT_UI_HH
#define VITAMATERIALKIT_UI_HH


#include "ui/UiCards.hh"
#include "ui/UiTheme.hh"
#include "ui/UiIcons.hh"
#include "ui/UiTexts.hh"
#include "ui/UiButtons.hh"
#include "../ui/LayoutTheme.hh"
#include "ui/UiCheckboxes.hh"
#include "ui/UiTextFields.hh"


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
    UiCheckboxes *checkboxes;
    UiTextFields *textFields;
    UiCards *cards;

    LayoutTheme *layoutTheme;

    Ui();
};


#endif //VITAMATERIALKIT_UI_HH
