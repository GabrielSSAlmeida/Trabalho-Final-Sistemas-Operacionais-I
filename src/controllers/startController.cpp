#include "../../include/controllers/controllers.hpp"
#include <iostream>

StartController::StartController(GameData *data) 
    : Controller(data) {}

StartController::~StartController() {}

bool StartController::IsLastController() { return false; }

DisplayContent StartController::GetDisplayContent() {
    std::string aux = 
    "\n\n"
    "#    # ####### ######  #     # #######\n"
    "#   #  #       #     # ##   ## #     #\n"
    "#  #   #       #     # # # # # #     #\n"
    "###    #####   ######  #  #  # #     #\n"
    "#  #   #       #   #   #     # #     #\n"
    "#   #  #       #    #  #     # #     #\n"
    "#    # ####### #     # #     # #######\n"
    "\n\n"
    
    "Regras do jogo:\n"
    "1. Você deve adivinhar uma palavra de 5 letras\n"
    "2. O timer mostra o tempo restante para adivinhar a palavra\n"
    "3. A cada acerto, é fornecido um bônus de tempo\n"
    "4. Quantas palavras você consegue adivinhar?\n"
    "Pressione enter para começar!\n"
    ;

    return DisplayContent(aux, &data->timer, false);
}

void StartController::HandleInput() {
    if(std::cin.peek() == '\n')
        std::cin.ignore();
    std::cin.get();
}

Controller *StartController::Next() {
    if (jump_to_last_page)
        return new FinalController(data);
    return new GuessController(data);
}

