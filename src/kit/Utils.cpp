#include "Utils.hh"

Utils::Utils() {
    this->init();
    this->webModal->launchAutoWebModal();//auto launch
}

void Utils::init() {
   this->touch = new UtilsTouch();
   this->pad = new UtilsPad();
   this->config = new Config();
   this->i18n = new UtilsI18n();
   this->ime = new UtilsIME();
   this->webModal = new WebModal(this->config);
   this->ptc = new UtilsPadTouchCtrl(this->pad, this->touch);
}

void Utils::read() {
    pad->read();
    touch->read();
    ptc->controller();
}

