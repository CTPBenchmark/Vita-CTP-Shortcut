/*
 **
 ** Made by Applelo
 **
 */


#include "../include/Menu.hh"

extern unsigned char _binary_img_WalloloRep_png_start;
extern unsigned char _binary_img_SettingsIcon_png_start;
extern unsigned char _binary_img_ExitIcon_png_start;
extern unsigned char _binary_img_CloseIcon_png_start;
extern unsigned char _binary_img_CheckIcon_png_start;
extern unsigned char _binary_img_SaveIcon_png_start;

Menu::Menu() {
    _pgf = vita2d_load_default_pgf();
    _engine = new Engine();
    _wallolo = vita2d_load_PNG_buffer(&_binary_img_WalloloRep_png_start);
    _icons["settings"] = vita2d_load_PNG_buffer(&_binary_img_SettingsIcon_png_start);
    _icons["exit"] = vita2d_load_PNG_buffer(&_binary_img_ExitIcon_png_start);
    _icons["close"] = vita2d_load_PNG_buffer(&_binary_img_CloseIcon_png_start);
    _icons["check"] = vita2d_load_PNG_buffer(&_binary_img_CheckIcon_png_start);
    _icons["save"] = vita2d_load_PNG_buffer(&_binary_img_SaveIcon_png_start);

    _background = new Background(_wallolo, _engine->getBackgroundColor(), _engine->getLogoColor());
    _logo = _engine->getLogo();
    _selectorX = 1;
    _selectorY = 1;
    _ctrlMode = false;
    _rgbMode = "logo";

    if (_engine->getLang() == SCE_SYSTEM_PARAM_LANG_FRENCH) {
        _lang["news"] = "Actualités";
        _lang["forum"] = "Forum";
        _lang["logo"] = "Logo";
        _lang["background"] = "Arrière plan";
        _lang["launch_news"] = "Ouvrir la partie news de Custom Protocol au lancement de l'application";
        _lang["launch_forum"] = "Ouvrir la partie forum de Custom Protocol au lancement de l'application";
        _lang["customisation"] = "Activer la personnalisation de l'application";
        _lang["red"] = "Rouge";
        _lang["green"] = "Vert";
        _lang["blue"] = "Bleu";
    }
    else {
        _lang["news"] = "News";
        _lang["forum"] = "Forum";
        _lang["logo"] = "Logo";
        _lang["background"] = "Background";
        _lang["launch_news"] = "Open the Custom Protocol news when application launching";
        _lang["launch_forum"] = "Open the Custom Protocol forum when application launching";
        _lang["customisation"] = "Activer la customisation de l'application";
        _lang["red"] = "Red";
        _lang["green"] = "Green";
        _lang["blue"] = "Blue";

    }

    _buttons["news"] = new Buttons(_pgf, _lang["news"], SCREEN_L/6, 300, 200, 75);
    _buttons["forum"] = new Buttons(_pgf, _lang["forum"], SCREEN_L - (SCREEN_L/6) - 200, 300, 200, 75);
    _buttons["settings"] = new Buttons(_icons["settings"], SCREEN_L - 164, 25, 52, 52);
    _buttons["exit"] = new Buttons(_icons["exit"], SCREEN_L - 77, 25, 52, 52);

    _buttons["close"] = new Buttons(_icons["close"], SCREEN_L - 77, 25, 52, 52);
    _buttons["save"] = new Buttons(_icons["save"], SCREEN_L - 77, 25, 52, 52);
    _checkboxes["launch_news"] = new Checkbox(_icons["check"], 50, 180, 48, 48, _engine->getLaunchNews());
    _checkboxes["launch_news"]->setLocked(_engine->getLaunchForum());
    _checkboxes["launch_forum"] = new Checkbox(_icons["check"], 50, 260, 48, 48, _engine->getLaunchForum());
    _checkboxes["launch_forum"]->setLocked(_engine->getLaunchNews());
    _checkboxes["customisation"] = new Checkbox(_icons["check"], 50, 340, 48, 48, _engine->getCustomisation());
    _buttons["logo"] = new Buttons(_pgf, _lang["logo"], SCREEN_L/6, 419, 200, 75);
    _buttons["logo"]->setLocked(!_engine->getCustomisation());
    _buttons["background"] = new Buttons(_pgf, _lang["background"], SCREEN_L - (SCREEN_L/6) - 200, 419, 200, 75);
    _buttons["background"]->setLocked(!_engine->getCustomisation());

    _keyboard = new Keyboard(3, SCE_IME_TYPE_NUMBER);

    int color;
    for (int i = 0; i < 3; ++i) {
        if (i == 0)
            color = COLOR_RED;
        else if (i == 1)
            color = COLOR_GREEN;
        else
            color = COLOR_BLUE;

        _less[i] = new Buttons(_pgf, "-", 246, 200 + (75 * i) , 48, 48);
        _number[i] = new Buttons(_pgf, "", 246 + 73, 200 + (75 * i) , 96, 48, COLOR_BUTTON_FIRST, COLOR_BUTTON_SECOND, COLOR_BUTTON_THIRD, color);
        _more[i] = new Buttons(_pgf, "+", 246 + 194, 200 + (75 * i), 48, 48);
    }



    _newsUri = URL_NEWS;
    _newsUri = "webmodal: " + _newsUri;

    _forumUri = URL_FORUM;
    _forumUri = "webmodal: " + _forumUri;



    //AutoLaunch
    if (_engine->getLaunchNews())
        sceAppMgrLaunchAppByUri(0xF0000, (char*) _newsUri.c_str());

    if (_engine->getLaunchForum())
        sceAppMgrLaunchAppByUri(0xF0000, (char*) _forumUri.c_str());


}

