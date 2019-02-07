#include "IME.hpp"


static uint16_t ime_title_utf16[SCE_IME_DIALOG_MAX_TITLE_LENGTH];
static uint16_t ime_initial_text_utf16[SCE_IME_DIALOG_MAX_TEXT_LENGTH];
static uint16_t ime_input_text_utf16[SCE_IME_DIALOG_MAX_TEXT_LENGTH + 1];
static uint8_t ime_input_text_utf8[SCE_IME_DIALOG_MAX_TEXT_LENGTH + 1];
		
void IME::utf16_to_utf8(uint16_t *src, uint8_t *dst) {
	for (i = 0; src[i]; i++) {
		if ((src[i] & 0xFF80) == 0) {
			*(dst++) = (uint8_t) (src[i] & 0xFF);
		} else if((src[i] & 0xF800) == 0) {
			*(dst++) = (uint8_t) (((src[i] >> 6) & 0xFF) | 0xC0);
			*(dst++) = (uint8_t) ((src[i] & 0x3F) | 0x80);
		} else if((src[i] & 0xFC00) == 0xD800 && (src[i + 1] & 0xFC00) == 0xDC00) {
			*(dst++) = (uint8_t) ((((src[i] + 64) >> 8) & 0x3) | 0xF0);
			*(dst++) = (uint8_t) ((((src[i] >> 2) + 16) & 0x3F) | 0x80);
			*(dst++) = (uint8_t) (((src[i] >> 4) & 0x30) | 0x80 | ((src[i + 1] << 2) & 0xF));
			*(dst++) = (uint8_t) ((src[i + 1] & 0x3F) | 0x80);
			i += 1;
		} else {
			*(dst++) = (uint8_t) (((src[i] >> 12) & 0xF) | 0xE0);
			*(dst++) = (uint8_t) (((src[i] >> 6) & 0x3F) | 0x80);
			*(dst++) = (uint8_t) ((src[i] & 0x3F) | 0x80);
		}
	}

	*dst = '\0';
}

void IME::utf8_to_utf16(uint8_t *src, uint16_t *dst) {
	for (i = 0; src[i];) {
		if ((src[i] & 0xE0) == 0xE0) {
			*(dst++) = (uint16_t) (((src[i] & 0x0F) << 12) | ((src[i + 1] & 0x3F) << 6) | (src[i + 2] & 0x3F));
			i += 3;
		} else if ((src[i] & 0xC0) == 0xC0) {
			*(dst++) = (uint16_t) (((src[i] & 0x1F) << 6) | (src[i + 1] & 0x3F));
			i += 2;
		} else {
			*(dst++) = src[i];
			i += 1;
		}
	}

	*dst = '\0';
}
 
void IME::initImeDialog(const char *title, const char *initialText, int maxTextLength, unsigned int type, unsigned int option) {
    // Convert UTF8 to UTF16
	utf8_to_utf16((uint8_t *)title, ime_title_utf16);
	utf8_to_utf16((uint8_t *)initialText, ime_initial_text_utf16);
 
    SceImeDialogParam param;
	sceImeDialogParamInit(&param);

	param.sdkVersion = 0x03150021,
	param.supportedLanguages = 0x0001FFFF;
	param.languagesForced = SCE_TRUE;
	param.type = type;
	param.option = option;
	if (option == SCE_IME_OPTION_MULTILINE)
		param.dialogMode = SCE_IME_DIALOG_DIALOG_MODE_WITH_CANCEL;
	param.title = ime_title_utf16;
	param.maxTextLength = (SceUInt32) maxTextLength;
	param.initialText = ime_initial_text_utf16;
	param.inputTextBuffer = ime_input_text_utf16;

	sceImeDialogInit(&param);
}

void IME::oslOskGetText(char *text){
	// Convert UTF16 to UTF8
	utf16_to_utf8(ime_input_text_utf16, ime_input_text_utf8);
	strcpy(text,(char*)ime_input_text_utf8);
}

std::string IME::getUserText(const char *title , const char *showtext, unsigned int type, unsigned int option) {
    bool shown_dial = false;
   
    char userText[512];
    strcpy(userText, showtext);
   	int run = 1;

   
    while (run) {
        vita2d_start_drawing();
        vita2d_clear_screen();
       
        if (!shown_dial) {
            initImeDialog(title, userText, 128, type, option);
            shown_dial = true;
            }
       
        status = sceImeDialogGetStatus();
       
        if (status == (SceCommonDialogStatus)IME_DIALOG_RESULT_FINISHED) {
            SceImeDialogResult result;
            memset(&result, 0, sizeof(SceImeDialogResult));
            sceImeDialogGetResult(&result);
 
            if (result.button == SCE_IME_DIALOG_BUTTON_CLOSE)
                status = (SceCommonDialogStatus)IME_DIALOG_RESULT_CANCELED;
            else
                oslOskGetText(userText);
 
            sceImeDialogTerm();
            shown_dial = 0;
            run = 0;
		}
       
        vita2d_end_drawing();
        vita2d_common_dialog_update();
        vita2d_swap_buffers();
        sceDisplayWaitVblankStart();
	}
    return userText;
}



IME::IME(){
	SceAppUtilInitParam initParam;
	SceAppUtilBootParam bootParam;
	SceCommonDialogConfigParam dialogParam;

	memset(&initParam, 0, sizeof(SceAppUtilInitParam));
	memset(&bootParam, 0, sizeof(SceAppUtilBootParam));
	memset(&dialogParam, 0, sizeof(SceCommonDialogConfigParam));

	sceAppUtilInit(&initParam, &bootParam);
	sceCommonDialogSetConfigParam(&dialogParam);
}

SceCommonDialogStatus IME::getStatus() const {
	return status;
}

