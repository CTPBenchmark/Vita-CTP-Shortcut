#ifndef VITAMATERIALKIT_UTILS_HH
#define VITAMATERIALKIT_UTILS_HH


#include "utils/CTPApi.hh"
#include "utils/Config.hh"
#include "utils/WebModal.hh"
#include "kit/utils/UtilsTouch.hh"
#include "kit/utils/UtilsPad.hh"
#include "kit/utils/UtilsI18n.hh"
#include "kit/utils/UtilsIME.hh"
#include "kit/utils/UtilsPadTouchCtrl.hh"
#include "kit/utils/UtilsScroll.hh"


class Utils {
protected:
    virtual void init();
public:
    UtilsTouch *touch;
    UtilsPad *pad;
    Config *config;
    UtilsI18n *i18n;
    UtilsIME *ime;
    WebModal *webModal;
    UtilsPadTouchCtrl *ptc;
    UtilsScroll *scroll;

    Utils();
    virtual void read();
};


#endif //VITAMATERIALKIT_UTILS_HH
