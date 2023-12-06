#include "../include/timer.hpp"
#include <thread>

Timer::Timer(int startingTime) {
    this->startingTime = startingTime;
    timeLeft = startingTime;
    timerRunning = false;
    sem_init(&stop, 0, 0);
}

// void Timer::displayProgressBar(int progress, int total){
//     const int barWidth = 100;
//     float percentage = static_cast<float>(progress) / total;
//     int progressBarWidth = static_cast<int>(barWidth * percentage);

//     std::lock_guard<std::mutex> lock(consoleMutex);  // Lock to protect console output
//     std::cout << "[";
//     for (int i = 0; i < barWidth; ++i) {
//         if (i < progressBarWidth) {
//             std::cout << "=";
//         } else {
//             std::cout << " ";
//         }
//     }

//     // Calculating time in minutes
//     int minutes = 0;
//     while(progress >= 60){        
//         minutes++;
//         progress -= 60;
//     }

//     //std::cout << "] " << static_cast<int>(minutes) << ":" << static_cast<int>(progress) << " left\r";
//     std::cout << "] " << std::setfill('0') << std::setw(2) << minutes << ":" << std::setw(2) << progress << " left\r";
//     std::cout.flush();
// }

void Timer::Start(){
    if (IsRunning() || TimedOut())
        Reset();

    timerRunning = true;
    timeLeft = startingTime;

    std::thread([=]{ 
        while(timeLeft > 0 && timerRunning) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            timeLeft--;
        }

        if (!timerRunning)
            sem_post(&stop);

        timerRunning = false;
    }).detach();
}

std::string Timer::ToString() {
    const int barWidth = 100;
    float percentage = static_cast<float>(timeLeft) / startingTime;
    int progressBarWidth = static_cast<int>(barWidth * percentage);

    // Calculating time in minutes
    int minutes = 0;
    int seconds = timeLeft;
    while(timeLeft >= 60){        
        minutes++;
        seconds -= 60;
    }

    std::string str = "Tempo restante: [";
    str.append(std::string(progressBarWidth, '#'));
    str.append(std::string(barWidth - progressBarWidth, ' '));
    str.append("]");
    str.append(std::to_string(minutes));
    str.append(":");
    str.append(std::to_string(seconds));
    return str;
}

void Timer::Reset() {
    if (timerRunning) {
        timerRunning = false;
        sem_wait(&stop);
        timeLeft = startingTime;     
    }
}

Timer::~Timer() {
    Reset();
}

bool Timer::IsRunning(){
    return timerRunning;
}

bool Timer::TimedOut(){
    return timeLeft == 0;
}

void Timer::AddBonus(int tries){
    if(!IsRunning()) return;
    
    int bonus = 14 - tries*2;

    if(timeLeft + bonus > this->startingTime)
        timeLeft = this->startingTime;
    else
        timeLeft += bonus;
}