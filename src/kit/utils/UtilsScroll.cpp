#include "UtilsScroll.hh"

UtilsScroll::UtilsScroll(UtilsTouch *touch) : touch(touch) {}


void UtilsScroll::create(std::string channel, ScrollDirection scrollDirection, int min, int max, int xZone, int yZone, int widthZone, int heightZone) {
    ScrollChannelData scrollChannelData;

    scrollChannelData.scrollDirection = scrollDirection;
    scrollChannelData.max = max;
    scrollChannelData.min = min;
    scrollChannelData.value = 0;

    scrollChannelData.xZone = xZone;
    scrollChannelData.yZone = yZone;
    scrollChannelData.widthZone = widthZone;
    scrollChannelData.heightZone = heightZone;

    channels[channel] = scrollChannelData;
}

void UtilsScroll::remove(std::string channel) {
    channels.erase(channel);
}


void UtilsScroll::controller(std::string channel, bool decreaseTrigger, bool increaseTrigger, int speed) {
    if (touch != nullptr) {
        if(touch->lastTouchPoint.x <= channels[channel].xZone + channels[channel].widthZone
        && touch->lastTouchPoint.x >= channels[channel].xZone
        && touch->lastTouchPoint.y <= channels[channel].yZone + channels[channel].heightZone
        && touch->lastTouchPoint.y >= channels[channel].yZone){

            channels[channel].value -= (channels[channel].scrollDirection == SCROLL_DIR_X) ? touch->scrollDirX : touch->scrollDirY;

        }
    }

    if (decreaseTrigger) {
        channels[channel].value -= speed;
    }
    if (increaseTrigger) {
        channels[channel].value += speed;
    }

    if(channels[channel].value < channels[channel].min) {
        channels[channel].value = channels[channel].min;
    }

    if (channels[channel].value > channels[channel].max) {
        channels[channel].value = channels[channel].max;
    }

}

int UtilsScroll::getScroll(std::string channel) {
    return channels[channel].value;
}


