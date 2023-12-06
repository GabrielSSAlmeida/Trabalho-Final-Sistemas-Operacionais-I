#ifndef CONTROLLERS
#define CONTROLLERS

#include "../display_content.hpp"
#include "gameController.hpp"
#include <thread>

class Controller {
    public:
        Controller(GameData *content);

        virtual ~Controller();

        virtual bool IsLastController();

        virtual DisplayContent GetDisplayContext();
        
        virtual void HandleInput();

        virtual Controller *Next();

    protected:
        GameData *data;
        bool jump_to_last_page;
};

class StartController : public Controller {
    public:
        StartController(GameData *data);

        ~StartController();

        bool IsLastController();

        DisplayContent GetDisplayContent();
        
        void HandleInput();

        Controller *Next();
};

class GuessController : public Controller {
    public:
        GuessController(GameData *data);

        ~GuessController();

        bool IsLastController();

        DisplayContent GetDisplayContent();
        
        void HandleInput();

        Controller *Next();
};

class FinalController : public Controller {
    public:
        FinalController(GameData *data);

        ~FinalController();

        bool IsLastController();

        DisplayContent GetDisplayContent();
        
        void HandleInput();

        Controller *Next();
};

#endif
