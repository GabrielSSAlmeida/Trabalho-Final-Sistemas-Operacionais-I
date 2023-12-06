#include "../include/wordManager.hpp"
#include <fstream>
#include <thread>
#include <ctype.h>
#include <iostream>

#include <ranges>

#define CHAR_BYTES 1
#define WORD_SIZE 6

#define NUMBER_OF_WORDS 2293

using namespace std;


void WordManager::ReadNextWord() {
    if (isRunning) {
        std::string randomWord;
        int numWords = 0;
        if (wordFile.is_open()) {
            // Obtém o tamanho total do arquivo
            wordFile >> numWords;

            // Garante que há pelo menos um caractere no arquivo
            if (numWords > 0) {
                srand(static_cast<unsigned>(time(nullptr)));
                int random = rand() % numWords;

                int byteoffsetWOrd = (random * WORD_SIZE * CHAR_BYTES);
    
                // Move o ponteiro do arquivo para a posição aleatória
                wordFile.seekg(byteoffsetWOrd, std::ios::beg);

                // Lê a palavra aleatória
                wordFile >> randomWord;
            } else {
                std::cerr << "O arquivo está vazio." << std::endl;
            }

            wordFile.close();
        } else {
            std::cerr << "Erro ao abrir o arquivo" << std::endl;
        }
        nextWordBuffer.write(randomWord);
    }
}

WordManager::WordManager(const std::string &words_address) {
    wordFile.open(words_address);
    wordCounter = -1;
    isRunning = true;
    sem_init(&stop, 0, 0);
    thread([=]{
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

std::string WordManager::GetNextWord() {
    if (wordCounter >= NUMBER_OF_WORDS)
        return string("");
    std::string question = nextWordBuffer.read();
    wordCounter++;
    return question;
}

bool WordManager::isCorrect(std::string answer) {
    std::ranges::transform(answer, answer.begin(), [](unsigned char &c){
        return std::tolower(c);
    });

    return answer == curr;
}
