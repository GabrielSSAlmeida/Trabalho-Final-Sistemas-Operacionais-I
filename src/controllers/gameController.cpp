#include "../../include/controllers/gameController.hpp"

GameData::GameData(const std::string questions_addr, int timeLeft) 
        :  WordsManager(wordAddress), timer(timeLeft) {
    correctGuesses = 0;
}

