#ifndef DISPLAY_CONTENT
    #define DISPLAY_CONTENT

    #include <iostream>
    #include "timer.hpp"

    class DisplayContent{
        public:
            std::string content;
            Timer *timer;
            bool stop;

            DisplayContent();

            DisplayContent(std::string content, Timer *timer, bool stop);
    };

#endif
