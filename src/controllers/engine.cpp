#include "../../include/controllers/engine.hpp"
#include "../../include/utils.hpp"
#include <iostream>

#define TIMER_TIMEOUT 30

Engine::Engine(SharedBuffer<DisplayContent> *buffer, std::string questions_address) 
        : context(questions_address, TIMER_TIMEOUT){
    current_controller = new StartController(&context);
    engine_thread = std::thread([&] {
            while(!current_controller->IsLastController()) {
                buffer->write(current_controller->GetDisplayContext());
                current_controller->HandleInput();
                delete_and_assign(&current_controller, current_controller->Next());
            }
            buffer->write(current_controller->GetDisplayContext());
            current_controller->HandleInput();
    });
}

Engine::~Engine() {
    delete current_controller;
}

void Engine::start_detached() {
    engine_thread.detach();
}

void Engine::start_joined() {
    engine_thread.join();
}
