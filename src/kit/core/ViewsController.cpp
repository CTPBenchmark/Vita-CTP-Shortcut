#include "ViewsController.hh"

ViewsController::ViewsController(std::string actualView) : actualView(actualView) {
    previousView = actualView;
}

std::string ViewsController::getActualView() {
    return actualView;
}

std::string ViewsController::getPreviousView() {
    return previousView;
}

void ViewsController::setActualView(std::string actualView) {
    this->previousView = this->actualView;
    this->actualView = std::move(actualView);
}

