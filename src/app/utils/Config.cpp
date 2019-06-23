#include "Config.hh"

Config::Config() {
    sceIoMkdir(CONFIG_DIRECTORY_PATH, 0777);

    SceUID fileHandle = sceIoOpen(CONFIG_FILE_PATH, SCE_O_RDONLY, 0777);
    if (fileHandle < 0) {
       this->createConfig();
    }
    else {
        json = json_load_file(CONFIG_FILE_PATH, 0, nullptr);
        this->avoidOldConfig();
    }
    sceIoClose(fileHandle);

    this->loadConfig();
}

const RGBAColor &Config::getBackgroundColor() const {
    return backgroundColor;
}

const RGBAColor &Config::getIconsColor() const {
    return iconsColor;
}

const RGBAColor &Config::getForegroundColor() const {
    return foregroundColor;
}

int Config::getSpeed() const {
    return speed;
}

bool Config::isLaunchNews() const {
    return launchNews;
}

bool Config::isLaunchForum() const {
    return launchForum;
}

bool Config::isCustomisation() const {
    return customisation;
}

void Config::createConfig() {
    json = json_pack(
            "{"
            "s:{s:i, s:i, s:i, s:i},"
            "s:{s:i, s:i, s:i, s:i}, "
            "s:{s:i, s:i, s:i, s:i},"
            "s:{s:b,s:b},"
            "s:i,"
            "s:b"
            "}",

            "icons", "r", ICONS_COLOR_CTP_R, "g", ICONS_COLOR_CTP_G, "b", ICONS_COLOR_CTP_B, "a", 255,
            "background", "r", BACKGROUND_COLOR_CTP_R, "g", BACKGROUND_COLOR_CTP_G, "b", BACKGROUND_COLOR_CTP_B, "a", 255,
            "foreground", "r", 0, "g", 0, "b", 0, "a", 0,
            "launch", "news", false, "forum", false,
            "speed", DEFAULT_SPEED,
            "customisation", false
    );
    json_dump_file(json, CONFIG_FILE_PATH, 0);
}

void Config::loadConfig() {
    customisation = json_boolean_value(json_object_get(json, "customisation"));
    launchNews = json_boolean_value(json_object_get(json_object_get(json, "launch"), "news"));
    launchForum = json_boolean_value(json_object_get(json_object_get(json, "launch"), "forum"));

    iconsColor.r = (unsigned int) json_number_value(json_object_get(json_object_get(json, "icons"), "r"));
    iconsColor.g = (unsigned int) json_number_value(json_object_get(json_object_get(json, "icons"), "g"));
    iconsColor.b = (unsigned int) json_number_value(json_object_get(json_object_get(json, "icons"), "b"));
    iconsColor.a = (unsigned int) json_number_value(json_object_get(json_object_get(json, "icons"), "a"));;

    backgroundColor.r = (unsigned int) json_number_value(json_object_get(json_object_get(json, "background"), "r"));
    backgroundColor.g = (unsigned int) json_number_value(json_object_get(json_object_get(json, "background"), "g"));
    backgroundColor.b = (unsigned int) json_number_value(json_object_get(json_object_get(json, "background"), "b"));
    backgroundColor.a = (unsigned int) json_number_value(json_object_get(json_object_get(json, "background"), "a"));

    foregroundColor.r = (unsigned int) json_number_value(json_object_get(json_object_get(json, "foreground"), "r"));
    foregroundColor.g = (unsigned int) json_number_value(json_object_get(json_object_get(json, "foreground"), "g"));
    foregroundColor.b = (unsigned int) json_number_value(json_object_get(json_object_get(json, "foreground"), "b"));
    foregroundColor.a = (unsigned int) json_number_value(json_object_get(json_object_get(json, "foreground"), "a"));

    speed = (int)json_number_value(json_object_get(json, "speed"));
}

void Config::saveConfig() {
    json = json_pack(
            "{"
            "s:{s:i, s:i, s:i, s:i},"
            "s:{s:i, s:i, s:i, s:i}, "
            "s:{s:i, s:i, s:i, s:i},"
            "s:{s:b,s:b},"
            "s:i,"
            "s:b"
            "}",

            "icons", "r", iconsColor.r, "g", iconsColor.g, "b", iconsColor.b, "a", iconsColor.a,
            "background", "r", backgroundColor.r, "g", backgroundColor.g, "b", backgroundColor.b, "a", backgroundColor.a,
            "foreground", "r", foregroundColor.r, "g", foregroundColor.g, "b", foregroundColor.b, "a", foregroundColor.a,
            "launch", "news", launchNews, "forum", launchForum,
            "speed", speed,
            "customisation", customisation
    );

    sceIoRemove(CONFIG_FILE_PATH);
    json_dump_file(json, CONFIG_FILE_PATH, 0);
}

void Config::avoidOldConfig() {
    if (json_object_get(json, "foreground") == nullptr) {
        sceIoRemove(CONFIG_FILE_PATH);
        this->createConfig();
    }
}

void Config::setBackgroundColor(const RGBAColor &backgroundColor) {
    Config::backgroundColor = backgroundColor;
}

void Config::setIconsColor(const RGBAColor &iconsColor) {
    Config::iconsColor = iconsColor;
}

void Config::setForegroundColor(const RGBAColor &foregroundColor) {
    Config::foregroundColor = foregroundColor;
}

void Config::setLaunchNews(bool launchNews) {
    Config::launchNews = launchNews;
}

void Config::setLaunchForum(bool launchForum) {
    Config::launchForum = launchForum;
}

void Config::setCustomisation(bool customisation) {
    Config::customisation = customisation;
}

void Config::setSpeed(int speed) {
    Config::speed = speed;
}

