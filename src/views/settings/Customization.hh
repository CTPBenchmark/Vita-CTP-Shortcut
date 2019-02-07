#ifndef CTP_SHORTCUT_CUSTOMIZATION_HH
#define CTP_SHORTCUT_CUSTOMIZATION_HH

#include "../../kit/core/View.hh"

class Customization : public View {
private:
    ZoneEvent backgroundButtonZE, iconsButtonZE, foregroundButtonZE, speedTextFieldZE, backButtonZE;
    ZoneEventCheckboxes customizationCheckboxZE;
    UiCheckboxesStatus customizationCheckbox;
    int CUSTOMIZATION_NUMBER_OF_BUTTONS;
public:
    Customization(const std::string &name);

    void contents() override;

    void controls() override;

    void beforeEnter() override;
};


#endif //CTP_SHORTCUT_CUSTOMIZATION_HH
