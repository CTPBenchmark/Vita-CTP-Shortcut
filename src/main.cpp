#include "Menu.hh"

int main() {

    int run = 1;
    sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG);
	sceTouchSetSamplingState(SCE_TOUCH_PORT_FRONT, SCE_TOUCH_SAMPLING_STATE_START);
	sceTouchEnableTouchForce(SCE_TOUCH_PORT_FRONT);

	vita2d_init();
	vita2d_set_clear_color(RGBA8(0x00, 0x00, 0x00, 0xFF));

	Menu* menu = new Menu();



    while (run) {

    	vita2d_start_drawing();
    	vita2d_clear_screen();



    	if (menu->getMenu() == Step::MAIN)
    		menu->main();
    	//if (menu->getMenu() == Step::SETTINGS)
    		//menu->settings();
		//if (menu->getMenu() == Step::CUSTOMISATION)
			//menu->customisation();
        if (menu->getMenu() == Step::EXIT)
            run = 0;


        vita2d_end_drawing();
        vita2d_common_dialog_update();
        vita2d_swap_buffers();
        sceDisplayWaitVblankStart();
    }

    vita2d_fini();
    sceKernelExitProcess(0);
    return 0;
}
