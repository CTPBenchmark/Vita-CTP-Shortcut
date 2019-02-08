#include "Customization.hh"

Customization::Customization(const std::string &name) : View(name) {
}

void Customization::contents() {
    if (chosen.empty()) {
        this->contentsDefault();
    }
    else {
        this->contentsCustomizeColors();
    }

}

void Customization::controls() {
    if (chosen.empty()) {
        this->controlsDefault();
    }
    else {
        this->controlsCustomizeColors();
    }
}


void Customization::contentsDefault() {

    vita2d_draw_rectangle(10, 10, 960 - 20, 90, ui->theme->convertHexToRGBA(ui->theme->getPrimaryHEX().dark, 200));
    ui->texts->draw(115, 42, Body1, THEME_PRIMARY, i18nCustomization["customizationInstruction"]);
    customizationCheckboxZE = ui->checkboxes->draw(20, 15, customizationCheckbox, utils->selector == 1);

    if (utils->config->isCustomisation()) {

        backgroundButtonZE = ui->buttons->containedDraw(i18nCustomization["background"], 10, 110, THEME_PRIMARY, utils->selector == 2);
        iconsButtonZE = ui->buttons->containedDraw(i18nCustomization["icons"], 10, 120 + backgroundButtonZE.height, THEME_PRIMARY, utils->selector == 3);
        foregroundButtonZE = ui->buttons->containedDraw(i18nCustomization["foreground"], 10, 130 + backgroundButtonZE.height + iconsButtonZE.height, THEME_PRIMARY, utils->selector == 4);
        speedTextFieldZE = ui->textFields->filledDraw(10, 140 + backgroundButtonZE.height + iconsButtonZE.height + foregroundButtonZE.height, TEXTFIELD_MODE_SINGLE, 100, utils->selector == 5, i18nCustomization["speed"], std::to_string(utils->config->getSpeed()), "", "", 2);
    }

    backButtonZE = ui->buttons->containedDraw(i18nCustomization["save"], 10, 544 - backButtonZE.height - 10, THEME_PRIMARY, utils->selector == CUSTOMIZATION_NUMBER_OF_BUTTONS, ICON_MDI_CHECK);
}

void Customization::controlsDefault() {
    if (utils->touchMode == 1) {
        customizationCheckbox = ui->checkboxes->onTouchAuto(customizationCheckboxZE, utils->touch->lastClickPoint);
    }
    else {
        customizationCheckbox = ui->checkboxes->onPadAuto(customizationCheckboxZE, utils->pad->pressed.cross);
    }

    if ((!utils->config->isCustomisation() && customizationCheckbox == CHECKED) ||
        (utils->config->isCustomisation() && customizationCheckbox == UNCHECKED)) {

        utils->config->setCustomisation(customizationCheckbox == CHECKED);
        CUSTOMIZATION_NUMBER_OF_BUTTONS = utils->config->isCustomisation() ? 7 : 2;

        ui->layoutTheme->updateBackground();
    }


    if (ui->buttons->onTouch(backgroundButtonZE, utils->touch->lastClickPoint) ||
        ui->buttons->onPad(backgroundButtonZE, utils->pad->pressed.cross)) {
        chosen = "background";
        rgbaCustomization = utils->config->getBackgroundColor();
        utils->selector = 1;
    }

    if (ui->buttons->onTouch(iconsButtonZE, utils->touch->lastClickPoint) ||
        ui->buttons->onPad(iconsButtonZE, utils->pad->pressed.cross)) {
        chosen = "icons";
        rgbaCustomization = utils->config->getIconsColor();
        utils->selector = 1;
    }

    if (ui->buttons->onTouch(foregroundButtonZE, utils->touch->lastClickPoint) ||
        ui->buttons->onPad(foregroundButtonZE, utils->pad->pressed.cross)) {
        chosen = "foreground";
        rgbaCustomization = utils->config->getForegroundColor();
        utils->selector = 1;
    }


    if (ui->textFields->onTouch(speedTextFieldZE, utils->touch->lastClickPoint) ||
        ui->textFields->onPad(speedTextFieldZE, utils->pad->pressed.cross)) {
        int speed = utils->config->getSpeed();
        speed = std::stoi(utils->ime->getUserText(i18nCustomization["speed"].c_str(), std::to_string(speed).c_str(), SCE_IME_TYPE_NUMBER, 2));
        if (speed > 99) {
            speed = 99;
        }
        if (speed < 0) {
            speed = 0;
        }
        utils->config->setSpeed(speed);
        ui->layoutTheme->updateBackground();
    }


    if (ui->buttons->onTouch(backButtonZE, utils->touch->lastClickPoint) ||
        utils->pad->pressed.circle ||
        ui->buttons->onPad(backButtonZE, utils->pad->pressed.cross)) {
        utils->config->saveConfig();
        viewsController->setActualView("Settings");
    }



    //pad
    if (utils->touchMode == 0) {
        if (utils->pad->pressed.down) {
            utils->selector++;
        }
        if (utils->pad->pressed.up) {
            utils->selector--;
        }

        if (utils->selector > CUSTOMIZATION_NUMBER_OF_BUTTONS) {
            utils->selector = 1;
        }

        if (utils->selector < 1) {
            utils->selector = CUSTOMIZATION_NUMBER_OF_BUTTONS;
        }
    }
}



