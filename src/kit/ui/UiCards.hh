#ifndef VITAMATERIALKIT_UICARDS_HH
#define VITAMATERIALKIT_UICARDS_HH

#include <vita2d.h>
#include <string>
#include "../core/UiEvent.hh"
#include "UiTheme.hpp"
#include "UiTexts.hpp"
#include "UiButtons.hpp"

#define CARDS_DEFAULT_WIDTH 400
#define CARDS_DEFAULT_PADDING 16
#define CARDS_DEFAULT_COLOR_HEADER_TEXT (unsigned int)RGBA8(0, 0, 0, 222)
#define CARDS_DEFAULT_COLOR_SUBHEAD_TEXT (unsigned int)RGBA8(0, 0, 0, 111)
#define CARDS_DEFAULT_COLOR_BACKGROUND (unsigned int)RGBA8(255, 255, 255, 255)

typedef struct CardPrePrimaryTitle {
    std::string headerText;
    std::string subHead;
    int height;
} CardPrePrimaryTitle;

typedef struct CardPreSummary {
    std::string text;
    int height;
} CardPreSummary;

class UiCards : public UiEvent {
private:
    UiTheme *theme;
    UiTexts *texts;
    UiIcons *icons;
    UiButtons *buttons;
    int x, y;
    int width, height;
    int typeTheme;
    ZoneEvent zoneEvent;

    int xOffset, yOffset, heightOffset;
    TextData textData;
    std::string showedText;
    int heightHeaderText, heightSubHead;

    CardPrePrimaryTitle cardPrePrimaryTitle;
    CardPreSummary cardPreSummary;

    void resetCard();
    void resetOffset();
public:
    UiCards(UiTheme *theme, UiTexts *texts, UiIcons *icons, UiButtons *buttons);

    ZoneEvent initCard(int x, int y, int width = CARDS_DEFAULT_WIDTH, TypeTheme typeTheme = THEME_PRIMARY);

    ZoneEvent drawPrimaryTitle(std::string headerText, std::string subHead = "", int height = 0);
    ZoneEvent drawPrimaryTitle(CardPrePrimaryTitle prePrimaryTitle);

    ZoneEvent drawMedia(vita2d_texture *media, int height = 0);

    ZoneEvent drawSummary(std::string text, int height = 0);
    ZoneEvent drawSummary(CardPreSummary cardPreSummary);

    //ZoneEvent drawAction(std::string actionText1 = "", std::string actionText2 = "");

    CardPrePrimaryTitle prePrimaryTitle(std::string headerText, std::string subHead, int width = CARDS_DEFAULT_WIDTH, int height = 0);
    CardPreSummary preSummaryTitle(std::string text, int width = CARDS_DEFAULT_WIDTH, int height = 0);

};


#endif //VITAMATERIALKIT_UICARDS_HH
