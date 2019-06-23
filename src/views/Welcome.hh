#ifndef VITAMATERIALKIT_WELCOME_HH
#define VITAMATERIALKIT_WELCOME_HH

#include "../kit/core/View.hh"
#include "../utils/CTPApi.hh"
#include <utils/CTPApiThread.hh>

typedef struct CardPostContent {
    CardPrePrimaryTitle cardPrePrimaryTitle;
    CardPreSummary cardPreSummary;
    ZoneEvent zoneEvent;
    std::string url;
} CardPostContent;

class Welcome: public View {
private:
    ZoneEvent forumZE, websiteZE, optionsZE, exitZE, centerZE;
    std::map<std::string, std::string> i18nWelcome;
    std::vector<CardPostContent> cardPosts;
    int cardsSelector = -1;
public:
    Welcome(const char *name);
    void contents() override;
    void controls() override;

    void mounted() override;

    void beforeEnter() override;
    void beforeExit() override;

    void gridNoCards();
    void gridWithCards();

};

#endif //VITAMATERIALKIT_WELCOME_HH
