#include "UiCheckboxes.hh"

UiCheckboxes::UiCheckboxes(UiTheme *theme) {
    this->theme = theme;
    icons = new UiIcons();
    this->selectorColor = theme->convertHexToRGBA(theme->getSecondaryHEX().light, 150);
}

UiCheckboxes::UiCheckboxes(UiTheme *theme, UiIcons *icons) : theme(theme), icons(icons) {
    this->theme = theme;
    this->icons = icons;
    this->selectorColor = theme->convertHexToRGBA(theme->getSecondaryHEX().light, 150);
}

ZoneEventCheckboxes UiCheckboxes::draw(int x, int y, UiCheckboxesStatus status, bool selector, unsigned int size) {
    zoneEvent.x = x;
    zoneEvent.y = y;
    zoneEvent.width = size * 2;
    zoneEvent.height = size * 2;
    zoneEvent.selector = selector;
    zoneEvent.status = status;


    if (selector) {
        vita2d_draw_fill_circle(x + size, y + size, size, selectorColor);
    }

    if (status == INDERTERMINATE || status == CHECKED) {
        icons->draw(ICON_MDI_CHECKBOX_BLANK, x + (size / 2), y + (size / 2), (unsigned int) RGBA8(255, 255, 255, 255), size);
    }


    if (status == UNCHECKED) {
        icons->draw(ICON_MDI_CHECKBOX_BLANK_OUTLINE, x + (size / 2), y + (size / 2), (unsigned int) RGBA8(92, 92, 92, 255), size);
    }
    else if (status == INDERTERMINATE) {
        icons->draw(ICON_MDI_MINUS_BOX, x + (size / 2), y + (size / 2), theme->getSecondaryRGBA().dark, size);
    }
    else {
        icons->draw(ICON_MDI_CHECKBOX_MARKED, x + (size / 2), y + (size / 2), theme->getSecondaryRGBA().dark, size);
    }


    return zoneEvent;
}


UiCheckboxesStatus UiCheckboxes::onPadAuto(ZoneEventCheckboxes zoneEvent, bool button) {
    if (UiEvent::onPad(zoneEvent, button)) {
        if (zoneEvent.status == UNCHECKED || zoneEvent.status == INDERTERMINATE) {
            return CHECKED;
        }
        else {
            return UNCHECKED;
        }
    }
    return zoneEvent.status;
}

UiCheckboxesStatus UiCheckboxes::onTouchAuto(ZoneEventCheckboxes zoneEvent, vector2 touchInfo) {
    if (UiEvent::onTouch(zoneEvent, touchInfo)) {
        if (zoneEvent.status == UNCHECKED || zoneEvent.status == INDERTERMINATE) {
            return CHECKED;
        }
        else {
            return UNCHECKED;
        }
    }
    return zoneEvent.status;
}
