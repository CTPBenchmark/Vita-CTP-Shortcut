#ifndef CTP_SHORTCUT_LAYOUTTHEME_HH
#define CTP_SHORTCUT_LAYOUTTHEME_HH

#define LOGO_WIDTH 370

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
    int getForegroundColor();
    float getSpeed();
public:
    LayoutTheme(Config *config);
    void display(bool displayLogo);
    void updateBackground();
};


#endif //CTP_SHORTCUT_LAYOUTTHEME_HH
