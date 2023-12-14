#include "../includes/globals.h"

std::mutex tela;

std::mutex mutexContador;
int contadorInicial = 180;
int contador = contadorInicial;
bool gameOver = false;
int numTentativasRestantes = 6;
int acertos = 0;
bool leituraPronta = false;
std::vector<std::string> palavrasAcertadas = {};

std::mutex mutexBuffer;
std::string buffer("");
std::mutex mutexTentativas;
std::mutex mutexAcertos;
std::mutex gameOverMutex;
std::mutex mutexArquivo;
std::mutex letrasMutex;
std::mutex proxRodadaMutex;

tabelaLetras letras;

void console_pegaTela(){
    tela.lock();
}

void console_largaTela(){
    tela.unlock();
}