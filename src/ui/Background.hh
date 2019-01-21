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

#define LOGO_COLOR_CTP 				RGBA8(208, 210, 210, 255)
#define LOGO_COLOR_HALLOWEEN 		RGBA8(171, 88, 57, 255)
#define LOGO_COLOR_CHRISTMAS 		RGBA8(212, 36, 38, 255)
#define LOGO_COLOR_ANNIVERSARY 		RGBA8(101, 48, 177, 255)

class Background {
private:
	int backgroundColor;
	int iconColor;
	int foregroundColor;
	float speed;
	float position;
	vita2d_texture* texture;
	int imgWidth;
	int imgHeight;
	int calc;

public:
	Background();
	Background(vita2d_texture* texture, int backgroundColor, int iconColor);
	Background(vita2d_texture* texture, int backgroundColor, int iconColor, int foregroundColor, float speed);
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
