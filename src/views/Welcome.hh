#ifndef VITAMATERIALKIT_WELCOME_HH
#define VITAMATERIALKIT_WELCOME_HH

#include "../kit/core/View.hh"

class Welcome: public View {
private:
    ZoneEvent buttonsTZE;
    ZoneEvent i18nTZE;
    ZoneEvent iconsTZE;
    ZoneEvent textsTZE;
    ZoneEvent imeTZE;
    ZoneEvent exitTZE;
    int selector;

public:
    Welcome(const char *name);
    void contents() override;
    void controls() override;
};

#endif //VITAMATERIALKIT_WELCOME_HH
