#ifndef PAGES
#define PAGES

#include "display_content.hpp"
#include "shared_buffer.hpp"

class PagesManager {
    public:
        PagesManager(SharedBuffer<DisplayContent> *buffer);

        ~PagesManager();

        bool is_at_last_page();

        void display_page();

        void next_page();

    protected:
        SharedBuffer<DisplayContent> *buffer;
        DisplayContent context;
};

#endif
