#ifndef VITAMATERIALKIT_UICHECKBOXES_HH
#define VITAMATERIALKIT_UICHECKBOXES_HH


#include "UiTheme.hpp"
#include "UiIcons.hpp"
#include "../core/UiEvent.hh"

#define DEFAULT_CHECKBOX_SIZE 40

typedef enum UiCheckboxesStatus {
    UNCHECKED = 0,
    INDERTERMINATE = -1,
    CHECKED = 1
} UiCheckboxesStatus;

typedef struct ZoneEventCheckbox : public ZoneEvent {
    UiCheckboxesStatus status;
} ZoneEventCheckboxes;

class UiCheckboxes : public UiEvent {
private:
    UiTheme *theme;
    UiIcons *icons;
    ZoneEventCheckboxes zoneEvent;
    unsigned int selectorColor;
public:
    UiCheckboxes(UiTheme *theme);
    UiCheckboxes(UiTheme *theme, UiIcons *icons);

    ZoneEventCheckbox draw(int x, int y, UiCheckboxesStatus status, bool selector, unsigned int size = DEFAULT_CHECKBOX_SIZE);

    UiCheckboxesStatus onPadAuto(ZoneEventCheckboxes zoneEvent, bool button);
    UiCheckboxesStatus onTouchAuto(ZoneEventCheckboxes zoneEvent, vector2 touchInfo);

    bool onPad(ZoneEventCheckboxes zoneEvent, bool button);
    bool onTouch(ZoneEventCheckboxes zoneEvent, vector2 touchInfo);
};


#endif //VITAMATERIALKIT_UICHECKBOXES_HH
