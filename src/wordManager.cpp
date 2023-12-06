#include "../include/wordManager.h"
#include <fstream>
#include <thread>
#include <ctype.h>

#include <ranges>

#define NUMBER_OF_WORDS 20

using namespace std;

const std::vector<char> CORRECT_ANSWERS({
    'A', 'C', 'D', 'C', 'B', 'D', 'A', 'A', 'A', 'C',
    'B', 'B', 'A', 'D', 'D', 'B', 'D', 'A', 'C', 'B'
});

void WordsManager::readNextWord(){
    if(isRunning){
        std::getline(wordFile, nextWord);
    }
}

WordsManager::WordsManager(const std::string &wordsAddress) {
    wordFile.open(wordsAddress);
    
    wordCounter = -1;
    is_running = true;

    sem_init(&stop, 0, 0);
    thread([=]{
        while(is_running) {
            readNextWord();
        }
        sem_post(&stop);
    }).detach();
}

WordsManager::~WordsManager() {
    isRunning = false;
    getNextWord();
    sem_wait(&stop);
    wordFile.close();
}

std::string WordsManager::getNextWord(){
    if(wordCounter >= NUMBER_OF_WORDS)
        return string("");

    std::string word = nextWordBuffer.read();
    wordCounter++;

    return word;
}

bool WordsManager::isCorrect(std::string answer){
    std::ranges::transform(answer, answer.begin(), [](unsigned char &c){
        return std::tolower(c);
    });

    return answer;
}
