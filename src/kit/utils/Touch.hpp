#ifndef VITA_MATERIAL_KIT_TOUCH_HPP
#define VITA_MATERIAL_KIT_TOUCH_HPP

#include <string.h>
#include <stdlib.h>

#include <psp2/touch.h>

#define SLEEP_CLICK_NORMAL 150000
#define SLEEP_CLICK_EXTENDED 350000

#define MIN_DIST_TO_SCROLL_Y 2
#define MIN_DIST_TO_SCROLL_X 2

typedef struct{
	int x;
	int y;
}vector2;

class Touch{
	private:
		int port;
		vector2 emptyClickPoint;

	public:
		Touch();

		SceTouchData touch_old[SCE_TOUCH_PORT_MAX_NUM];
		SceTouchData touch[SCE_TOUCH_PORT_MAX_NUM];
		vector2 lastClickPoint;
		vector2 lastTouchPoint;
		bool clicking;
		bool scrolling;
		int scrollDirX ;
		int scrollDirY;

		vector2 getClickPoint();
		void read();

		
};








#endif



