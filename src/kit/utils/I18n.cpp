
#include <string.h>
#include "I18n.hpp"

I18n::I18n() {
    SceAppUtilInitParam initParam;
    SceAppUtilBootParam bootParam;
    memset(&initParam, 0, sizeof(SceAppUtilInitParam));
    memset(&bootParam, 0, sizeof(SceAppUtilBootParam));

    sceAppUtilInit(&initParam, &bootParam);
    sceAppUtilSystemParamGetInt(SCE_SYSTEM_PARAM_ID_LANG, &defaultLang);
    this->setCurrentLanguage(defaultLang);
}

I18n::I18n(int lang) {
    this->setCurrentLanguage(lang);
}

void I18n::setCurrentLanguage(int lang) {
    json_error_t error;
    char languageCode[25];

    currentLang = lang;

    sprintf(languageCode, "app0:i18n/%s.json", getLanguageCode(lang));
    i18n_file = json_load_file(languageCode, 0, &error);
}

std::map<std::string, std::string> I18n::getI18nByCat(std::string cat) {
    std::map<std::string, std::string> result;

    json_t *obj = json_object_get(i18n_file, cat.c_str());
    const char *key;
    json_t *value;

    json_object_foreach(obj, key, value) {
        result.insert(std::pair<std::string,std::string>(key, json_string_value(value)));
    }

    return result;
}

int I18n::getCurrentLanguage() {
    return currentLang;
}

int I18n::getDefaultLanguage() {
    return defaultLang;
}


const char *I18n::getLanguageCode(int lang) {
    switch(lang) {
        case SCE_SYSTEM_PARAM_LANG_JAPANESE:
            return "jap";
        case SCE_SYSTEM_PARAM_LANG_ENGLISH_US:
            return "en_us";
        case SCE_SYSTEM_PARAM_LANG_FRENCH:
            return "fr";
        case SCE_SYSTEM_PARAM_LANG_SPANISH:
            return "es";
        case SCE_SYSTEM_PARAM_LANG_GERMAN:
            return "de";
        case SCE_SYSTEM_PARAM_LANG_ITALIAN:
            return "it";
        case SCE_SYSTEM_PARAM_LANG_DUTCH:
            return "nl";
        case SCE_SYSTEM_PARAM_LANG_PORTUGUESE_PT:
            return "pt";
        case SCE_SYSTEM_PARAM_LANG_RUSSIAN:
            return "ru";
        case SCE_SYSTEM_PARAM_LANG_KOREAN:
            return "ko";
        case SCE_SYSTEM_PARAM_LANG_CHINESE_T:
            return "zh_t";
        case SCE_SYSTEM_PARAM_LANG_CHINESE_S:
            return "zh_s";
        case SCE_SYSTEM_PARAM_LANG_FINNISH:
            return "fi";
        case SCE_SYSTEM_PARAM_LANG_SWEDISH:
            return "sv";
        case SCE_SYSTEM_PARAM_LANG_DANISH:
            return "da";
        case SCE_SYSTEM_PARAM_LANG_NORWEGIAN:
            return "no";
        case SCE_SYSTEM_PARAM_LANG_POLISH:
            return "pl";
        case SCE_SYSTEM_PARAM_LANG_PORTUGUESE_BR:
            return "br";
        case SCE_SYSTEM_PARAM_LANG_ENGLISH_GB:
            return "en_gb";
        case SCE_SYSTEM_PARAM_LANG_TURKISH:
            return "tk";
        default:
            return "en_us";
    }
}


