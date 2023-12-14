#include "../includes/globals.h"
#include "../includes/printer.h"
#include "../includes/file.h"
#include "../includes/palavra.h"
#include <iostream>

void timer();
void entradaUser(std::string &palavraCorreta);
void imprimeTerminal(std::string &palavraCorreta);


int main(){
    std::string palavra;
    
    readRandomWord("palavrasKermo.txt", std::ref(palavra));

    std::thread p_teclado(entradaUser, std::ref(palavra));
    std::thread p_timer(timer);
    std::thread p_terminal(imprimeTerminal, std::ref(palavra));
    

    p_teclado.join();
    p_terminal.join();
    p_timer.join();

    return 0;
}

void timer(){
    while(!gameOver)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        mutexContador.lock();
        --contador;
        if(contador == 0){
            gameOverMutex.lock();
            gameOver = true;
            gameOverMutex.unlock();
        }
        mutexContador.unlock();
    }

}

void imprimeTerminal(std::string &palavraCorreta){
    while(!gameOver)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        console_pegaTela();
        system("clear");
        PrintLogo();
        PrintTimer();

        proxRodadaMutex.lock();

        mutexAcertos.lock();
        std::cout << "Pontuação: " << acertos << "\n";
        mutexAcertos.unlock();

        mutexTentativas.lock();
        std::cout << "Tentativas restantes: ";
        if(numTentativasRestantes > 4){
            std::cout << GREEN;
        }else if(numTentativasRestantes > 2){
            std::cout << YELLOW;
        }else{
            std::cout << RED;
        }
        std::cout << numTentativasRestantes << "\n\n" << RESET;

        mutexTentativas.unlock();

        mutexBuffer.lock();
        std::cout << buffer << "\n";
        mutexBuffer.unlock();

        proxRodadaMutex.unlock();

        console_largaTela();

        mutexTentativas.lock();

        if(numTentativasRestantes == 0){
            gameOverMutex.lock();
            gameOver = true;
            gameOverMutex.unlock();
        }

        mutexTentativas.unlock();
    }

    ImprimeGameOver(palavraCorreta);
    
}

void entradaUser(std::string &palavraCorreta){
    char aux[20];

    while(!gameOver){
        fgets(aux, 20, stdin);

        std::string enter(aux);
        enter.pop_back();
        
        if(enter.length() == 5){
            proxRodadaMutex.lock();

            std::string formatada = verificaPalavra(enter, palavraCorreta);

            mutexTentativas.lock();
            numTentativasRestantes--;
            mutexTentativas.unlock();

            mutexBuffer.lock();
            buffer += formatada;
            mutexBuffer.unlock();

            proxRodadaMutex.unlock();
        }

    }
    
}