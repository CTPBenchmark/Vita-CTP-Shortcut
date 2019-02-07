#include "Utils.hh"
#include "../utils/WebModal.hh"

Utils::Utils() {
    this->init();

    this->webModal->launchAutoWebModal();//auto launch
}

void Utils::init() {
   this->touch = new Touch();
   this->pad = new Pad();
   this->config = new Config();
   this->i18n = new I18n();
   this->webModal = new WebModal(this->config);
}

void Utils::read() {
    pad->read();
    touch->read();
}

