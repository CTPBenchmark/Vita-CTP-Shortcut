#ifndef CTP_SHORTCUT_CUSTOMIZATION_HH
#define CTP_SHORTCUT_CUSTOMIZATION_HH

#include "kit/core/View.hh"
#include <stdlib.h>

class Customization : public View {
private:
    ZoneEvent backgroundButtonZE, iconsButtonZE, foregroundButtonZE, speedTextFieldZE, backButtonZE;
    ZoneEvent redZE, greenZE, blueZE, alphaZE;
    ZoneEventCheckboxes customizationCheckboxZE;
    UiCheckboxesStatus customizationCheckbox;
    std::map<std::string, std::string> i18nCustomization;
    std::string chosen;
    RGBAColor rgbaCustomization;

    unsigned int getColorPart(std::string name, unsigned int value);
    void refreshBackground();
public:
    Customization(const std::string &name);

    void contents() override;
    void controls() override;

    void contentsDefault();
    void contentsCustomizeColors();

    void controlsDefault();
    void controlsCustomizeColors();


    void beforeEnter() override;
    void beforeExit() override;

    void mounted() override;
};


#endif //CTP_SHORTCUT_CUSTOMIZATION_HH
