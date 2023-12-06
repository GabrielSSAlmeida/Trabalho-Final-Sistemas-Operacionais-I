#include "../../include/controllers/controllers.hpp"
#include <iostream>

StartController::StartController(GameContent *content) 
    : Controller(content) {}

StartController::~StartController() {}

bool StartController::isLastController() { return false; }

DisplayContent StartController::getDisplayContent() {
    std::string content = 
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

    return DisplayContent(content, &content->timer, false);
}

void StartController::handleInput() {
    if(std::cin.peek() == '\n')
        std::cin.ignore();
    std::cin.get();
}

Controller *StartController::next() {
    if (jump_to_last_page)
        return new FinalController(content);
    return new GuessController(content);
}

