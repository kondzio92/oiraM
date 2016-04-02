#ifndef THREADWINDOW_HPP
#define THREADWINDOW_HPP

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include <string.h>
#include "defines.h"
#ifdef __linux__
#include <X11/Xlib.h>
#endif

class ThreadWindow{
	public:
		ThreadWindow(int w, int h, std::string title);
		virtual ~ThreadWindow();
		void wait();
		void setShared(Shared *shared);
        bool isOpen();

    protected:
    	virtual void main();
        sf::Thread thread;
        sf::RenderWindow *window;
        int width, height;
        std::string title;
        Shared *shared;
	private:

};

#endif