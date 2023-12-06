#include <iostream>
#include <cstdio>
#include <thread>

#include <fstream>
#include <vector>
#include <string>

#include "../include/menu.hpp" 
#include "../include/palavra.hpp"

#define CHAR_BYTES 1
#define WORD_SIZE 6
#define HEAD_SIZE 5


// Função para ler uma palavra aleatória do arquivo
void readRandomWord(const std::string& filename, std::string& randomWord) {
    std::ifstream file(filename);
    int numWords = 0;
    if (file.is_open()) {
        // Obtém o tamanho total do arquivo
        file >> numWords;

        // Garante que há pelo menos um caractere no arquivo
        if (numWords > 0) {
            srand(static_cast<unsigned>(time(nullptr)));
            int random = rand() % numWords;

            int byteoffsetWOrd = (random * WORD_SIZE * CHAR_BYTES)+HEAD_SIZE;
   
            // Move o ponteiro do arquivo para a posição aleatória
            file.seekg(byteoffsetWOrd, std::ios::beg);

            // Lê a palavra aleatória
            file >> randomWord;
        } else {
            std::cerr << "O arquivo está vazio." << std::endl;
        }

        file.close();
    } else {
        std::cerr << "Erro ao abrir o arquivo: " << filename << std::endl;
    }
}



int main(){

    PrintMenu();

    // Iniciar timer
    // Enquanto tiver tempo...
    // Receber palavra aleatória do arquivo
    std::string palavra;

    // Nome do arquivo a ser lido
    std::string filename = "saida.txt";

    // Criar uma thread para ler o arquivo
    std::thread fileReadingThread(readRandomWord, filename, std::ref(palavra));


    // Aguardar a conclusão da thread
    fileReadingThread.join();

    // Imprimir as linhas do arquivo
    std::cout << palavra;


    // Jogo inicia para essa palavra
    //IniciarJogo(palavra);

    return  0;
}