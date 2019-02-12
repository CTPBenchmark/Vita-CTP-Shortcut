#include "Welcome.hh"


Welcome::Welcome(const char *name) : View(name) {
}

void Welcome::contents() {

    websiteZE = ui->buttons->containedDraw(i18nWelcome["website"], 20 + LOGO_WIDTH, 10 + (LOGO_HEIGHT / 2) - (websiteZE.height / 2), THEME_PRIMARY, false, ICON_MDI_NEWSPAPER);
    forumZE = ui->buttons->containedDraw(i18nWelcome["forum"], websiteZE.x + websiteZE.width + 20, 10 + (LOGO_HEIGHT / 2) - (forumZE.height / 2), THEME_PRIMARY, false, ICON_MDI_FORUM);
    optionsZE = ui->buttons->floatDraw(ICON_MDI_SETTINGS, 960 - (optionsZE.width) - 10, 10 + (LOGO_HEIGHT / 2) - (optionsZE.height / 2), THEME_PRIMARY, false);

    if (!cardPosts.empty()) {
        int i = 0;
        for (auto &post : cardPosts) {
            ui->cards->initCard(10 + (10 * i) + (i * 400) - utils->scroll->getScroll("cards"), LOGO_HEIGHT + 20);
            ui->cards->drawPrimaryTitle(post.cardPrePrimaryTitle);
            ui->cards->drawSummary(post.cardPreSummary);
            i++;
        }
    }
    else if (CTPApi::getInstance()->getStatus() == CTPAPI_STATUS_NOT_LAUNCH) {
        centerZE = ui->buttons->containedDraw("Load news", 480 - (centerZE.width / 2), 272 - (centerZE.height / 2), THEME_PRIMARY, utils->ptc->isY(2), ICON_MDI_RELOAD);
    }
    else if (CTPApi::getInstance()->getStatus() == CTPAPI_STATUS_ERROR) {
        centerZE = ui->buttons->containedDraw("Error, try again", 480 - (centerZE.width / 2), 272 - (centerZE.height / 2), THEME_PRIMARY, utils->ptc->isY(2), ICON_MDI_PROGRESS_ALERT);
    }
    else {
        centerZE = ui->buttons->containedDraw("Loading", 480 - (centerZE.width / 2), 272 - (centerZE.height / 2), THEME_SECONDARY, false, ICON_MDI_PROGRESS_DOWNLOAD);
    }



    exitZE = ui->buttons->containedDraw(i18nWelcome["exit"], 10, 544 - 10 - exitZE.height, THEME_PRIMARY, utils->ptc->isY(PADTOUCHCTRL_IS_LAST), ICON_MDI_EXIT_TO_APP);
}

void Welcome::controls() {

    utils->scroll->controller("cards", utils->pad->pressed.left && utils->ptc->isY(2), utils->pad->pressed.right && utils->ptc->isY(2), 400);

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

    if (CTPApi::getInstance()->getStatus() == CTPAPI_STATUS_NOT_LAUNCH ||
        CTPApi::getInstance()->getStatus() == CTPAPI_STATUS_ERROR) {
        this->utils->ptc->setLimit(PADTOUCHCTRL_TYPE_Y, 3, 2);

        if (ui->buttons->onTouch(centerZE, utils->touch->lastClickPoint) ||
            ui->buttons->onPad(centerZE, utils->pad->pressed.cross)) {
            getPostsByApiStartThread();
        }
    }
    else {
        this->utils->ptc->setLimit(PADTOUCHCTRL_TYPE_Y, 3, 2);
    }

    if (ui->buttons->onTouch(exitZE, utils->touch->lastClickPoint) ||
        ui->buttons->onPad(exitZE, utils->pad->pressed.cross)) {
        viewsController->setActualView(VIEWS_CONTROLLER_EXIT);
    }

    //transform api data to card data
    if (CTPApi::getInstance()->getStatus() == CTPAPI_STATUS_LOADED && cardPosts.empty()) {
        CardPreSummary cardPreSummary;
        CardPrePrimaryTitle cardPrePrimaryTitle;
        CardPostContent cardPostContent;
        for (auto &post : CTPApi::getInstance()->getPosts()) {
            cardPrePrimaryTitle = ui->cards->prePrimaryTitle(post.title, post.author, 200);
            cardPreSummary = ui->cards->preSummaryTitle(post.excerpt, 100);

            cardPostContent.cardPrePrimaryTitle = cardPrePrimaryTitle;
            cardPostContent.cardPreSummary = cardPreSummary;

            cardPosts.emplace(cardPosts.end(), cardPostContent);
        }
    }

}

void Welcome::mounted() {
    i18nWelcome = utils->i18n->getI18nByCat("welcome");
    utils->scroll->create("cards", SCROLL_DIR_X, 0, 400 * 6, 10, 10, 960, 400);
}

void Welcome::beforeEnter() {


}