#include "../../include/control/controllers.h"

Controller::Controller(GameContext *context) {
    this->context = context;
    jump_to_last_page = false;
}

Controller::~Controller() {}

bool Controller::isLastController() { return false; }

DisplayContext Controller::getDisplayContext() { return DisplayContext(); }

void Controller::handleInput() {}

Controller *Controller::next() { return NULL; }
