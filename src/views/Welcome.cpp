#include "Welcome.hh"


Welcome::Welcome(const char *name) : View(name) {
}

void Welcome::contents() {

    optionsZE = ui->buttons->containedDraw(i18nWelcome["settings"], 960 - (optionsZE.width) - 10, 10, THEME_SECONDARY, utils->selector == 1, ICON_MDI_SETTINGS);

    websiteZE = ui->buttons->containedDraw(i18nWelcome["website"], 480 - (websiteZE.width / 2), 180, THEME_PRIMARY, utils->selector == 2, ICON_MDI_NEWSPAPER);
    forumZE = ui->buttons->containedDraw(i18nWelcome["forum"], 480 - (forumZE.width / 2), 180 + websiteZE.height + 20, THEME_PRIMARY, utils->selector == 3, ICON_MDI_FORUM);
    exitZE = ui->buttons->containedDraw(i18nWelcome["exit"], 480 - (exitZE.width / 2), 450, THEME_PRIMARY, utils->selector == WELCOME_NUMBER_OF_BUTTONS, ICON_MDI_EXIT_TO_APP);
}

void Welcome::controls() {

//events
    if (ui->buttons->onTouch(optionsZE, utils->touch->lastClickPoint) ||
        ui->buttons->onPad(optionsZE, utils->pad->pressed.cross)) {
        viewsController->setActualView("Settings");
    }

    if (ui->buttons->onTouch(websiteZE, utils->touch->lastClickPoint) ||
        ui->buttons->onPad(websiteZE, utils->pad->pressed.cross)
            ) {
        utils->webModal->launchCTPNews();
    }

    if (ui->buttons->onTouch(forumZE, utils->touch->lastClickPoint) ||
        ui->buttons->onPad(forumZE, utils->pad->pressed.cross)) {
        utils->webModal->launchCTPForum();
    }

    if (ui->buttons->onTouch(exitZE, utils->touch->lastClickPoint) ||
        ui->buttons->onPad(exitZE, utils->pad->pressed.cross)) {
        viewsController->setActualView(VIEWS_CONTROLLER_EXIT);
    }


    //pad
    if (utils->touchMode == 0) {
        if (utils->pad->pressed.down) {
            utils->selector++;
        }
        if (utils->pad->pressed.up) {
            utils->selector--;
        }

        if (utils->selector > WELCOME_NUMBER_OF_BUTTONS) {
            utils->selector = 1;
        }

        if (utils->selector < 1) {
            utils->selector = WELCOME_NUMBER_OF_BUTTONS;
        }
    }

}

void Welcome::beforeEnter() {
    if (utils->touchMode == 0) {
        utils->selector = 2;
    }

    i18nWelcome = utils->i18n->getI18nByCat("welcome");
}

