#ifndef CONTROLLERS
#define CONTROLLERS

#include "../display/display_content.h"
#include "game_content.hpp"
#include <thread>

class Controller {
    public:
        Controller(GameContext *context, int rightGuesses);

        virtual ~Controller();

        virtual bool isLastController();

        virtual DisplayContext getDisplayContext();
        
        virtual void handleInput();

        virtual Controller *next();

    protected:
        GameContext *content;
        int rightGuesses;
        bool jump_to_last_page;
};

class StartController : public Controller {
    public:
        IntroductionController(GameContext *context, std::string username,
                int rightGuesses);

        ~IntroductionController();

        bool isLastController();

        DisplayContext getDisplayContext();
        
        void handleInput();

        Controller *next();
};

class GuessController : public Controller {
    public:
        GuessController(GameContext *context, int rightGuesses);

        ~GuessController();

        bool isLastController();

        DisplayContext getDisplayContext();
        
        void handleInput();

        Controller *next();
};

class FinalController : public Controller {
    public:
        FinalController(GameContext *content, int rightGuesses);

        ~FinalController();

        bool isLastController();

        DisplayContext getDisplayContext();
        
        void handleInput();

        Controller *next();
};

#endif
