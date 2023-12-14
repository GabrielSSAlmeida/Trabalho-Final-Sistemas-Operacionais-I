#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <mutex>
#include <map>
#include <vector>
#include <string>


// ANSI escape codes for text color
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"

std::mutex tela;


void console_pegaTela(){
    tela.lock();
}

void console_largaTela(){
    tela.unlock();
}


std::mutex mutexContador;
int contadorInicial = 50;
int contador = contadorInicial;
bool gameOver = false;
int numTentativasRestantes = 6;
int acertos = 0;

std::mutex mutexBuffer;
std::string buffer("");
std::mutex mutexTentativas;
std::mutex mutexAcertos;
std::mutex gameOverMutex;

void PrintLogo(){
    std::string kermo = 
        "\n\n"
        "#    # ####### ######  #     # #######\n"
        "#   #  #       #     # ##   ## #     #\n"
        "#  #   #       #     # # # # # #     #\n"
        "###    #####   ######  #  #  # #     #\n"
        "#  #   #       #   #   #     # #     #\n"
        "#   #  #       #    #  #     # #     #\n"
        "#    # ####### #     # #     # #######\n"
        "\n\n";
    
    std::cout << kermo << std::endl;
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

void PrintTimer(){
    const int barWidth = 100;

    // Calculating time in minutes
    int minutes = 0;
    mutexContador.lock();
    int aux = contador;
    mutexContador.unlock();

    int seconds = aux;
    while(seconds >= 60){        
        minutes++;
        seconds -= 60;
    }

    float percentage = static_cast<float>(aux) / contadorInicial;
    int progressBarWidth = static_cast<int>(barWidth * percentage);

    std::string str = "Tempo: ";
    if(percentage > static_cast<float>(2)/3) str.append(GREEN);
    else if(percentage > static_cast<float>(1)/3) str.append(YELLOW);
    else str.append(RED);
    str.append("[");
    str.append(std::string(progressBarWidth, '#'));
    str.append(std::string(barWidth - progressBarWidth, ' '));
    str.append("] ");
    str.append((minutes < 10 ? "0" : "") + std::to_string(minutes));
    str.append(":");
    str.append((seconds < 10 ? "0" : "") + std::to_string(seconds));
    std::cout << str << RESET << "\n\n";
}

void ImprimeGameOver(){
    std::cout << "Fim de jogo! Sua pontuação foi " << RED << acertos << RESET << "\n\n";
    std::cout << "Pressione " << BLUE << "ENTER" << RESET << " para sair.\n";
}


void imprimeTerminal(){
    while(!gameOver)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        console_pegaTela();
        system("clear");
        PrintLogo();
        PrintTimer();

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

        if(numTentativasRestantes == 0){
            gameOverMutex.lock();
            gameOver = true;
            gameOverMutex.unlock();
        }

        mutexTentativas.unlock();

        mutexBuffer.lock();
        std::cout << buffer << "\n";
        mutexBuffer.unlock();

        console_largaTela();
    }

    ImprimeGameOver();
    
}




std::string verificaPalavra(std::string palavra);

void entradaUser(){
    char aux[2000];

    gameOverMutex.lock();
    while(!gameOver){
        gameOverMutex.unlock();

        fgets(aux, 2000, stdin);

        std::string enter(aux);
        enter.pop_back();
        
        if(enter.length() == 5){

            std::string formatada = verificaPalavra(enter);

            mutexTentativas.lock();
            numTentativasRestantes--;
            mutexTentativas.unlock();

            mutexBuffer.lock();
            buffer += formatada;
            mutexBuffer.unlock();
        }

        gameOverMutex.lock();
    }
    gameOverMutex.unlock();
    
}




typedef std::map<char, std::vector<int>> tabelaLetras;


tabelaLetras letras;

// Função que imprime a palavra inserida pelo jogador
// Cada caracter é impresso de acordo com sua existência em obj
std::string verificaPalavra(std::string palavra){

    std::string retorno = "";

    for(int i=0; i<static_cast<int>(palavra.length()); i++){
        char c = palavra[i];
        // O caracter não existe no objetivo
        if(letras[c].empty()){
            retorno += c; // Imprime na cor padrão
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
                retorno += GREEN;
                retorno += c;
                retorno += RESET;
            } else {
                // Imprimir o caracter em amarelo
                retorno += YELLOW;
                retorno += c; 
                retorno += RESET;
            }
        }
    }
    retorno += "\n";

    return retorno;
}


// Função que recebe uma palavra e inicia a dinâmica
// até que o jogador acerte ou zere suas tentativas
void IniciarJogo(std::string obj){

    // Cria um map com as letras e respectiva pos na palavra
    // tabelaLetras letras;
    for(int i=0; i<static_cast<int>(obj.length()); i++){
        letras[obj[i]].push_back(i);
    }

}

int main() {
    IniciarJogo("kermo");

    std::thread p_timer(timer);
    std::thread p_terminal(imprimeTerminal);
    std::thread p_teclado(entradaUser);

    p_teclado.join();
    p_terminal.join();
    p_timer.join();

    return 0;
}