#ifndef VITA_MATERIAL_KIT_PAD_HPP
#define VITA_MATERIAL_KIT_PAD_HPP

#include <psp2/ctrl.h>
#include <psp2/registrymgr.h>
#include <math.h>

#define PAD_ANALOG_DEADZONE 25
#define PAD_ANALOG_CALIBRATION 128

typedef struct PadButtons {
    bool up;
    bool right;
    bool down;
    bool left;

    bool cross;
    bool circle;
    bool triangle;
    bool square;

    bool leftTrigger;
    bool rightTrigger;

    bool start;
    bool select;

    bool volup;
    bool voldown;

    bool clicking;
} PadButtons;

typedef struct PadAnalog {
	unsigned int x;
	unsigned int y;

	int xCalibrated;
	int yCalibrated;

	bool moving;
} PadAnalog;

typedef enum PadAnalogPosition {
	PAD_ANALOG_LEFT,
	PAD_ANALOG_RIGHT
} PadAnalogPosition;


class UtilsPad{
	
	public:
		UtilsPad();
		~UtilsPad();
		void read();
		PadButtons pressed, held;//, released;
		PadAnalog right, left;
	private:
		int buttonAssign;
		SceCtrlData ctrlPeek, ctrlPress;

        int checkButtonAssign();
        PadButtons resetPadButtons(PadButtons padButtons);
        PadAnalog resetPadAnalog(PadAnalog padAnalog);
        bool getButtonStatus(unsigned int buttons, SceCtrlButtons sceCtrlButtons);

        PadAnalog readAnalog(SceCtrlData sceCtrlData, PadAnalog padAnalog, PadAnalogPosition padAnalogPosition);
        PadButtons readButtons(unsigned int buttons, PadButtons padButtons);

	
};


#endif //VITA_MATERIAL_KIT_PAD_HPP




