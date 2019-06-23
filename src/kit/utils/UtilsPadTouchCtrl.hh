#ifndef VITAMATERIALKIT_PADTOUCHCTRL_HH
#define VITAMATERIALKIT_PADTOUCHCTRL_HH

#include <psp2/kernel/sysmem.h>
#include <string>
#include <list>

#include "UtilsPad.hh"
#include "UtilsTouch.hh"
#include "UtilsScroll.hh"

typedef enum PadTouchCtrlType {
    PADTOUCHCTRL_TYPE_X,
    PADTOUCHCTRL_TYPE_Y
} PadTouchCtrlType;

typedef enum PadTouchCtrlIs {
    PADTOUCHCTRL_IS_FIRST,
    PADTOUCHCTRL_IS_LAST
} PadTouchCtrlIs;

typedef enum PadTouchCtrlMode {
    PADTOUCHCTRL_MODE_AUTO,
    PADTOUCHCTRL_MODE_TOUCH,
    PADTOUCHCTRL_MODE_CTRL
} PadTouchCtrlMode;

class UtilsPadTouchCtrl {
private:
    UtilsPad *pad;
    UtilsTouch *touch;
    UtilsScroll *scroll;
    int model;
    int xItem, yItem, xGlobalLimit, yGlobalLimit;
    int xOldItem, yOldItem;
    bool touchMode, ctrlMode;
    PadTouchCtrlMode mode;
    std::map<std::string, int> scrollBuffers;
    std::string debugText;

    std::list <std::pair<int, std::pair<int, int> >> xLimits, yLimits;
    void clearLimits();
    void setMode();
public:

    UtilsPadTouchCtrl(UtilsPad *pad);
    UtilsPadTouchCtrl(UtilsPad *pad, UtilsTouch *touch);
    UtilsPadTouchCtrl(UtilsPad *pad, UtilsTouch *touch, UtilsScroll *scroll);

    void controller();

    void setLimit(PadTouchCtrlType type, int limit);
    void setLimit(PadTouchCtrlType type, int limit, int start);
    void setLimit(int xLimit, int yLimit);
    void setLimit(int xLimit, int yLimit, int xStart, int yStart);

    void updateLimit(PadTouchCtrlType type, int limit);
    void updateStart(PadTouchCtrlType type, int start);
    void updateLimit(int xLimit, int yLimit);
    void updateStart(int xStart, int yStart);

    void addLimit(PadTouchCtrlType type, int line, int first, int last);

    void scrollController(const std::string& channel, int line, int size);

    bool isX(int x);
    bool isX(PadTouchCtrlIs x);
    bool isY(int y);
    bool isY(PadTouchCtrlIs y);

    bool isXY(int x, int y);
    bool isXY(PadTouchCtrlIs x, PadTouchCtrlIs y);
    bool isXY(int x, PadTouchCtrlIs y);
    bool isXY(PadTouchCtrlIs x, int y);

    bool isTouchMode() const;
    bool isCtrlMode() const;

    PadTouchCtrlMode getMode();
    void updateMode(PadTouchCtrlMode mode);

    std::string debug();
};


#endif //VITAMATERIALKIT_PADTOUCHCTRL_HH