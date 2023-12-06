#include "../../include/controllers/controllers.hpp"

Controller::Controller(GameData *data) {
    this->data = data;
    jump_to_last_page = false;
}

Controller::~Controller() {}

bool Controller::IsLastController() { return false; }

DisplayContent Controller::GetDisplayContext() { return DisplayContent(); }

void Controller::HandleInput() {}

Controller *Controller::Next() { return NULL; }
