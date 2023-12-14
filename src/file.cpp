#include <iostream>
#include <fstream>
#include "../includes/file.h"
#include "../includes/palavra.h"


#define CHAR_BYTES 1
#define WORD_SIZE 6
#define HEAD_SIZE 5

// Função para ler uma palavra aleatória do arquivo
void readRandomWord(const std::string& filename, std::string &randomWord){
    std::ifstream file(filename);
    int numWords = 0;
    if(file.is_open()){
        // Obtém o tamanho total do arquivo
        file >> numWords;

        // Garante que há pelo menos um caractere no arquivo
        if(numWords > 0){
            srand(static_cast<unsigned>(time(nullptr)));
            int random = rand() % numWords;

            int byteoffsetWOrd = (random * WORD_SIZE * CHAR_BYTES)+HEAD_SIZE;
   
            // Move o ponteiro do arquivo para a posição aleatória
            file.seekg(byteoffsetWOrd, std::ios::beg);

            // Lê a palavra aleatória

            file >> randomWord;
            ArmazenaPalavra(randomWord);
        }
        file.close();
    } else {
        std::cerr << "Erro ao abrir o arquivo: " << filename << std::endl;
    }
}