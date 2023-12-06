#include "../../include/controllers/controllers.h"
#include "../../include/utils.h"
#include <iostream>

static const std::vector<int> PRIZES({0, 50000, 75000, 250000, 1000000});

GuessController::GuessController(GameContext *context) : Controller(context) { }

GuessController::~GuessController() {}

bool GuessController::isLastController() { return false; }

DisplayContext GuessController::getDisplayContext() {
    int prize = PRIZES[context->correct_answers / 5];
    std::string Guess = "Prêmio: $" + std::to_string(prize) + "\n\n"
        + context->Guess_manager.get_next_Guess() + "\n";
    context->timer.start();
    return DisplayContext(Guess, &context->timer, false);
}

void GuessController::handleInput() {
    char input = std::cin.get();

    if (std::cin.peek() == '\n')
        std::cin.ignore();
    jump_to_last_page = !context->timer.isRunning(); 

    if (!jump_to_last_page){
        bool is_correct = context->Guess_manager.answer_is_correct(input);
        bool is_ignore = context->Guess_manager.answer_is_ignore(input);



        context->correct_answers += is_correct ? 1 : 0;
        context->timer.reset();
        jump_to_last_page = !is_correct && !is_ignore;
    }
}

Controller *GuessController::next() {
    if (rightGuesses >= 20 || jump_to_last_page)
        return new FinalController(context, rightGuesses + 1);
    return new GuessController(context, rightGuesses + 1);
}
