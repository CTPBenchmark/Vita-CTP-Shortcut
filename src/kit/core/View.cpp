
#include "View.hh"

View::View(std::string name)  {
    this->name = std::move(name);
}

std::string View::getName() const {
    return name;
}

void View::setUi(Ui *ui) {
    View::ui = ui;
}

void View::setViewsController(ViewsController *viewsController) {
    View::viewsController = viewsController;
}

void View::setUtils(Utils *utils) {
    View::utils = utils;
}

void View::contents() {

}

void View::controls() {

}

void View::beforeEnter() {

}

void View::beforeExit() {

}