Menu::~Menu() {
}

void Menu::main() {
    this->startMenu();
    _buttons["news"]->display();
    _buttons["forum"]->display();
    _buttons["exit"]->display();
    //_buttons["settings"]->display();

    //CTP control
    if ((_buttons["news"]->touchButton(_touchX, _touchY) && !_buttons["news"]->touchButton(_touchOldX, _touchOldY)) ||
        (_selectorX == 1 && _selectorY == 2 && _ctrlMode && _ctrl_press.buttons & SCE_CTRL_CROSS)) {
        sceAppMgrLaunchAppByUri(0xF0000, (char*) _newsUri.c_str());
        if (_ctrlMode) {
            _selectorY = 2;
            _selectorX = 1;
        }

    }

    //Forum control
    if ((_buttons["forum"]->touchButton(_touchX, _touchY) && !_buttons["forum"]->touchButton(_touchOldX, _touchOldY)) ||
        (_selectorX == 2 && _selectorY == 2 && _ctrlMode && _ctrl_press.buttons & SCE_CTRL_CROSS)) {
        sceAppMgrLaunchAppByUri(0xF0000, (char*) _forumUri.c_str());
        if (_ctrlMode) {
            _selectorY = 2;
            _selectorX = 2;
        }
    }


    //Settings control
    //if ((_buttons["settings"]->touchButton(_touchX, _touchY) && !_buttons["settings"]->touchButton(_touchOldX, _touchOldY)) ||
     //       (_selectorX == 1 && _selectorY == 1 && _ctrlMode && _ctrl_press.buttons & SCE_CTRL_CROSS)) {
     //       _step = SETTINGS;
     //       if (_ctrlMode) {
     //           _selectorY = 1;
    //            _selectorX = 1;
    //        }
    //}

    //Exit control
        if ((_buttons["exit"]->touchButton(_touchX, _touchY) && !_buttons["exit"]->touchButton(_touchOldX, _touchOldY)) ||
            (_selectorX == 2 && _selectorY == 1 && _ctrlMode && _ctrl_press.buttons & SCE_CTRL_CROSS)) {
            _step = EXIT;
            if (_ctrlMode) {
                _selectorY = 1;
                _selectorX = 2;
            }
    }



    if (_ctrlMode) {
        _buttons["settings"]->setSelected((_selectorY == 1 && _selectorX == 1));
        _buttons["exit"]->setSelected((_selectorY == 1 && _selectorX == 2));
        _buttons["news"]->setSelected((_selectorY == 2 && _selectorX == 1));
        _buttons["forum"]->setSelected((_selectorY == 2 && _selectorX == 2));


        if (_selectorX > 2)
            _selectorX = 1;
        if (_selectorX < 1)
            _selectorX = 2;

        if (_selectorY > 2)
            _selectorY = 1;
        if (_selectorY < 1)
            _selectorY = 2;
    }

    this->endMenu();
}

