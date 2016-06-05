#ifndef THREADWINDOW_HPP
#define THREADWINDOW_HPP

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <list>
#include <string.h>
#include "headers.h"
#ifdef __linux__
#include <X11/Xlib.h>
#endif

class ThreadWindow{
    public:
        ThreadWindow(int width, int height, std::string title, Shared *shared);
        virtual ~ThreadWindow();
        void wait();
        void setShared(Shared *shared);
        bool isOpen();
        sf::RenderWindow* getWindow();

    protected:
        virtual void main();
        bool open = false;
        int width, height;
        std::string title;
        sf::Thread thread;
        sf::RenderWindow *window;
        sf::Texture player_tex, grass_tex, rock_tex, sky_tex, castle_tex;
        sf::RectangleShape *start_button;
        Shared *shared;
};

#endif
