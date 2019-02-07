#ifndef VITA_MATERIAL_KIT_UI_BUTTON_HPP
#define VITA_MATERIAL_KIT_UI_BUTTON_HPP

#include "../utils/Touch.hpp"
#include "../utils/Pad.hpp"

#include "UiTexts.hpp"
#include "UiIcons.hpp"
#include "UiTheme.hpp"
#include "../core/UiEvent.hh"

class UiButtons : public UiEvent {
private:
    UiIcons *icons;
    UiTexts *texts;
    UiTheme *theme;
    TextData textData;
    ZoneEvent zoneEvent;
    TextStyle textStyle = Button;

    void drawOutlinedRectangle(int x, int y, int w, int h, unsigned int color);
    void textDrawFinal(std::string text, int x, int y, TypeTheme typeTheme = THEME_PRIMARY, const char* icon = "");
public:
    UiButtons(UiTheme *theme);
    UiButtons(UiTheme *theme, UiTexts *texts, UiIcons *icons);
    UiButtons(UiTheme *theme, TextStyle textStyle);
    UiButtons(UiTheme *theme, UiTexts *texts, UiIcons *icons, TextStyle textStyle);

    ZoneEvent textDraw(std::string text, int x, int y, TypeTheme typeTheme = THEME_PRIMARY, bool selected = false, const char* icon = "");

    ZoneEvent outlinedDraw(std::string text, int x, int y, TypeTheme typeTheme = THEME_PRIMARY, bool selected = false, const char* icon = "");

    ZoneEvent containedDraw(std::string text, int x, int y, TypeTheme typeTheme = THEME_PRIMARY, bool selected = false, const char *icon = "");

    ZoneEvent floatDraw(const char *icon, int x, int y, TypeTheme typeTheme = THEME_PRIMARY, bool selected = false, std::string text = "");

};


#endif //VITA_MATERIAL_KIT_UI_BUTTON_HPP
