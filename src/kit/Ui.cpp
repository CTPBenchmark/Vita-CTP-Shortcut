#include "Ui.hh"

Ui::Ui() {
    this->initTheme();
    this->init();
}

void Ui::init() {
    this->theme         = new UiTheme(primaryThemeColor, secondaryThemeColor);
    this->texts         = new UiTexts(this->theme);
    this->icons         = new UiIcons(this->theme);
    this->buttons       = new UiButtons(this->theme, this->texts, this->icons);
    this->checkboxes    = new UiCheckboxes(this->theme, this->icons);
    this->textFields    = new UiTextFields(this->theme, this->texts, this->icons);
}

void Ui::initTheme() {
    //https://material.io/tools/color/#!/?view.left=0&view.right=0&primary.color=7837e5&secondary.color=673AB7 by Tuxbot123
    primaryThemeColor.normal = "#7837e5";
    primaryThemeColor.dark = "#3e00b2";
    primaryThemeColor.light = "#af67ff";
    primaryThemeColor.text = "#ffffff";
    secondaryThemeColor.normal = "#673ab7";
    secondaryThemeColor.dark = "#320b86";
    secondaryThemeColor.light = "#9a67ea";
    secondaryThemeColor.text = "#ffffff";
}