void Menu::settings() {
    this->startMenu();

    vita2d_draw_rectangle(25, 155, SCREEN_L - 50, SCREEN_H - 155 - 25, COLOR_BUTTON_SECOND);
    _buttons["save"]->display();
    _buttons["logo"]->display();
    _buttons["background"]->display();
    _checkboxes["launch_news"]->display();
    _checkboxes["launch_forum"]->display();
    _checkboxes["customisation"]->display();


    vita2d_pgf_draw_textf(_pgf, 120, 180 + 24 + (vita2d_pgf_text_height(_pgf, 1.0, _lang["launch_news"].c_str())/2), COLOR_WHITE, 1.0, _lang["launch_news"].c_str());
    vita2d_pgf_draw_textf(_pgf, 120, 260 + 24 + (vita2d_pgf_text_height(_pgf, 1.0, _lang["launch_forum"].c_str())/2), COLOR_WHITE, 1.0, _lang["launch_forum"].c_str());
    vita2d_pgf_draw_textf(_pgf, 120, 340 + 24 + (vita2d_pgf_text_height(_pgf, 1.0, _lang["customisation"].c_str())/2), COLOR_WHITE, 1.0, _lang["customisation"].c_str());

    //Save & close control
    if ((_buttons["save"]->touchButton(_touchX, _touchY) && !_buttons["save"]->touchButton(_touchOldX, _touchOldY)) ||
        (_selectorX == 1 && _selectorY == 1 && _ctrlMode && _ctrl_press.buttons & SCE_CTRL_CROSS) || (_ctrl_press.buttons & SCE_CTRL_CIRCLE)) {
        _engine->saveData();
        _step = MAIN;
        if (_ctrlMode) {
            _selectorY = 1;
            _selectorX = 1;
        }
    }

    //Launch News
    if ((_checkboxes["launch_news"]->touchButton(_touchX, _touchY) && !_checkboxes["launch_news"]->touchButton(_touchOldX, _touchOldY)) ||
        (_selectorX == 1 && _selectorY == 2 && _ctrlMode && _ctrl_press.buttons & SCE_CTRL_CROSS && !_checkboxes["launch_news"]->getLocked())) {
        _checkboxes["launch_news"]->setStatus(!_checkboxes["launch_news"]->getStatus());
        _checkboxes["launch_forum"]->setLocked(_checkboxes["launch_news"]->getStatus());
        _engine->setLaunchNews(!_engine->getLaunchNews());
        if (_engine->getLaunchNews()) {
            _engine->setLaunchForum(false);
            _checkboxes["launch_forum"]->setStatus(false);
        }

        if (_ctrlMode) {
            _selectorY = 2;
            _selectorX = 1;
        }
    }

    //Launch Forum
    if ((_checkboxes["launch_forum"]->touchButton(_touchX, _touchY) && !_checkboxes["launch_forum"]->touchButton(_touchOldX, _touchOldY)) ||
        (_selectorX == 1 && _selectorY == 3 && _ctrlMode && _ctrl_press.buttons & SCE_CTRL_CROSS && !_checkboxes["launch_forum"]->getLocked())) {
        _checkboxes["launch_forum"]->setStatus(!_checkboxes["launch_forum"]->getStatus());
        _checkboxes["launch_news"]->setLocked(_checkboxes["launch_forum"]->getStatus());
        _engine->setLaunchForum( !_engine->getLaunchForum());
        if (_engine->getLaunchForum()) {
            _engine->setLaunchNews(false);
            _checkboxes["launch_news"]->setStatus(false);
        }

        if (_ctrlMode) {
            _selectorY = 3;
            _selectorX = 1;
        }
    }

    //Customisation
    if ((_checkboxes["customisation"]->touchButton(_touchX, _touchY) && !_checkboxes["customisation"]->touchButton(_touchOldX, _touchOldY)) ||
        (_selectorX == 1 && _selectorY == 4 && _ctrlMode && _ctrl_press.buttons & SCE_CTRL_CROSS)) {
        _checkboxes["customisation"]->setStatus(!_checkboxes["customisation"]->getStatus());
        _buttons["logo"]->setLocked(!_checkboxes["customisation"]->getStatus());
        _buttons["background"]->setLocked(!_checkboxes["customisation"]->getStatus());
        _engine->setCustomisation(_checkboxes["customisation"]->getStatus());
        _background->setBackgroundColor(_engine->getBackgroundColor());
        _background->setLogoColor(_engine->getLogoColor());

        if (_ctrlMode) {
            _selectorY = 4;
            _selectorX = 1;
        }
    }

    //Logo control
    if ((_buttons["logo"]->touchButton(_touchX, _touchY) && !_buttons["logo"]->touchButton(_touchOldX, _touchOldY)) ||
        (_selectorX == 1 && _selectorY == 5 && _ctrlMode && _ctrl_press.buttons & SCE_CTRL_CROSS && !_buttons["logo"]->getLocked())) {
        _rgbMode = "logo";
        _actualRgb = _engine->getRgbColor(_engine->getLogoColor());
        for (int i = 0; i < 3; ++i) {
            _number[i]->setText(std::to_string(_actualRgb[i]));
        }
        _step = CUSTOMISATION;
        if (_ctrlMode) {
            _selectorY = 2;
            _selectorX = 2;
        }
    }

    //Background control
    if ((_buttons["background"]->touchButton(_touchX, _touchY) && !_buttons["background"]->touchButton(_touchOldX, _touchOldY)) ||
        (_selectorX == 2 && _selectorY == 5 && _ctrlMode && _ctrl_press.buttons & SCE_CTRL_CROSS && !_buttons["background"]->getLocked())) {
        _rgbMode = "background";
        _actualRgb = _engine->getRgbColor(_engine->getBackgroundColor());
        for (int i = 0; i < 3; ++i) {
            _number[i]->setText(std::to_string(_actualRgb[i]));
        }
        _step = CUSTOMISATION;
        if (_ctrlMode) {
            _selectorY = 2;
            _selectorX = 2;
        }
    }

    if (_ctrlMode) {
        _buttons["save"]->setSelected((_selectorY == 1 && _selectorX == 1));
        _buttons["logo"]->setSelected((_selectorY == 5 && _selectorX == 1));
        _buttons["background"]->setSelected((_selectorY == 5 && _selectorX == 2));
        _checkboxes["launch_news"]->setSelected((_selectorY == 2 && _selectorX == 1));
        _checkboxes["launch_forum"]->setSelected((_selectorY == 3 && _selectorX == 1));
        _checkboxes["customisation"]->setSelected((_selectorY == 4 && _selectorX == 1));

        if (_selectorX > 2)
            _selectorX = 1;
        if (_selectorX < 1)
            _selectorX = 2;
        if (_selectorY != 5)//block x axis selector
            _selectorX = 1;

        if (_selectorY > 5)
            _selectorY = 1;
        if (_selectorY < 1)
            _selectorY = 5;
    }

    this->endMenu();
}

