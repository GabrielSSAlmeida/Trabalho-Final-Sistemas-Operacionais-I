#include "../include/input.hpp"
#include "../include/display.hpp"

void UserReader::Start() {
    inputThread = std::thread(&UserReader::InputThreadFunction, this);
}

std::string UserReader::GetUserInput() {
    std::unique_lock<std::mutex> lock(inputMutex);
    inputCV.wait(lock, [&] { return userInputReady.load(); });

    // Process user input
    std::string input = userInput;

    // Reset user input variables
    userInput.clear();
    userInputReady = false;

    return input;
}

bool UserReader::IsUserInputReady() const {
    return userInputReady.load();
}

void UserReader::ResetUserInput() {
    std::unique_lock<std::mutex> lock(inputMutex);
    userInput.clear();
    userInputReady = false;
}

void UserReader::InputThreadFunction() {
    while (true) {
        std::string input;
        std::getline(std::cin, input);

        // Lock and update shared variables
        std::unique_lock<std::mutex> lock(inputMutex);
        userInput = input;
        userInputReady = true;

        // Notify the main thread that user input is ready
        inputCV.notify_all();
    }
}


void UserReader::SignalDisplay() {
    std::unique_lock<std::mutex> lock(inputMutex);
    userInputReady = true;
    inputCV.notify_all();
}

void UserReader::ReleaseInputSemaphore() {
    std::unique_lock<std::mutex> lock(inputMutex);
    userInputReady = false;
}