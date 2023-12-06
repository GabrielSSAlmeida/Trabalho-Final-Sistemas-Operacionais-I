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

void WordsManager::readNextQuestion() {
    if (isRunning) {
        std::string nextWord;
        std::getline(wordFile, nextWord);
        std::string aux;
        for (int i = 0; i < NUMBER_OF_ALTERNATIVES; i++) {
            std::getline(wordFile, aux);
            nextWord.append("\n").append(aux);
        }
        std::getline(wordFile, aux);
        nextWord.append("\n").append(std::string(REFUSE_TO_ANSWER));
        nextWord_buffer.write(nextWord);
    }
}

WordsManager::WordsManager(const std::string &words_address) {
    wordFile.open(Words_address);
    current_question = -1;
    is_running = true;
    sem_init(&stop, 0, 0);
    thread([=]{
        while(is_running) {
            read_nextWord();
        }
        sem_post(&stop);
    }).detach();
}

WordsManager::~WordsManager() {
    is_running = false;
    get_nextWord();
    sem_wait(&stop);
    wordFile.close();
}

std::string WordsManager::get_nextWord() {
    if (current_question >= NUMBER_OF_Words)
        return string("");
    std::string question = nextWord_buffer.read();
    current_question++;
    return question;
}

bool WordsManager::isCorrect(std::string answer) {
    std::ranges::transform(answer, answer.begin(), [](unsigned char &c){
        return std::tolower(c);
    });

    return answer;
}
