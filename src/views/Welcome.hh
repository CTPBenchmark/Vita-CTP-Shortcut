#ifndef VITAMATERIALKIT_WELCOME_HH
#define VITAMATERIALKIT_WELCOME_HH

#include "../kit/core/View.hh"

#define WELCOME_NUMBER_OF_BUTTONS 4

class Welcome: public View {
private:
    ZoneEvent forumZE, websiteZE, optionsZE, exitZE;
    std::map<std::string, std::string> i18nWelcome;

public:
    Welcome(const char *name);
    void contents() override;
    void controls() override;

    void beforeEnter() override;
};

#endif //VITAMATERIALKIT_WELCOME_HH
