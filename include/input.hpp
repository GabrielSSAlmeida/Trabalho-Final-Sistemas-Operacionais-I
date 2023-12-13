#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>

class UserReader {
public:
    UserReader() : userInputReady(false) {}

    // Function to get user input
    std::string GetUserInput();

    // Function to check if user input is ready
    bool IsUserInputReady() const;

    // Function to reset user input
    void ResetUserInput();


        // Additional functions for signaling and releasing
    void SignalDisplay();
    void ReleaseInputSemaphore();

    void Start();
private:
    // Function to handle user input in a separate thread
    void InputThreadFunction();

private:
    std::string userInput;
    std::mutex inputMutex;
    std::condition_variable inputCV;
    std::atomic<bool> userInputReady;
    std::thread inputThread;
};

#endif