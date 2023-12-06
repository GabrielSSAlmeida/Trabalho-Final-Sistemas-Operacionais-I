#include "../include/wordManager.hpp"
#include <fstream>
#include <thread>
#include <ctype.h>
#include <algorithm>

#include <ranges>

#define NUMBER_OF_WORDS 2293

using namespace std;

void WordManager::ReadNextWord(){
    nextWordBuffer.write("kermo");
}

WordManager::WordManager(const std::string &wordsAddress) {
    wordFile.open(wordsAddress);
    
    wordCounter = -1;
    isRunning = true;

    sem_init(&stop, 0, 0);
    thread([&]{
        while(isRunning) {
            ReadNextWord();
        }
        sem_post(&stop);
    }).detach();
}

WordManager::~WordManager() {
    isRunning = false;
    GetNextWord();
    sem_wait(&stop);
    wordFile.close();
}

std::string WordManager::GetNextWord(){
    if(wordCounter >= NUMBER_OF_WORDS)
        return string("");

    currentWord = nextWordBuffer.read();
    wordCounter++;

    return currentWord;
}

bool WordManager::IsCorrect(std::string answer) {
    std::transform(answer.begin(), answer.end(), answer.begin(), [](unsigned char c) {
        return std::tolower(c);
    });

    return answer == currentWord;
}