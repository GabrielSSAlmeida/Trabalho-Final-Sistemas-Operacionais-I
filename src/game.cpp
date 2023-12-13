#include "../include/game.hpp"

Game::Game(Timer *timer, Display *display){
    this->timer = timer;
    this->display = display;
}

void Game::StartGame(){
    while(true){

        std::string palavra = "kermo";

        // Cria um map com as letras e respectiva pos na palavra
        for(int i=0; i<static_cast<int>(palavra.length()); i++){
            letras[palavra[i]].push_back(i);
        }


        std::thread timerThread(&Timer::Start,&timer);        
        std::thread displayThread(&Display::RunDisplay, &display);
        displayThread.detach();
        timerThread.join();
    }
}

// Função que imprime a palavra inserida pelo jogador
// Cada caracter é impresso de acordo com sua existência em obj
void Game::verificaPalavra(std::string palavra){
    for(int i=0; i<static_cast<int>(palavra.length()); i++){
        char c = palavra[i];
        // O caracter não existe no objetivo
        if(this->letras[c].empty()){
            std::cout << c; // Imprime na cor padrão
        } else {
            bool posicaoCorreta = false;
            // O caracter existe no objetivo
            for(int pos : letras[c]){
                if(pos == i){
                    posicaoCorreta = true;
                }
            }
            if (posicaoCorreta) {
                // Imprimir o caracter em verde
                std::cout << GREEN << c << RESET;
            } else {
                // Imprimir o caracter em amarelo
                std::cout << YELLOW << c << RESET;
            }
        }
    }
    std::cout << std::endl;
}