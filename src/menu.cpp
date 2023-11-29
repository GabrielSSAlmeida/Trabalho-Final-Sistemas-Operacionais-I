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

void PrintLogo(){
    std::string kermo = "Regras do Jogo:";

    std::cout << kermo << std::endl;

}


void PrintMenu(){
    
    PrintLogo();
    PrintRegras();
}

