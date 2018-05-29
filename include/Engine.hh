/*
**
** Made by Applelo
**
*/

#include "../include/Utils.h"

#ifndef ENGINE_HH_
# define ENGINE_HH_



class Engine {
private:
    SceAppUtilInitParam _init_param;
    SceAppUtilBootParam _boot_param;
	SceDateTime _time;
	json_t *_data;
    int _lang;
    int _logoRgb[3];
    int _backgroundRgb[3];
	bool _customisation;
	bool _launchNews;
	bool _launchForum;


public:
	Engine();
	virtual ~Engine();

    void saveData();

	//Getter
	int getLogoColor();
	int getBackgroundColor();
	int getLang();
	vita2d_texture *getLogo();
	int * getRgbColor(int col);
	bool getCustomisation();
	bool getLaunchNews();
	bool getLaunchForum();

	//Setter
	void setRgbColor(const char* type, int *rgb);
	void setLaunchNews(bool launchNews);
	void setLaunchForum(bool launchForum);
	void setCustomisation(bool customisation);

};

#endif /* !MENU_HH_ */
