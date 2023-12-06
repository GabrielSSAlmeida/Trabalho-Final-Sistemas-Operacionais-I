#ifndef GAME_CONTROLLER
#define GAME_CONTROLLER

#include "../wordManager.hpp"
#include "../timer.hpp" 

class GameData{
    public:
        WordManager wordManager;
        Timer timer;
        int correctGuesses;

        GameData(const std::string wordsAddress, int timeLeft); 
};

#endif
