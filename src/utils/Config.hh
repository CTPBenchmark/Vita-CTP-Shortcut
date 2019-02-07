#ifndef CTP_SHORTCUT_CONFIG_HH
#define CTP_SHORTCUT_CONFIG_HH

#include <jansson.h>
#include <psp2/io/dirent.h>
#include <psp2/io/fcntl.h>

#include "../ui/Background.hh"

#define CONFIG_DIRECTORY_PATH "ux0:/data/CTP/"
#define CONFIG_FILE_NAME "config.json"
#define CONFIG_FILE_PATH CONFIG_DIRECTORY_PATH CONFIG_FILE_NAME

typedef struct RGBAColor {
    unsigned int r;
    unsigned int g;
    unsigned int b;
    unsigned int a;
} RGBAColor;

class Config {
private:
    RGBAColor backgroundColor, iconsColor, foregroundColor;
    bool launchNews, launchForum, customisation;
    float speed;
    json_t *json;

    void createConfig();
    void loadConfig();
    void avoidOldConfig();

public:
    Config();

    const RGBAColor &getBackgroundColor() const;
    const RGBAColor &getIconsColor() const;
    const RGBAColor &getForegroundColor() const;

    float getSpeed() const;

    bool isLaunchNews() const;
    bool isLaunchForum() const;
    bool isCustomisation() const;

    void saveConfig();


};


#endif //CTP_SHORTCUT_CONFIG_HH
