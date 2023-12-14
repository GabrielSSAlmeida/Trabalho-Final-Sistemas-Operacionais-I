#include <iostream>
#include "../includes/globals.h"
#include "../includes/palavra.h"
#include "../includes/file.h"


// Função que recebe uma palavra e inicia a dinâmica
// até que o jogador acerte ou zere suas tentativas
void ArmazenaPalavra(std::string obj){

    // Cria um map com as letras e respectiva pos na palavra
    // tabelaLetras letras;
    letrasMutex.lock();
    letras.clear();
    for(int i=0; i<static_cast<int>(obj.length()); i++){
        letras[obj[i]].push_back(i);
    }
    letrasMutex.unlock();

}


// Função que imprime a palavra inserida pelo jogador
// Cada caracter é impresso de acordo com sua existência em obj
std::string verificaPalavra(std::string palavra, std::string &palavraCorreta){

    std::string retorno = "";

    if(palavra == palavraCorreta){
        palavrasAcertadas.push_back(palavraCorreta);

        retorno = "Palavras encontradas: ";
        retorno += GREEN;
        for(auto c: palavrasAcertadas){
            retorno += c + " ";
        }
        //retorno += palavra;
        retorno += RESET;
        retorno += "\n";

        mutexAcertos.lock();
        acertos++;
        mutexAcertos.unlock();
        
        mutexContador.lock();
        contador += 10 * numTentativasRestantes;
        if(contador > contadorInicial)
            contador = contadorInicial;
        mutexContador.unlock();

        numTentativasRestantes = 7;

        mutexBuffer.lock();
        buffer = "";
        mutexBuffer.unlock();
        
        readRandomWord("palavrasKermo.txt", std::ref(palavraCorreta));

    }
    else{
        for(int i=0; i<static_cast<int>(palavra.length()); i++){
            char c = palavra[i];
            // O caracter não existe no objetivo
            letrasMutex.lock();
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

            letrasMutex.unlock();
        }
    }

    retorno += "\n";

    

    return retorno;
}