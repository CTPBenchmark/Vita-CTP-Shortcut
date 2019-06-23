#include "UiCards.hh"

UiCards::UiCards(UiTheme *theme, UiTexts *texts, UiIcons *icons, UiButtons *buttons) : theme(theme), texts(texts),
                                                                                       icons(icons), buttons(buttons) {}


void UiCards::resetCard() {
    x = 0;
    y = 0;
    width = 0;
    height = 0;
    mediaFirst = 0;
    selected = false;
}

void UiCards::resetOffset() {
    xOffset = 0;
    yOffset = 0;
    heightOffset = 0;
}

bool UiCards::outsideScreen() {
    return x + width < 0 || y + height < 0 || x > SCREEN_WIDTH || y > SCREEN_HEIGHT;
}

void UiCards::start(int x, int y, int width, TypeTheme typeTheme, bool selected) {
    this->x = x;
    this->y = y;
    this->xStart = x;
    this->yStart = y;
    this->width = width;
    this->typeTheme = typeTheme;
    this->selected = selected;
}

ZoneEvent UiCards::end() {
    zoneEvent.x = xStart;
    zoneEvent.y = yStart;
    zoneEvent.width = width;
    zoneEvent.height = height;
    zoneEvent.selector = selected;

    //clean for the next draw card
    this->resetCard();
    this->resetOffset();

    return zoneEvent;
}

ZoneEvent UiCards::drawPrimaryTitle(CardPrePrimaryTitle prePrimaryTitle) {
    if (outsideScreen())
        return {};

    if (mediaFirst == 0)
        mediaFirst = -1;

    this->resetOffset();

    zoneEvent.x = x;
    zoneEvent.y = y;
    zoneEvent.width = width;

    xOffset = x + CARDS_DEFAULT_PADDING;
    yOffset = y + CARDS_DEFAULT_PADDING;

    textData = texts->getTextData(prePrimaryTitle.headerText, H6);

    if (prePrimaryTitle.height == 0) {
        heightOffset = CARDS_DEFAULT_PADDING;
        heightOffset += textData.height;
        if (!prePrimaryTitle.subHead.empty()) {
            textData = texts->getTextData(prePrimaryTitle.subHead, Body1);
            heightOffset += textData.height + CARDS_DEFAULT_PADDING_SMALL;
        }
        heightOffset += CARDS_DEFAULT_PADDING;
    }
    else {
        heightOffset = prePrimaryTitle.height;
    }

    vita2d_draw_rectangle(x, yOffset - CARDS_DEFAULT_PADDING, width, heightOffset + CARDS_DEFAULT_PADDING, this->selected && this->mediaFirst == 1 ? CARDS_DEFAULT_COLOR_SELECTED : CARDS_DEFAULT_COLOR_BACKGROUND);

    texts->draw(xOffset, yOffset, H6, CARDS_DEFAULT_COLOR_HEADER_TEXT, prePrimaryTitle.headerText);
    if (!prePrimaryTitle.subHead.empty()) {
        textData = texts->getTextData(prePrimaryTitle.headerText, H6);
        texts->draw(xOffset, yOffset + textData.height + CARDS_DEFAULT_PADDING_SMALL, Body1, CARDS_DEFAULT_COLOR_SUBHEAD_TEXT, prePrimaryTitle.subHead);
    }

    zoneEvent.height = heightOffset;
    this->height = heightOffset;

    y += heightOffset;

    return zoneEvent;
}

ZoneEvent UiCards::drawPrimaryTitle(std::string headerText, std::string subHead, int height) {
   this->prePrimaryTitle(std::move(headerText), std::move(subHead), width, height);
   return this->drawPrimaryTitle(cardPrePrimaryTitle);
}

ZoneEvent UiCards::drawMedia(vita2d_texture *media, CardPrePrimaryTitle prePrimaryTitle) {
    if (outsideScreen())
        return {};

    if (mediaFirst == 0)
        mediaFirst = 1;

    this->resetOffset();

    if (media == nullptr) {
        heightOffset = prePrimaryTitle.height == 0 ? 200 : prePrimaryTitle.height;
        vita2d_draw_rectangle(x, y, width, heightOffset, CARDS_DEFAULT_COLOR_HEADER_TEXT);
    }
    else {
        heightOffset = prePrimaryTitle.height == 0 ? vita2d_texture_get_height(media) : prePrimaryTitle.height;
        vita2d_draw_texture_part(media, x, y, 0, 0, width, heightOffset);
    }

    yOffset = y - CARDS_DEFAULT_PADDING + heightOffset;
    xOffset = x + CARDS_DEFAULT_PADDING;

    if (!prePrimaryTitle.subHead.empty()) {
        textData = texts->getTextData(prePrimaryTitle.subHead, Body1);
        yOffset -= textData.height + CARDS_DEFAULT_PADDING;
        texts->draw(xOffset, yOffset, Body1, CARDS_DEFAULT_COLOR_SUBHEAD_TEXT_MEDIA, prePrimaryTitle.subHead);
    }
    if (!prePrimaryTitle.subHead.empty()) {
        textData = texts->getTextData(prePrimaryTitle.headerText, H6);
        yOffset -= textData.height + CARDS_DEFAULT_PADDING_SMALL;
        texts->draw(xOffset, yOffset, H6, CARDS_DEFAULT_COLOR_HEADER_TEXT_MEDIA, prePrimaryTitle.headerText);
    }


    if (this->selected) {
        vita2d_draw_rectangle(x, y, width, heightOffset, CARDS_DEFAULT_COLOR_SELECTED_MEDIA);
    }


    zoneEvent.x = x;
    zoneEvent.y = y;
    zoneEvent.width = width;
    zoneEvent.height = heightOffset;

    y += heightOffset;
    this->height += heightOffset;

    return zoneEvent;
}

