// #ifndef TIMER_H
//     #define TIMER_H

//     #include <iostream>
//     #include <chrono>
//     #include <thread>
//     #include <mutex>
//     #include <iomanip>

//     class Timer {
//     private:         
//         std::mutex consoleMutex;  // Mutex to protect console output    
//         int starting_time;

//     public:
//         //Timer(int starting_time);

//         ~Timer();

//         void displayProgressBar(int progress, int total);

//         void countdownTimer(int seconds);
//     };


// #endif



#ifndef TIMER_H
    #define TIMER_H

    #include <iostream>
    #include <chrono>
    #include <thread>
    #include <mutex>
    #include <iomanip>
    #include "semaphore.h"
    #include <atomic>
    #include <string>


    class Timer{
        private: 
            sem_t stop;
            std::atomic<bool> timerRunning;
            std::atomic<int> timeLeft; 
            int startingTime;
            std::thread timerThread;

        public:
            Timer(int starting_time);

            ~Timer();

            void Start();

            void Reset();
            
            std::string ToString();

            bool TimedOut();

            bool IsRunning();

            void AddBonus(int tries);

            void Join();
    };

#endif
