#include "../../include/controllers/controllers.hpp"

Controller::Controller(GameData *content) {
    this->content = content;
    jump_to_last_page = false;
}

Controller::~Controller() {}

bool Controller::isLastController() { return false; }

DisplayContent Controller::getDisplayContext() { return DisplayContent(); }

void Controller::handleInput() {}

Controller *Controller::next() { return NULL; }
