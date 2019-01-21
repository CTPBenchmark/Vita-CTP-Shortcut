#ifndef VITAMATERIALKIT_UTILS_HH
#define VITAMATERIALKIT_UTILS_HH


#include "utils/I18n.hpp"
#include "utils/Touch.hpp"
#include "utils/Pad.hpp"

class Utils {
protected:
    virtual void init();
public:
    Touch *touch;
    Pad *pad;
    I18n *i18n;
    Utils();
    virtual void read();
};


#endif //VITAMATERIALKIT_UTILS_HH
