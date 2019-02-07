#include "Customization.hh"

Customization::Customization(const std::string &name) : View(name) {

}

void Customization::contents() {

    vita2d_draw_rectangle(10, 10, 960 - 20, 90, ui->theme->convertHexToRGBA(ui->theme->getPrimaryHEX().dark, 200));
    ui->texts->draw(120, 42, Body1, THEME_PRIMARY, "Customisation du fond de l'application");
    customizationCheckboxZE = ui->checkboxes->draw(20, 15, customizationCheckbox, utils->selector == 1);

    if (utils->config->isCustomisation()) {

        backgroundButtonZE = ui->buttons->containedDraw("ArriÈre plan", 10, 110, THEME_PRIMARY, utils->selector == 2);
        iconsButtonZE = ui->buttons->containedDraw("Icones", 10, 120 + backgroundButtonZE.height, THEME_PRIMARY, utils->selector == 3);
        foregroundButtonZE = ui->buttons->containedDraw("Premier plan", 10, 130 + backgroundButtonZE.height + iconsButtonZE.height, THEME_PRIMARY, utils->selector == 4);
        speedTextFieldZE = ui->textFields->filledDraw(10, 140 + backgroundButtonZE.height + iconsButtonZE.height + foregroundButtonZE.height, TEXTFIELD_MODE_SINGLE, utils->selector == 5, "Speed", std::to_string(utils->config->getSpeed()));

    }

    backButtonZE = ui->buttons->containedDraw(utils->i18n->getI18nByCat("settings")["back"], 10, 544 - backButtonZE.height - 10, THEME_PRIMARY, utils->selector == CUSTOMIZATION_NUMBER_OF_BUTTONS, ICON_MDI_ARROW_LEFT);
}

void Customization::controls() {



    if (ui->buttons->onTouch(backButtonZE, utils->touch->lastClickPoint) ||
        utils->pad->pressed.circle ||
        ui->buttons->onPad(backButtonZE, utils->pad->pressed.cross)) {
        viewsController->setActualView("Settings");
    }

    if (utils->touchMode == 1) {
        customizationCheckbox = ui->checkboxes->onTouchAuto(customizationCheckboxZE, utils->touch->lastClickPoint);
    }
    else {
        customizationCheckbox = ui->checkboxes->onPadAuto(customizationCheckboxZE, utils->pad->pressed.cross);
    }

    if ((!utils->config->isCustomisation() && customizationCheckbox == CHECKED) ||
        (utils->config->isCustomisation() && customizationCheckbox == UNCHECKED)) {

        utils->config->setCustomisation(customizationCheckbox == CHECKED);
        CUSTOMIZATION_NUMBER_OF_BUTTONS = utils->config->isCustomisation() ? 6 : 2;

        utils->config->saveConfig();
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

void Customization::beforeEnter() {
    if (utils->touchMode == 0) {
        utils->selector = 1;
    }

    CUSTOMIZATION_NUMBER_OF_BUTTONS = utils->config->isCustomisation() ? 6 : 2;
}
