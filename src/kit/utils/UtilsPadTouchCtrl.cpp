#include "UtilsPadTouchCtrl.hh"

UtilsPadTouchCtrl::UtilsPadTouchCtrl(UtilsPad *pad) {
    touchMode = false;
    ctrlMode = true;
}


UtilsPadTouchCtrl::UtilsPadTouchCtrl(UtilsPad *pad, UtilsTouch *touch) : pad(pad), touch(touch) {
    model = sceKernelGetModel();

    if (model == SCE_KERNEL_MODEL_VITATV) {
        touchMode = false;
        ctrlMode = true;
    }
    else {
        touchMode = true;
        ctrlMode = false;
    }
}

void UtilsPadTouchCtrl::controller() {

    if (this->touch != nullptr) {
        if (this->touch->clicking && ctrlMode) {
            yOldItem = yItem;
            xOldItem = xItem;

            yItem = -1;
            xItem = -1;

            touchMode = true;
            ctrlMode = false;
        }
    }

    if (this->pad->held.clicking && touchMode) {
        touchMode = false;
        ctrlMode = true;

        yItem = yOldItem;
        xItem = xOldItem;
    }

    if (ctrlMode) {
        //add support for analog stick
        if (pad->pressed.down) {
            yItem++;
        }
        if (pad->pressed.up) {
            yItem--;
        }
        if (pad->pressed.right) {
            xItem++;
        }
        if (pad->pressed.left) {
            xItem--;
        }

        if (yItem > yLimit) {
            yItem = 1;
        }
        if (yItem < 1) {
            yItem = yLimit;
        }

        if (xItem > xLimit) {
            xItem = 1;
        }
        if (xItem < 1) {
            xItem = xLimit;
        }

        for (auto& limit: yLimits) {

            if (xItem == limit.first) {
                if (yItem > limit.second.second) {
                    yItem = limit.second.second;
                }
                if (yItem < limit.second.first) {
                    yItem = limit.second.first;
                }
            }
        }

        for (auto& limit: xLimits) {

            if (yItem == limit.first) {
                if (xItem > limit.second.second) {
                    xItem = limit.second.second;
                }
                if (xItem < limit.second.first) {
                    xItem = limit.second.first;
                }
            }
        }
    }
}



void UtilsPadTouchCtrl::setLimit(PadTouchCtrlType type, int limit) {
    this->clearLimits();
    if (type == PADTOUCHCTRL_TYPE_X) {
        xLimit = limit;
    }
    else {
        yLimit = limit;
    }
}


void UtilsPadTouchCtrl::setLimit(PadTouchCtrlType type, int limit, int start) {
    this->setLimit(type, limit);
    if (type == PADTOUCHCTRL_TYPE_X) {
        xOldItem = start;
        if (ctrlMode) {
            xItem = start;
        }
    }
    else {
        yOldItem = start;
        if (ctrlMode) {
            yItem = start;
        }
    }
}

void UtilsPadTouchCtrl::setLimit(int xLimit, int yLimit) {
    this->clearLimits();
    this->xOldItem = xLimit;
    this->yOldItem = yLimit;
}

void UtilsPadTouchCtrl::setLimit(int xLimit, int yLimit, int xStart, int yStart) {
    this->setLimit(xLimit, yLimit);
    xItem = xStart;
    yItem = yStart;
    if (ctrlMode) {
        xItem = xStart;
        yItem = yStart;
    }
}

bool UtilsPadTouchCtrl::isX(int x) {
    return xItem == x;
}

bool UtilsPadTouchCtrl::isY(int y) {
    return yItem == y;
}

bool UtilsPadTouchCtrl::isXY(int x, int y) {
    return isX(x) && isY(y);
}

bool UtilsPadTouchCtrl::isX(PadTouchCtrlIs x) {
    if (x == PADTOUCHCTRL_IS_FIRST) {
        return xItem == 1;
    }
    return xItem == xLimit;
}

bool UtilsPadTouchCtrl::isY(PadTouchCtrlIs y) {
    if (y == PADTOUCHCTRL_IS_FIRST) {
        return yItem == 1;
    }
    return yItem == yLimit;
}

bool UtilsPadTouchCtrl::isXY(PadTouchCtrlIs x, PadTouchCtrlIs y) {
    return isX(x) && isY(y);
}

bool UtilsPadTouchCtrl::isXY(int x, PadTouchCtrlIs y) {
    return isX(x) && isY(y);
}

bool UtilsPadTouchCtrl::isXY(PadTouchCtrlIs x, int y) {
    return isX(x) && isY(y);
}

void UtilsPadTouchCtrl::addLimit(PadTouchCtrlType type, int line, int first, int last) {
    //rework add limit to add 4 conditions !
    if (type == PADTOUCHCTRL_TYPE_X) {
        xLimits.emplace(xLimits.begin(), line, std::make_pair(first, last));
    }
    else {
        yLimits.emplace(yLimits.begin(), line, std::make_pair(first, last));
    }
}


bool UtilsPadTouchCtrl::isTouchMode() const {
    return touchMode;
}

bool UtilsPadTouchCtrl::isCtrlMode() const {
    return ctrlMode;
}

void UtilsPadTouchCtrl::clearLimits() {
    xLimits.clear();
    yLimits.clear();
}


