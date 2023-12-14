#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <mutex>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <condition_variable>


#define CHAR_BYTES 1
#define WORD_SIZE 6
#define HEAD_SIZE 5


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
int contadorInicial = 500;
int contador = contadorInicial;
bool gameOver = false;
int numTentativasRestantes = 6;
int acertos = 0;
bool leituraPronta = false;

std::mutex mutexBuffer;
std::string buffer("");
std::mutex mutexTentativas;
std::mutex mutexAcertos;
std::mutex gameOverMutex;
std::mutex mutexArquivo;
std::condition_variable semaforoArquivo;

typedef std::map<char, std::vector<int>> tabelaLetras;

tabelaLetras letras;

// Função que recebe uma palavra e inicia a dinâmica
// até que o jogador acerte ou zere suas tentativas
void ArmazenaPalavra(std::string obj){

    // Cria um map com as letras e respectiva pos na palavra
    // tabelaLetras letras;
    letras.clear();
    for(int i=0; i<static_cast<int>(obj.length()); i++){
        letras[obj[i]].push_back(i);
    }

}


// Função para ler uma palavra aleatória do arquivo
void readRandomWord(const std::string& filename, std::string& randomWord){
    std::ifstream file(filename);
    int numWords = 0;
    if(file.is_open()){
        // Obtém o tamanho total do arquivo
        file >> numWords;

        // Garante que há pelo menos um caractere no arquivo
        while(numWords > 0 && !gameOver){
            srand(static_cast<unsigned>(time(nullptr)));
            int random = rand() % numWords;

            int byteoffsetWOrd = (random * WORD_SIZE * CHAR_BYTES)+HEAD_SIZE;
   
            // Move o ponteiro do arquivo para a posição aleatória
            file.seekg(byteoffsetWOrd, std::ios::beg);

            // Lê a palavra aleatória

            file >> randomWord;
            ArmazenaPalavra(randomWord);


            std::unique_lock<std::mutex> lock(mutexArquivo);
            semaforoArquivo.wait(lock, []{ return leituraPronta; });

        }
        file.close();
    } else {
        std::cerr << "Erro ao abrir o arquivo: " << filename << std::endl;
    }
}

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
    std::cout << "Fim de jogo! Sua pontuação foi " << GREEN << acertos << RESET << "\n\n";
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

        mutexTentativas.unlock();

        mutexBuffer.lock();
        std::cout << buffer << "\n";
        mutexBuffer.unlock();

        console_largaTela();

        mutexTentativas.lock();

        if(numTentativasRestantes == 0){
            gameOverMutex.lock();
            gameOver = true;
            gameOverMutex.unlock();
        }

        mutexTentativas.unlock();
    }

    ImprimeGameOver();
    
}



std::string verificaPalavra(std::string palavra);


void entradaUser(){
<<<<<<< HEAD
    std::string enter;
=======
    char aux[20];
>>>>>>> StartingOver!

    while(!gameOver){
        fgets(aux, 20, stdin);

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

    }
    
}


// Função que imprime a palavra inserida pelo jogador
// Cada caracter é impresso de acordo com sua existência em obj
std::string verificaPalavra(std::string palavra){

    std::string retorno = "";
    bool correctWord = true;

    for(int i=0; i<static_cast<int>(palavra.length()); i++){
        char c = palavra[i];
        // O caracter não existe no objetivo
        if(letras[c].empty()){
            retorno += c; // Imprime na cor padrão
            correctWord = false;
        } else {
            bool posicaoCorreta = false;
    
            // O caracter existe no objetivo
            for(int pos : letras[c]){
                if(pos == i){
                    posicaoCorreta = true;
                }else{
                    correctWord = false;
                }
            }
            if(posicaoCorreta) {
                // Imprimir o caracter em verde
                retorno += GREEN;
                retorno += c;
                retorno += RESET;
            }else{
                // Imprimir o caracter em amarelo
                retorno += YELLOW;
                retorno += c; 
                retorno += RESET;
            }
        }
    }

    retorno += "\n";

    
    if(correctWord){
        mutexAcertos.lock();
        acertos++;
        mutexAcertos.unlock();

        numTentativasRestantes = 6;
        
        mutexContador.lock();
        contador = (contador + 20);
        if(contador > contadorInicial)
            contador = contadorInicial;
        mutexContador.unlock();

        mutexBuffer.lock();
        buffer = "";
        mutexBuffer.unlock();
        

        {
            std::lock_guard<std::mutex> lock(mutexArquivo);
            leituraPronta = true;
        }
        semaforoArquivo.notify_all();
    }

    return retorno;
}





int main(){
    std::string palavra;
    std::thread p_arquivo(readRandomWord, "palavrasKermo.txt", std::ref(palavra));
    std::thread p_teclado(entradaUser);
    std::thread p_timer(timer);
    std::thread p_terminal(imprimeTerminal);
    

    p_teclado.join();
    p_terminal.join();
    p_timer.join();
    p_arquivo.join();

    return 0;
}