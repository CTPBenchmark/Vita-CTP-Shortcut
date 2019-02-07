#ifndef VITAMATERIALKIT_WELCOME_HH
#define VITAMATERIALKIT_WELCOME_HH

#include "../kit/core/View.hh"

#define WELCOME_NUMBER_OF_BUTTONS 4

class Welcome: public View {
private:
    ZoneEvent forumZE, websiteZE, optionsZE, exitZE;
    int selector = -1;
    I18n *i18n;
    int touchMode = 1;

public:
    Welcome(const char *name);
    void contents() override;
    void controls() override;
};

#endif //VITAMATERIALKIT_WELCOME_HH
