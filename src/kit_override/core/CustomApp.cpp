#include "CustomApp.hh"

CustomApp::CustomApp(const char *firstView) : App(firstView) {
    ui->layoutTheme = new LayoutTheme(utils->config);
}

void CustomApp::beforeView() {
    ui->layoutTheme->display(this->viewsController->getActualView() == "Welcome");
}

