#ifndef VITAMATERIALKIT_UTILS_HH
#define VITAMATERIALKIT_UTILS_HH


#include "../utils/CTPApi.hh"
#include "../utils/Config.hh"
#include "../utils/WebModal.hh"
#include "utils/UtilsTouch.hh"
#include "utils/UtilsPad.hh"
#include "utils/UtilsI18n.hh"
#include "utils/UtilsIME.hh"
#include "utils/UtilsPadTouchCtrl.hh"
#include "utils/UtilsScroll.hh"


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
