#include "Welcome.hh"


Welcome::Welcome(const char *name) : View(name) {
}

void Welcome::contents() {

    ui->texts->drawF(0, 0, Body1, (unsigned int)RGBA8(255, 0, 0, 255), false,
                     "TouchMode: %d\nSelector: %d\nCtrl: %s",
                     touchMode,
                     selector,
                     utils->pad->held.clicking ? "true" : "false"
    );

    optionsZE = ui->buttons->containedDraw(utils->i18n->getI18nByCat("welcome")["settings"], 960 - (optionsZE.width) - 10, 10, THEME_SECONDARY, selector == 1, ICON_MDI_SETTINGS);

    websiteZE = ui->buttons->containedDraw(utils->i18n->getI18nByCat("welcome")["website"], 480 - (websiteZE.width / 2), 180, THEME_PRIMARY, selector == 2, ICON_MDI_NEWSPAPER);
    forumZE = ui->buttons->containedDraw(utils->i18n->getI18nByCat("welcome")["forum"], 480 - (forumZE.width / 2), 180 + websiteZE.height + 20, THEME_PRIMARY, selector == 3, ICON_MDI_FORUM);
    exitZE = ui->buttons->containedDraw(utils->i18n->getI18nByCat("welcome")["exit"], 480 - (exitZE.width / 2), 450, THEME_PRIMARY, selector == WELCOME_NUMBER_OF_BUTTONS, ICON_MDI_EXIT_TO_APP);
}

void Welcome::controls() {

//events
    if (ui->buttons->onTouch(optionsZE, utils->touch->lastClickPoint) ||
        ui->buttons->onPad(optionsZE, utils->pad->pressed.cross)) {
        viewsController->setActualView("ButtonsSample");
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
    if (touchMode == 0) {
        if (utils->pad->pressed.down) {
            selector++;
        }
        if (utils->pad->pressed.up) {
            selector--;
        }

        if (selector > WELCOME_NUMBER_OF_BUTTONS) {
            selector = 1;
        }

        if (selector < 1) {
            selector = WELCOME_NUMBER_OF_BUTTONS;
        }
    }


    //touch & pad switch
    if (utils->touch->clicking && touchMode == 0) {
        touchMode = 1;
        selector = -1;
    }
    if (utils->pad->held.clicking && touchMode == 1) {
        touchMode = 0;
        selector = 2;
    }

}

