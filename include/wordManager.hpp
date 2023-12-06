#ifndef QUESTION
#define QUESTION

#include "shared_buffer.hpp"
#include <semaphore.h>
#include <string>
#include <fstream>
#include <vector>
#include <atomic>

class WordManager {
    private:
        sem_t stop;
        std::atomic<bool> isRunning;
        std::ifstream wordFile;
        SharedBuffer<std::string> nextWordBuffer;
        int wordCounter;
        std::string currentWord;

        void ReadNextWord();

    public:
        WordManager(const std::string &wordsAddress);

        ~WordManager();

        std::string GetNextWord();

        bool IsCorrect(std::string answer);
};

#endif
