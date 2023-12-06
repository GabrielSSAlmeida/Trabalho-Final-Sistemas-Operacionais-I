#ifndef DISPLAY
#define DISPLAY

#include "display_content.hpp" 
#include "pages_manager.hpp" 
#include "../shared_buffer.hpp"
#include <thread>
#include <atomic>

class Display{
    public:
        Display(SharedBuffer<DisplayContent> *buffer);

        ~Display();

        void startDetached();
        
        void startJoined();

    private:
        SharedBuffer<DisplayContext> *buffer;
        std::thread displayThread;
};

#endif
