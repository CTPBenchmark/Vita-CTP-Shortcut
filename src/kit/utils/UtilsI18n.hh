
#ifndef VITA_MATERIAL_KIT_I18N_HH
#define VITA_MATERIAL_KIT_I18N_HH

#include <string>
#include <stdio.h>
#include <map>
#include <jansson.h>
#include <psp2/apputil.h>
#include <psp2/system_param.h>

class UtilsI18n {
    private:
        json_t *i18nFile;
        int currentLang, defaultLang;

        const char* getLanguageCode(int lang);
    public:
        UtilsI18n();
        UtilsI18n(int lang);
        std::map<std::string, std::string> getI18nByCat(std::string cat);

        void setCurrentLanguage(int lang);
        int getCurrentLanguage();
        int getDefaultLanguage();
};


#endif //VITA_MATERIAL_KIT_I18N_HH
