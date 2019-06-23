#include "WebModal.hh"

WebModal::WebModal(Config *config) : config(config) {
}

void WebModal::invokeWebModal(const char *url) {
    webModalUrl = URI_WEBMODAL + std::string(url);
    sceAppMgrLaunchAppByUri(0xF0000, const_cast<char *>(webModalUrl.c_str()));
}

void WebModal::launchAutoWebModal() {
    if (config->isLaunchNews()) {
        this->launchCTPNews();
    }

    if (config->isLaunchForum()) {
       this->launchCTPForum();
    }
}

void WebModal::launchCTPNews() {
    this->invokeWebModal(CTP_NEWS);
}

void WebModal::launchCTPForum() {
    this->invokeWebModal(CTP_FORUM);
}
