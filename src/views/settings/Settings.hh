#ifndef CTP_SHORTCUT_SETTINGS_HH
#define CTP_SHORTCUT_SETTINGS_HH

#include "../../kit/core/View.hh"

class Settings : public View {
public:
    Settings(const std::string &name);

    void contents() override;

    void controls() override;
};


#endif //CTP_SHORTCUT_SETTINGS_HH
