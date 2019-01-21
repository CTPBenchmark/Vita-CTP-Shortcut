#include "CustomApp.hh"

extern unsigned char _binary_assets_img_WalloloRep_png_start;

CustomApp::CustomApp(const char *firstView) : App(firstView) {
    wallolo = vita2d_load_PNG_buffer(&_binary_assets_img_WalloloRep_png_start);
    ui->background = new Background(wallolo, BACKGROUND_COLOR_CTP, LOGO_COLOR_CTP);
}

void CustomApp::beforeView() {
    ui->background->display();//fonctionne pas car croit que c'est Ui et pas UiCustom :'(
}

