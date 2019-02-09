
#include "UiRadioBoxes.hh"

UiRadioBoxes::UiRadioBoxes(UiTheme *theme) : UiParentBoxes(theme) {}
UiRadioBoxes::UiRadioBoxes(UiTheme *theme, UiIcons *icons) : UiParentBoxes(theme, icons) {}
UiRadioBoxes::UiRadioBoxes(UiTheme *theme, UiIcons *icons, UiTexts *texts) : UiParentBoxes(theme, icons,
                                                                                                    texts) {}

ZoneEventRadioBoxes UiRadioBoxes::draw(int x, int y, UiRadioBoxesStatus status, bool selector, TypeTheme typeTheme, unsigned int size) {
    return this->drawWithText(x, y, status, "", selector, typeTheme, size);
}

ZoneEventRadioBoxes UiRadioBoxes::drawWithText(int x, int y, UiRadioBoxesStatus status, std::string text, bool selector, TypeTheme typeTheme, unsigned int size) {
    zoneEvent.x = x;
    zoneEvent.y = y;
    zoneEvent.width = size * 2;
    zoneEvent.height = size * 2;
    zoneEvent.selector = selector;
    zoneEvent.status = status;

    this->drawSelector(x, y, selector, typeTheme);

    if (status == RADIOBOX_CHECKED) {
        this->drawBoxButton(x, y,  ICON_MDI_RADIOBOX_MARKED, typeTheme, size);
    }
    else {
        this->drawBoxButton(x, y, ICON_MDI_RADIOBOX_BLANK, BOXES_DEFAULT_COLOR_UNCHECKED, size);
    }

    if (!text.empty()) {
        zoneEvent.width += this->drawText(x, y , size, text).width;
    }


    return zoneEvent;
}


UiRadioBoxesStatus UiRadioBoxes::onPadAuto(ZoneEventRadioBoxes zoneEvent, bool button) {
    if (UiEvent::onPad(zoneEvent, button)) {
        if (zoneEvent.status == RADIOBOX_UNCHECKED) {
            return RADIOBOX_CHECKED;
        }
        else {
            return RADIOBOX_UNCHECKED;
        }
    }
    return zoneEvent.status;
}

UiRadioBoxesStatus UiRadioBoxes::onTouchAuto(ZoneEventRadioBoxes zoneEvent, SceIVector2 touchInfo) {
    if (UiEvent::onTouch(zoneEvent, touchInfo)) {
        if (zoneEvent.status == RADIOBOX_UNCHECKED) {
            return RADIOBOX_CHECKED;
        }
        else {
            return RADIOBOX_UNCHECKED;
        }
    }
    return zoneEvent.status;
}



