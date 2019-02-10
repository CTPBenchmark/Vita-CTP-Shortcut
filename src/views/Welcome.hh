#ifndef VITAMATERIALKIT_WELCOME_HH
#define VITAMATERIALKIT_WELCOME_HH

#include "../kit/core/View.hh"
#include "../utils/CTPApi.hh"
#include <utils/CTPApiThread.hh>

class Welcome: public View {
private:
    ZoneEvent forumZE, websiteZE, optionsZE, exitZE, centerZE;
    std::map<std::string, std::string> i18nWelcome;

public:
    Welcome(const char *name);
    void contents() override;
    void controls() override;

    void beforeEnter() override;

    void mounted() override;
};

#endif //VITAMATERIALKIT_WELCOME_HH
