#ifndef CONTROL
#define CONTROL

#include "../display_content.hpp"
#include "controllers.hpp"
#include "gameController.hpp"
#include <atomic>
#include <thread>

class Engine {
    public:
        Engine(SharedBuffer<DisplayContent> *buffer, 
                const std::string questions_addr);

        ~Engine();

        void start_detached();

        void start_joined();

    private:
        Controller *current_controller;
        GameData context;
        std::thread engine_thread;
};

#endif
