#include "../../include/controllers/controllers.h"
#include <iostream>

static const std::vector<int> PRIZES({0, 50000, 75000, 250000, 1000000});

FinalController::FinalController(GameContext *context) : Controller(context) {}

FinalController::~FinalController() {}

bool FinalController::isLastController() { return true; }

DisplayContext FinalController::getDisplayContext() {
    std::string content;
    int prize = PRIZES[context->correct_answers / 5];
    if (prize == 1000000)
        content = "Parabéns!!! Você ganhou o jogo e agora é milionário!";
    else 
        content = "Fim de jogo. Você ganhou $" + std::to_string(prize) + "\n\n";
    content += "Pressione enter para sair...";
    return DisplayContext(content, &context->timer, true);
}

void FinalController::handleInput() {
    if (std::cin.peek() == '\n')
        std::cin.ignore();
    std::cin.get();
}

Controller *FinalController::next() {
    return NULL;
}