void Customization::contentsCustomizeColors() {
    ui->texts->draw(10, 10, H4, ui->theme->getPrimaryRGBA().normal, i18nCustomization[chosen]);

    redZE = ui->textFields->filledDraw(10, 70, TEXTFIELD_MODE_SINGLE, 100, utils->selector == 1, i18nCustomization["red"], std::to_string(rgbaCustomization.r));
    greenZE = ui->textFields->filledDraw(10, 10 + redZE.y + redZE.height, TEXTFIELD_MODE_SINGLE, 100, utils->selector == 2, i18nCustomization["green"], std::to_string(rgbaCustomization.g));
    blueZE = ui->textFields->filledDraw(10, 10 + greenZE.y + greenZE.height, TEXTFIELD_MODE_SINGLE, 100, utils->selector == 3, i18nCustomization["blue"], std::to_string(rgbaCustomization.b));
    alphaZE = ui->textFields->filledDraw(10, 10 + blueZE.y + blueZE.height, TEXTFIELD_MODE_SINGLE, 100, utils->selector == 4, i18nCustomization["alpha"], std::to_string(rgbaCustomization.a));


    backButtonZE = ui->buttons->containedDraw(i18nCustomization["validate"], 960 - backButtonZE.width - 10, 544 - backButtonZE.height - 10, THEME_PRIMARY, utils->selector == 5, ICON_MDI_CONTENT_SAVE);
}

void Customization::controlsCustomizeColors() {


    if (ui->buttons->onTouch(redZE, utils->touch->lastClickPoint) ||
        ui->buttons->onPad(redZE, utils->pad->pressed.cross)) {

        rgbaCustomization.r = getColorPart("red", rgbaCustomization.r);
        this->refreshBackground();
    }

    if (ui->buttons->onTouch(greenZE, utils->touch->lastClickPoint) ||
        ui->buttons->onPad(greenZE, utils->pad->pressed.cross)) {

        rgbaCustomization.g = getColorPart("green", rgbaCustomization.g);
        this->refreshBackground();
    }

    if (ui->buttons->onTouch(blueZE, utils->touch->lastClickPoint) ||
        ui->buttons->onPad(blueZE, utils->pad->pressed.cross)) {

        rgbaCustomization.b = getColorPart("blue", rgbaCustomization.b);
        this->refreshBackground();
    }

    if (ui->buttons->onTouch(alphaZE, utils->touch->lastClickPoint) ||
        ui->buttons->onPad(alphaZE, utils->pad->pressed.cross)) {

        rgbaCustomization.a = getColorPart("alpha", rgbaCustomization.a);
        this->refreshBackground();
    }


    if (ui->buttons->onTouch(backButtonZE, utils->touch->lastClickPoint) ||
        utils->pad->pressed.circle ||
        ui->buttons->onPad(backButtonZE, utils->pad->pressed.cross)) {

        utils->selector = 1;

        chosen.clear();
    }

    //pad
    if (utils->touchMode == 0) {
        if (utils->pad->pressed.down) {
            utils->selector++;
        }
        if (utils->pad->pressed.up) {
            utils->selector--;
        }

        if (utils->selector > 5) {
            utils->selector = 1;
        }

        if (utils->selector < 1) {
            utils->selector = 5;
        }
    }

}

unsigned int Customization::getColorPart(std::string name, unsigned int value) {
    int colorPart = std::stoi(utils->ime->getUserText(i18nCustomization[name].c_str(), std::to_string(value).c_str(), SCE_IME_TYPE_NUMBER, 3));
    if (colorPart < 0) {
        colorPart = 0;
    }
    if (colorPart > 255) {
        colorPart = 255;
    }
    return (unsigned int)colorPart;
}


void Customization::beforeEnter() {
    i18nCustomization = utils->i18n->getI18nByCat("customization");

    if (utils->touchMode == 0) {
        utils->selector = 1;
    }

    CUSTOMIZATION_NUMBER_OF_BUTTONS = utils->config->isCustomisation() ? 6 : 2;
}

void Customization::beforeExit() {

    utils->config->loadConfig();
    ui->layoutTheme->updateBackground();
}

void Customization::refreshBackground() {
    if (chosen == "background") {
        utils->config->setBackgroundColor(rgbaCustomization);
    }
    else if (chosen == "icons") {
        utils->config->setIconsColor(rgbaCustomization);
    }
    else if (chosen == "foreground") {
        utils->config->setForegroundColor(rgbaCustomization);
    }

    ui->layoutTheme->updateBackground();
}

