#include "../../include/controllers/gameController.hpp"

GameData::GameData(const std::string wordsAddress, int timeLeft) 
        :  wordManager(wordsAddress), timer(timeLeft) {
    correctGuesses = 0;
}

