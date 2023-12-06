#include <iostream>
#include <cstdio>
#include <thread>

#include <fstream>
#include <vector>
#include <string>

#include "../include/menu.hpp" 
#include "../include/palavra.hpp"

// #define TIMELIMIT 300

// std::mutex consoleMutex;

// int *inputCounter = &numTentativas;

// void displayProgressBar(int progress, int total){
//     const int barWidth = 100;
//     float percentage = static_cast<float>(progress) / total;
//     int progressBarWidth = static_cast<int>(barWidth * percentage);

//     {
//         std::lock_guard<std::mutex> lock(consoleMutex);  // Lock to protect console output
        
//         std::cout << "\e[A" << "\r";
        
//         std::cout << "[";
//         for (int i = 0; i < barWidth; ++i) {
//             if (i < progressBarWidth) {
//                 std::cout << "=";
//             } else {
//                 std::cout << " ";
//             }
//         }

//         // Calculating time in minutes
//         int minutes = 0;
//         while(progress >= 60){        
//             minutes++;
//             progress -= 60;
//         }

//         //std::cout << "] " << static_cast<int>(minutes) << ":" << static_cast<int>(progress) << " left\r";
//         std::cout << "] " << std::setfill('0') << std::setw(2) << minutes << ":" << std::setw(2) << progress << " left";
//         std::cout.flush();
//     }
// }

// void countdownTimer(int seconds){
//     for (int i = seconds; i > 0; --i) {
//         displayProgressBar(i, seconds);
//         {
//             std::lock_guard<std::mutex> lock(consoleMutex);  // Lock to protect console output
        
//             std::cout << "\n";
//         }

//         std::this_thread::sleep_for(std::chrono::seconds(1));
//     }

//     // Display a newline to move to the next line after the progress bar
//     {
//         std::lock_guard<std::mutex> lock(consoleMutex);  // Lock to protect console output
//         std::cout << std::endl;
//     }
// }
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
    // Oculta o cursor no terminal
    std::cout << "\e[?25l";

    PrintMenu();

    // Iniciar timer
    // Enquanto tiver tempo...
    // Receber palavra aleatória do arquivo

    // Iniciar timer
    std::thread countdownThread(countdownTimer, TIMELIMIT);

    std::string palavra = "kermo";
    
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

    countdownThread.join();


    std::cout << "\e[?25h";

    return  0;
}