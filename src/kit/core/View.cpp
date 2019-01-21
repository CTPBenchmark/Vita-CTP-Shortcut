#include "View.hh"

View::View(std::string name)  {
    this->name = name;
}

std::string View::getName() const {
    return name;
}

void View::contents() {
//display stuff go here
}

void View::controls() {
//controls go here
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


