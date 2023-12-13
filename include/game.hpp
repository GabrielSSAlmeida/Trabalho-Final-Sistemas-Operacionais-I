
#ifndef GAME_H
    #define GAME_H

    #include <iostream>
    #include <unordered_map>
    #include <vector>
    #include <string>
    #include <chrono>
    #include <thread>
    #include <mutex>
    #include <iomanip>
    #include "semaphore.h"
    #include <atomic>
    #include <string>
    #include "timer.hpp"
    #include "display.hpp"

    #define MAX_TIME 50

    // ANSI escape codes for text color
    #define RESET   "\033[0m"
    #define RED     "\033[31m"
    #define GREEN   "\033[32m"
    #define YELLOW  "\033[33m"
    #define BLUE    "\033[34m"

    typedef std::unordered_map<char, std::vector<int> > tabelaLetras;

    class Game{
        private: 
            Timer *timer;
            Display *display;
            int tentativas;
            tabelaLetras letras;

            void verificaPalavra(std::string palavra);

            
        public:
            
            Game(Timer *timer, Display *display);

            void StartGame();
    };

#endif
