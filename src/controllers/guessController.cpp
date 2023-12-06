#include "../../include/controllers/controllers.hpp"
//#include "../../include/utils.hpp"
#include <iostream>

GuessController::GuessController(GameData *data) : Controller(data){ }

GuessController::~GuessController(){}

bool GuessController::IsLastController(){ return false; }

DisplayContent GuessController::GetDisplayContent() {
    std::string Guess = "Pontuação: " + std::to_string(data->correctGuesses) + "\n\n"
        + data->wordManager.GetNextWord() + "\n";
    
    return DisplayContent(Guess, &data->timer, false);
}

void GuessController::HandleInput() {
    std::string input;

    std::getline(std::cin, input);

    if (std::cin.peek() == '\n')
        std::cin.ignore();

    jump_to_last_page = !data->timer.IsRunning(); 

    if(!jump_to_last_page){
        bool isCorrect = data->wordManager.IsCorrect(input);

        if(isCorrect){
            data->correctGuesses += isCorrect ? 1 : 0;
            data->timer.AddBonus(1);
        }
        jump_to_last_page = !isCorrect;
    }
}

Controller *GuessController::Next() {
    if(jump_to_last_page)
        return new FinalController(data);
    return new GuessController(data);
}
