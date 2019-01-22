#ifndef CTP_SHORTCUT_CONFIG_HH
#define CTP_SHORTCUT_CONFIG_HH

#include <jansson.h>
#include <psp2/io/dirent.h>
#include <psp2/io/fcntl.h>

#include "../ui/Background.hh"

#define CONFIG_DIRECTORY_PATH "ux0:/data/CTP/"
#define CONFIG_FILE_NAME "config.json"
#define CONFIG_FILE_PATH CONFIG_DIRECTORY_PATH CONFIG_FILE_NAME

typedef struct RGBColor {
    unsigned int r;
    unsigned int g;
    unsigned int b;
} RGBColor;

class Config {
private:
    RGBColor backgroundColor, iconsColor;
    bool launchNews, launchForum, customisation;
    json_t *json;

    void createConfig();
    void loadConfig();
    void avoidOldConfig();

public:
    Config();

    const RGBColor &getBackgroundColor() const;
    const RGBColor &getIconsColor() const;

    bool isLaunchNews() const;
    bool isLaunchForum() const;
    bool isCustomisation() const;

    void saveConfig();


};


#endif //CTP_SHORTCUT_CONFIG_HH
