/*
 **
 ** Made by Applelo
 **
 */

#include "Engine.hh"

extern unsigned char _binary_assets_img_LogoCtp_png_start;
extern unsigned char _binary_assets_img_LogoCtpHalloween_png_start;
extern unsigned char _binary_assets_img_LogoCtpAnniversary_png_start;
extern unsigned char _binary_assets_img_LogoCtpChristmas_png_start;

Engine::Engine() {

    _customisation = false;
    _launchNews = false;
    _launchForum = false;

    memset(&_init_param, 0, sizeof(SceAppUtilInitParam));
    memset(&_boot_param, 0, sizeof(SceAppUtilBootParam));
    sceAppUtilInit(&_init_param, &_boot_param);
    sceAppUtilSystemParamGetInt(SCE_SYSTEM_PARAM_ID_LANG, &_lang);
    sceAppUtilShutdown();

    sceIoMkdir(DIRECTORY_DATA, 0777);


    SceUID fileHandle = sceIoOpen(DIRECTORY_DATA "config.json", SCE_O_RDONLY, 0777);
    if (fileHandle < 0) {
        memcpy(&_logoRgb, this->getRgbColor(this->getLogoColor()), sizeof(_logoRgb));
        memcpy(&_backgroundRgb, this->getRgbColor(this->getBackgroundColor()), sizeof(_backgroundRgb));
        _data = json_pack(
                "{s:{s:i, s:i, s:i},s:{s:i, s:i, s:i},s:{s:b,s:b},s:b}",
                "logo", "r", _logoRgb[0], "g", _logoRgb[1], "b", _logoRgb[2],
                "background", "r", _backgroundRgb[0], "g", _backgroundRgb[1], "b", _backgroundRgb[2],
                "launch", "news", false, "forum", false,
                "customisation", false
        );
        json_dump_file(_data, DIRECTORY_DATA "config.json", 0);

    }
    else {
        _data = json_load_file(DIRECTORY_DATA "config.json", 0, NULL);
        _customisation = json_boolean_value(json_object_get(_data, "customisation"));
        _launchNews = json_boolean_value(json_object_get(json_object_get(_data, "launch"), "news"));
        _launchForum = json_boolean_value(json_object_get(json_object_get(_data, "launch"), "forum"));

        _logoRgb[0] = (int) json_number_value(json_object_get(json_object_get(_data, "logo"), "r"));
        _logoRgb[1] = (int) json_number_value(json_object_get(json_object_get(_data, "logo"), "g"));;
        _logoRgb[2] = (int) json_number_value(json_object_get(json_object_get(_data, "logo"), "b"));;

        _backgroundRgb[0] = (int) json_number_value(json_object_get(json_object_get(_data, "background"), "r"));
        _backgroundRgb[1] = (int) json_number_value(json_object_get(json_object_get(_data, "background"), "g"));
        _backgroundRgb[2] = (int) json_number_value(json_object_get(json_object_get(_data, "background"), "b"));
    }
    sceIoClose(fileHandle);

}

Engine::~Engine() {
}

int Engine::getLogoColor() {

    if (_customisation)
        return RGBA8(_logoRgb[0], _logoRgb[1], _logoRgb[2], 255);

    //Halloween
    if (_time.month == 10 && _time.day > 15)
        return COLOR_CTP_LOGO_HALLOWEEN;

    //Christmas
    if (_time.month == 12 && (_time.day > 14 && _time.day < 28))
        return COLOR_CTP_LOGO_CHRISTMAS;

    //CTP Anniversary
    if (_time.month == 12 && _time.day == 14)
        return COLOR_CTP_LOGO_ANNIVERSARY;

    return COLOR_CTP_LOGO;
}

int Engine::getBackgroundColor() {

    if (_customisation)
        return RGBA8(_backgroundRgb[0], _backgroundRgb[1], _backgroundRgb[2], 255);

    //Halloween
    if (_time.month == 10 && _time.day > 15)
        return COLOR_CTP_BG_HALLOWEEN;

    //Christmas
    if (_time.month == 12 && (_time.day > 14 && _time.day < 28))
        return COLOR_CTP_BG_CHRISTMAS;

    //CTP Anniversary
    if (_time.month == 12 && _time.day == 14)
        return COLOR_CTP_BG_ANNIVERSARY;

    return COLOR_CTP_BG;

}

vita2d_texture *Engine::getLogo() {

    //Halloween
    if (_time.month == 10 && _time.day > 15)
        return vita2d_load_PNG_buffer(&_binary_assets_img_LogoCtpHalloween_png_start);

    //CTP Anniversary
    if (_time.month == 12 && _time.day == 14)
        return vita2d_load_PNG_buffer(&_binary_assets_img_LogoCtpAnniversary_png_start);

    //Christmas
    if (_time.month == 12 && (_time.day > 14 && _time.day < 28))
        return vita2d_load_PNG_buffer(&_binary_assets_img_LogoCtpChristmas_png_start);

    return vita2d_load_PNG_buffer(&_binary_assets_img_LogoCtp_png_start);
}

int Engine::getLang() {
    return _lang;
}

void Engine::saveData() {
    _data = json_pack(
            "{s:{s:i, s:i, s:i},s:{s:i, s:i, s:i},s:{s:b,s:b},s:b}",
            "logo", "r", _logoRgb[0], "g", _logoRgb[1], "b", _logoRgb[2],
            "background", "r", _backgroundRgb[0], "g", _backgroundRgb[1], "b", _backgroundRgb[2],
            "launch", "news", _launchNews, "forum", _launchForum,
            "customisation", _customisation
    );
    sceIoRemove(DIRECTORY_DATA "config.json");
    json_dump_file(_data, DIRECTORY_DATA "config.json", 0);

}

void Engine::setRgbColor(const char* type, int *rgb) {
    if (!strcmp(type, "logo")) {
        for (int i = 0; i < 3; ++i) {
            _logoRgb[i] = rgb[i];
        }
    }
    else {
        for (int i = 0; i < 3; ++i) {
            _backgroundRgb[i] = rgb[i];
        }
    }
}

int * Engine::getRgbColor(int col) {
    //SDL Source code to convert RGBA8 to rgb
    uint8_t r,g,b;
    float a;
    a = (col>>24)&0xFF;
    if(a == 0) a = 0xFF; //Hack, to make things easier.
    a /= 0xFF;
    b = r*(1-a) + ((col>>16)&0xFF)*(a);
    g = g*(1-a) + ((col>> 8)&0xFF)*(a);
    r = b*(1-a) + ((col>> 0)&0xFF)*(a);
    static int result[3];
    result[0] = r;
    result[1] = g;
    result[2] = b;

    return result;
}

bool Engine::getLaunchNews() {
    return _launchNews;
}

bool Engine::getLaunchForum() {
    return _launchForum;
}

bool Engine::getCustomisation() {
    return _customisation;
}

void Engine::setLaunchNews(bool launchNews) {
    _launchNews = launchNews;
}

void Engine::setLaunchForum(bool launchForum) {
    _launchForum = launchForum;
}

void Engine::setCustomisation(bool customisation) {
    _customisation = customisation;
}