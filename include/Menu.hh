/*
**
** Made by Applelo
**
*/

#include "Engine.hh"
#include "Background.hh"
#include "Buttons.hh"
#include "Checkbox.hh"
#include "Keyboard.hh"

#ifndef MENU_HH_
# define MENU_HH_

typedef enum Step {
	MAIN = 0,
    SETTINGS,
	CUSTOMISATION,
    EXIT
} Step;



class Menu {
private:
	Step _step;
	SceCtrlData _ctrl_peek;
	SceCtrlData _ctrl_press;
    SceTouchData _touchOld;
    SceTouchData _touch;
    int _touchX;
    int _touchY;
    int _touchOldX;
    int _touchOldY;
    int _selectorX;
    int _selectorY;
    bool _ctrlMode;
	const char *_rgbMode;
    int *_actualRgb;
    std::string _forumUri;
    std::string _newsUri;

	std::map<std::string, std::string> _lang;
	vita2d_pgf *_pgf;
    std::map<std::string, vita2d_texture*> _icons;
	vita2d_texture *_wallolo;
	Engine *_engine;
	Background *_background;
	vita2d_texture *_logo;
	std::map<int, Buttons*> _less;
	std::map<int, Buttons*> _number;
	std::map<int, Buttons*> _more;
	std::map<std::string, Buttons*> _buttons;
	std::map<std::string, Checkbox*> _checkboxes;
    Keyboard* _keyboard;

    void startMenu();
    void endMenu();


public:
	Menu();
	virtual ~Menu();

	//Getter
	const Step getMenu() const;

	//Setter
	void setMenu(const Step step);

	//Display Menu
	void main();
    void settings();
	void customisation();


};

#endif /* !MENU_HH_ */
