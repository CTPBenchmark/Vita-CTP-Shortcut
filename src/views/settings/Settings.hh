#ifndef CTP_SHORTCUT_SETTINGS_HH
#define CTP_SHORTCUT_SETTINGS_HH

#include "../../kit/core/View.hh"
#define SETTINGS_NUMBER_OF_BUTTONS 4

class Settings : public View {
private:
    ZoneEvent customizationButtonZE, backButtonZE;
    ZoneEventCheckboxes newsCheckboxZE, forumCheckboxZE;
    UiCheckboxesStatus newsCheckbox, forumCheckbox;
public:
    Settings(const std::string &name);

    void contents() override;

    void controls() override;

    void beforeEnter() override;

};


#endif //CTP_SHORTCUT_SETTINGS_HH
