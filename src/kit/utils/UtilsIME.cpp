#include "UtilsIME.hpp"


static uint16_t ime_title_utf16[SCE_IME_DIALOG_MAX_TITLE_LENGTH];
static uint16_t ime_initial_text_utf16[SCE_IME_DIALOG_MAX_TEXT_LENGTH];
static uint16_t ime_input_text_utf16[SCE_IME_DIALOG_MAX_TEXT_LENGTH + 1];
static uint8_t ime_input_text_utf8[SCE_IME_DIALOG_MAX_TEXT_LENGTH + 1];

UtilsIME::UtilsIME(){
	utilsTexts = new UtilsTexts();

	SceAppUtilInitParam initParam;
	SceAppUtilBootParam bootParam;
	SceCommonDialogConfigParam dialogParam;

	memset(&initParam, 0, sizeof(SceAppUtilInitParam));
	memset(&bootParam, 0, sizeof(SceAppUtilBootParam));
	memset(&dialogParam, 0, sizeof(SceCommonDialogConfigParam));

	sceAppUtilInit(&initParam, &bootParam);
	sceCommonDialogSetConfigParam(&dialogParam);
}
 
void UtilsIME::initImeDialog(const char *title, const char *initialText, int maxTextLength, unsigned int type, unsigned int option) {
    // Convert UTF8 to UTF16
	utilsTexts->utf8ToUtf16((uint8_t *)title, ime_title_utf16);
	utilsTexts->utf8ToUtf16((uint8_t *)initialText, ime_initial_text_utf16);
 
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

void UtilsIME::oslOskGetText(char *text){
	// Convert UTF16 to UTF8
	utilsTexts->utf16ToUtf8(ime_input_text_utf16, ime_input_text_utf8);
	strcpy(text,(char*)ime_input_text_utf8);
}

std::string UtilsIME::getUserText(const char *title , const char *showText, unsigned int type, int maxTextLength, unsigned int option) {
    bool shown_dial = false;
   
    char userText[SCE_IME_DIALOG_MAX_TEXT_LENGTH];
    strcpy(userText, showText);
   	int run = 1;

   
    while (run) {
        vita2d_start_drawing();
        vita2d_clear_screen();
       
        if (!shown_dial) {
            initImeDialog(title, userText, maxTextLength, type, option);
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



SceCommonDialogStatus UtilsIME::getStatus() const {
	return status;
}

