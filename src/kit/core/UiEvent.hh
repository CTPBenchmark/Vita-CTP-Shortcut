#ifndef VITAMATERIALKIT_UIEVENT_HH
#define VITAMATERIALKIT_UIEVENT_HH

#include "../utils/Touch.hpp"

typedef struct ZoneEvent {
    int x;
    int y;
    int width;
    int height;
    bool selector;
} ZoneEvent;

class UiEvent {
protected:
    ZoneEvent zoneEvent;
public:
    bool onPad(ZoneEvent zoneEvent, bool button);
    bool onTouch(ZoneEvent zoneEvent, vector2 touchInfo);
};


#endif //VITAMATERIALKIT_UIEVENT_HH
