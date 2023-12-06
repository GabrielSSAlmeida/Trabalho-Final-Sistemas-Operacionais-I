#include "../../include/display_content.hpp"

DisplayContent::DisplayContent() {
    content = "";
    timer = NULL;
    stop = false;
}

DisplayContent::DisplayContent(std::string content, Timer *timer, bool stop) {
    this->content = content;
    this->timer = timer;
    this->stop = stop;
}
