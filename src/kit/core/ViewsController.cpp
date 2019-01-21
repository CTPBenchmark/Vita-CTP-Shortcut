#include "ViewsController.hh"

ViewsController::ViewsController(std::string actualView) : actualView(actualView) {}

std::string ViewsController::getActualView() {
    return actualView;
}

void ViewsController::setActualView(std::string actualView) {
    this->actualView = actualView;
}

