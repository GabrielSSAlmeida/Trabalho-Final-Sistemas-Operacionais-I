#include "../include/palavra.hpp"

// Função que imprime a palavra inserida pelo jogador
// Cada caracter é impresso de acordo com sua existência em obj
void verificaPalavra(std::string palavra, tabela letras){
    for(int i=0; i<static_cast<int>(palavra.length()); i++){
        char c = palavra[i];
        // O caracter não existe no objetivo
        if(letras[c].empty()){
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

// Função que recebe uma palavra e inicia a dinâmica
// até que o jogador acerte ou zere suas tentativas
void IniciarJogo(std::string obj){

    // Cria um map com as letras e respectiva pos na palavra
    tabela letras;
    for(int i=0; i<static_cast<int>(obj.length()); i++){
        letras[obj[i]].push_back(i);
    }

    // O jogador tem 5 tentativas
    int numTentativas = 5;
    std::string palavra;

    while(numTentativas > 0){
        std::cin >> palavra;
        if(palavra != obj){
            numTentativas--;
            // Imprime a palavra com caracteres verdes / amarelos
            verificaPalavra(palavra, letras);
        } else {
            // Imprimir palavra toda verde
            // std::cout << "Palavra correta!" << std::endl;
            std::cout << GREEN << palavra << "\n";
            break;
        }
    }

}