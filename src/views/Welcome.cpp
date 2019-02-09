#include "Welcome.hh"


Welcome::Welcome(const char *name) : View(name) {
}

void Welcome::contents() {

    optionsZE = ui->buttons->containedDraw(i18nWelcome["settings"], 960 - (optionsZE.width) - 10, 10, THEME_SECONDARY, utils->ptc->isY(PADTOUCHCTRL_IS_FIRST), ICON_MDI_SETTINGS);

    websiteZE = ui->buttons->containedDraw(i18nWelcome["website"], 480 - (websiteZE.width / 2), 180, THEME_PRIMARY, utils->ptc->isY(2), ICON_MDI_NEWSPAPER);
    forumZE = ui->buttons->containedDraw(i18nWelcome["forum"], 480 - (forumZE.width / 2), 180 + websiteZE.height + 20, THEME_PRIMARY, utils->ptc->isY(3), ICON_MDI_FORUM);
    exitZE = ui->buttons->containedDraw(i18nWelcome["exit"], 480 - (exitZE.width / 2), 450, THEME_PRIMARY, utils->ptc->isY(PADTOUCHCTRL_IS_LAST), ICON_MDI_EXIT_TO_APP);
}

void Welcome::controls() {

//events
    if (UiButtons::onTouch(optionsZE, utils->touch->lastClickPoint) ||
        UiButtons::onPad(optionsZE, utils->pad->pressed.cross)) {
        viewsController->setActualView("Settings");
    }

    if (UiButtons::onTouch(websiteZE, utils->touch->lastClickPoint) ||
        UiButtons::onPad(websiteZE, utils->pad->pressed.cross)
            ) {
        utils->webModal->launchCTPNews();
    }

    if (UiButtons::onTouch(forumZE, utils->touch->lastClickPoint) ||
        UiButtons::onPad(forumZE, utils->pad->pressed.cross)) {
        utils->webModal->launchCTPForum();
    }

    if (UiButtons::onTouch(exitZE, utils->touch->lastClickPoint) ||
        UiButtons::onPad(exitZE, utils->pad->pressed.cross)) {
        viewsController->setActualView(VIEWS_CONTROLLER_EXIT);
    }

}

void Welcome::mounted() {
    i18nWelcome = utils->i18n->getI18nByCat("welcome");
}

void Welcome::beforeEnter() {
    this->utils->ptc->setLimit(PADTOUCHCTRL_TYPE_Y, 4);
}