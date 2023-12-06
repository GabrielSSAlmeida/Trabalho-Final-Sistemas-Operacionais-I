#include "../../include/controllers/controllers.hpp"
#include <iostream>

FinalController::FinalController(GameData *data) : Controller(data) {}

FinalController::~FinalController() {}

bool FinalController::IsLastController() { return true; }

DisplayContent FinalController::GetDisplayContent() {
    std::string content;
    
    content = "Pontuação:" + std::to_string(data->correctGuesses) + "\n\n";
    
    content += "Pressione enter para sair...";

    return DisplayContent(content, &data->timer, true);
}

void FinalController::HandleInput() {
    if (std::cin.peek() == '\n')
        std::cin.ignore();
    std::cin.get();
}

Controller *FinalController::Next() {
    return NULL;
}
