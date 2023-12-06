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
        int currentWord;

        void readNextWord();

    public:
        WordManager(const std::string &Word_adderess);

        ~WordManager();

        std::string getNextWord();

        bool isCorrect(char answer);
};

#endif