void Menu::customisation() {
    this->startMenu();
    _buttons["close"]->display();

    //Close control
    if ((_buttons["close"]->touchButton(_touchX, _touchY) && !_buttons["close"]->touchButton(_touchOldX, _touchOldY)) ||
        (_selectorX == 1 && _selectorY == 1 && _ctrlMode && _ctrl_press.buttons & SCE_CTRL_CROSS) || (_ctrl_press.buttons & SCE_CTRL_CIRCLE)) {
        _step = SETTINGS;
        if (_ctrlMode) {
            _selectorY = 1;
            _selectorX = 1;
        }
    }

    for (int i = 0; i < 3; ++i) {
        _less[i]->display();
        _number[i]->display();
        _more[i]->display();

        _less[i]->setSelected((_selectorY == (i+2) && _selectorX == 1));
        _number[i]->setSelected((_selectorY == (i+2) && _selectorX == 2));
        _more[i]->setSelected((_selectorY == (i+2) && _selectorX == 3));

        //Less
        if ((_less[i]->touchButton(_touchX, _touchY) && !_less[i]->touchButton(_touchOldX, _touchOldY)) ||
            (_selectorX == 1 && _selectorY == i + 2 && _ctrlMode && _ctrl_press.buttons & SCE_CTRL_CROSS && !_less[i]->getLocked())) {
            _actualRgb[i]--;
            if (_actualRgb[i] <= 0)
                _actualRgb[i] = 0;
            _engine->setRgbColor(_rgbMode, _actualRgb);
            _number[i]->setText(std::to_string(_actualRgb[i]));
            if (!strcmp(_rgbMode, "background"))
                _background->setBackgroundColor(_engine->getBackgroundColor());
            else
                _background->setLogoColor(_engine->getLogoColor());

            if (_ctrlMode) {
                _selectorY = i + 2;
                _selectorX = 1;
            }
        }

        //Number
        if ((_less[i]->touchButton(_touchX, _touchY) && !_less[i]->touchButton(_touchOldX, _touchOldY)) ||
            (_selectorX == 2 && _selectorY == i + 2 && _ctrlMode && _ctrl_press.buttons & SCE_CTRL_CROSS)) {

            std::string name;
            if (i == 0)
                name = _lang["red"];
            else if (i == 1)
                name = _lang["green"];
            else
                name = _lang["blue"];


            if (_ctrlMode) {
                _selectorY = i + 2;
                _selectorX = 2;
            }
        }

        //More
        if ((_more[i]->touchButton(_touchX, _touchY) && !_more[i]->touchButton(_touchOldX, _touchOldY)) ||
            (_selectorX == 3 && _selectorY == (i + 2) && _ctrlMode && _ctrl_press.buttons & SCE_CTRL_CROSS && !_more[i]->getLocked())) {
            _actualRgb[i]++;
            if (_actualRgb[i] >= 255)
                _actualRgb[i] = 255;
            _engine->setRgbColor(_rgbMode, _actualRgb);
            _number[i]->setText(std::to_string(_actualRgb[i]));
            if (!strcmp(_rgbMode, "background"))
                _background->setBackgroundColor(_engine->getBackgroundColor());
            else
                _background->setLogoColor(_engine->getLogoColor());


            if (_ctrlMode) {
                _selectorY = i + 2;
                _selectorX = 3;
            }
        }


        if (_actualRgb[i] == 0 && !_less[i]->getLocked()) {
            _less[i]->setLocked(true);
        }
        if (_actualRgb[i] > 0 && _less[i]->getLocked()) {
            _less[i]->setLocked(false);
        }

        if (_actualRgb[i] == 255 && !_more[i]->getLocked()) {
            _more[i]->setLocked(true);
        }
        if (_actualRgb[i] < 255 && _more[i]->getLocked()) {
            _more[i]->setLocked(false);
        }

    }


    if (_ctrlMode) {
        _buttons["close"]->setSelected((_selectorY == 1 && _selectorX == 1));
        if (_selectorX > 3)
            _selectorX = 1;
        if (_selectorX < 1)
            _selectorX = 3;
        if (_selectorY == 1)//block x axis selector
            _selectorX = 1;

        if (_selectorY > 4)
            _selectorY = 1;
        if (_selectorY < 1)
            _selectorY = 4;
    }


    this->endMenu();
}

