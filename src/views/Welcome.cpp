#include "Welcome.hh"


Welcome::Welcome(const char *name) : View(name) {
}

void Welcome::contents() {

    websiteZE = ui->buttons->containedDraw(i18nWelcome["website"], 20 + LOGO_WIDTH, 10 + (LOGO_HEIGHT / 2) - (websiteZE.height / 2), THEME_PRIMARY, utils->ptc->isXY(PADTOUCHCTRL_IS_FIRST, PADTOUCHCTRL_IS_FIRST), ICON_MDI_NEWSPAPER);
    forumZE = ui->buttons->containedDraw(i18nWelcome["forum"], websiteZE.x + websiteZE.width + 20, 10 + (LOGO_HEIGHT / 2) - (forumZE.height / 2), THEME_PRIMARY, utils->ptc->isXY(2, PADTOUCHCTRL_IS_FIRST), ICON_MDI_FORUM);
    optionsZE = ui->buttons->floatDraw(ICON_MDI_SETTINGS, 960 - (optionsZE.width) - 10, 10 + (LOGO_HEIGHT / 2) - (optionsZE.height / 2), THEME_PRIMARY, utils->ptc->isXY(3, PADTOUCHCTRL_IS_FIRST));

    //cardposts
    if (!cardPosts.empty()) {
        int i = 0;
        for (auto &post : cardPosts) {
            ui->cards->start(10 + (10 * i) + (i * 400) - utils->scroll->getValue("cards"), LOGO_HEIGHT + 20, CARDS_DEFAULT_WIDTH, THEME_PRIMARY, utils->ptc->isXY(i+1,2));
            ui->cards->drawPrimaryTitle(post.cardPrePrimaryTitle);
            ui->cards->drawSummary(post.cardPreSummary);
            post.zoneEvent = ui->cards->end();
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
        centerZE = ui->buttons->containedDraw("Loading", 480 - (centerZE.width / 2), 272 - (centerZE.height / 2), THEME_SECONDARY, utils->ptc->isY(2), ICON_MDI_PROGRESS_DOWNLOAD);
    }

    exitZE = ui->buttons->containedDraw(i18nWelcome["exit"], 10, 544 - 10 - exitZE.height, THEME_PRIMARY, utils->ptc->isY(PADTOUCHCTRL_IS_LAST), ICON_MDI_EXIT_TO_APP);
}

void Welcome::controls() {

    utils->ptc->scrollController("cards", 2, 410);

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

        if (ui->buttons->onTouch(centerZE, utils->touch->lastClickPoint) ||
            ui->buttons->onPad(centerZE, utils->pad->pressed.cross)) {
            getPostsByApiStartThread();
        }
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
            cardPrePrimaryTitle = ui->cards->prePrimaryTitle(post.title, post.author, CARDS_DEFAULT_WIDTH, 200);
            cardPreSummary = ui->cards->preSummaryTitle(post.excerpt, CARDS_DEFAULT_WIDTH, 130);

            if (cardPreSummary.text == "...") {
                cardPreSummary.text = "";
            }

            cardPostContent.cardPrePrimaryTitle = cardPrePrimaryTitle;
            cardPostContent.cardPreSummary = cardPreSummary;
            cardPostContent.url = post.url;

            cardPosts.emplace(cardPosts.end(), cardPostContent);
        }
        gridWithCards();
    }

    for (auto &post : cardPosts) {
        if (ui->cards->onTouch(post.zoneEvent, utils->touch->lastClickPoint) ||
            ui->cards->onPad(post.zoneEvent, utils->pad->pressed.cross)
                ) {
            utils->webModal->invokeWebModal(post.url.c_str());
        }
    }

}

void Welcome::mounted() {
    i18nWelcome = utils->i18n->getI18nByCat("welcome");
}

void Welcome::beforeEnter() {

    if (CTPApi::getInstance()->getStatus() == CTPAPI_STATUS_LOADED && !cardPosts.empty()) {
        gridWithCards();
    }
    else {
        gridNoCards();
    }

    utils->scroll->create("cards", SCROLL_DIR_X, 0, CARDS_DEFAULT_WIDTH * 8, 10, 20 + LOGO_HEIGHT, SCREEN_WIDTH, 330);
}

void Welcome::beforeExit() {
    utils->scroll->remove("cards");
}

void Welcome::gridNoCards() {
    utils->ptc->setLimit(3, 3);
    utils->ptc->addLimit(PADTOUCHCTRL_TYPE_X, 1, 1, 3);
    utils->ptc->addLimit(PADTOUCHCTRL_TYPE_X, 2, 1, 1);
    utils->ptc->addLimit(PADTOUCHCTRL_TYPE_X, 3, 1, 1);
}

void Welcome::gridWithCards() {
    utils->ptc->setLimit(cardPosts.size(), 3);
    utils->ptc->addLimit(PADTOUCHCTRL_TYPE_X, 1, 1, 3);
    utils->ptc->addLimit(PADTOUCHCTRL_TYPE_X, 2, 1, cardPosts.size());
    utils->ptc->addLimit(PADTOUCHCTRL_TYPE_X, 3, 1, 1);
}

