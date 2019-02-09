#ifndef VITAMATERIALKIT_UICHECKBOXES_HH
#define VITAMATERIALKIT_UICHECKBOXES_HH


#include "UiTheme.hpp"
#include "UiIcons.hpp"
#include "../core/UiEvent.hh"
#include "parent/UiParentBoxes.hh"

typedef enum UiCheckboxesStatus {
    CHECKBOX_UNCHECKED = 0,
    CHECKBOX_INDERTERMINATE = -1,
    CHECKBOX_CHECKED = 1
} UiCheckboxesStatus;


typedef struct ZoneEventCheckboxes : public ZoneEvent {
    UiCheckboxesStatus status;
} ZoneEventCheckboxes;

class UiCheckboxes : public UiEvent, UiParentBoxes {
private:
    ZoneEventCheckboxes zoneEvent;
public:
    UiCheckboxes(UiTheme *theme);
    UiCheckboxes(UiTheme *theme, UiIcons *icons);
    UiCheckboxes(UiTheme *theme, UiIcons *icons, UiTexts *texts);

    ZoneEventCheckboxes draw(int x, int y, UiCheckboxesStatus status, bool selector, TypeTheme typeTheme = THEME_PRIMARY, unsigned int size = BOXES_DEFAULT_SIZE);
    ZoneEventCheckboxes drawWithText(int x, int y, UiCheckboxesStatus status, std::string text, bool selector, TypeTheme typeTheme = THEME_PRIMARY, unsigned int size = BOXES_DEFAULT_SIZE);

    UiCheckboxesStatus onPadAuto(ZoneEventCheckboxes zoneEvent, bool button);
    UiCheckboxesStatus onTouchAuto(ZoneEventCheckboxes zoneEvent, SceIVector2 touchInfo);
};


#endif //VITAMATERIALKIT_UICHECKBOXES_HH
