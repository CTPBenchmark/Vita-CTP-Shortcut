#ifndef VITAMATERIALKIT_UTILS_HH
#define VITAMATERIALKIT_UTILS_HH


#include "../utils/Config.hh"
#include "../utils/WebModal.hh"
#include "utils/UtilsTouch.hpp"
#include "utils/UtilsPad.hpp"
#include "utils/UtilsI18n.hpp"
#include "utils/UtilsIME.hpp"
#include "utils/UtilsPadTouchCtrl.hh"


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

    Utils();
    virtual void read();
};


#endif //VITAMATERIALKIT_UTILS_HH
