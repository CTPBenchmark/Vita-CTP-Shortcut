#ifndef VITA_MATERIAL_KIT_IME_HH
#define VITA_MATERIAL_KIT_IME_HH

#include <stdio.h>
#include <string>
#include <string.h>
#include <stdbool.h>

#include <vita2d.h>
#include <psp2/appmgr.h>
#include <psp2/apputil.h>
#include <psp2/types.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/message_dialog.h>
#include <psp2/ime_dialog.h>
#include <psp2/display.h>
#include <psp2/gxm.h>
#include <psp2/kernel/sysmem.h>

#define IME_DIALOG_RESULT_NONE 0
#define IME_DIALOG_RESULT_RUNNING 1
#define IME_DIALOG_RESULT_FINISHED 2
#define IME_DIALOG_RESULT_CANCELED 3


class UtilsIME{
private:
	int i;
	SceCommonDialogStatus status;

	void oslOskGetText(char *text);
	void initImeDialog(const char *title, const char *initialText, int maxTextLength, unsigned int type, unsigned int option);

	public:
		UtilsIME();
		std::string getUserText(const char *title, const char *showText = "", unsigned int type = SCE_IME_TYPE_BASIC_LATIN, int maxTextLength = 128, unsigned int option = 0);
		SceCommonDialogStatus getStatus() const;

		void utf16ToUtf8(uint16_t *src, uint8_t *dst);
		void utf8ToUtf16(uint8_t *src, uint16_t *dst);
};

#endif

