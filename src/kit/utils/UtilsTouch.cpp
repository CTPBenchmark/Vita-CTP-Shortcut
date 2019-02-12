#include "UtilsTouch.hpp"

UtilsTouch::UtilsTouch(){
	emptyClickPoint.x = emptyClickPoint.y = 0;

	sceTouchSetSamplingState(SCE_TOUCH_PORT_FRONT, SCE_TOUCH_SAMPLING_STATE_START);
	sceTouchSetSamplingState(SCE_TOUCH_PORT_BACK, SCE_TOUCH_SAMPLING_STATE_START);
	sceTouchEnableTouchForce(SCE_TOUCH_PORT_FRONT);
	sceTouchEnableTouchForce(SCE_TOUCH_PORT_BACK);
}


void UtilsTouch::read(){
	memcpy(touchOld, touch, sizeof(touchOld));

	for(port = 0; port < SCE_TOUCH_PORT_MAX_NUM; port++) {
		sceTouchPeek((SceUInt32) port, &touch[port], 1);
	}

	if (touchOld[SCE_TOUCH_PORT_FRONT].reportNum >= 1 && touch[SCE_TOUCH_PORT_FRONT].reportNum == 0) {

		if(!scrolling){

			lastClickPoint.x = touchOld[SCE_TOUCH_PORT_FRONT].report[0].x / 2;  // 1920 touch => 960 display
			lastClickPoint.y = touchOld[SCE_TOUCH_PORT_FRONT].report[0].y / 2;
			scrollDirX = scrollDirY = 0;
			lastTouchPoint = emptyClickPoint;
			scrolling = false;
			clicking = true;

		} else {

			lastClickPoint = emptyClickPoint;
			lastTouchPoint = emptyClickPoint;
			scrollDirX = scrollDirY = 0;
			scrolling = false;
			clicking = false;

		}

	}else if(touchOld[SCE_TOUCH_PORT_FRONT].reportNum >= 1 && touch[SCE_TOUCH_PORT_FRONT].reportNum >= 1){

		scrollDirX = (touch[SCE_TOUCH_PORT_FRONT].report[0].x - touchOld[SCE_TOUCH_PORT_FRONT].report[0].x)/2;
		scrollDirY = (touch[SCE_TOUCH_PORT_FRONT].report[0].y - touchOld[SCE_TOUCH_PORT_FRONT].report[0].y)/2;
		lastTouchPoint.x = touchOld[SCE_TOUCH_PORT_FRONT].report[0].x/2;
		lastTouchPoint.y = touchOld[SCE_TOUCH_PORT_FRONT].report[0].y/2;

		if( abs(scrollDirX) > MIN_DIST_TO_SCROLL_X || abs(scrollDirY) > MIN_DIST_TO_SCROLL_Y) {
			lastClickPoint = emptyClickPoint;
			scrolling = true;
			clicking = false;
		}

	} else {

		lastClickPoint = emptyClickPoint;
		lastTouchPoint = emptyClickPoint;
		scrollDirX = scrollDirY = 0;
		scrolling = false;
		clicking = false;

	}
}

SceIVector2 UtilsTouch::getClickPoint() {
	return lastClickPoint;
}
