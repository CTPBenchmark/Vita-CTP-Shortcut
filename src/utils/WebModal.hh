#ifndef CTP_SHORTCUT_WEBMODAL_HH
#define CTP_SHORTCUT_WEBMODAL_HH

#include "Config.hh"
#include <psp2/appmgr.h>
#include <string>

#define URI_WEBMODAL "webmodal: "
#define CTP_NEWS "http://customprotocol.com"
#define CTP_FORUM "http://customprotocol.com/forum"

class WebModal {
private:
    Config *config;
    std::string webModalUrl;
    void invokeWebModal(const char *url);
public:
    WebModal(Config *config);

    void launchAutoWebModal();
    void launchCTPNews();
    void launchCTPForum();
};


#endif //CTP_SHORTCUT_WEBMODAL_HH
