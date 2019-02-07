#include "UiTheme.hpp"

UiTheme::UiTheme() = default;

UiTheme::UiTheme(const colorSchemeHEX &primary, const colorSchemeHEX &secondary) {

    this->primaryHEX = primary;
    this->secondaryHEX = secondary;

    this->primaryRGBA = this->colorSchemeHEXToColorShemeRGBA(this->primaryHEX);
    this->secondaryRGBA = this->colorSchemeHEXToColorShemeRGBA(this->secondaryHEX);

}

unsigned int UiTheme::convertHexToRGBA(const char *hex, unsigned int alpha) {
    int r, g, b;
    sscanf(hex, "#%02x%02x%02x", &r, &g, &b);
    return RGBA8(r, g, b, alpha);
}

colorSchemeRGBA UiTheme::colorSchemeHEXToColorShemeRGBA(colorSchemeHEX hex) {
    colorSchemeRGBA rgba;

    rgba.normal = this->convertHexToRGBA(hex.normal);
    rgba.dark = this->convertHexToRGBA(hex.dark);
    rgba.light = this->convertHexToRGBA(hex.light);
    rgba.text = this->convertHexToRGBA(hex.text);

    return rgba;
}

const colorSchemeHEX &UiTheme::getPrimaryHEX() const {
    return primaryHEX;
}

const colorSchemeHEX &UiTheme::getSecondaryHEX() const {
    return secondaryHEX;
}

const colorSchemeRGBA &UiTheme::getPrimaryRGBA() const {
    return primaryRGBA;
}

const colorSchemeRGBA &UiTheme::getSecondaryRGBA() const {
    return secondaryRGBA;
}




