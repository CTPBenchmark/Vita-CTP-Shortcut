#ifndef CTP_SHORTCUT_LAYOUTTHEME_HH
#define CTP_SHORTCUT_LAYOUTTHEME_HH

#include <vita2d.h>
#include "../utils/Config.hh"
#include "Background.hh"

class LayoutTheme {
private:
    Config *config;
    SceDateTime time;
    vita2d_texture *logo;
    vita2d_texture *wallolo;
    Background *background;

    vita2d_texture *initLogo();
    int getIconColor();
    int getBackgroundColor();
public:
    LayoutTheme(Config *config);
    void display();
};


#endif //CTP_SHORTCUT_LAYOUTTHEME_HH
