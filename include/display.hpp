
#ifndef DISPLAY_H
    #define DISPLAY_H

    #include <iostream>
    #include <chrono>
    #include <thread>
    #include <mutex>
    #include <iomanip>
    #include "semaphore.h"
    #include <atomic>
    #include <string>
    #include "timer.hpp"


    class Display{
        private: 
            std::string content;
            Timer *timer;
            
        public:
            std::mutex displayMutex;  // Mutex for thread safety

            Display(Timer *timer);

            ~Display();

            void UpdateDisplay();

            void ClearDisplay();

            void RunDisplay();
    };

#endif
