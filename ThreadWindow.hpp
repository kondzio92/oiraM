#ifndef THREADWINDOW_HPP
#define THREADWINDOW_HPP

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include <string.h>
#include "headers.h"
#ifdef __linux__
#include <X11/Xlib.h>
#endif

class ThreadWindow{
	public:
		ThreadWindow(int w, int h, std::string title, Shared *shared);
		virtual ~ThreadWindow();
		void wait();
		void setShared(Shared *shared);
        bool isOpen();
        sf::RenderWindow* getWindow();

    protected:
    	virtual void main();
        sf::Thread thread;
        sf::RenderWindow *window;
        int width, height;
        std::string title;
        Shared *shared;
        sf::Texture player_tex, grass_tex, rock_tex, sky_tex, castle_tex;
        sf::RectangleShape *start_button;
        bool open= false;
	private:

};

#endif