#ifndef VITAMATERIALKIT_UTILS_HH
#define VITAMATERIALKIT_UTILS_HH


#include "utils/I18n.hpp"
#include "utils/Touch.hpp"
#include "utils/Pad.hpp"
#include "../utils/Config.hh"
#include "../utils/WebModal.hh"
#include "utils/IME.hpp"

class Utils {
protected:
    virtual void init();
public:
    int touchMode = 1;
    int selector = -1;
    Touch *touch;
    Pad *pad;
    Config *config;
    I18n *i18n;
    IME *ime;
    WebModal *webModal;
    Utils();
    virtual void read();
};


#endif //VITAMATERIALKIT_UTILS_HH
