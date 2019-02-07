/*
**
** Made by Applelo
**
*/

#ifndef BACKGROUND_HH_
# define BACKGROUND_HH_

#include <vita2d.h>
#include <math.h>

#define BACKGROUND_COLOR_CTP 			RGBA8(238, 238, 238, 255)
#define BACKGROUND_COLOR_HALLOWEEN 		RGBA8(223, 107, 63, 255)
#define BACKGROUND_COLOR_CHRISTMAS 		RGBA8(255, 255, 255, 255)
#define BACKGROUND_COLOR_ANNIVERSARY 	RGBA8(126, 60, 222, 255)

#define ICONS_COLOR_CTP 				RGBA8(208, 210, 210, 255)
#define ICONS_COLOR_HALLOWEEN 			RGBA8(171, 88, 57, 255)
#define ICONS_COLOR_CHRISTMAS 			RGBA8(212, 36, 38, 255)
#define ICONS_COLOR_ANNIVERSARY 		RGBA8(101, 48, 177, 255)

#define FOREGROUND_COLOR_CTP			RGBA8(0, 0, 0, 0)

#define BACKGROUND_COLOR_CTP_R 238
#define BACKGROUND_COLOR_CTP_G 238
#define BACKGROUND_COLOR_CTP_B 238

#define ICONS_COLOR_CTP_R 208
#define ICONS_COLOR_CTP_G 210
#define ICONS_COLOR_CTP_B 210

#define DEFAULT_SPEED 0.5

class Background {
private:
	int backgroundColor;
	int iconsColor;
	int foregroundColor;
	float speed;
	float position;
	vita2d_texture* texture;
	int imgWidth;
	int imgHeight;
	int calc;

public:
	Background();
	Background(vita2d_texture* texture, int backgroundColor, int iconsColor);
	Background(vita2d_texture* texture, int backgroundColor, int iconsColor, int foregroundColor, float speed);
	virtual ~Background();

	//Setter
	void setTexture(vita2d_texture* texture);
	void setSpeed(float speed);
	void setBackgroundColor(int backgroundColor);
	void setLogoColor(int iconColor);
	void setForegroundColor(int foregroundColor);

	//Getter
	float getPosition();

	// Display
	void display();


};

#endif /* !BACKGROUND_HH_ */
