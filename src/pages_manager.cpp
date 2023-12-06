#include "../include/pages_manager.hpp"
#include <iostream>

PagesManager::PagesManager(SharedBuffer<DisplayContent> *buffer) {
    this->buffer = buffer;
    next_page();
}

PagesManager::~PagesManager() {}

void PagesManager::display_page() {
    std::system("tput reset");

    std::cout << context.content << std::endl;

    bool clear_after = context.timer->IsRunning();

    while(context.timer->IsRunning()) {
        std::cout << "\r" << context.timer->ToString() 
            << std::string(50, ' ') << "R: " << std::flush;
    }
    
    if (clear_after) {
        std::system("tput reset");
        if (context.timer->TimedOut())
            std::cout << "Aperte enter para ver os resultados..." << std::endl;
    }
}

bool PagesManager::is_at_last_page() {
    return context.stop;
}

void PagesManager::next_page() {
    if (!context.stop)
        context = buffer->read();
}
