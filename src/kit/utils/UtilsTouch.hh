#ifndef VITA_MATERIAL_KIT_TOUCH_HH
#define VITA_MATERIAL_KIT_TOUCH_HH

#include <string.h>
#include <stdlib.h>

#include <psp2/touch.h>

#define SLEEP_CLICK_NORMAL 150000
#define SLEEP_CLICK_EXTENDED 350000

#define MIN_DIST_TO_SCROLL_Y 2
#define MIN_DIST_TO_SCROLL_X 2


class UtilsTouch{
	private:
		int port;
		SceIVector2 emptyClickPoint;

	public:
		UtilsTouch();

		SceTouchData touchOld[SCE_TOUCH_PORT_MAX_NUM];
		SceTouchData touch[SCE_TOUCH_PORT_MAX_NUM];
		SceIVector2 lastClickPoint;
		SceIVector2 lastTouchPoint;
		bool clicking;
		bool scrolling;
		int scrollDirX ;
		int scrollDirY;

		SceIVector2 getClickPoint();
		void read();

		
};








#endif



