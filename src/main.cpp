#include <iostream>
#include <cstdio>

#include "../include/display.hpp"
#include "../include/controllers/engine.hpp"

const std::string wordsAddress = "words.txt";

#define WINDOW_HEIGHT 50
#define WINDOW_WIDTH 50

int main(){
    // Oculta o cursor no terminal
    std::cout << "\e[?25l";

    // PrintMenu();

    // // Iniciar timer
    // // Enquanto tiver tempo...
    // // Receber palavra aleatória do arquivo

    // // Iniciar timer
    // std::thread countdownThread(countdownTimer, TIMELIMIT);

    // std::string palavra = "kermo";
    
    // // Jogo inicia para essa palavra
    // IniciarJogo(palavra);

    // countdownThread.join();


    SharedBuffer<DisplayContent> display_context;
    Display display(&display_context);
    Engine engine(&display_context, wordsAddress);
    display.startDetached();
    engine.start_joined();
    std::cout << "\e[?25h";

    return  0;
}