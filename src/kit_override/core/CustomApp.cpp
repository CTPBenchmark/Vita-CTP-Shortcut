#include "CustomApp.hh"

extern unsigned char _binary_assets_img_WalloloRep_png_start;

CustomApp::CustomApp(const char *firstView) : App(firstView) {
    ui->layoutTheme = new LayoutTheme(utils->config);
}

void CustomApp::beforeView() {
    ui->layoutTheme->display(this->viewsController->getActualView() == "Welcome");
}

