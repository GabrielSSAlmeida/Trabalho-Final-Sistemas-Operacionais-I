#include "../includes/globals.h"
#include <iostream>

void ImprimeGameOver(std::string palavra){
    std::cout << "Fim de jogo! A palavra era " << RED << palavra << RESET << "\n\n";
    std::cout << "Você encontrou " << GREEN << acertos << RESET << 
    ((acertos == 1) ? " palavra!" : " palavras!") << "\n\n";
    std::cout << "Pressione " << BLUE << "ENTER" << RESET << " para sair.\n";
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