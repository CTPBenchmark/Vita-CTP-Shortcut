#include "LayoutTheme.hh"

extern unsigned char _binary_assets_img_WalloloRep_png_start;

extern unsigned char _binary_assets_img_LogoCtp_png_start;
extern unsigned char _binary_assets_img_LogoCtpHalloween_png_start;
extern unsigned char _binary_assets_img_LogoCtpAnniversary_png_start;
extern unsigned char _binary_assets_img_LogoCtpChristmas_png_start;

LayoutTheme::LayoutTheme(Config *config) : config(config) {
    logo = this->initLogo();

    wallolo = vita2d_load_PNG_buffer(&_binary_assets_img_WalloloRep_png_start);
    background = new Background(wallolo, this->getBackgroundColor(), this->getIconColor());
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

    //Halloween
    if (time.month == 10 && time.day > 15)
        return BACKGROUND_COLOR_HALLOWEEN;

    //Christmas
    if (time.month == 12 && (time.day > 14 && time.day < 28))
        return BACKGROUND_COLOR_ANNIVERSARY;

    //CTP Anniversary
    if (time.month == 12 && time.day == 14)
        return BACKGROUND_COLOR_ANNIVERSARY;

    return BACKGROUND_COLOR_CTP;
}

int LayoutTheme::getIconColor() {

    //Halloween
    if (time.month == 10 && time.day > 15)
        return LOGO_COLOR_HALLOWEEN;

    //Christmas
    if (time.month == 12 && (time.day > 14 && time.day < 28))
        return LOGO_COLOR_CHRISTMAS;

    //CTP Anniversary
    if (time.month == 12 && time.day == 14)
        return LOGO_COLOR_ANNIVERSARY;

    return LOGO_COLOR_CTP;
}

void LayoutTheme::display() {
    background->display();
    vita2d_draw_texture(logo, 25, 25);
}