ZoneEvent UiCards::drawMedia(vita2d_texture *media, std::string headerText, std::string subHead, int height) {
    cardPrePrimaryTitle.headerText = headerText;
    cardPrePrimaryTitle.subHead = subHead;
    cardPrePrimaryTitle.height = height;
    return this->drawMedia(media, cardPrePrimaryTitle);
}

ZoneEvent UiCards::drawMedia(vita2d_texture *media, int height) {
    cardPrePrimaryTitle.headerText = "";
    cardPrePrimaryTitle.subHead = "";
    cardPrePrimaryTitle.height = height;
    return this->drawMedia(media, cardPrePrimaryTitle);
}

ZoneEvent UiCards::drawSummary(CardPreSummary cardPreSummary) {
    this->resetOffset();

    if (outsideScreen())
        return {};

    if (mediaFirst == 0)
        mediaFirst = -1;

    if (cardPreSummary.height == 0) {
        textData = texts->getTextData(cardPreSummary.text, Body1);
        heightOffset = textData.height + CARDS_DEFAULT_PADDING + CARDS_DEFAULT_PADDING;
    }
    else {
        heightOffset = cardPreSummary.height;
    }

    vita2d_draw_rectangle(x, y - CARDS_DEFAULT_PADDING, width, heightOffset + CARDS_DEFAULT_PADDING, this->selected ? CARDS_DEFAULT_COLOR_SELECTED : CARDS_DEFAULT_COLOR_BACKGROUND);

    texts->draw(x + CARDS_DEFAULT_PADDING, y + CARDS_DEFAULT_PADDING, Body1, CARDS_DEFAULT_COLOR_SUBHEAD_TEXT, cardPreSummary.text);


    zoneEvent.x = x;
    zoneEvent.y = y;
    zoneEvent.width = width;
    zoneEvent.height = heightOffset;

    this->height += heightOffset;

    return zoneEvent;
}

ZoneEvent UiCards::drawSummary(std::string text, int height) {
    cardPreSummary = this->preSummaryTitle(std::move(text), width, height);
    return this->drawSummary(cardPreSummary);
}



CardPrePrimaryTitle UiCards::prePrimaryTitle(std::string headerText, std::string subHead, int width, int height) {
    headerText = texts->applyTextWidthLimit(headerText, width - (CARDS_DEFAULT_PADDING * 2), texts->getTextStyleData(H6));
    subHead = texts->applyTextWidthLimit(subHead, width - (CARDS_DEFAULT_PADDING * 2), texts->getTextStyleData(Body1));


    if (height > 0) {
        textData = texts->getTextData(headerText, H6);
        heightHeaderText = textData.height;
        textData = texts->getTextData(subHead, Body1);
        heightSubHead = textData.height;

        if (heightHeaderText + heightSubHead > (height - CARDS_DEFAULT_PADDING)) {
            while (heightHeaderText + heightSubHead > (height - CARDS_DEFAULT_PADDING)) {
                if (heightHeaderText > (int)texts->getTextStyleData(H6).size) {
                    heightHeaderText -= texts->getTextStyleData(H6).size;
                }
                if (heightSubHead > (int)texts->getTextStyleData(Body1).size) {
                    heightSubHead -= texts->getTextStyleData(Body1).size;
                }
            }
        }

        showedText = texts->applyTextHeightLimitCut(headerText, heightHeaderText, texts->getTextStyleData(H6), TEXT_LIMIT_START);
        if (headerText.length() > showedText.length()) {
            showedText.append("...");
        }
        headerText = showedText;

        showedText = texts->applyTextHeightLimitCut(subHead, heightSubHead, texts->getTextStyleData(Body1), TEXT_LIMIT_START);
        if (subHead.length() > showedText.length()) {
            showedText.append("...");
        }
        subHead = showedText;
    }

    cardPrePrimaryTitle.headerText = headerText;
    cardPrePrimaryTitle.subHead = subHead;
    cardPrePrimaryTitle.height = height;

    return cardPrePrimaryTitle;
}

CardPreSummary UiCards::preSummaryTitle(std::string text, int width, int height) {
    text = texts->applyTextWidthLimit(text, width - (CARDS_DEFAULT_PADDING), texts->getTextStyleData(Body1));
    if (height > 0) {
        text = texts->applyTextHeightLimitCut(text, height - (CARDS_DEFAULT_PADDING * 2), texts->getTextStyleData(Body1), TEXT_LIMIT_START);
        text.append("...");
    }

    cardPreSummary.text = text;
    cardPreSummary.height = height;

    return cardPreSummary;
}