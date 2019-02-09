#ifndef VITAMATERIALKIT_UIEVENT_HH
#define VITAMATERIALKIT_UIEVENT_HH

#include "../utils/UtilsTouch.hpp"

typedef struct ZoneEvent {
    int x;
    int y;
    int width;
    int height;
    bool selector;
} ZoneEvent;

class UiEvent {
public:
    static bool onPad(ZoneEvent zoneEvent, bool button);
    static bool onTouch(ZoneEvent zoneEvent, SceIVector2 touchInfo);
};


#endif //VITAMATERIALKIT_UIEVENT_HH
