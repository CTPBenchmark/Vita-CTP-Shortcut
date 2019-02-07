#include "LayoutTheme.hh"

extern unsigned char _binary_assets_img_WalloloRep_png_start;

extern unsigned char _binary_assets_img_LogoCtp_png_start;
extern unsigned char _binary_assets_img_LogoCtpHalloween_png_start;
extern unsigned char _binary_assets_img_LogoCtpAnniversary_png_start;
extern unsigned char _binary_assets_img_LogoCtpChristmas_png_start;

LayoutTheme::LayoutTheme(Config *config) : config(config) {
    logo = this->initLogo();

    wallolo = vita2d_load_PNG_buffer(&_binary_assets_img_WalloloRep_png_start);
    background = new Background(wallolo, this->getBackgroundColor(), this->getIconColor(), this->getForegroundColor(), this->getSpeed());
}

vita2d_texture *LayoutTheme::initLogo() {
    //Halloween
    if (time.month == 10 && time.day > 15)
        return vita2d_load_PNG_buffer(&_binary_assets_img_LogoCtpHalloween_png_start);

    //CTP Anniversary
    if (time.month == 12 && time.day == 14)
        return vita2d_load_PNG_buffer(&_binary_assets_img_LogoCtpAnniversary_png_start);

    //Christmas
    if (time.month == 12 && (time.day > 14 && time.day < 28))
        return vita2d_load_PNG_buffer(&_binary_assets_img_LogoCtpChristmas_png_start);

    return vita2d_load_PNG_buffer(&_binary_assets_img_LogoCtp_png_start);
}

int LayoutTheme::getBackgroundColor() {

    if (config->isCustomisation())
        return RGBA8(config->getBackgroundColor().r, config->getBackgroundColor().g, config->getBackgroundColor().b, config->getBackgroundColor().a);

    //Halloween
    if (time.month == 10 && time.day > 15)
        return BACKGROUND_COLOR_HALLOWEEN;

    //Christmas
    if (time.month == 12 && (time.day > 14 && time.day < 28))
        return BACKGROUND_COLOR_CHRISTMAS;

    //CTP Anniversary
    if (time.month == 12 && time.day == 14)
        return BACKGROUND_COLOR_ANNIVERSARY;

    return BACKGROUND_COLOR_CTP;
}

int LayoutTheme::getIconColor() {

    if (config->isCustomisation())
        return RGBA8(config->getIconsColor().r, config->getIconsColor().g, config->getIconsColor().b, config->getIconsColor().a);

    //Halloween
    if (time.month == 10 && time.day > 15)
        return ICONS_COLOR_HALLOWEEN;

    //Christmas
    if (time.month == 12 && (time.day > 14 && time.day < 28))
        return ICONS_COLOR_CHRISTMAS;

    //CTP Anniversary
    if (time.month == 12 && time.day == 14)
        return ICONS_COLOR_ANNIVERSARY;

    return ICONS_COLOR_CTP;
}

int LayoutTheme::getForegroundColor() {
    if (config->isCustomisation())
        return RGBA8(config->getForegroundColor().r, config->getForegroundColor().g, config->getForegroundColor().b, config->getForegroundColor().a);

    return FOREGROUND_COLOR_CTP;
}

float LayoutTheme::getSpeed() {
    if (config->isCustomisation())
        return config->getSpeed();

    return DEFAULT_SPEED;
}

void LayoutTheme::display(bool displayLogo) {
    background->display();

    if (displayLogo) {
        vita2d_draw_texture(logo, 480 - (LOGO_WIDTH / 2), 10);
    }
}



