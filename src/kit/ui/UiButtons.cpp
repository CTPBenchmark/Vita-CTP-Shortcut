#include <utility>


#include "UiButtons.hpp"

UiButtons::UiButtons(UiTheme *theme) {
    this->theme = theme;
    this->texts = new UiTexts();
    this->icons = new UiIcons();
}

UiButtons::UiButtons(UiTheme *theme, TextStyle textStyle) {
    this->theme = theme;
    this->texts = new UiTexts();
    this->icons = new UiIcons();
    this->textStyle = textStyle;
}

UiButtons::UiButtons(UiTheme *theme, UiTexts *texts, UiIcons *icons) {
    this->theme = theme;
    this->texts = texts;
    this->icons = icons;
}

UiButtons::UiButtons(UiTheme *theme, UiTexts *texts, UiIcons *icons, TextStyle textStyle) {
    this->theme = theme;
    this->texts = texts;
    this->icons = icons;
    this->textStyle = textStyle;
}

ZoneEvent UiButtons::textDraw(std::string text, int x, int y, bool selected, const char* icon) {
    textData = texts->getTextData(text, textStyle);

    if (strlen(icon) > 0) {
        icons->draw(icon, x + 15, y + 6, ICON_SECONDARY, 30);
        texts->draw(x + 56, y + 12, textStyle, TEXT_SECONDARY, text);

        zoneEvent.width = textData.width + 76;
        zoneEvent.height = textData.height + 20;
    }
    else {
        texts->draw(x + 20, y + 12, textStyle, TEXT_SECONDARY, text);

        zoneEvent.width = textData.width + 40;
        zoneEvent.height = textData.height + 20;
    }

    zoneEvent.x = x;
    zoneEvent.y = y;
    zoneEvent.selector = selected;

    return zoneEvent;
}


ZoneEvent UiButtons::outlinedDraw(std::string text, int x, int y, bool selected, const char *icon) {
    textData = texts->getTextData(text, textStyle);

    if (strlen(icon) > 0) {
        this->drawOutlinedRectangle(x, y, textData.width + 76, textData.height + 20, selected ? theme->getPrimaryRGBA().normal : theme->getSecondaryRGBA().normal);
        this->textDraw(text, x, y, false, icon);
    }
    else {
        this->drawOutlinedRectangle(x, y, textData.width + 40, textData.height + 20, selected ? theme->getPrimaryRGBA().normal : theme->getSecondaryRGBA().normal);
        this->textDraw(text, x, y, false);
    }

    zoneEvent.x = x;
    zoneEvent.y = y;
    zoneEvent.selector = selected;
    return zoneEvent;
}


ZoneEvent UiButtons::containedDraw(std::string text, int x, int y, bool selected, const char *icon) {
    textData = texts->getTextData(text, textStyle);

    if (strlen(icon) > 0) {
        vita2d_draw_rectangle(x, y, textData.width + 76, textData.height + 20, selected ? theme->getPrimaryRGBA().normal : theme->getSecondaryRGBA().normal);
        this->textDraw(text, x, y, false, icon);

        zoneEvent.width = textData.width + 76;
        zoneEvent.height = textData.height + 20;
    }
    else {
        vita2d_draw_rectangle(x, y, textData.width + 40, textData.height + 20, selected ? theme->getPrimaryRGBA().normal : theme->getSecondaryRGBA().normal);
        this->textDraw(text, x, y, false);

        zoneEvent.width = textData.width + 40;
        zoneEvent.height = textData.height + 20;
    }

    zoneEvent.x = x;
    zoneEvent.y = y;
    zoneEvent.selector = selected;

    return zoneEvent;
}

ZoneEvent UiButtons::floatDraw(const char *icon, int x, int y, bool selected, std::string text) {

    if (text.length() > 0) {
        TextData textData = texts->getTextData(text, textStyle);
        int circleHeight = (textData.height + 20) / 2;

        vita2d_draw_fill_circle(x + circleHeight, y + circleHeight, circleHeight, selected ? theme->getPrimaryRGBA().normal : theme->getSecondaryRGBA().normal);
        vita2d_draw_rectangle(x + textData.height, y, textData.width + 30, textData.height + 20, selected ? theme->getPrimaryRGBA().normal : theme->getSecondaryRGBA().normal);
        vita2d_draw_fill_circle(x + circleHeight + textData.width + 30, y + circleHeight, circleHeight, selected ? theme->getPrimaryRGBA().normal : theme->getSecondaryRGBA().normal);

        this->textDraw(text, x, y, false, icon);

        zoneEvent.width = textData.width + 76;
        zoneEvent.height = textData.height + 20;
    }
    else {
        vita2d_draw_fill_circle(x + 25, y + 25, 25, selected ? theme->getPrimaryRGBA().normal : theme->getSecondaryRGBA().normal);
        icons->draw(icon, x + 10, y + 8, ICON_SECONDARY, 30);

        zoneEvent.width = 50;
        zoneEvent.height = 50;
    }

    zoneEvent.x = x;
    zoneEvent.y = y;
    zoneEvent.selector = selected;

    return zoneEvent;
}



void UiButtons::drawOutlinedRectangle(int x, int y, int w, int h, unsigned int color) {
    x += 1;
    y += 1;
    w -= 1;
    h -= 1;
    vita2d_draw_line(x, y, x + w, y, color); //top
    vita2d_draw_line(x + w, y, x + w, y + h, color); //right
    vita2d_draw_line(x, y + h, x + w, y + h, color); //bottom
    vita2d_draw_line(x, y, x, y + h, color); //left
}



