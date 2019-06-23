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
public:
    WebModal(Config *config);

    void invokeWebModal(const char *url);
    void launchAutoWebModal();
    void launchCTPNews();
    void launchCTPForum();
};


#endif //CTP_SHORTCUT_WEBMODAL_HH
