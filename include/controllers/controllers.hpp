#ifndef CONTROLLERS
#define CONTROLLERS

#include "../display_content.hpp"
#include "gameController.hpp"
#include <thread>

class Controller {
    public:
        Controller(GameData *content);

        virtual ~Controller();

        virtual bool isLastController();

        virtual DisplayContent getDisplayContext();
        
        virtual void handleInput();

        virtual Controller *next();

    protected:
        GameData *content;
        int rightGuesses;
        bool jump_to_last_page;
};

class StartController : public Controller {
    public:
        StartController(GameData *content, int rightGuesses);

        ~StartController();

        bool isLastController();

        DisplayContent getDisplayContext();
        
        void handleInput();

        Controller *next();
};

class GuessController : public Controller {
    public:
        GuessController(GameData *context, int rightGuesses);

        ~GuessController();

        bool isLastController();

        DisplayContent getDisplayContext();
        
        void handleInput();

        Controller *next();
};

class FinalController : public Controller {
    public:
        FinalController(GameData *content, int rightGuesses);

        ~FinalController();

        bool isLastController();

        DisplayContent getDisplayContext();
        
        void handleInput();

        Controller *next();
};

#endif
