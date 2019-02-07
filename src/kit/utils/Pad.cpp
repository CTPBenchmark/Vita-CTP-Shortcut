#include "Pad.hpp"

Pad::Pad(){
	buttonAssign = checkButtonAssign();
	sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG_WIDE);

	ctrlPress = ctrlPeek;
	sceCtrlPeekBufferPositive(0, &ctrlPeek, 1);
	ctrlPress.buttons = ctrlPeek.buttons &  ~ctrlPress.buttons;
}


Pad::~Pad(){
	
}

void Pad::read(){
	
	ctrlPress = ctrlPeek;
	sceCtrlPeekBufferPositive(0, &ctrlPeek, 1);
	ctrlPress.buttons = ctrlPeek.buttons &  ~ctrlPress.buttons;

	held = this->readButtons(ctrlPeek.buttons, held);
	pressed = this->readButtons(ctrlPress.buttons, pressed);

	right = this->readAnalog(ctrlPeek, right, PAD_ANALOG_RIGHT);
	left = this->readAnalog(ctrlPeek, left, PAD_ANALOG_LEFT);

}

int Pad::checkButtonAssign(){
	
	int ret = 0;
	
	if(buttonAssign != -1)
		return buttonAssign;

	ret = sceRegMgrGetKeyInt("/CONFIG/SYSTEM", "button_assign", &buttonAssign);
	if (ret < 0) {
		return ret;
	}else{
		return buttonAssign;
	}
}

PadButtons Pad::resetPadButtons(PadButtons padButtons) {
	padButtons.up = false;
	padButtons.right = false;
	padButtons.down = false;
	padButtons.left = false;
	padButtons.cross = false;
	padButtons.circle = false;
	padButtons.triangle = false;
	padButtons.square = false;
	padButtons.leftTrigger = false;
	padButtons.rightTrigger = false;
	padButtons.start = false;
	padButtons.select = false;
	padButtons.volup = false;
	padButtons.voldown = false;

	padButtons.clicking = false;

	return padButtons;
}

PadAnalog Pad::readAnalog(SceCtrlData sceCtrlData, PadAnalog padAnalog, PadAnalogPosition padAnalogPosition) {

	padAnalog = this->resetPadAnalog(padAnalog);

	if (padAnalogPosition == PAD_ANALOG_LEFT) {
		padAnalog.x = sceCtrlData.lx;
		padAnalog.y = sceCtrlData.ly;
	}
	else {
		padAnalog.x = sceCtrlData.rx;
		padAnalog.y = sceCtrlData.ry;
	}

	if(abs((int) (padAnalog.x - PAD_ANALOG_CALIBRATION)) > PAD_ANALOG_DEADZONE){
		padAnalog.xCalibrated = ((padAnalog.x - PAD_ANALOG_CALIBRATION)/8);
		padAnalog.moving = true;
	}
	else {
		padAnalog.xCalibrated = 0;
	}

	if(abs((int) (padAnalog.y - PAD_ANALOG_CALIBRATION)) > PAD_ANALOG_DEADZONE){
		padAnalog.yCalibrated = ((padAnalog.y - PAD_ANALOG_CALIBRATION)/8);
		padAnalog.moving = true;
	}
	else {
		padAnalog.yCalibrated = 0;
	}


	return padAnalog;
}

PadButtons Pad::readButtons(unsigned int buttons, PadButtons padButtons) {

	padButtons = this->resetPadButtons(padButtons);

	padButtons.select = this->getButtonStatus(buttons, SCE_CTRL_SELECT);
	padButtons.start = this->getButtonStatus(buttons, SCE_CTRL_START);

	padButtons.up = this->getButtonStatus(buttons, SCE_CTRL_UP);
	padButtons.right = this->getButtonStatus(buttons, SCE_CTRL_RIGHT);
	padButtons.down = this->getButtonStatus(buttons, SCE_CTRL_DOWN);
	padButtons.left = this->getButtonStatus(buttons, SCE_CTRL_LEFT);

	padButtons.leftTrigger = this->getButtonStatus(buttons, SCE_CTRL_LTRIGGER) || this->getButtonStatus(buttons, SCE_CTRL_L1);
	padButtons.rightTrigger = this->getButtonStatus(buttons, SCE_CTRL_RTRIGGER) || this->getButtonStatus(buttons, SCE_CTRL_R1);

	padButtons.voldown = this->getButtonStatus(buttons, SCE_CTRL_VOLDOWN);
	padButtons.volup = this->getButtonStatus(buttons, SCE_CTRL_UP);

	padButtons.triangle = this->getButtonStatus(buttons, SCE_CTRL_TRIANGLE);
	padButtons.square = this->getButtonStatus(buttons, SCE_CTRL_SQUARE);
	padButtons.cross = buttonAssign ? this->getButtonStatus(buttons, SCE_CTRL_CIRCLE) : this->getButtonStatus(buttons, SCE_CTRL_CROSS);
	padButtons.circle = buttonAssign ? this->getButtonStatus(buttons, SCE_CTRL_CROSS) : this->getButtonStatus(buttons, SCE_CTRL_CIRCLE);

	padButtons.clicking = 	padButtons.select || padButtons.start ||
							padButtons.up || padButtons.right || padButtons.down || padButtons.left ||
							padButtons.leftTrigger || padButtons.rightTrigger ||
							padButtons.voldown || padButtons.volup ||
							padButtons.triangle || padButtons.square || padButtons.cross || padButtons.circle;

	return padButtons;
}

PadAnalog Pad::resetPadAnalog(PadAnalog padAnalog) {
	padAnalog.moving = false;
	padAnalog.xCalibrated = 0;
	padAnalog.yCalibrated = 0;

	return padAnalog;
}

bool Pad::getButtonStatus(unsigned int buttons, SceCtrlButtons sceCtrlButtons) {
	return (buttons & sceCtrlButtons) != 0;
}


