#include "../include/menu.hpp"

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

void PrintRegras(){
    std::cout << "Regras do Jogo:" << std::endl;
    std::cout << "1. Você deve adivinhar uma palavra de 5 letras" << std::endl;
    std::cout << "2. O timer mostra o tempo restante para adivinhar a palavra" << std::endl;
    std::cout << "3. A cada acerto, é fornecido um bônus de tempo" << std::endl;
    std::cout << "4. Quantas palavras você consegue adivinhar?\n" << std::endl;
}

void PrintMenu(){
    PrintLogo();
    PrintRegras();
}