#include "Settings.hh"

Settings::Settings(const std::string &name) : View(name) {
}

void Settings::contents() {

    customizationButtonZE = ui->buttons->containedDraw(i18nSettings["customization"], 10, 10, THEME_PRIMARY, utils->selector == 1, ICON_MDI_PENCIL);

    vita2d_draw_rectangle(10, 40 + customizationButtonZE.height, 960 - 20, 230, ui->theme->convertHexToRGBA(ui->theme->getPrimaryHEX().dark, 200));

    ui->texts->draw(20, 50 + customizationButtonZE.height, H6, THEME_PRIMARY, i18nSettings["autoLaunchInstruction"]);
    newsCheckboxZE = ui->checkboxes->draw(20, 130, newsCheckbox, utils->selector == 2);
    ui->texts->draw(120, 160, Body1, THEME_PRIMARY, i18nSettings["theNews"]);

    forumCheckboxZE = ui->checkboxes->draw(20, 220, forumCheckbox, utils->selector == 3);
    ui->texts->draw(120, 250, Body1, THEME_PRIMARY, i18nSettings["theForum"]);



    backButtonZE = ui->buttons->containedDraw(i18nSettings["back"], 10, 544 - backButtonZE.height - 10, THEME_PRIMARY, utils->selector == SETTINGS_NUMBER_OF_BUTTONS, ICON_MDI_ARROW_LEFT);
}

void Settings::controls() {

    //events
    if (ui->buttons->onTouch(customizationButtonZE, utils->touch->lastClickPoint) ||
        ui->buttons->onPad(customizationButtonZE, utils->pad->pressed.cross)) {
        viewsController->setActualView("Customization");
    }

    if (ui->checkboxes->onTouch(newsCheckboxZE, utils->touch->lastClickPoint) ||
        ui->checkboxes->onPad(newsCheckboxZE, utils->pad->pressed.cross)) {
        if (forumCheckbox == CHECKED && newsCheckbox == UNCHECKED) {
            forumCheckbox = UNCHECKED;

            utils->config->setLaunchForum(forumCheckbox == CHECKED);
        }
        newsCheckbox = newsCheckbox == CHECKED ? UNCHECKED : CHECKED;

        utils->config->setLaunchNews(newsCheckbox == CHECKED);
        utils->config->saveConfig();
    }

    if (ui->checkboxes->onTouch(forumCheckboxZE, utils->touch->lastClickPoint) ||
        ui->checkboxes->onPad(forumCheckboxZE, utils->pad->pressed.cross)) {
        if (newsCheckbox == CHECKED && forumCheckbox == UNCHECKED) {
            newsCheckbox = UNCHECKED;

            utils->config->setLaunchNews(newsCheckbox == CHECKED);
        }
        forumCheckbox = forumCheckbox == CHECKED ? UNCHECKED : CHECKED;

        utils->config->setLaunchForum(forumCheckbox == CHECKED);
        utils->config->saveConfig();
    }



    if (ui->buttons->onTouch(backButtonZE, utils->touch->lastClickPoint) ||
        utils->pad->pressed.circle ||
        ui->buttons->onPad(backButtonZE, utils->pad->pressed.cross)) {
        viewsController->setActualView("Welcome");
    }


    //pad
    if (utils->touchMode == 0) {
        if (utils->pad->pressed.down) {
            utils->selector++;
        }
        if (utils->pad->pressed.up) {
            utils->selector--;
        }

        if (utils->selector > SETTINGS_NUMBER_OF_BUTTONS) {
            utils->selector = 1;
        }

        if (utils->selector < 1) {
            utils->selector = SETTINGS_NUMBER_OF_BUTTONS;
        }
    }
}

void Settings::beforeEnter() {
    if (utils->touchMode == 0) {
        utils->selector = 1;
    }

    newsCheckbox = utils->config->isLaunchNews() ? CHECKED : UNCHECKED;
    forumCheckbox = utils->config->isLaunchForum() ? CHECKED : UNCHECKED;

    i18nSettings = utils->i18n->getI18nByCat("settings");
}
