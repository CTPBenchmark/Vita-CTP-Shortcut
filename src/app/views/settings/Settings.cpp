#include "Settings.hh"

Settings::Settings(const std::string &name) : View(name) {
}

void Settings::contents() {

    customizationButtonZE = ui->buttons->containedDraw(i18nSettings["customization"], 10, 10, THEME_PRIMARY, utils->ptc->isY(PADTOUCHCTRL_IS_FIRST), ICON_MDI_PENCIL);

    vita2d_draw_rectangle(10, 40 + customizationButtonZE.height, 960 - 20, 230, ui->theme->convertHexToRGBA(ui->theme->getPrimaryHEX().dark, 200));

    ui->texts->draw(20, 50 + customizationButtonZE.height, H6, THEME_PRIMARY, i18nSettings["autoLaunchInstruction"]);
    newsCheckboxZE = ui->checkboxes->drawWithText(20, 130, newsCheckbox, i18nSettings["theNews"], utils->ptc->isY(2), THEME_PRIMARY, 40, RGBA8(255, 255, 255, 255));
    forumCheckboxZE = ui->checkboxes->drawWithText(20, 220, forumCheckbox, i18nSettings["theForum"], utils->ptc->isY(3), THEME_PRIMARY, 40, RGBA8(255, 255, 255, 255));

    backButtonZE = ui->buttons->containedDraw(i18nSettings["back"], 10, 544 - backButtonZE.height - 10, THEME_PRIMARY, utils->ptc->isY(PADTOUCHCTRL_IS_LAST), ICON_MDI_ARROW_LEFT);
}

void Settings::controls() {

    //events
    if (ui->buttons->onTouch(customizationButtonZE, utils->touch->lastClickPoint) ||
        ui->buttons->onPad(customizationButtonZE, utils->pad->pressed.cross)) {
        viewsController->setActualView("Customization");
    }

    if (ui->checkboxes->onTouch(newsCheckboxZE, utils->touch->lastClickPoint) ||
        ui->checkboxes->onPad(newsCheckboxZE, utils->pad->pressed.cross)) {
        if (forumCheckbox == CHECKBOX_CHECKED && newsCheckbox == CHECKBOX_UNCHECKED) {
            forumCheckbox = CHECKBOX_UNCHECKED;

            utils->config->setLaunchForum(forumCheckbox == CHECKBOX_CHECKED);
        }
        newsCheckbox = newsCheckbox == CHECKBOX_CHECKED ? CHECKBOX_UNCHECKED : CHECKBOX_CHECKED;

        utils->config->setLaunchNews(newsCheckbox == CHECKBOX_CHECKED);
        utils->config->saveConfig();
    }

    if (ui->checkboxes->onTouch(forumCheckboxZE, utils->touch->lastClickPoint) ||
        ui->checkboxes->onPad(forumCheckboxZE, utils->pad->pressed.cross)) {
        if (newsCheckbox == CHECKBOX_CHECKED && forumCheckbox == CHECKBOX_UNCHECKED) {
            newsCheckbox = CHECKBOX_UNCHECKED;

            utils->config->setLaunchNews(newsCheckbox == CHECKBOX_CHECKED);
        }
        forumCheckbox = forumCheckbox == CHECKBOX_CHECKED ? CHECKBOX_UNCHECKED : CHECKBOX_CHECKED;

        utils->config->setLaunchForum(forumCheckbox == CHECKBOX_CHECKED);
        utils->config->saveConfig();
    }



    if (ui->buttons->onTouch(backButtonZE, utils->touch->lastClickPoint) ||
        utils->pad->pressed.circle ||
        ui->buttons->onPad(backButtonZE, utils->pad->pressed.cross)) {
        viewsController->setActualView("Welcome");
    }

}

void Settings::beforeEnter() {
    newsCheckbox = utils->config->isLaunchNews() ? CHECKBOX_CHECKED : CHECKBOX_UNCHECKED;
    forumCheckbox = utils->config->isLaunchForum() ? CHECKBOX_CHECKED : CHECKBOX_UNCHECKED;

    utils->ptc->setLimit(PADTOUCHCTRL_TYPE_Y, 4);
}

void Settings::mounted() {
    i18nSettings = utils->i18n->getI18nByCat("settings");
}
