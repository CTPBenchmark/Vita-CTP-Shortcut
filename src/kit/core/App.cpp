#include "App.hh"

App::App(const char *firstView) {
    this->initVita2d();

    this->ui = new Ui();
    this->utils = new Utils();
    this->viewsController = new ViewsController(firstView);

    run = 1;
};


void App::insertView(View *view) {
    view->setViewsController(this->viewsController);
    view->setUi(this->ui);
    view->setUtils(this->utils);
    this->views[view->getName()] = view;
}


void App::main() {

    while (run) {
        vita2d_start_drawing();
        vita2d_clear_screen();

        this->utils->read();

        this->beforeView();

        if (this->views.find(viewsController->getActualView()) != this->views.end()) {
            this->views[viewsController->getActualView()]->contents();
            this->views[viewsController->getActualView()]->controls();
        }

        this->afterView();

        if (DEBUG_APP == 1) {
            this->debug();
        }

        this->checkExit();

        vita2d_end_drawing();
        vita2d_swap_buffers();
    }

}

void App::checkExit() {

    if (viewsController->getActualView() == VIEWS_CONTROLLER_EXIT_LOOP) {
        run = 0;
    }
    else if (viewsController->getActualView() == VIEWS_CONTROLLER_EXIT) {
        vita2d_fini();
        sceKernelExitProcess(0);
    }
}

void App::initVita2d() {
    vita2d_init();
    vita2d_set_clear_color((unsigned int) RGBA8(218, 219, 219, 255));
}

void App::debug() {

    ui->texts->drawF(0, 0, Body1, RGBA8(255, 0, 0, 255), false,
            "Current view: *%s*\nView found: %s",
            viewsController->getActualView().c_str(),
            this->views.find(viewsController->getActualView()) != this->views.end() ? "true" : "false"
    );
    int i = 0;
    for(auto const &kv : views) {
        ui->texts->drawF(600, 25 * i, Body1, RGBA8(255, 0, 0, 255), false,
                         "*%s* : %s", kv.first.c_str(), kv.second != nullptr ? "true" : "false");
        i++;
    }

}

void App::beforeView() {

}

void App::afterView() {

}
