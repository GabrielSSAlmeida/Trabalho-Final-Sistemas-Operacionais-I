#include "../include/timer.hpp"
#include "../include/display.hpp"
#include "../include/input.hpp"
#include <iostream>
#include <chrono>
#include <thread>
#include <semaphore>

#define MAX_TIME 50

int main() {

    //Starting Timer
    Timer timer(MAX_TIME);
    std::thread timerThread(&Timer::Start,&timer);

    //Starting Display
    Display display(&timer);
    //display.RunDisplay();
    std::thread displayThread(&Display::RunDisplay, &display);
    displayThread.detach();


    timerThread.join();

    // //Starting InputReader
    // UserReader userReader;
    // userReader.Start();
    // userReader.GetUserInput();

    // //std::thread inputThread(&UserReader::GetUserInput, &userReader);

    //std::this_thread::sleep_for(std::chrono::seconds(50));
    // //displayThread.join();
    // //inputThread.join();



    return 0;
}
