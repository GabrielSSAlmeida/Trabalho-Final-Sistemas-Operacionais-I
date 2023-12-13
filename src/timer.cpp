#include "../include/timer.hpp"
#include <thread>

Timer::Timer(int startingTime){
    this->startingTime = startingTime;
    timeLeft = startingTime;
    timerRunning = false;
    sem_init(&stop, 0, 0);
}

void Timer::Start(){
    if(IsRunning() || TimedOut())
        Reset();

    timerRunning = true;

    while(this->timeLeft > 0 && timerRunning) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        
        this->timeLeft--;
    }

    if(!timerRunning)
        sem_post(&stop);

    timerRunning = false;

}

std::string Timer::ToString() {
    const int barWidth = 100;
    float percentage = static_cast<float>(this->timeLeft) / this->startingTime;
    int progressBarWidth = static_cast<int>(barWidth * percentage);

    // Calculating time in minutes
    int minutes = 0;
    int seconds = this->timeLeft;
    while(seconds >= 60){        
        minutes++;
        seconds -= 60;
    }

    std::string str = "Tempo: [";
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