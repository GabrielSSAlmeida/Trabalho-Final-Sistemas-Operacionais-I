#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <stdlib.h>
#include <mutex>  // Added for thread safety

#include "../include/display.hpp"

Display::Display(Timer* timer) {
    this->timer = timer;
}

Display::~Display() {}

void Display::UpdateDisplay() {
    std::lock_guard<std::mutex> lock(displayMutex);  // Lock the mutex for thread safety
    std::cout<<"\x1B[2J\x1B[0;0f";
    std::cout << this->content;
    verificaPalavra();
    fflush(stdin);
}

void Display::ClearDisplay() {
    {
        std::lock_guard<std::mutex> lock(displayMutex);  // Lock the mutex for thread safety
        this->content = "";
    }

    UpdateDisplay();
}

void Display::RunDisplay() {
    while (true) {
        // Update the content with the timer value
        {
            std::lock_guard<std::mutex> lock(displayMutex);  // Lock the mutex for thread safety
            this->content = timer->ToString() + "\n\n";
            this->content += "Kermo!";
        }

        UpdateDisplay();
    }
}

