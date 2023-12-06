#include "../../include/display/display.hpp"

Display::Display(SharedBuffer<DisplayContext> *buffer) {
    displayThread = std::thread([=]{
        
        PagesManager pages_manager(buffer);

        while(!pages_manager.is_at_last_page()) {
            pages_manager.display_page();
            pages_manager.next_page();
        }

        pages_manager.display_page();
    });
}

Display::~Display() {}

void Display::startDetached() {
    displayThread.detach();
}

void Display::startJoined() {
    displayThread.join();
}
