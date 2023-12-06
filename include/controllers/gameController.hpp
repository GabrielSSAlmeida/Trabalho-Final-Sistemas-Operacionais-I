#ifndef GAME_CONTEXT
#define GAME_CONTEXT

#include "../questions_manager.hpp"
#include "../timer.hpp" 

class GameData{
    public:
        WordManager wordManager;
        Timer timer;
        int correctGuesses;

        GameData(const std::string questions_addr, int questions_timeout); 
};

#endif
