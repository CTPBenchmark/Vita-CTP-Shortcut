#include "Config.hh"

Config::Config() {
    sceIoMkdir(CONFIG_DIRECTORY_PATH, 0777);

    SceUID fileHandle = sceIoOpen(CONFIG_FILE_PATH, SCE_O_RDONLY, 0777);
    if (fileHandle < 0) {
       this->createConfig();
    }
    else {
        json = json_load_file(CONFIG_FILE_PATH, 0, NULL);
        this->avoidOldConfig();
    }
    sceIoClose(fileHandle);

    this->loadConfig();
}

const RGBColor &Config::getBackgroundColor() const {
    return backgroundColor;
}

const RGBColor &Config::getIconsColor() const {
    return iconsColor;
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
            "{s:{s:i, s:i, s:i},s:{s:i, s:i, s:i},s:{s:b,s:b},s:b}",
            "icons", "r", ICONS_COLOR_CTP_R, "g", ICONS_COLOR_CTP_G, "b", ICONS_COLOR_CTP_B,
            "background", "r", BACKGROUND_COLOR_CTP_R, "g", BACKGROUND_COLOR_CTP_G, "b", BACKGROUND_COLOR_CTP_B,
            "launch", "news", false, "forum", false,
            "customisation", false
    );
    json_dump_file(json, CONFIG_FILE_PATH, 0);
}

void Config::loadConfig() {
    customisation = json_boolean_value(json_object_get(json, "customisation"));
    launchNews = json_boolean_value(json_object_get(json_object_get(json, "launch"), "news"));
    launchForum = json_boolean_value(json_object_get(json_object_get(json, "launch"), "forum"));

    iconsColor.r = (unsigned int) json_number_value(json_object_get(json_object_get(json, "icons"), "r"));
    iconsColor.g = (unsigned int) json_number_value(json_object_get(json_object_get(json, "icons"), "g"));;
    iconsColor.b = (unsigned int) json_number_value(json_object_get(json_object_get(json, "icons"), "b"));;

    backgroundColor.r = (unsigned int) json_number_value(json_object_get(json_object_get(json, "background"), "r"));
    backgroundColor.g = (unsigned int) json_number_value(json_object_get(json_object_get(json, "background"), "g"));
    backgroundColor.b = (unsigned int) json_number_value(json_object_get(json_object_get(json, "background"), "b"));
}

void Config::saveConfig() {
    json = json_pack(
            "{s:{s:i, s:i, s:i},s:{s:i, s:i, s:i},s:{s:b,s:b},s:b}",
            "icons", "r", iconsColor.r, "g", iconsColor.g, "b", iconsColor.b,
            "background", "r", backgroundColor.r, "g", backgroundColor.g, "b", backgroundColor.b,
            "launch", "news", launchNews, "forum", launchForum,
            "customisation", customisation
    );
    sceIoRemove(CONFIG_FILE_PATH);
    json_dump_file(json, CONFIG_FILE_PATH, 0);
}

void Config::avoidOldConfig() {
    if (json_object_get(json, "logo") != nullptr) {
        sceIoRemove(CONFIG_FILE_PATH);
        this->createConfig();
    }
}

