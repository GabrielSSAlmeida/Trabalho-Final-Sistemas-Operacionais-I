#include <iostream>
#include <cstdio>

#include "../include/menu.hpp" 
#include "../include/palavra.hpp"

int main(){

    PrintMenu();

    // Iniciar timer
    // Enquanto tiver tempo...
    // Receber palavra aleatória do arquivo
    std::string palavra = "kermo";
    // Jogo inicia para essa palavra
    IniciarJogo(palavra);

    return  0;
}