void Menu::startMenu() {
    _background->displayBackground();
    vita2d_draw_texture(_logo, 25, 25);

    //Controls
    _ctrl_press = _ctrl_peek;
    sceCtrlPeekBufferPositive(0, &_ctrl_peek, 1);
    _ctrl_press.buttons = _ctrl_peek.buttons & ~_ctrl_press.buttons;
    if (_ctrlMode) {
        if (_ctrl_press.buttons & SCE_CTRL_UP)
            _selectorY--;
        if (_ctrl_press.buttons & SCE_CTRL_DOWN)
            _selectorY++;

        if (_ctrl_press.buttons & SCE_CTRL_LEFT)
            _selectorX--;
        if (_ctrl_press.buttons & SCE_CTRL_RIGHT)
            _selectorX++;

        if ((_touchX > 0 && _touchX < SCREEN_L && _touchY > 0 && _touchY < SCREEN_H) && !(_touchOldX > 0 && _touchOldX < SCREEN_L && _touchOldY > 0 && _touchOldY < SCREEN_H)) {
            _ctrlMode = false;
            for (std::map<std::string, Buttons*>::iterator it=_buttons.begin(); it!=_buttons.end(); ++it)
                it->second->setSelected(false);
            for (std::map<std::string, Checkbox*>::iterator it=_checkboxes.begin(); it!=_checkboxes.end(); ++it)
                it->second->setSelected(false);
        }
    }


    //Touch
    memcpy( &_touchOld,  &_touch, sizeof(_touchOld));
    sceTouchPeek(0, &_touch, 1);

    _touchX = lerp(_touch.report[0].x, 1919, 960);
    _touchY = lerp(_touch.report[0].y, 1087, 544);

    _touchOldX = lerp(_touchOld.report[0].x, 1919, 960);
    _touchOldY = lerp(_touchOld.report[0].y, 1087, 544);

}

void Menu::endMenu() {
    if (!_ctrlMode) {
        if (_ctrl_press.buttons)
            _ctrlMode = true;
    }

}



//Setter
void Menu::setMenu(const Step step) {
	_step = step;
}

// Getter
const Step Menu::getMenu() const {
	return _step;
}
