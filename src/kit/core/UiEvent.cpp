#include "UiEvent.hh"

bool UiEvent::onPad(ZoneEvent zoneEvent, bool button) {
    return zoneEvent.selector && button;
}

bool UiEvent::onTouch(ZoneEvent zE, SceIVector2 touchInfo) {
    return (touchInfo.x > zE.x && touchInfo.y > zE.y && touchInfo.x < zE.x + zE.width && touchInfo.y < zE.y + zE.height);
}
